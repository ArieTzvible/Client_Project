#pragma once

#ifndef Header
#define Header

#define _CRT_SECURE_NO_WARNINGS
#define _CRTDBG_MAP_ALLOC
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <crtdbg.h>

#define FILE_NAME ".csv"
#define FILE_NAME_EXTENSION ".csv"// ending
#define ID 9//Maximum digits in ID.
#define PHONE 10//Maximum digits in phon.
#define DAY 31//Maximum days.
#define MONTH 12//Maximum months.
#define MAX_YEAR 2500//Maximum years
#define MIN_YEAR 1000//Minimum years ending

typedef struct Date {//Date structure.
	unsigned int day : 6;
	unsigned int month : 4;
	unsigned int year : 12;
}Date;

typedef struct Error {//Client error checking structure
	unsigned int ERROR : 1;//Checking for errors.
	unsigned int firstName : 1;//Error getting first name.
	unsigned int lastName : 1;//Error getting last name
	unsigned int id : 1;//Error getting ID.
	unsigned int phone : 1;//Error getting phone.
	unsigned int date : 1;//Error getting date.
	unsigned int debt : 1;//Error getting debt.
	unsigned int lacksValues : 1;//Missing values error.  
	unsigned int comparisonFirstName : 1;//Error first name does not match ID.
	unsigned int comparisonLastName : 1;//Error last name does not match ID.
}Error;

typedef struct Client {//Client structure.
	char* firstName;
	char* lastName;
	char* id;
	char* phone;
	struct Client* next;//A place to receive the next cell
	float debt;
	Date date;
	Error error;//Errors by error structure
}Client, *PClient;

typedef struct List {//List manager structure
	PClient head;//The head list 
	PClient headError;//The head errors list
}List, *ListManager;

void addToHeadTheList(PClient* head, PClient newCell);//add to the top of the list
void addingASortedCustomerToTheList(PClient* head, PClient newCell);//Sorting and adding to the list

ListManager createANewListManager();//Creating a new manager structure
PClient initializeErrorsinAnewCell();//Creating a structure of a new client

#endif