# AI-Collaborative Snake Game

A classic Snake game developed through a Human-AI collaborative effort. The project features a retro pixel-art style, smooth gameplay, and a local scoreboard system, built from scratch using C++ and SDL2.

## Play the Game (For Players)

No setup or dependencies required! 

You don't need to install any compilers, C++ runtimes, or libraries to play. 
1. Go to the Releases page on the right side of this repository.
2. Download the latest GAME.zip file.
3. Extract the .zip file.
4. Double-click SNAKEGAME.exe to start playing!

(Note: The C++ runtime libraries are statically linked, and the SDL2.dll is included in the package, ensuring a pure out-of-the-box experience.)

### Controls
* Arrow Keys or W / A / S / D: Move the snake.
* Enter / Space: Start the game from the main menu.
* Space: Pause / Resume during gameplay.
* R / Enter: Restart after a Game Over.
* Esc: Exit the game.


## Build from Source (For Developers)

This project is developed using C++14 and SDL2. The source code is contained within a single GAME.cpp file for easy reading and modification.

### Prerequisites
* OS: Windows (tested)
* IDE: CLion (Recommended)
* Build System: CMake (Version 4.2 or higher)
* Compiler: MinGW (Bundled with CLion)
* Library: SDL2 (The required headers, libraries, and DLLs are already included in the SDL2/ directory of this repository).

### Compilation Steps
1. Get the source code:
   * Option A (Using GitHub Desktop): Click the "Code" button on the repository page, select "Open with GitHub Desktop", and clone it to your local machine.
   * Option B (Manual Download): Click the "Code" button and select "Download ZIP", then extract the files.
2. Open the project folder in CLion. (CLion will automatically detect the CMakeLists.txt).
3. Wait for the CMake project to load.
4. In the top-right corner, select the Release build configuration.
5. Click the Build (hammer) icon.
6. Once the build is successful, the executable SNAKEGAME.exe and the required SDL2.dll will be automatically generated and copied to the cmake-build-release directory.

Note on Static Linking: The CMakeLists.txt is configured to statically link the C++ runtime (-static -static-libgcc -static-libstdc++). This means the compiled .exe is larger but does not require users to install external MinGW runtime DLLs to run the game.


## About the Human-AI Collaboration

This project was born from a fun experiment: How far can a human developer and an AI language model go in building a complete game together?
* The Human: Responsible for the initial idea, testing, debugging, environment configuration, and game design feedback.
* The AI: Assisted in writing the core C++ logic, implementing the custom pixel font renderer, handling the file I/O for the scoreboard, and configuring the CMake build system.

The result is a clean, single-file C++ codebase that is both educational and playable.

## Open Source & Free to Use

This project is completely free and open. There is no strict license attached. 

You are free to copy, modify, distribute, and use this code for any purpose (personal, educational, or commercial) without asking for permission. 

Disclaimer: This software is provided "as is", without warranty of any kind. Enjoy the game!