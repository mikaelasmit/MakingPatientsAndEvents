/////////////////////////////////////////////////////////////////
//    Created by Mikaela Smit on 07/11/2014.				   //
//    Copyright (c) 2014 Mikaela Smit. All rights reserved.    //
//    These event are added to the EventQ.					   //
/////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <ctime>
#include "eventfunctions.h"
#include "event.h"														// Need to add these to be able to	
#include "eventQ.h"														// [...]run Global Time and Recurrent events pointers
#include "person.h"
using namespace std;


//// --- OUTSIDE INFORMATION --- ////
extern double *p_GT;													// Tell this .cpp that there is pointer to Global Time defined externally
extern priority_queue<event*, vector<event*>, timeComparison> *p_PQ;	// Tell this .cpp that there is a priorty_queue externall and define pointer to it

extern int final_number_people;											// To determine the final size of the total population to be modeled 
extern int init_pop;
extern int total_population;											// Update total population for output and for next new entry
extern double new_entry;	
extern person** MyArrayOfPointersToPeople;

extern void MakeNewPerson();
extern void MakeNewPersonID();
extern void MakeNewGenderDistribution();
extern void MakeNewYearOfBirth();
extern void MakeNewBirthdayM();



//// --- FUNCTIONS FOR EVENTS --- ////


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
	
	total_population=total_population+1;						// Update total population for output and for next new entry

	MyArrayOfPointersToPeople[total_population]=new person();
	(MyArrayOfPointersToPeople[total_population])->PersonIDAssign(total_population);
	(MyArrayOfPointersToPeople[total_population])->Alive=1;
	(MyArrayOfPointersToPeople[total_population])->GenderDistribution();
	(MyArrayOfPointersToPeople[total_population])->GetMyYearOfBirthNewEntry();
	//(MyArrayOfPointersToPeople[total_population])->GetDateOfDeath(18,80);
	//(MyArrayOfPointersToPeople[total_population])->GetDateOfHIVInfection(1,2);
	
	// Link Mother and Child
	(MyArrayOfPointersToPeople[total_population])->MotherID=MyPointerToPerson->PersonID;
	MyPointerToPerson->ChildID=(MyArrayOfPointersToPeople[total_population])->PersonID;


	
	cout << "Person " << MyPointerToPerson->PersonID << " has just been created and is " << MyPointerToPerson->Age << " years old.  " << endl;
	cout << "The total populaiton is " << total_population << endl;
}


