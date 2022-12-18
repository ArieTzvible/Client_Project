
#include "HeaderUtilities.h"

void addToHeadTheList(PClient* head, PClient newCell)
{
	newCell->next = *head;
	*head = newCell;
}

/*A function for sortingand adding to the list*/
void addingASortedCustomerToTheList(PClient* head, PClient newCell) 
	{
	if (!newCell) return;

	if (*head == NULL || newCell->debt <= (*head)->debt) //Checking whether the first cell is empty
	{
		newCell->next = *head;//Bringing the customer to the top of the list
		*head = newCell;//Moving the pointer to the top of the list
		return;
	}

	PClient temp = *head;//Declare a pointer to the first cell in the list

	while (temp)
	{
		/*Test A. End of list B. A debt smaller than the current debt*/
		if ((!temp->next) || (newCell->debt <= temp->next->debt)) 
		{
			newCell->next = temp->next;//Bringing the client to the current location
			temp->next = newCell;//Getting the next client on the list
			return;
		}

		temp = temp->next;//Move the pointer to the next cell
	}
}

ListManager createANewListManager() //creating a manager structure
{
	ListManager temp = (ListManager)malloc(sizeof(List));//creating a new structure
	
	if (temp == NULL)
		printf("Not enough memory\n");//print error;//Error printing when there is no space in memory
	
	else 
	{
		temp->head = NULL;//statement to the top of the list
		temp->headError = NULL;//statement to the top of the errors list 
	}

	return temp;//returning the structure
}

PClient initializeErrorsinAnewCell() //initialize a new client structure
	{
	PClient newClient = (PClient)malloc(sizeof(Client));//Declaration and creation of a new structure
	
	if (!newClient)
	{
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
	newClient->error.id = 0;//. Error in ID
	newClient->error.phone = 0;//Error on phone
	newClient->error.date = 0;//Error in date
	newClient->error.debt = 0;//Error in debt
	newClient->error.comparisonFirstName = 0;//record T.Z. Does not match first name
	newClient->error.comparisonLastName = 0;//Error ID Does not match last name
	newClient->error.lacksValues = 0;//Error Not enough values

	return newClient;
}
