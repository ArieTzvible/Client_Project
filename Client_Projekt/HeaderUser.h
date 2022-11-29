
#pragma once

#ifndef HeaderUser
#define HeaderUser

#include "HeaderMain.h"

PClient createANewCellFromTheUser(char* line);//Creating a new client from the user
void sortingByRequest(ListManager list);//Sort by request from the user
void testFunction(ListManager list, int (*testing)(PClient, void*), void* value, char opr);//Sorting and printing according to request
void addingClientFromUser(ListManager* list, FILE* out);//Print a new line from the user to the file

#endif