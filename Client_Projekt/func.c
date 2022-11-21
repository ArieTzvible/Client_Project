
#include "HeaderProject.h"
#include "HeaderTest.h"

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

char* GettingLine(FILE* file) {//getting a complete line from the file
	char* input = NULL;//statement about a pointer to a row that the user entered
	char string[200];//Declaration of a variable
	fgets(string, 200, file);//Getting a string from the file
	if (feof(file)) return NULL;//Returning NULL when reaching the end of the file
	input = _strdup(string);//Creating a variable and copying the string
	if (!input) {// checking whether there is space in the memory
		printf("Not enough memory\n");//Error printing when there is no space in memory
		return input;
	}
	if (input[strlen(input) - 1] == '\n' || input[strlen(input) - 1] == '\0') {//Checking whether the entire line was received
		input[strlen(input) - 1] = '\0';//Changing the last cell to \0
		return input;
	}

	char tempBuf[CHUNK] = { 0 };//Declaration of a variable to receive values from the user
	size_t tempLen = 0, inputLen = strlen(input);//declaration of variables to test the length of the received line
	do {	
		fgets(tempBuf, CHUNK, file);// getting 10 cells from the row
		tempLen = (int)strlen(tempBuf);//put the number of characters received
		char* temp = (char*)realloc(input, (inputLen + tempLen + 1) * sizeof(char));//adding space to receive the string
		if (!temp) {// checking whether there is space in the memory
			printf("Not enough memory\n");//Error printing when there is no space in memory
			return input;
		}
		else
			input = temp;//getting the new length of the string
		strcpy(input + inputLen, tempBuf);// Copy from the last location we copied
		inputLen += tempLen;//Getting the current string length

	} while (tempLen == CHUNK - 1 && tempBuf[CHUNK - 2] != '\n');
	if (input[strlen(input) - 1] == '\n')// Checking if the last location contains '\n'
		input[strlen(input) - 1] = '\0';//set the last place to \0
	else {//
		char* temp = (char*)realloc(input, (strlen(input) + 1) * sizeof(char));//Add a space to the string
		if (!temp) {// checking whether there is space in the memory
			printf("Not enough memory\n");//Error printing when there is no space in memory
			return input;
		}
		else {//If the end of the file is reached (in the case of reading from a file)
			input = temp;//getting the new length of the string
			input[strlen(input)] = '\0'; // set the last place to \0
		}
	}
	return input;
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

//***********************************************************************************************************************

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