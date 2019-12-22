#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <locale.h>

// Functions
int randomizer(bool negative);
int startGame();
double precisioner(double numb, int pre);
int randomRange(int min, int max);
void printHelp();
void printSyntax();
void printYatirimDurum();
int my_atoi(const char* snum);//https://stackoverflow.com/questions/7021725/how-to-convert-a-string-to-integer-in-c
// End Of Functions

// #define __ENABLE_TEST_MODE // Belli yerleri kontrol amaçlý
#define __CAR_COUNT 2 // Bazý yerleri tamamlayamadýðým için sadece iki araba için çalýþýr durumda

const int startingMoney[2] = {400, 700};// min, max
const int finishMoney = 25000;
const int raceLenghts[2] = {45,85};// min, max
const char carNames[__CAR_COUNT+1]="RM";

int yatirilanPara = 0; int yatirilanAraba = 0;
int randoms[__CAR_COUNT][10];
