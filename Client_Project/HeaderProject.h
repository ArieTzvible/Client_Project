
#pragma once
#ifndef HeaderProject
#define HeaderProject

#define CHUNK 10
#define ID 9//Maximum digits in ID.
#define PHONE 10//Maximum digits in phon.
#define DAY 31//Maximum days.
#define MONTH 12//Maximum months.
#define YEAR 2500//Maximum years

#include "HeaderStruct.h"


#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

//File
PClient createNewClientFromFile(FILE* file, char* line);//Create a new cell from the file
void creatingListOfClientsFromAFile(ListManager manager, FILE* file);//Creating a list from the file

//General
char* getNewFileName();//Requesting a different file name
char* GettingLine(FILE* file);//getting a complete row
Date creatingANewDateStructure(char* date);//Create a new date
char* creatingADynamicCharWithContent(char* string);//Create a dynamic string with content
float convertStringToDebt(char* strDebt);//Convert a string to a sum with only two digits after the dot


#endif