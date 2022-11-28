#pragma once
#ifndef HeaderGeneral
#define HeaderGeneral

#include "Header.h"

#define CHUNK 10

int isNum(char ch);
int isInt(char* num);//Checking the correctness of the int in the string
int isFloat(char* num);//Checking the correctness of the float in the string
int isNegativeInt(char* num);
int isNegativeFloat(char* num);
int isLetter(char* ch);
int isTheStringCorrect(char* string);//Checking the correctness of the letters and changing uppercase to lowercase letters
float stringConversionToFloat(char* strFloat);//Convert a string to a sum with only two digits after the dot
char* GettingLine(FILE* file);//getting a complete line from the file

#endif