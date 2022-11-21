#pragma once

#ifndef HeaderTest
#define HeaderTest

int isNum(char ch);
int isInt(char* num);//Checking the correctness of the int in the string
int isFloat(char* num);//Checking the correctness of the float in the string
int isNegativeInt(char* num);
int isNegativeFloat(char* num);
int isLetter(char* ch);
int isTheStringCorrect(char* string);//Checking the correctness of the letters and changing uppercase to lowercase letters
float stringConversionToFloat(char* strDebt);//Convert a string to a sum with only two digits after the dot

void testingTheNewCell(ListManager manager, PClient* newCell);// Checking whether the ID already exists
void cellUpdate(PClient* newCell, PClient* temp);//Cell update
int comparisonOfCells(PClient* newCell, PClient* temp);//Cell comparison
int comparingDates(Date nweCell, Date temp);//Comparing dates
void isTheDataCorrect(PClient* client);

#endif