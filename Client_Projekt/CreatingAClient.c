
#include "HeaderCreatingAClient.h"

void fillingInAFirstName(PClient curr, char* string) {
	if ((!curr) || (!string)) return;
	curr->firstName = creatingADynamicCharWithContent(string);//Getting first name
}

void fillingInALastName(PClient curr, char* string) {
	if ((!curr) || (!string)) return;
	curr->lastName = creatingADynamicCharWithContent(string);//Getting last name 
}

void fillingInAID(PClient curr, char* string) {
	if ((!curr) || (!string)) return;
	curr->id = creatingADynamicCharWithContent(string);//Getting ID
}

void fillingInAPhone(PClient curr, char* string) {
	if ((!curr) || (!string)) return;
	curr->phone = creatingADynamicCharWithContent(string);//Getting phone
}

void fillingInADebt(PClient curr, char* string) {
	if ((!curr) || (!string)) return;
	char* strDebt;//Creating a variable for a debt check without the minus
	strDebt = creatingADynamicCharWithContent(string);//Getting debt
	if (strDebt && isNegativeFloat(strDebt))
		curr->debt = stringConversionToFloat(string);//Receiving the number for the client
	else
		curr->error.ERROR = curr->error.debt = 1;//error in receiving the debt
	free(strDebt);
}

void fillingInADate(PClient curr, char* string) {
	if ((!curr) || (!string)) return;
	curr->date = creatingANewDateStructure(string);//send to create a date
	if ((!curr->date.day) && (!curr->date.month) && (!curr->date.year))
		curr->error.lacksValues = curr->error.ERROR = 1;//Missing values
	else if (!(curr->date.day && (curr->date.month) && curr->date.year))// check that all date values exist
		curr->error.ERROR = curr->error.date = 1;// Error in date
}

PClient createNewClientFromFile(char* line) {//creating a new customer from the file
	if (!*line) {
		free(line);
		return NULL;
	}
	PClient temp = initializeErrorsinAnewCell();//initialize a new client structure
	void (*arr[6])(PClient curr, char* string) = {
		fillingInAFirstName, fillingInALastName, fillingInAID,
		fillingInAPhone, fillingInADebt, fillingInADate };

	int i = 0;
	char* token;
	token = strtok(line, ",");//accepting up to a comma (a cell in the file) and accepting it into a pointer

	do {
		arr[i++](temp, token);
		token = strtok(NULL, ",");//accepting up to a comma (a cell in the file) and accepting it into a pointer
	} while (token && i < 6);

	//Checking that all values exist
	if (!(temp->firstName && temp->lastName && temp->id && temp->phone && temp->debt)) {
		temp->error.lacksValues = temp->error.ERROR = 1;//Missing values
	}
	if ((!temp->date.day) && (!temp->date.month) && (!temp->date.year))
		temp->error.lacksValues = temp->error.ERROR = 1;//Missing values

	free(line);
	return temp;
}

void creatingListOfClientsFromAFile(ListManager manager, FILE* file) {//creating a list from the file
	char* tempLine;
	while (!(feof(file))) {// checking whether the end of the file has been reached
		tempLine = GettingLine(file);//send to get a line from the file
		if (tempLine != NULL && *tempLine != '\n') {
			PClient temp = createNewClientFromFile(tempLine);// send to create a new cell
			testingTheNewCell(manager, &temp);//Testing new cell
		}
	}
}

Date creatingANewDateStructure(char* date) {//create date
	Date temp = { 0 };//Creating a date structure type variable
	if (!date) return temp;//check that the received string contains characters
	char* strDate = date;//Declaration of a variable holding the resulting string
	if (((int)strlen(strDate) == 10) && (strDate[2] == '/' && strDate[5] == '/')) {//Is the date correct.
		char* token;
		token = strtok(date, "/");//accepting up to a comma (a cell in the file) and accepting it into a pointer
		if (isInt(token)) {//Is the number correct?
			int day = atoi(token);//Convert string to number
			if (day <= DAY && day > 0) {//Is the number in the normal range
				temp.day = day;// Application of the number in the designated cell
			}
		}
		token = strtok(NULL, "/");
		if (isInt(token)) {//Is the number correct?
			int month = atoi(token);//Convert string to number
			if (month <= MONTH && month > 0) {//Is the number in the normal range
				temp.month = month;// Application of the number in the designated cell
			}
		}
		token = strtok(NULL, "\n");
		if (isInt(token)) {//Is the number correct?
			int year = atoi(token);//Convert string to number
			if (year <= MAX_YEAR && year > MIN_YEAR) {//Is the number in the normal range
				temp.year = year;// Application of the number in the designated cell
			}
		}
	}
	return temp;//Return new cell
}