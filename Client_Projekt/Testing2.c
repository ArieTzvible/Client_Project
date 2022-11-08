
#include "HeaderProject.h"
#include "HeaderTest.h"
#include "HeaderDelet.h"
#include "HeaderPrintingManager.h"

int isNum(char ch) {
	if (ch >= '0' && ch <= '9')
		return 1;
	return 0;
}
int isTheIntCorrect(char* num) {//Checking the correctness of the int in the string
	if (!num) return 0;
	for (int i = 0; i < strlen(num); i++)
		if (!isNum(num[i]))
			return 0;
	return 1;
}
int isTheFloatCorrect(char* num) {//Checking the correctness of the float in the string
	if (!num) return 0;
	for (int i = 0; i < strlen(num); i++)
		if (num[i] != '.')
			if (!isNum(num[i]))
				return 0;
	return 1;
}

int isLetter(char* ch) {
	if ((*ch < 'a') || (*ch > 'z')) {//Checking that the character is a letter
		if ((*ch < 'A') || (*ch > 'Z')) //Checking and converting an uppercase letter to lowercase
			return 0;
		*ch += 32;//Converting an uppercase letter to a lowercase letter
	}
	return 1;
}
int isTheStringCorrect(char* string) {//Checking the correctness of the letters and changing uppercase to lowercase letters
	char *tempStr = string;
	while ((tempStr) && (*tempStr != '\0') && (*tempStr != '\n')) {
		if (*tempStr != ' ')//Skipping profits
			if (!isLetter(tempStr))
				return 0;
		tempStr++;
	}
	return 1;
}

float convertStringToDebt(char* strDebt) {
	float debt1 = 100 * (float)atof(strDebt);
	int debt2 = (int)debt1;//Multiply the debt by one hundred
	return debt2 / (float)100;//Returning the debt with two decimal digits
}

void isTheDataCorrect(PClient* client) {
	if ((*client)->error.ERROR) return;
	if (strlen((*client)->id) != ID || (!isTheIntCorrect((*client)->id)))//Checking the ID
		(*client)->error.id = 1;
	if(!isTheStringCorrect((*client)->firstName))
		(*client)->error.firstName = 1;//first name check
	if(!isTheStringCorrect((*client)->lastName))
		(*client)->error.lastName = 1;//last name check
	if(!isTheIntCorrect((*client)->phone))
		(*client)->error.phone = 1;
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
	if (strlen((*client)->phone) != PHONE) (*client)->error.phone = 1;
	if ((*client)->error.id || (*client)->error.firstName || (*client)->error.lastName || (*client)->error.phone)
		(*client)->error.ERROR = 1;
}