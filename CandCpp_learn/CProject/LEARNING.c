#include <stdio.h>
#include <limits.h>
#include <math.h>
#include <float.h>

void PRINT(int NO,float CHAPTER);

void jolly();
void deny();
void br();
void ic();
void smile();
void one_three();
void two();
void T();


void T()
{printf("\n");}

void PRINT(const int NO,const float CHAPTER)
{
    printf("%.2f,NO.%d\n",CHAPTER,NO);
}//Utility function to display the chapters of an exercise set and the exercise numbers within each chapter.

void jolly()
{printf("For he's a jolly fellow!\n");}

void deny()
{printf("Which nobody can deny\n");}

void br()
{printf("Brazil, Russia");}

void ic()
{printf("India, China");}

void smile()
{printf("Smile!");}

void one_three()
{printf("One\n");two();printf("Three\n");}

void two()
{printf("Two!\n");}

int main()
{
    int   OverflowExNum = UINT_MAX - 50000u;
    unsigned int old_int = OverflowExNum;
    float OverflowExNumf = 1.0f, old_f;
    const int yearDayCommon = 365, toes = 10;
    float CHAPTER = 2.12f;

    //CHAPTER 2
    PRINT(1,CHAPTER);
    printf("SawlRo Alan\nSawlRo\nAlan\n");
    T();
    PRINT(2,CHAPTER);
    printf("SawlRo Alan, Earth\n");
    T();
    PRINT(3,CHAPTER);
    printf("%d,%d\n",yearDayCommon,yearDayCommon*19);
    T();
    PRINT(4,CHAPTER);
    jolly();jolly();jolly();deny();
    T();
    PRINT(5,CHAPTER);
    br();printf(", ");ic();printf("\n");
    br();printf("\n");
    ic();printf("\n");
    T();
    PRINT(6,CHAPTER);
    printf("Orign Number:%d,Double Rate:%d,The Square:%d\n",toes,toes*2,toes*toes);
    T();
    PRINT(7,CHAPTER);
    smile();smile();smile();printf("\n");
    smile();smile();printf("\n");
    smile();printf("\n");
    T();
    PRINT(8,CHAPTER);
    printf("Staring now\n");
    one_three();
    printf("Done!\n");
    T();

    //CHAPTER 3
    CHAPTER = 3.11f;
    PRINT(1,CHAPTER);
    OverflowExNum += 100000u;
    printf("Positive integer overflow: %u -> %u\n", old_int, OverflowExNum);

    while (!isinf(OverflowExNumf)) {
        old_f = OverflowExNumf;
        OverflowExNumf *= 2.0f;
    }
    printf("Floating-point overflow: %e -> %e\n", old_f, OverflowExNumf);

    OverflowExNumf = -1.0f;
    while (!isinf(OverflowExNumf)) {
        old_f = OverflowExNumf;
        OverflowExNumf *= 2.0f;
    }
    printf("Negative overflow: %e -> %e\n", old_f, OverflowExNumf);

    OverflowExNumf = FLT_MIN;
    old_f = OverflowExNumf;
    while (OverflowExNumf != 0.0f) {
        old_f = OverflowExNumf;
        OverflowExNumf /= 2.0f;
    }
    printf("Floating-point underflow: %e -> %e\n", old_f, OverflowExNumf);

    PRINT(2,CHAPTER);
    

    PRINT(3,CHAPTER);
    PRINT(4,CHAPTER);
    PRINT(5,CHAPTER);
    PRINT(6,CHAPTER);
    PRINT(7,CHAPTER);
    PRINT(8,CHAPTER);
    return 0;
}