/////////////////////////////////////////////////////////////////
//    Created by Mikaela Smit on 07/11/2014.				   //	
//    These event are added to the EventQ.					   //
/////////////////////////////////////////////////////////////////

#include <stdio.h>
#include "person.h"
using namespace std;


	//// --- Life Events ---
	void EventMyDeathDate(person *MyPointerToPerson);
	void EventTellAgeCohort(person *MyPointerToPerson);

	
	//// --- Birth ---
	void EventBirth(person *MyPointerToPerson);
	void EventTellBirthByAge(person *MyPointerToPerson);

	//// --- New Year ---
	void EventTellNewYear(person *MyPointerToPerson);					// THINK ABOUT DOING DIFFERENT TYPES OF EVENTS!!!!


	//// --- HIV Events --- 
	//double GetDateOfHIVInfection(int x, int y);							// Function to get date of HIV infection
	//void EventMyHivStatus(person *MyPointerToPerson);					// Function to be executed when HIV infection occurs
