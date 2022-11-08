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



////****בדיקה למחיקה
//int IsTheLengthCorrect(int temp, int max, int min);//Checking the correctness of the numbers in INT
////*****
//
//void isTheDataCorrect(PClient* client);
//
////***  --isNumCorrect--
//int checkingTheAmountOfNumbersIsProper_CHAR(char* num, int size);//Checking the correctness of the numbers in the STRING
////***  --isStringCorrect--
//int checkingIfTheNameIsProper(char* string);//Checking the correctness of the letters and changing uppercase to lowercase letters
////***  --IsTheLengthCorrect--
//int checkingTheAmountOfNumbersIsProper_INT(int temp, int max, int min);//Checking the correctness of the numbers in INT
////***  --isTheDataCorrect--
//void checkingDataInTheNewCell(PClient* client);//Data check

void testingTheNewCell(ListManager manager, PClient* newCell);// Checking whether the ID already exists
void cellUpdate(PClient* newCell, PClient* temp);//Cell update
int comparisonOfCells(PClient* newCell, PClient* temp);//Cell comparison
int comparingDates(Date nweCell, Date temp);//Comparing dates




#endif