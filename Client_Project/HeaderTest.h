#pragma once

#ifndef HeaderTest
#define HeaderTest

int checkingTheAmountOfNumbersIsProper_CHAR(char* num, int size);//Checking the correctness of the numbers in the STRING
int checkingIfTheNameIsProper(char* string);//Checking the correctness of the letters and changing uppercase to lowercase letters
int checkingTheAmountOfNumbersIsProper_INT(int temp, int max, int min);//Checking the correctness of the numbers in INT
void checkingDataInTheNewCell(PClient* client);//Data check
void testingTheNewCell(ListManager manager, PClient* newCell);// Checking whether the ID already exists
void cellUpdate(PClient* newCell, PClient* temp);//Cell update
int comparisonOfCells(PClient* newCell, PClient* temp);//Cell comparison
int comparingDates(Date nweCell, Date temp);//Comparing dates

#endif