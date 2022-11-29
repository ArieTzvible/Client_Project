#pragma once

#ifndef HeaderCreatingAClient
#define HeaderCreatingAClient

#include "HeaderTest.h"

void fillingInAFirstName(PClient curr, char* string);
void fillingInALastName(PClient curr, char* string);
void fillingInAID(PClient curr, char* string);
void fillingInAPhone(PClient curr, char* string);
void fillingInADebt(PClient curr, char* string);
void fillingInADate(PClient curr, char* string);
PClient createNewClientFromFile(char* line);//Create a new cell from the file
void creatingListOfClientsFromAFile(ListManager manager, FILE* file);//creating a list from the file
Date creatingANewDateStructure(char* date);//Create a new date

#endif