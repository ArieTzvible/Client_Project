
#include "HeaderProject.h"
#include "HeaderTest.h"

char* getNewFileName() {//Requesting another file name
	printf("Enter a file name: ");
	char* string = GettingLine(stdin);//getting a line from the user includes creating a dynamic string

	if (string[strlen(string) - 4] != '.' || string[strlen(string) - 3] != 'c' ||
		string[strlen(string) - 2] != 's' || string[strlen(string) - 1] != 'v') {// check that there is no file name at the end(CSV)
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


float convertStringToDebt(char* strDebt) {
	float debt = (float)atof(strDebt);//Convert string to float
	debt *= 100;//Multiplying the debt by one hundredand
	int tempDebt = (int)debt; //casts it to an int to zero out the digits after the dot
	debt = tempDebt / (float)100;//Receiving the debt again with two digits after the point
	return debt;
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
		return "Error";// Returning an error
	}
	else {
		strcpy(temp, string);//copying the string we received from the user to the string we allocated space for
		temp[strlen(temp)] = '\0';//string closure
	}
	return temp;
}


//***********************************************************************************************************************
PClient createNewClientFromFile(FILE* file, char* line) {//creating a new customer from the file
	if (!*line) {
		free(line);
		return NULL;
	}
	PClient temp = initializeErrorsinAnewCell();//creating a new client
	char* token;
	token = strtok(line, ",");//accepting up to a comma (a cell in the file) and accepting it into a pointer
	temp->firstName = creatingADynamicCharWithContent(token);//Getting first name
	if (token) {
		token = strtok(NULL, ",");//accepting up to a comma (a cell in the file) and accepting it into a pointer
		temp->lastName = creatingADynamicCharWithContent(token);//Getting last name 
		if (token) {
			token = strtok(NULL, ",");//accepting up to a comma (a cell in the file) and accepting it into a pointer
			temp->id = creatingADynamicCharWithContent(token);//Getting ID
			if (token) {
				token = strtok(NULL, ",");//accepting up to a comma (a cell in the file) and accepting it into a pointer
				temp->phone = creatingADynamicCharWithContent(token);//Getting phone
				if (token) {
					token = strtok(NULL, ",");//accepting up to a comma (a cell in the file) and accepting it into a pointer					
					char* tempChar;//Creating a variable for a debt check without the minus
					char* tempForFree;//Creating a variable for the head of the string to allow deletion
					tempChar = creatingADynamicCharWithContent(token);//Getting debt
					tempForFree = tempChar;
					if (tempChar) {
						if (*tempChar == '-')// Check if there is a minus
							tempChar++;//Move pointer to next cell
						if (!checkingTheAmountOfNumbersIsProper_CHAR(tempChar, (int)strlen(tempChar)))//send to check that the string contains only numbers
							temp->debt = convertStringToDebt(token);//Receiving the number for the client
					}
					else
						temp->error.ERROR = temp->error.debt = 1;//error in receiving the debt
					free(tempForFree);//Getting a pointer to the head of the string to allow deletion
					if (token) {
						token = strtok(NULL, ",");//accepting up to a comma (a cell in the file) and accepting it into a pointer
						temp->date = creatingANewDateStructure(token);//send to create a date
						if ((!temp->date.day) && (!temp->date.month) && (!temp->date.year))
							temp->error.lacksValues = temp->error.ERROR = 1;//Missing values
						else if (!(temp->date.day && (temp->date.month) && temp->date.year))// check that all date values exist
							temp->error.ERROR = temp->error.date = 1;// Error in date
					}
				}
			}
		}
	}
	//Checking that all values exist
	if (!(temp->firstName || temp->lastName || temp->id || temp->phone || temp->debt)) {
		temp->error.lacksValues = temp->error.ERROR = 1;//Missing values
	}
	if ((!temp->date.day) && (!temp->date.month) && (!temp->date.year))
		temp->error.lacksValues = temp->error.ERROR = 1;//Missing values

	free(line);
	return temp;
}
//***********************************************************************************************************************


void creatingListOfClientsFromAFile(ListManager manager, FILE* file) {//creating a list from the file
	char* tempLine;
	while (!(feof(file))) {// checking whether the end of the file has been reached
		tempLine = GettingLine(file);//send to get a line from the file
		if (tempLine != NULL && *tempLine != '\n') {
			PClient temp = createNewClientFromFile(file, tempLine);// send to create a new cell
			testingTheNewCell(manager, &temp);//Testing new cell
		}
	}
}

Date creatingANewDateStructure(char* date) {//create date
	Date temp = { 0 };//Creating a date structure type variable
	if (!date) return temp;//check that the received string contains characters
	char* strDate = date;//Declaration of a variable holding the resulting string
	int tempDate;//Declaration of a variable holding the resulting string
	if (((int)strlen(strDate) == 10) && (strDate[2] == '/' && strDate[5] == '/')) {// check that the date was entered correctly
		char tempDateStr[5] = { 0 };
		int flag = 0;// Creating a variable to check the number of times we entered the loop
		while (*strDate) {// check that we haven't reached the end of the string yet
			for (int i = 0; *strDate && *strDate != '/'; i++, flag++)// checking that we haven't reached the end of the string and that the character is not '/'
				tempDateStr[i] = *strDate++;//adding the character to the string
			if (!(checkingTheAmountOfNumbersIsProper_CHAR(tempDateStr, (int)strlen(tempDateStr)))) {//check that the string contains only numbers
				if (flag <= 4) strDate++; //Move the pointer to the next cell
				if (flag == 2) {//check that we received the days
					if (!(checkingTheAmountOfNumbersIsProper_INT((tempDate = atoi(tempDateStr)), DAY, 1))) //Check that the number is within the legal range
						temp.day = tempDate;// Application of the number in the designated cell
				}
				else if (flag == 4) {//check that we received the month
					if (!(checkingTheAmountOfNumbersIsProper_INT((tempDate = atoi(tempDateStr)), MONTH, 1))) //Check that the number is within the legal range
						temp.month = tempDate;// Application of the number in the designated cell
				}
				else {
					if (!(checkingTheAmountOfNumbersIsProper_INT((tempDate = atoi(tempDateStr)), YEAR, 1))) //Check that the number is within the legal range
						temp.year = tempDate;// Application of the number in the designated cell
				}
			}
		}
	}
	return temp;
}
