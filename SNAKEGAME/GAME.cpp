#include <SDL.h>

#include <algorithm>
#include <array>
#include <cstdlib>
#include <ctime>
#include <deque>
#include <fstream>
#include <iostream>
#include <map>
#include <random>
#include <string>

namespace {
const int kBoardWidth = 20;
const int kBoardHeight = 20;
const int kCellSize = 24;
const int kBoardX = 28;
const int kBoardY = 76;
const int kWindowWidth = 790;
const int kWindowHeight = 610;
const char* kStatsFile = "snake_stats.txt";

struct Stats {
    unsigned long long games = 0;
    int bestScore = 0;
    unsigned long long wins = 0;
};

enum class GameState { Ready, Playing, Paused, GameOver, Won };

const std::map<char, std::array<unsigned char, 7> >& font() {
    static const std::map<char, std::array<unsigned char, 7> > glyphs = {
        {'A', {{14, 17, 17, 31, 17, 17, 17}}}, {'B', {{30, 17, 17, 30, 17, 17, 30}}},
        {'C', {{14, 17, 16, 16, 16, 17, 14}}}, {'D', {{30, 17, 17, 17, 17, 17, 30}}},
        {'E', {{31, 16, 16, 30, 16, 16, 31}}}, {'F', {{31, 16, 16, 30, 16, 16, 16}}},
        {'G', {{14, 17, 16, 23, 17, 17, 15}}}, {'H', {{17, 17, 17, 31, 17, 17, 17}}},
        {'I', {{14, 4, 4, 4, 4, 4, 14}}},  {'J', {{7, 2, 2, 2, 18, 18, 12}}},
        {'K', {{17, 18, 20, 24, 20, 18, 17}}}, {'L', {{16, 16, 16, 16, 16, 16, 31}}},
        {'M', {{17, 27, 21, 21, 17, 17, 17}}}, {'N', {{17, 25, 21, 19, 17, 17, 17}}},
        {'O', {{14, 17, 17, 17, 17, 17, 14}}}, {'P', {{30, 17, 17, 30, 16, 16, 16}}},
        {'Q', {{14, 17, 17, 17, 21, 18, 13}}}, {'R', {{30, 17, 17, 30, 20, 18, 17}}},
        {'S', {{15, 16, 16, 14, 1, 1, 30}}}, {'T', {{31, 4, 4, 4, 4, 4, 4}}},
        {'U', {{17, 17, 17, 17, 17, 17, 14}}}, {'V', {{17, 17, 17, 17, 17, 10, 4}}},
        {'W', {{17, 17, 17, 21, 21, 21, 10}}}, {'X', {{17, 17, 10, 4, 10, 17, 17}}},
        {'Y', {{17, 17, 10, 4, 4, 4, 4}}}, {'Z', {{31, 1, 2, 4, 8, 16, 31}}},
        {'0', {{14, 17, 19, 21, 25, 17, 14}}}, {'1', {{4, 12, 4, 4, 4, 4, 14}}},
        {'2', {{14, 17, 1, 2, 4, 8, 31}}}, {'3', {{30, 1, 1, 14, 1, 1, 30}}},
        {'4', {{2, 6, 10, 18, 31, 2, 2}}}, {'5', {{31, 16, 16, 30, 1, 1, 30}}},
        {'6', {{14, 16, 16, 30, 17, 17, 14}}}, {'7', {{31, 1, 2, 4, 8, 8, 8}}},
        {'8', {{14, 17, 17, 14, 17, 17, 14}}}, {'9', {{14, 17, 17, 15, 1, 1, 14}}},
        {':', {{0, 4, 4, 0, 4, 4, 0}}}, {'-', {{0, 0, 0, 31, 0, 0, 0}}},
        {' ', {{0, 0, 0, 0, 0, 0, 0}}}
    };
    return glyphs;
}

void setColor(SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b) {
    SDL_SetRenderDrawColor(renderer, r, g, b, 255);
}

void drawText(SDL_Renderer* renderer, const std::string& text, int x, int y,
              int scale, SDL_Color color) {
    setColor(renderer, color.r, color.g, color.b);
    for (char c : text) {
        const char key = (c >= 'a' && c <= 'z') ? static_cast<char>(c - 'a' + 'A') : c;
        const std::map<char, std::array<unsigned char, 7> >::const_iterator glyph = font().find(key);
        if (glyph != font().end()) {
            for (int row = 0; row < 7; ++row) {
                for (int col = 0; col < 5; ++col) {
                    if (glyph->second[row] & (1 << (4 - col))) {
                        SDL_Rect pixel = {x + col * scale, y + row * scale, scale, scale};
                        SDL_RenderFillRect(renderer, &pixel);
                    }
                }
            }
        }
        x += 6 * scale;
    }
}

bool loadStats(Stats& stats) {
    std::ifstream input(kStatsFile);
    if (!input) {
        std::ifstream probe(kStatsFile);
        return !probe.good();
    }
    Stats loaded;
    if (!(input >> loaded.games >> loaded.bestScore >> loaded.wins) ||
        loaded.bestScore < 0 || loaded.wins > loaded.games) {
        std::cerr << "Cannot read valid game records from " << kStatsFile << ".\n";
        return false;
    }
    stats = loaded;
    return true;
}

bool saveStats(const Stats& stats) {
    std::ofstream output(kStatsFile, std::ios::trunc);
    if (!output || !(output << stats.games << '\n' << stats.bestScore << '\n' << stats.wins << '\n')) {
        std::cerr << "Cannot save game records to " << kStatsFile << ".\n";
        return false;
    }
    return true;
}

class SnakeGame {
public:
    SnakeGame(SDL_Renderer* renderer, Stats& stats)
        : renderer_(renderer), stats_(stats), random_(static_cast<unsigned int>(std::time(NULL))),
          state_(GameState::Ready), score_(0), directionX_(1), directionY_(0),
          nextDirectionX_(1), nextDirectionY_(0), lastMove_(0), saveFailed_(false) {
        resetBoard();
    }

    void handleKey(SDL_Keycode key) {
        if (key == SDLK_ESCAPE) {
            running_ = false;
            return;
        }

        if (state_ == GameState::Ready) {
            if (key == SDLK_RETURN || key == SDLK_SPACE) startGame();
            return;
        }
        if (state_ == GameState::GameOver || state_ == GameState::Won) {
            if (key == SDLK_RETURN || key == SDLK_r) startGame();
            return;
        }
        if (key == SDLK_SPACE) {
            state_ = state_ == GameState::Paused ? GameState::Playing : GameState::Paused;
            lastMove_ = SDL_GetTicks();
            return;
        }
        if (state_ != GameState::Playing) return;

        int dx = 0;
        int dy = 0;
        if (key == SDLK_LEFT || key == SDLK_a) dx = -1;
        else if (key == SDLK_RIGHT || key == SDLK_d) dx = 1;
        else if (key == SDLK_UP || key == SDLK_w) dy = -1;
        else if (key == SDLK_DOWN || key == SDLK_s) dy = 1;
        if ((dx != 0 || dy != 0) && !(dx == -directionX_ && dy == -directionY_)) {
            nextDirectionX_ = dx;
            nextDirectionY_ = dy;
        }
    }

    void update(Uint32 now) {
        if (state_ != GameState::Playing || now - lastMove_ < 105) return;
        lastMove_ = now;
        directionX_ = nextDirectionX_;
        directionY_ = nextDirectionY_;
        SDL_Point head = snake_.front();
        head.x += directionX_;
        head.y += directionY_;
        if (head.x < 0 || head.x >= kBoardWidth ||
            head.y < 0 || head.y >= kBoardHeight) {
            state_ = GameState::GameOver;
            if (!saveStats(stats_)) saveFailed_ = true;
            return;
        }
        const bool eating = head.x == fruit_.x && head.y == fruit_.y;
        const std::size_t bodyLength = snake_.size() - (eating ? 0 : 1);
        for (std::size_t i = 0; i < bodyLength; ++i) {
            if (snake_[i].x == head.x && snake_[i].y == head.y) {
                state_ = GameState::GameOver;
                if (!saveStats(stats_)) saveFailed_ = true;
                return;
            }
        }
        snake_.push_front(head);
        if (eating) {
            score_ += 10;
            stats_.bestScore = std::max(stats_.bestScore, score_);
            if (snake_.size() == static_cast<std::size_t>(kBoardWidth * kBoardHeight)) {
                ++stats_.wins;
                state_ = GameState::Won;
                if (!saveStats(stats_)) saveFailed_ = true;
                return;
            }
            placeFruit();
            if (!saveStats(stats_)) saveFailed_ = true;
        } else {
            snake_.pop_back();
        }
    }

    void draw() {
        setColor(renderer_, 15, 20, 31);
        SDL_RenderClear(renderer_);
        drawText(renderer_, "SNAKE", kBoardX, 24, 3, {115, 230, 160, 255});

        SDL_Rect board = {kBoardX, kBoardY, kBoardWidth * kCellSize, kBoardHeight * kCellSize};
        setColor(renderer_, 23, 32, 46);
        SDL_RenderFillRect(renderer_, &board);
        setColor(renderer_, 38, 51, 67);
        for (int i = 0; i <= kBoardWidth; ++i) {
            SDL_RenderDrawLine(renderer_, kBoardX + i * kCellSize, kBoardY,
                               kBoardX + i * kCellSize, kBoardY + board.h);
            SDL_RenderDrawLine(renderer_, kBoardX, kBoardY + i * kCellSize,
                               kBoardX + board.w, kBoardY + i * kCellSize);
        }
        SDL_Rect fruitRect = {kBoardX + fruit_.x * kCellSize + 4,
                              kBoardY + fruit_.y * kCellSize + 4, kCellSize - 8, kCellSize - 8};
        setColor(renderer_, 255, 103, 105);
        SDL_RenderFillRect(renderer_, &fruitRect);
        for (std::size_t i = 0; i < snake_.size(); ++i) {
            SDL_Rect segment = {kBoardX + snake_[i].x * kCellSize + 2,
                                kBoardY + snake_[i].y * kCellSize + 2, kCellSize - 4, kCellSize - 4};
            if (i == 0) setColor(renderer_, 127, 245, 169);
            else setColor(renderer_, 63, 190, 125);
            SDL_RenderFillRect(renderer_, &segment);
        }

        const int panelX = 540;
        drawText(renderer_, "SCORE", panelX, 91, 2, {154, 174, 195, 255});
        drawText(renderer_, std::to_string(score_), panelX, 115, 3, {245, 248, 252, 255});
        drawText(renderer_, "BEST", panelX, 176, 2, {154, 174, 195, 255});
        drawText(renderer_, std::to_string(stats_.bestScore), panelX, 200, 3, {245, 248, 252, 255});
        drawText(renderer_, "PLAYS", panelX, 261, 2, {154, 174, 195, 255});
        drawText(renderer_, std::to_string(stats_.games), panelX, 285, 3, {245, 248, 252, 255});
        drawText(renderer_, "WINS", panelX, 346, 2, {154, 174, 195, 255});
        drawText(renderer_, std::to_string(stats_.wins), panelX, 370, 3, {245, 248, 252, 255});

        if (state_ == GameState::Ready) drawText(renderer_, "ENTER TO START", panelX, 445, 1, {115, 230, 160, 255});
        if (state_ == GameState::Paused) drawText(renderer_, "PAUSED", panelX, 445, 2, {255, 205, 105, 255});
        if (state_ == GameState::GameOver) drawText(renderer_, "GAME OVER", panelX, 445, 2, {255, 120, 120, 255});
        if (state_ == GameState::Won) drawText(renderer_, "YOU WIN", panelX, 445, 2, {115, 230, 160, 255});
        if (state_ == GameState::GameOver || state_ == GameState::Won)
            drawText(renderer_, "ENTER OR R RESTART", panelX, 473, 1, {186, 199, 215, 255});
        if (saveFailed_) drawText(renderer_, "SAVE ERROR", panelX, 510, 1, {255, 120, 120, 255});

        drawText(renderer_, "MOVE ARROWS WASD", kBoardX, 574, 1, {154, 174, 195, 255});
        drawText(renderer_, "SPACE PAUSE  ESC EXIT", kBoardX + 200, 574, 1, {154, 174, 195, 255});
        SDL_RenderPresent(renderer_);
    }

    bool running() const { return running_; }
    void stop() { running_ = false; }

private:
    void resetBoard() {
        snake_.clear();
        snake_.push_back({kBoardWidth / 2, kBoardHeight / 2});
        snake_.push_back({kBoardWidth / 2 - 1, kBoardHeight / 2});
        snake_.push_back({kBoardWidth / 2 - 2, kBoardHeight / 2});
        score_ = 0;
        directionX_ = nextDirectionX_ = 1;
        directionY_ = nextDirectionY_ = 0;
        placeFruit();
    }

    void placeFruit() {
        std::uniform_int_distribution<int> xDistribution(0, kBoardWidth - 1);
        std::uniform_int_distribution<int> yDistribution(0, kBoardHeight - 1);
        do {
            fruit_.x = xDistribution(random_);
            fruit_.y = yDistribution(random_);
        } while (std::any_of(snake_.begin(), snake_.end(), [this](const SDL_Point& point) {
            return point.x == fruit_.x && point.y == fruit_.y;
        }));
    }

    void startGame() {
        resetBoard();
        ++stats_.games;
        state_ = GameState::Playing;
        lastMove_ = SDL_GetTicks();
        if (!saveStats(stats_)) saveFailed_ = true;
    }

    SDL_Renderer* renderer_;
    Stats& stats_;
    std::mt19937 random_;
    std::deque<SDL_Point> snake_;
    SDL_Point fruit_;
    GameState state_;
    bool running_ = true;
    int score_;
    int directionX_;
    int directionY_;
    int nextDirectionX_;
    int nextDirectionY_;
    Uint32 lastMove_;
    bool saveFailed_;
};
}

int main(int, char**) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL initialization failed: " << SDL_GetError() << '\n';
        return 1;
    }
    Stats stats;
    if (!loadStats(stats)) {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Snake", "Game records are invalid.", NULL);
        SDL_Quit();
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Snake - SDL2", SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED, kWindowWidth, kWindowHeight,
                                          SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "Window creation failed: " << SDL_GetError() << '\n';
        SDL_Quit();
        return 1;
    }
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    if (!renderer) {
        std::cerr << "Renderer creation failed: " << SDL_GetError() << '\n';
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SnakeGame game(renderer, stats);
    while (game.running()) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) game.stop();
            else if (event.type == SDL_KEYDOWN && !event.key.repeat) game.handleKey(event.key.keysym.sym);
        }
        game.update(SDL_GetTicks());
        game.draw();
        SDL_Delay(8);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
