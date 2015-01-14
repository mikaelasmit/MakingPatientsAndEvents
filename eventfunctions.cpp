//
//  Created by Mikaela Smit on 07/11/2014.
//  Copyright (c) 2014 Mikaela Smit. All rights reserved.
//  These event are added to the EventQ
//

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include "eventfunctions.h"
#include "event.h"														// Need to add these to be able to	
#include "eventQ.h"														// [...]run Global Time and Recurrent events pointers
#include "person.h"
using namespace std;


//// --- Outside Information ---
extern double *p_GT;													// Tell this .cpp that there is pointer to Global Time defined externally
extern priority_queue<event*, vector<event*>, timeComparison> *p_PQ;	// Tell this .cpp that there is a priorty_queue externall and define pointer to it

extern int final_number_people;											// To determine the final size of the total population to be modeled 
extern int init_pop;
extern int total_population;											// Update total population for output and for next new entry
extern double new_entry;	

extern void MakeNewPerson();
extern void MakeNewPersonID();
extern void MakeNewGenderDistribution();
extern void MakeNewYearOfBirth();
extern void MakeNewBirthdayM();


//// --- FUNCTIONS FOR EVENTS --- ////
//void GetDateBirthFirstChild(person *MyPointerToPerson){					// Get My First Child's Birthday
//	cout << "The date of the first child of " << MyPointerToPerson->PersonID << " is being determined. " << endl;}

void EventMyHivStatus(person *MyPointerToPerson){						// The bit inside the bracket allows to link event to specific person using person pointer 						
	 cout << "Person " << MyPointerToPerson->PersonID << " just got an HIV test.  " << endl;}


void EventMyDeathDate(person *MyPointerToPerson){									
	 cout << "Person " << MyPointerToPerson->PersonID << " just died.  "  << endl;}


void EventMyBirthDate(person *MyPointerToPerson){									
	
	 event * RecurrentBirthdayDate = new event;							// --- Schedule recurrent Birthday ---
	 RecurrentBirthdayDate->time = *p_GT + 1;							// Re-use code as in main to add recurrent BD to the queue (incl time and function pointer)
	 RecurrentBirthdayDate->p_fun = &EventMyBirthDate;
	 RecurrentBirthdayDate->person_ID=MyPointerToPerson;
	 p_PQ->push(RecurrentBirthdayDate);

	 MyPointerToPerson->Age=MyPointerToPerson->Age+1; 
	 	
	 cout << "Person " << MyPointerToPerson->PersonID << " just had their birthday.  They are now " << MyPointerToPerson->Age << " years old.  " << endl;
	 cout << "Person " << MyPointerToPerson->PersonID << " will have their next birthday on " << *p_GT + 1 << ".  " << endl;
}




void EventNewEntry(person *MyPointerToPerson){	

	cout << "New person are being created" << endl;
	
	 event * RecurrentNewEntry = new event;								// --- Schedule recurrent New Entry ---
	 RecurrentNewEntry->time = *p_GT + 2;								// Re-use code as in main to add recurrent BD to the queue (incl time and function pointer)
	 RecurrentNewEntry->p_fun = &EventNewEntry;
	 //RecurrentNewEntry->person_ID=MyPointerToPerson;					// CAN I JUST IGNORE THIS??? SEEMS TO WORK?
	 p_PQ->push(RecurrentNewEntry);

		
	//// --- CODE FOR NEW ENTRY (THE SIMPLE WAY!!) --- ////				// This 'if' loop gives the right numbers of birth by calendar time 
	if (*p_GT>=1950 & *p_GT<1955)			{new_entry=35;}			// [...] according to Un data 335
	if (*p_GT>=1955 & *p_GT<1960)			{new_entry=88;}
	if (*p_GT>=1960 & *p_GT<1965)			{new_entry=449;}
	if (*p_GT>=1965 & *p_GT<1970)			{new_entry=525;}
	if (*p_GT>=1970 & *p_GT<1975)			{new_entry=628;}
	if (*p_GT>=1975 & *p_GT<1980)			{new_entry=743;}
	if (*p_GT>=1980 & *p_GT<1985)			{new_entry=869;}
	if (*p_GT>=1985 & *p_GT<1990)			{new_entry=972;}
	if (*p_GT>=1990 & *p_GT<1995)			{new_entry=1006;}
	if (*p_GT>=1995 & *p_GT<2000)			{new_entry=1123;}
	if (*p_GT>=2000 & *p_GT<2005)			{new_entry=1304;}
	if (*p_GT>=2005 & *p_GT<2011)			{new_entry=1455;}

	cout << "The number of new entries is " << new_entry << " and it is " << *p_GT << endl;		// Check to make sure the number of New Entry is correct 

	MakeNewPerson();													// Make new person in the array.  The below functions give them characteristics
	MakeNewPersonID();
	MakeNewGenderDistribution();
	MakeNewYearOfBirth();
	MakeNewBirthdayM();

	 total_population=total_population+new_entry;						// Update total population for output and for next new entry

	 cout << "Person " << MyPointerToPerson->PersonID << " has just been created and is " << MyPointerToPerson->Age << " years old.  " << endl;
	 cout << "The total populaiton is " << total_population << endl;
}


