
#pragma once
#ifndef HeaderProject
#define HeaderProject

#include "HeaderStruct.h"

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

//File
void fillingInAFirstName(PClient curr, char* string);
void fillingInALastName(PClient curr, char* string);
void fillingInAID(PClient curr, char* string);
void fillingInAPhone(PClient curr, char* string);
void fillingInADebt(PClient curr, char* string);
void fillingInADate(PClient curr, char* string);
PClient createNewClientFromFile(char* line);//Create a new cell from the file

void creatingListOfClientsFromAFile(ListManager manager, FILE* file);//Creating a list from the file

char* getNewFileName();//Requesting a different file name
char* GettingLine(FILE* file);//getting a complete row
Date creatingANewDateStructure(char* date);//Create a new date
char* creatingADynamicCharWithContent(char* string);//Create a dynamic string with content

#endif
