
#include "HeaderProject.h"
#include "HeaderTest.h"
#include "HeaderDelet.h"
#include "HeaderPrint.h"


int checkingTheAmountOfNumbersIsProper_CHAR(char* num, int size) {//Checking the correctness of the numbers in the STRING
	if (num[size] != '\0')// Checking whether the number received is smaller or larger than the correct length
		return 1;
	for (int i = 0; i < size; i++)
		if ((num[i] < '0' || num[i] > '9') && num[i] != '.')//Checking that the character is a number
			return 1;
	return 0;
}

int checkingIfTheNameIsProper(char* string) {//Checking the correctness of the letters and changing uppercase to lowercase letters
	if (!string) return 0;//Checking that the string is not empty
	char* temp = string;//Creating a pointer to the string we received
	while (*temp != '\0' && *temp != '\n' && temp != NULL) {//Checking that we haven't reached the end of the string
		if (*temp != ' ') {//Skipping profits
			if (*temp < 'a' || *temp > 'z') {//Checking that the character is a letter
				if (*temp < 'A' || *temp > 'Z') //Checking and converting an uppercase letter to lowercase
					return 1;
				*temp += ' ';//Converting an uppercase letter to a lowercase letter
			}
		}
		temp++;//Move the pointer to the next cell
	}
	return 0;
}

int checkingTheAmountOfNumbersIsProper_INT(int temp, int max, int min) {//Checking the number within the set range
	if (temp > max || temp < min)//A check that is no greater than the maximum and no less than the minimum
		return 1;
	return 0;
}

void checkingDataInTheNewCell(PClient* client) {//Test Data
	if ((*client)->error.ERROR) return;
	(*client)->error.ERROR = (*client)->error.id = checkingTheAmountOfNumbersIsProper_CHAR((*client)->id, ID);//Checking the ID	 
	if (checkingIfTheNameIsProper((*client)->firstName))//first name check
		(*client)->error.ERROR = (*client)->error.firstName = 1;//Error application in first name
	if (checkingIfTheNameIsProper((*client)->lastName))//last name check
		(*client)->error.ERROR = (*client)->error.lastName = 1;//Error application in last name
	if (((int)strlen((*client)->phone) == 9) && *(*client)->phone != '0') {//Checking if the phone is smaller than 10 because there is no 0 at the beginning
		char* phone = (char*)malloc(11 * sizeof(char));//Declaration of a dynamic variable
		if (!phone)//Checking if there is space in the memory
			printf("Not enough memory\n");
		else {
			strcpy(phone, "0");//Added 0 in the first place
			strcat(phone, (*client)->phone);//Copy of the rest of the number
			free((*client)->phone);//Dropping the existing string to get a new string
			(*client)->phone = phone;//receiving the phone
		}
	}
	if ((*client)->phone != NULL) {
		if (checkingTheAmountOfNumbersIsProper_CHAR((*client)->phone, PHONE))//phone check
			(*client)->error.ERROR = (*client)->error.phone = 1;//Error application in phon
		else if ((*client)->phone[0] != '0')//Check if the number starts with 0
			(*client)->error.ERROR = (*client)->error.phone = 1;//Error application in phone
	}
	if ((*client)->firstName == NULL || (*client)->lastName == NULL ||
		(*client)->id == NULL || (*client)->phone == NULL ||
		(*client)->debt == 0 ) {//Checking if all values exist
		(*client)->error.ERROR = (*client)->error.lacksValues = 1;//Error application in values
	}
	if ((*client)->date.day == 0 && (*client)->date.month == 0 && (*client)->date.year == 0){
	(*client)->error.ERROR = (*client)->error.lacksValues = 1;//Error application in values
		}

}

void testingTheNewCell(ListManager manager, PClient* newCell) {// Checking whether the ID already exists
	if (!*newCell) return;
	checkingDataInTheNewCell(newCell);//Checking the data in the new cell
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