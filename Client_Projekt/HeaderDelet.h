#pragma once
#ifndef HeaderDelet
#define HeaderDelet

#include "HeaderProject.h"

void deletingACellFromTheList(PClient* currentCell);//Deleting a cell from the list
void deletingTheEntireList(ListManager  manager);//Deleting the entire list
void errorPrintingandDeletingACell(PClient* cell, char* str);//print an error and delete the cell


#endif