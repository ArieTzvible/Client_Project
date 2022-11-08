#pragma once

#ifndef HeaderTest
#define HeaderTest

int isNum(char ch);
int isTheIntCorrect(char* num);//Checking the correctness of the int in the string
int isTheFloatCorrect(char* num);//Checking the correctness of the float in the string
int isLetter(char* ch);
int isTheStringCorrect(char* string);//Checking the correctness of the letters and changing uppercase to lowercase letters
float convertStringToDebt(char* strDebt);//Convert a string to a sum with only two digits after the dot
void isTheDataCorrect(PClient* client);
void testingTheNewCell(ListManager manager, PClient* newCell);// Checking whether the ID already exists
void cellUpdate(PClient* newCell, PClient* temp);//Cell update
int comparisonOfCells(PClient* newCell, PClient* temp);//Cell comparison
int comparingDates(Date nweCell, Date temp);//Comparing dates




#endif