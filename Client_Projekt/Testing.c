
#include "HeaderProject.h"
#include "HeaderTest.h"
#include "HeaderDelet.h"
#include "HeaderPrintingManager.h"

void testingTheNewCell(ListManager manager, PClient* newCell) {// Checking whether the ID already exists
	if (!*newCell) return;
	isTheDataCorrect(newCell);//Checking the data in the new cell
	if ((*newCell)->error.ERROR) {
		addToHeadTheList(&(manager->headError), *newCell);//Sending to add to the top of the list
		return;
	}
	if (!manager->head) {
		manager->head = *newCell;//Income at the top of the list
	}
	else {
		PClient temp = manager->head;//Declare a pointer to the first cell in the list
		PClient prev = manager->head;//Declare a pointer to the first cell in the list
		while (temp) {
			if (comparisonOfCells(newCell, &temp)) {
				cellUpdate(newCell, &temp);
				break;
			}
			if ((*newCell)->error.ERROR) {//Moving the pointer to the tail of the list
				addToHeadTheList(&(manager->headError), *newCell);//Sending to add to the top of the list
				return;
			}
			if (prev != temp)
				prev = prev->next;
			temp = temp->next;//Move the pointer to the next cell
		}
		if (!*newCell && temp) {
			if (temp == manager->head)
				manager->head = manager->head->next;//Moving the pointer to the top of the list to the next cell
			else
				prev->next = temp->next;//Move the pointer to the next cell
			temp->next = NULL;//Putting the next to NULL
			*newCell = temp;//Move the pointer to new cell
		}
		addingASortedCustomerToTheList(&(manager->head), *newCell);//Sending for sorting and adding to the list
	}
}

void cellUpdate(PClient* newCell, PClient* temp) {//Cell update
	(*temp)->debt += (*newCell)->debt;//Adding the debt to the current cell
	if (comparingDates((*newCell)->date, (*temp)->date) > 0) {//Checking if the new cell's date is closer
		(*temp)->date = (*newCell)->date;//update date in the current cell
		if (strcmp((*temp)->phone, (*newCell)->phone)) {//Update the phone in the current cell
			free((*temp)->phone);
			(*temp)->phone = creatingADynamicCharWithContent((*newCell)->phone);//Getting a new string for the phone
		}
	}
	deletingACellFromTheList(newCell);//cell release
	*newCell = NULL;
}

int comparisonOfCells(PClient* newCell, PClient* temp) {//Cell comparison
	if ((strcmp((*newCell)->id, (*temp)->id)))
		return 0;
	if ((strcmp((*newCell)->firstName, (*temp)->firstName))) //Checking whether the first name is different
		(*newCell)->error.ERROR = (*newCell)->error.comparisonFirstName = 1;
	if ((strcmp((*newCell)->lastName, (*temp)->lastName))) //Checking whether the last name is different
		(*newCell)->error.ERROR = (*newCell)->error.comparisonLastName = 1;
	if ((*newCell)->error.ERROR)
		return 0;
	return 1;
}

int comparingDates(Date nweCell, Date temp) {//Comparing dates
	if (nweCell.year != temp.year)//Checking whether the year in the new cell is closer
		return nweCell.year - temp.year;
	if (nweCell.month != temp.month)//Checking whether the month in the new cell is closer
		return nweCell.month - temp.month;
	if (nweCell.day != temp.day)//Checking whether the day in the new cell is closer
		return nweCell.day - temp.day;
	return 0;//Return when the date is equal
}