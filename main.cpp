﻿////////////////////////////////////////////////////////////////
//    Mikaela Epidemiology Model							  //
//    Created by Mikaela Smit on 7/11/2014.				      //
//    Copyright (c) 2014 Mikaela Smit. All rights reserved.   //
////////////////////////////////////////////////////////////////


#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <ctime>
#include "person.h"
#include "event.h"
#include "eventQ.h"
#include "eventfunctions.h"
#include "coutmacro.h"
#include "errorcoutmacro.h"
#include "demographmacro.h"

using namespace std;   

// TO FIX - FERTILITY
// 1. TRF at the moment is based on DoB - check if it represents fertility correctly - see eventfunction.cpp line ~113
// 2. Have to fix fertility array - atm not enough old women giving birth
// 3. Have to redo code for fertility (array) to make 49 years old=1 and not 50=1 to avoid 50 year old giving births!!
// 4. Rerun the model check from 1950-2010 to see if fertility correct now


// TO FIX GENERAL
// 1. Throw output out every 5 years - need to reset every 5 years - DONE
// 2. Change population to vector instead of array
// 3. When person dies, remove all related events
// 4. Make various event types (people/annual,...)
// 5. Use 'const' in model to stop model from changing variables thta it shouldn't change
// 6. Learn how to add a row to a vector (e.g every year it should add a new line for new year of output...
// 7. Remove all unecessary code
// 8. Turn bins into text files to make it easier to check what its doing!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

//  To Do List:
//	1. Expand model from 1950 to 2010!!!
//  2. Change population to expandable vector
//  3. Check that the Event Q is is not unnecessarily getting clogged up and slowing down model
//  4. Write code to empty Event Q after every model run
//  5. Write code to optain ChildID from vector or pointer to person class!!
//  6. Add HIV status and update it as a function of HIV test
//  7. Add more aspects of HIV care cascade (diagnosis, start cART,�)
//  8. Think about class destructors
//  9. Make C++ run with Matlab � THIS IS TAKING A WHILE AND I AM STILL BUSY WITH THIS.  I am going to look at SJ�s code for this



//// --- Function related to events - to be available externally ---
double *p_GT;																// Pointer to global time
int *p_PY;																	// Pointer to show which year range we are on
int PY=0;																	// Set the first pointer to year range reference to 0
double StartYear=1950;														// Define Start Year if the model and set it to year of choice
int EndYear=2010;															// If endyear is more than 2010, some things will need to get changes, an error message below has been set up as reminder


const int final_number_people=100000000;										// To determine the final size of the total population to be modeled
int init_pop =5910;															// Initial population 1st Jan 1950 as 5910 (see Excel for calculation)
int total_population=init_pop;												// Update total population for output and for next new entry

priority_queue<event*, vector<event*>, timeComparison> *p_PQ;				// Pointer to event queue so as to be able to push-in/pop-out new events that are ocurreing  as a result of 'primary' events in the queue, e.g. recurrent birthdays
person** MyArrayOfPointersToPeople = new person*[final_number_people];		// First 'person*' is a pointer (address) and 'new person' and space for x person which will point to actual person below

vector<event *> Events;														// vector<class*>name


// Have to now change [init_pop] to [final_number_people] to give the final size of 'matrix'


//// --- RUN THE MAIN MODEL ---
int main(){
	cout << "Hello, Mikaela!" << endl << endl ;	// Check if model is running
	

	//// Load relevant parameters
	cout << "Loading all parameter arrays" << endl;
	//loadBirthArray();
	//loadDeathArray_Women();
	//loadDeathArray_Men();
	cout << "Done, arrays are loaded!" << endl;


	//// Some notification code
	D(cout << "NOTE: The Debug Macro is working" << endl << endl;);
	E(cout << "NOTE: The Macro for error code is working" << endl << endl;)
	if (StartYear > 1954){cout << "NOTE: Remeber that fertility at the beginning is based on a TRF_init of 0, based on GlobalTime being between 1950 and 1954" << endl << endl;}
	if (EndYear > 2010){cout << "NOTE: The model runs after 2010 and output things need to be updated to avoid errors" << endl << endl;}

	
	//// --- Some pointers ---
	double GlobalTime=StartYear;											// Define Global Time and set it to 0 at the beginning of the model
	p_GT=&GlobalTime;														// Define the location the pointer to Global time is pointing to
	srand(time(NULL));														// Random Number generator using PC time
	priority_queue<event*, vector<event*>, timeComparison> iQ;				// Define th ePriority Q
	p_PQ=&iQ;																// Define pointer to event Q
	p_PY=&PY;
	
	
	//// --- Making Population---
	cout << "We got to section 1 - We are going to create a population" << endl;
	for(int i=0; i<total_population; i++){								// REMEMBER: this needs to stay "final_number_people" or it will give error with CSV FILES!!!!
		MyArrayOfPointersToPeople[i]=new person();						// The 'new person' the actual new person
		int a=i;
		(MyArrayOfPointersToPeople[i])->PersonIDAssign(a);				// --- Assign PersonID ---
	}
	
	for(int i=0; i<total_population; i++){
		(MyArrayOfPointersToPeople[i])->Alive=1;							// --- Assign Life Status ---

		(MyArrayOfPointersToPeople[i])->GenderDistribution();				// --- Assign Sex- ---

		(MyArrayOfPointersToPeople[i])->GetMyDoB();							// --- Assign DoB/Age ---

		(MyArrayOfPointersToPeople[i])->GetDateOfDeath();					// --- Assign date of death --- 

		if (MyArrayOfPointersToPeople[i]->Sex == 2 && MyArrayOfPointersToPeople[i]->Age<50 && MyArrayOfPointersToPeople[i]->AgeAtDeath>=15) {(MyArrayOfPointersToPeople[i])->GetDateOfBaby();}		// --- Assign Birth of all Children- ---
	}

	
	////// --- EVENTQ ---
	cout << "We got to section 2 - We finished crating a population" << endl;

	// Lets feed in calendar update
	event * TellNewYear = new event;											// --- Tell me every time  a new year start ---
	Events.push_back(TellNewYear);
	TellNewYear->time = StartYear;													// THINK ABOUT DOING DIFFERENT TYPES OF EVENTS!!!!					
	TellNewYear->p_fun = &EventTellNewYear;
	iQ.push(TellNewYear);
	
	
	////// --- GIVE OUTPUT OF QUEUE AS IT HAPPENS --- ////
	cout << "We got to section 4 - Lets run the EventQ" << endl;
	cout << endl << endl << "The characteristics of the event queue:" << endl;
	cout << "the first event will ocurr in " << iQ.top()->time << ".  " << endl;
	cout << "the size of the event queue is " << iQ.size() << endl;
	

	while(iQ.top()->time< EndYear+1/*|| !iQ.empty()*/){							// this loop throws up error because no recurrent birthday pushing gt over 5 yrs and iq.pop means gt cannot be updated after pop
		GlobalTime=iQ.top()->time;											// careful with order of global time update - do not touch or touch and check!!		
		iQ.top()-> p_fun(iQ.top()->person_ID);
		iQ.pop();		
	} 
	

	// --- Output the results in a csv file ---
	cout << "We got to section 5 - Lets create a csv file with the results" << endl;
	FILE* csv_out = fopen("test.csv","w");
	for (int i=0; i<total_population; i++) {								// Change the i< X here as well as the "%d!!
		fprintf(csv_out,"%d,%d,%f,%f,%d,%d, %f, %d \n",
			MyArrayOfPointersToPeople[i]->PersonID,
			MyArrayOfPointersToPeople[i]->Sex,
			MyArrayOfPointersToPeople[i]->DoB,
			MyArrayOfPointersToPeople[i]->Age,
			MyArrayOfPointersToPeople[i]->MotherID,
			MyArrayOfPointersToPeople[i]->DatesBirth.size(),
			MyArrayOfPointersToPeople[i]->DateOfDeath,
			MyArrayOfPointersToPeople[i]->AgeAtDeath		
			
			);}
	fclose(csv_out);

	

	//// --- LETS AVOID MEMORY LEAKS AND DELETE ALL NEW EVENTS --- ////
	cout << "Lets delete the heap! " << endl;
	for(int i=0; i<Events.size()-1; i++){
		E(cout << "Event " << Events.size() << " is " << Events.at(i)->time << endl;)
		delete Events.at(i);
		E(cout << "Event " << Events.size() << " is " << Events.at(i)->time << endl;)
	}

	for(int i=0; i<total_population; i++){								// REMEMBER: this needs to stay "final_number_people" or it will give error with CSV FILES!!!!
		delete MyArrayOfPointersToPeople[i];								// The 'new person' the actual new person
	}

		
	// --- End of code --- //
    cout << endl << "Hi Jack, so sorry\n";
	system("pause");
    return 0;
}


