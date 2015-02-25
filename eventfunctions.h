/////////////////////////////////////////////////////////////////
//    Created by Mikaela Smit on 07/11/2014.				   //	
//    Copyright (c) 2014 Mikaela Smit. All rights reserved.    //
//    These event are added to the EventQ.					   //
/////////////////////////////////////////////////////////////////

#include <stdio.h>
#include "person.h"
using namespace std;


	//// --- Get Birth of First Child ---
	//void GetDateOfMyFirstBaby (person *MyPointerToPerson);

	//// --- HIV Events --- 
	double GetDateOfHIVInfection(int x, int y);							// Function to get date of HIV infection
	void EventMyHivStatus(person *MyPointerToPerson);					// Function to be executed when HIV infection occurs
	
	//// --- Life Events ---
	void EventMyDeathDate(person *MyPointerToPerson);

	
	//// --- Birth ---
	void EventBirth(person *MyPointerToPerson);
	void EventStopBreastfeeding(person *MyPointerToPerson);
	void EventBirthForTheYear(person *MyPointerToPerson);

	//// --- New Year ---
	void EventTellNewYear(person *MyPointerToPerson);					// THINK ABOUT DOING DIFFERENT TYPES OF EVENTS!!!!





	
	/////////////////  OLDER CODE AND FUNCITONS ///////////////////

	//void EventMyBirthDate(person *MyPointerToPerson);
