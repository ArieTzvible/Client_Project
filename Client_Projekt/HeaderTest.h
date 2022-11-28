#pragma once

#ifndef HeaderTest
#define HeaderTest

#include "Header.h"

void testingTheNewCell(ListManager manager, PClient* newCell);// Checking whether the ID already exists
void cellUpdate(PClient* newCell, PClient* temp);//Cell update
int comparisonOfCells(PClient* newCell, PClient* temp);//Cell comparison
int comparingDates(Date nweCell, Date temp);//Comparing dates
void isTheDataCorrect(PClient* client);

#endif