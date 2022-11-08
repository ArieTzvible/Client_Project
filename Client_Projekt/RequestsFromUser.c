
#include "HeaderUser.h"

#include "HeaderProject.h"
#include "HeaderPrintingManager.h"
#include "HeaderTest.h"
#include "HeaderDelet.h"
#include "HeaderSpecific.h"


PClient createANewCellFromTheUser(char* line) {//Create a new cell from the user
	if (!*line) return NULL;//Checking that the string is not empty
	PClient cellNew = initializeErrorsinAnewCell();//Creating a new client
	if (!cellNew) return NULL;//Checking that the allocation was successful
	char* parameter, * value, * strDate = NULL;//Declaration of variables that will hold parenter and test value
	parameter = creatingADynamicCharWithContent(strtok(line, "="));//Accepting the test parameter without spaces
	do {
		value = creatingADynamicCharWithContent(strtok(NULL, ","));//Receiving the value without profits
		if (value) {
			if (isTheStringCorrect(parameter)) {
				if (!strcmp(parameter, "first name")) { //testing to which object in the cell we will add
					if (isTheStringCorrect(value))//Checking the value of the first name
						cellNew->firstName = value;//Getting a first name for the new cell
					if (!(cellNew->firstName)) {
						errorPrintingandDeletingACell(&cellNew, "\tERROR! It looks like you entered an invalid first name;\n");//printing an error and deleting a cell
						free(value);//Release a value
					}
				}
				else if (!strcmp(parameter, "last name")) { //testing to which object in the cell we will add
					if (isTheStringCorrect(value))//Checking the value of the last name
						cellNew->lastName = value;//Getting a last name for the new cell
					if (!(cellNew->lastName)) {
						errorPrintingandDeletingACell(&cellNew, "\tERROR! It looks like you entered an invalid last name;\n");//printing an error and deleting a cell
						free(value);//Release a value
					}
				}
				else if (!strcmp(parameter, "id")) { //testing to which object in the cell we will add
					if (isTheIntCorrect(value) && strlen(value) == ID) {//Checking the value of the ID
						cellNew->id = value;//Getting a ID for the new cell
					}
					if (!(cellNew->id)) {
						errorPrintingandDeletingACell(&cellNew, "\tERROR! It looks like you entered an invalid ID;\n");//printing an error and deleting a cell
						free(value);//Release a value
					}
				}
				else if (!strcmp(parameter, "phone")) {//testing to which object in the cell we will add
					if (isTheIntCorrect(value) && strlen(value) == PHONE) {//Checking the value of the phone
						cellNew->phone = value;//Getting a phone for the new cell
					}
					if (!cellNew->phone) {
						errorPrintingandDeletingACell(&cellNew, "\tERROR! It looks like you entered an invalid phone;\n");//printing an error and deleting a cell
						free(value);//Release a value
					}
				}
				else if (!strcmp(parameter, "debt")) {//testing to which object in the cell we will add
					char* strDebt = value;
					if (*strDebt == '-')
						strDebt++;
					if (isTheFloatCorrect(strDebt))//Checking the value of the debt
						cellNew->debt = convertStringToDebt(value);//Receiving the number for the client
					if (!(cellNew->debt))
						errorPrintingandDeletingACell(&cellNew, "\tERROR! It looks like you entered an invalid debt;\n");//printing an error and deleting a cell
					free(value);//Release a value
				}
				else if (!strcmp(parameter, "date")) { //testing to which object in the cell we will add
					strDate = _strdup(value);//Creating a pointer to the head of the string
					free(value);//Release a value
				}
				else {
					errorPrintingandDeletingACell(&cellNew, "\tERROR! There seems to be a mistake in typing the variable;\n");//printing an error and deleting a cell
					free(value);//Release a value
				}
			}
			else {
				errorPrintingandDeletingACell(&cellNew, "\tERROR! There seems to be a mistake in typing the request;\n");//printing an error and deleting a cell
				free(value);//Release a value
			}
		}
		free(parameter);//Release a parameter
		parameter = creatingADynamicCharWithContent(strtok(NULL, "="));
	} while ((parameter != NULL) && (cellNew != NULL));

	if (strDate) {
		cellNew->date = creatingANewDateStructure(strDate);//Send to create a date
		if ((!cellNew->date.day || !cellNew->date.month || !cellNew->date.year))
			errorPrintingandDeletingACell(&cellNew, "\tERROR! It looks like you entered an invalid date;\n");//printing an error and deleting a cell
		free(strDate);
	}
	if (cellNew != NULL) {//Checking that there are all values
		if (cellNew->firstName == NULL || cellNew->lastName == NULL ||
			cellNew->id == NULL || cellNew->phone == NULL ||
			cellNew->debt == 0 || cellNew->date.day == 0 ||
			cellNew->date.month == 0 || cellNew->date.year == 0) {
			errorPrintingandDeletingACell(&cellNew, "\tERROR! It seems that not enough values have been entered;\n");//printing an error and deleting a cell
		}
	}
	if (parameter)
		free(parameter);
	free(line);// Release a line
	return cellNew;
}

void sortingByRequest(ListManager list) {//Sort by request from the user
	char* line, * parameter, opr, * value;
	line = GettingLine(stdin);//Receiving a row from the user
	if (!*line) {
		free(line);
		return;//Test that the string is not empty
	}
	//Acceptance of the test operator
	if (strstr(line, "!=")) opr = '!';
	else if (strstr(line, "=")) opr = '=';
	else if (strstr(line, ">")) opr = '>';
	else if (strstr(line, "<")) opr = '<';
	else opr = '\0';

	parameter = creatingADynamicCharWithContent(strtok(line, "!=<>"));//Receiving the request
	if (!isTheStringCorrect(parameter)) //Entered an incorrect title
		printf("\tERROR!  It seems there was an error entering the parameter;\n");//print error
	else {
		value = strtok(NULL, "\n");//receiving the value
		if (value) {
			if (opr == '!') value++;//Move the pointer to the next cell
			value = creatingADynamicCharWithContent(value);
			if (!(strcmp(parameter, "first name"))) //Checking whether the sorting request is by first name
				if (!isTheStringCorrect(value)) //checking the correctness of the name and changing it from lowercase to uppercase
					printf("\tERROR! It looks like you entered an invalid first name;\n");//print error
				else
					testFunction(list, testingFirstName, value, opr);//Sending to a sorting function and printing according to the request
			else if (!(strcmp(parameter, "last name"))) //Checking whether the sorting request is by last name
				if (!isTheStringCorrect(value)) //checking the correctness of the name and changing it from lowercase to uppercase
					printf("\tERROR! It looks like you entered an invalid last name;\n");//print error
				else
					testFunction(list, testingLastName, value, opr);//Sending to a sorting function and printing according to the request
			else if (!(strcmp(parameter, "id"))) //Checking whether the sorting request is by ID
				if (strlen(value) != ID || !isTheIntCorrect(value))
					printf("\tERROR! It looks like you entered an invalid id; \n");//print error
				else
					testFunction(list, testingID, value, opr);//Sending to a sorting function and printing according to the request
			else if (!(strcmp(parameter, "phone"))) //Checking whether the sorting request is by phone
				if (strlen(value) != PHONE || !isTheIntCorrect(value))
					printf("\tERROR! It looks like you entered an invalid phone;\n");//print error
				else
					testFunction(list, testingPhone, value, opr);//Sending to a sorting function and printing according to the request
			else if (!(strcmp(parameter, "debt"))) {//Checking whether the sorting request is by debt
				char* tempCh = value;//Creating a pointer to the value for the test
				if (*tempCh == '-') tempCh++;//Moving the pointer to the next character in case there is a minus
				if (!isTheFloatCorrect(tempCh)) //Check that the value we received contains only numbers
					printf("\tERROR! It looks like you entered an invalid debt;\n");//print error
				else {
					float sumDebt = convertStringToDebt(value);//creating a variable to receive the debt from the string
					testFunction(list, testingDebt, &sumDebt, opr);//Sending to a sorting function and printing according to the request
				}
			}
			else if (!(strcmp(parameter, "date"))) { //Checking whether the sorting request is by date
				Date date = creatingANewDateStructure(value);//send to create a date
				if (!date.day || !date.month || !date.year)
					printf("\tERROR! It looks like you entered an invalid date;\n");//print error
				else
					testFunction(list, testingDate, &date, opr);//Sending to a sorting function and printing according to the request
			}
			else
				printf("\tERROR! It seems there was an error entering the request;\n");//print error
		}
		else
			printf("\tERROR! It seems there was an error entering the request;\n");//print error
		free(value);//Release a value
	}
	free(parameter);//Release a parameter
	free(line);//Release a line
}

void testFunction(ListManager list, int (*testing)(PClient, void*), void* value, char opr) {//Sorting and printing function according to the request
	PClient temp = list->head;//Create a pointer to the first cell in the existing list
	int test;// Create a variable to receive the test value
	int flag = 0;//Declaration of a variable that checks whether the table header has been printed
	while (temp != NULL) {//Check we haven't reached the end of the list
		test = testing(temp, value);//getting the test value
		if (opr == '=' && (test == 0))  //testing whether the user wants a comparison
			printASortedCell(temp, flag++);//Sending to print the cell and checking if the flag is raised			
		else if (opr == '!' && (test != 0)) //Checking if the user wants the different one
			printASortedCell(temp, flag++);//Sending to print the cell and checking if the flag is raised		
		else if (opr == '>' && (test > 0)) //testing whether the user wants the big one
			printASortedCell(temp, flag++);//Sending to print the cell and checking if the flag is raised		
		else if (opr == '<' && (test < 0)) //Check if the user wants the small one
			printASortedCell(temp, flag++);//Sending to print the cell and checking if the flag is raised
		temp = temp->next;//Move the pointer to the next cell
	}
	if (!flag)
		printf("\tThere are no debts in the current list;\n");//Print error
	else {
		printf("\t# ============================================================================================== #\n");
		printf("\t#                                                                                                #\n");
		printf("\t##################################################################################################\n\n\n");
	}
}

void addingClientFromUser(ListManager* list, FILE* out) {//printing a new line from the user to the file
	char* line = GettingLine(stdin);//Receiving a row from the user
	PClient	cellNew = createANewCellFromTheUser(line);//Create a new cell
	if (cellNew) {
		int Comparison = 0;// variable that will contain the comparison between two cells
		PClient temp = (*list)->head;//creating a pointer to the first cell
		if (!(*list)->head) {// checking whether the first cell is empty
			(*list)->head = cellNew;//Put the beginning and end of the list in the new cell
		}
		else {
			do {
				if (!temp->error.ERROR) {
					if (Comparison = comparisonOfCells(&cellNew, &temp))//Checking whether the ID exists
						break;
				}
				temp = temp->next;//Move the pointer to the next cell
			} while (temp && cellNew && !cellNew->error.ERROR);
			// checking that the list is not at the end or that the cell is empty or that there is an error in the cell
		}
		if (cellNew) {
			if (cellNew->error.ERROR) {
				printf("\t ERROR! The");
				//printing an error and deleting a cell in case the names and names do not match
				if (cellNew->error.comparisonFirstName && cellNew->error.comparisonLastName)
					printf(" first and last ");
				else if (cellNew->error.comparisonFirstName) printf(" first ");
				else if (cellNew->error.comparisonLastName) printf(" last ");
				errorPrintingandDeletingACell(&cellNew, "name you entered does not seem to match the ID you entered");
			}
			else {
				fprintf(out, "%s,%s,%s,%s,%.2f,%02d/%02d/%04d\n", cellNew->firstName, cellNew->lastName, cellNew->id, cellNew->phone,
					cellNew->debt, cellNew->date.day, cellNew->date.month, cellNew->date.year);//printing to a file what we received from the user
				printf("\tThe row was received successfully.\n");
				printf("\tThank you very much;\n");
				if (Comparison && temp)// Checking whether the ID is equal to one of the existing customers
					cellUpdate(&cellNew, &temp);//updating the cell and releasing the new cell
				else {
					addingASortedCustomerToTheList(&(*list)->head, cellNew);//Sending for sorting and adding to the list
				}
			}
		}
	}
}