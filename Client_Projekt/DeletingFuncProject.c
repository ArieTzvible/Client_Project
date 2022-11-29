//***********************vvvvvvvvvvvvvvvvvvvvvvvvv
#include "HeaderDelet.h"

void deletingACellFromTheList(PClient* currentCell) {//deleting a cell from the list
	free((*currentCell)->firstName);//Releasing a first name string
	free((*currentCell)->lastName);//Releasing last name string
	free((*currentCell)->id);//Releasing an ID string
	free((*currentCell)->phone);//Releasing a phone string
	free(*currentCell);//release current cell
	*currentCell = NULL;
}

void deletingTheEntireList(ListManager manager) {//deleting the whole list
	while (manager->head) {//Checking the list is not empty
		PClient temp = manager->head;
		manager->head = manager->head->next;//Move the pointer to the next cell
		deletingACellFromTheList(&temp);//cell release
	}
	while (manager->headError) {//Checking the list is not empty
		PClient temp = manager->headError;
		manager->headError = manager->headError->next;//Move the pointer to the next cell
		deletingACellFromTheList(&temp);//cell release
	}
	free(manager);//Releasing the manager structure
}

void errorPrintingandDeletingACell(PClient* cell, char* str) {//printing an error and deleting a cell
	printf("%s", str);//printing an error
	deletingACellFromTheList(cell);//deleting a cell
}
