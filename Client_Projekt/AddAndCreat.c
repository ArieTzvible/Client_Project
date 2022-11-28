
#include "Header.h"
#include "HeaderGeneral.h"

void addToHeadTheList(PClient* head, PClient newCell) {
	newCell->next = *head;
	*head = newCell;
}

void addingASortedCustomerToTheList(PClient* head, PClient newCell) {//A function for sorting and adding to the list
	if (!newCell) return;
	if (*head == NULL || newCell->debt <= (*head)->debt) {//Checking whether the first cell is empty
		newCell->next = *head;//Bringing the customer to the top of the list
		*head = newCell;//Moving the pointer to the top of the list
		return;
	}
	PClient temp = *head;//Declare a pointer to the first cell in the list
	while (temp) {
		if ((!temp->next) || (newCell->debt <= temp->next->debt)) {//Test A. End of list B. A debt smaller than the current debt
			newCell->next = temp->next;//Bringing the client to the current location
			temp->next = newCell;//Getting the next client on the list
			return;
		}
		temp = temp->next;//Move the pointer to the next cell
	}
}

ListManager createANewListManager() {//creating a manager structure
	ListManager temp = (ListManager)malloc(sizeof(List));//creating a new structure
	if (temp == NULL)
		printf("Not enough memory\n");//print error;//Error printing when there is no space in memory
	else {
		temp->head = NULL;//statement to the top of the list
		temp->headError = NULL;//statement to the top of the errors list 
	}
	return temp;//returning the structure
}

PClient initializeErrorsinAnewCell() {//initialize a new client structure
	PClient newClient = (PClient)malloc(sizeof(Client));//Declaration and creation of a new structure
	if (!newClient) {
		printf("Not enough memory\n");//Error printing when there is no space in memory
		return NULL;
	}
	newClient->next = NULL;
	newClient->firstName = NULL;
	newClient->lastName = NULL;
	newClient->id = NULL;
	newClient->phone = NULL;
	newClient->date.day = 0;
	newClient->date.month = 0;
	newClient->date.year = 0;
	newClient->debt = 0;
	newClient->error.ERROR = 0;
	newClient->error.firstName = 0;//error in first name
	newClient->error.lastName = 0;//Error in last name
	newClient->error.id = 0;//. Error in
	newClient->error.phone = 0;//Error on phone
	newClient->error.date = 0;//Error in date
	newClient->error.debt = 0;//Error in debt
	newClient->error.comparisonFirstName = 0;//record T.Z. Does not match first name
	newClient->error.comparisonLastName = 0;//Error ID Does not match last name
	newClient->error.lacksValues = 0;//Error Not enough values
	return newClient;
}

char* getNewFileName() {//Requesting another file name
	printf("\n\tEnter a file name: ");
	char* string = GettingLine(stdin);//getting a line from the user includes creating a dynamic string
	if (strcmp((string + (strlen(string) - 4)), ".csv")) {// check that there is no file name at the end(CSV)		
		char* str = (char*)malloc((strlen(string) + strlen(".csv") + 1) * sizeof(char));//creating a string that will also contain the document extension
		if (!str)//testing whether the allocation was successful
			printf("Not enough memory\n");//print error;//Error printing when there is no space in memory
		else {
			strcpy(str, string);//copy the string received from the user
			strcat(str, ".csv");//copy the file extension
			strcat(str, "\0");//adding 0\ at the end of the string
			free(string);//release the string we received from the user
			string = str;//setting the string to the string to send
		}
	}
	return string;//sending a pointer with the file name
}

char* creatingADynamicCharWithContent(char* string) {//Creating a dynamic variable with content
	if (!string) return NULL;//testing that we received a value
	while (*string == ' ' || *string == '\t') string++;//skipping all spaces before the string
	int i = (int)strlen(string) - 1;//creating a variable of the length of the string
	while (string[i] == ' ' || string[i] == '\t') string[i--] = '\0';// deletes all spaces after the string
	char* temp = (char*)malloc((strlen(string) + 1) * sizeof(char));// Create a dynamic variable with the size of the string
	if (!temp) {// check that the allocation was successful
		printf("Not enough memory\n");//Error printing when there is no space in memory
		return NULL;// Returning an error
	}
	else {
		strcpy(temp, string);//copying the string we received from the user to the string we allocated space for
		temp[strlen(temp)] = '\0';//string closure
	}
	return temp;
}