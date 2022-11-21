
#include "HeaderProject.h"
#include "HeaderTest.h"
#include "HeaderDelet.h"
#include "HeaderPrintingManager.h"

int isNum(char ch) {
	if (ch >= '0' && ch <= '9')
		return 1;
	return 0;
}

int isInt(char* num) {//Checking the correctness of the int in the string
	if (!num) return 0;
	size_t length = strlen(num);
	for (int i = 0; i < length; i++)
		if (!isNum(num[i]))
			return 0;
	return 1;
}

int isFloat(char* num) {//Checking the correctness of the float in the string
	if (!num) return 0;
	size_t length = strlen(num);
	for (int i = 0; i < length; i++)
		if ((num[i] != '.') && (!isNum(num[i])))
			return 0;
	return 1;
}

int isNegativeFloat(char* num) {
	if (*num == '-')
		return isFloat(num + sizeof(char));
	else
		return isFloat(num);
}

int isNegativeInt(char* num) {
	if (*num == '-')
		return isInt(num + sizeof(char));
	else
		return isInt(num);
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

float stringConversionToFloat(char* strDebt) {
	float debt1 = 100 * (float)atof(strDebt);
	int debt2 = (int)debt1;//Multiply the debt by one hundred
	return debt2 / (float)100;//Returning the debt with two decimal digits
}
