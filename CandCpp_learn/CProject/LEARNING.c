#include <stdio.h>
#include <limits.h>
#include <math.h>
#include <float.h>
#include <string.h>

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
    const unsigned long YearSecond = 31560000;
    unsigned long age, width;
    float OverflowExNumf = 1.0f, old_f;
    const int yearDayCommon = 365, toes = 10;
    float CHAPTER = 2.12f, ChangeF, water, FNum;
    double tall, TallSwitch = 2.54, cups;
    char test_char, firstname[10], lastname[10], name[40];
    float SpFile, MBfile, distance, FuelUse;

    const double num1 = 1.0/3.0;
    const float num2 = 1.0f/3.0f, Gallon = 3.785f, mile =  1.609f;

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
    T();

    PRINT(2,CHAPTER);
    printf("Please enter a ASCII value:");
    scanf("%c",&test_char);
    printf("%c\n",test_char);
    T();

    PRINT(3,CHAPTER);
    printf("'\007'Startled by the sudden sound,Sally shouted,\n\"By the Great Pumpkin, what was that!\"\n");
    T();

    PRINT(4,CHAPTER);
    printf("Enter a floating-point value:");
    scanf("%f",&ChangeF);
    printf("fixed-point notation:%f\nexponential notation:%e\np notation:%a\n",ChangeF,ChangeF,ChangeF);
    T();

    PRINT(5,CHAPTER);
    printf("Please enter your age:");
    scanf("%lu",&age);
    printf("Your age is %lu seconds.\n",age * YearSecond);
    T();

    PRINT(6,CHAPTER);
    printf("Please enter the number of quarts of water:");
    scanf("%f",&water);
    printf("%e\n",water*950/3.0E-23);
    T();

    PRINT(7,CHAPTER);
    printf("Please enter your feet");
    scanf("%lf",&tall);
    printf("Your height converted to feet is %lf inches: \n",tall*TallSwitch);
    T();

    PRINT(8,CHAPTER);
    printf("Please enter the num of cups: ");
    scanf("%lf",&cups);
    printf("%lf cups correspond to %lf pints, %lf fluid ounces, %lf tablespoons, and %lf teaspoons.",cups,cups/2.0,cups/8,cups/16,cups/48);
    T();

    CHAPTER = 4.08f;
    PRINT(1,CHAPTER);
    printf("Please enter your first and your last name(Each word must not exceed ten characters):\nFirst name:");
    scanf("%s",firstname);
    printf("Last name:");
    scanf("%s",lastname);
    printf("%s %s\n",lastname,firstname);
    T();

    PRINT(2,CHAPTER);
    printf("Please enter your name(Must not exceed forty characters):");
    scanf("%s",name);
    width = strlen(name);
    printf("\"%20s\"\n\"%-20s\"\n\"%*s\"\n",name,name,width+3,name);
    T();

    PRINT(3,CHAPTER);
    printf("Please input a float number:");
    scanf("%f",&FNum);
    printf("a.The input is %f or %e\nb.The input is %+f or %E\n",FNum,FNum,FNum,FNum);
    T();

    PRINT(4,CHAPTER);
    printf("Please enter your tall(inch) and your name.\nYour tall:");
    scanf("%lf",&tall);
    printf("Please enter your name.\nYour name:");
    scanf("%s",name);
    printf("%s, you are %lf feet tall\n",name,tall/12);
    T();

    PRINT(5,CHAPTER);
    printf("Please enter the download speed (Mb/s) and file size (MB).\nDownload speed:");
    scanf("%f",&SpFile);
    printf("File size:");
    scanf("%f",&MBfile);
    printf("At %f ,megabits per second, a file of %f megabytes downloads in %f seconds",SpFile,MBfile,MBfile*8/SpFile);
    T();

    PRINT(6,CHAPTER);
    printf("Please enter your name:\nYour first name:");
    scanf("%s",firstname);
    printf("Last name:");
    scanf("%s",lastname);
    printf("%s %s\n%zu %zu\n",lastname,firstname,strlen(firstname),strlen(lastname));
    T();

    PRINT(7,CHAPTER);
    printf("One:\t%6lf\t%6f\nTwo:\t%12lf\t%12f\nThree:\t%16lf\t%16f\n\t%d\t%d\n",num1,num2,num1,num2,num1,num2,FLT_DIG,DBL_DIG);
    T();

    PRINT(8,CHAPTER);
    printf("Please enter the distance traveled and the amount of gasoline consumed.\nDistance(mile):");
    scanf("%f",&distance);
    printf("Fuel use(gallon):");
    scanf("%f",&FuelUse);
    printf("One mile per gallon corresponds to %1f liters per 100 kilometers.",FuelUse * Gallon / distance * mile * 100);
    T();

    CHAPTER = 5.11f;
    PRINT(1,CHAPTER);
    PRINT(2,CHAPTER);
    PRINT(3,CHAPTER);
    PRINT(4,CHAPTER);
    return 0;
}