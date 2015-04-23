﻿////////////////////////////////////////////////////////////////
//    Mikaela Epidemiology Model							  //
//    Created by Mikaela Smit on 7/11/2014.				      //
//    Copyright (c) 2014 Mikaela Smit. All rights reserved.   //
////////////////////////////////////////////////////////////////


#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "person.h"
#include <ctime>
#include "event.h"
#include "eventQ.h"
#include "eventfunctions.h"
#include "coutmacro.h"
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

//    To Do List:
//  1.	Making a population (i.e. more than one person) and assign variables (Person ID, Sex, HIV status, Birthday, Date of Death,�) - DONE
//  2.	Use simple distributions (e.g. uniform distribution, etc) to assign characteristics - DONE
//  3.	Develop EventQ and play around with it � DONE
//  4.	Insert events into the EventQ, e.g. HIV-infection, Death and Birthdays � DONE
//  5.	Separate EventQ code into different .h and .cpp files � TOOK A WHILE BUT DONE
//  6.	Insert a global time counter into the model to record time � DONE
//  7.	Add global time to the EventQ � DONE
//  8.	Make birthdays into recurrent event using pointers and global time  - DONE
//  9.	Remove repeat code for EventQ and from main() and make into self-contained loop � DONE
//  10.	Add stop time into the model for EventQ � DONE
//  11.	Merge MakingPatients and EventQ code to make events happen to two different people � DONE
//  12.	Give people an age using birthday and vice versa � DONE
//  13.	Include Age at T0 to record age at start of model � DONE
//  14.	Add ages to the EventQ and update every year � DONE
//  15.	Make C++ output .csv  files to be able to run large populations and generate graphs � DONE
//  16.	Find Kanyan age-distribution in 1950 - DONE
//  17.	Add Kenyan age-distribution as per 1950s � DONE
//  18.	Run model with this age distribution and generate population pyramids � DONE
//  19. Add new entries to run population forward and simulate population growth - DONE 
//  20.	Link deaths to age using UN data - DONE
//  21.	Compare population to data in Kenya, improve as necessary - BUSY WITH
//  22.	Improve 'new entry' as expandable vector (deal with bigger population size) - DONE
//  23. Improve code with arrays (e.g. death code and ChildID) - DONE
//
//	STILL TO DO:
//	1. Expand model from 1950 to 2010!!!
//  2. Change population to expandable vector
//  3. Check that the Event Q is is not unnecessarily getting clogged up and slowing down model
//  4. Write code to empty Event Q after every model run
//  5. Write code to optain ChildID from vector or pointer to person class!!
//  6.	Add HIV status and update it as a function of HIV test 
//  7.	Add more aspects of HIV care cascade (diagnosis, start cART,�)
//  8. Think about class destructors
//  9.	Make C++ run with Matlab � THIS IS TAKING A WHILE AND I AM STILL BUSY WITH THIS.  I am going to look at SJ�s code for this



//// --- Function related to event - to be available externally ---
double *p_GT;																// Pointer to global time
// REMOVE - double *p_SY;																// Pointer to start year of the model
double StartYear=1950;													// Define Start Year if the model and set it to year of choice
int *p_FF;																	// This is the fraction of the total female population that will be given the higher birth rate
priority_queue<event*, vector<event*>, timeComparison> *p_PQ;				// Pointer to event queue so as to be able to push-in/pop-out new events that are ocurreing
int *p_PY;																	// [...] as a result of 'primary' events in the queue, e.g. recurrent birthdays

//// --- Functions from outside --- ////
extern int *p_CFP;															// 
//extern int *p_PY;

//// --- Function relating to New Entry - to be available externally ---
const int final_number_people=100000;										// To determine the final size of the total population to be modeled 
int init_pop =5910;															// Initial population 1st Jan 1950 as 5910 (see Excel for calculation)
int total_population=init_pop;												// Update total population for output and for next new entry
int Female_pop = 0;															// Variable to count how many women are in the population - will be used to count female pop by GlobalTime for fertility TFR	
int Female_fraction = 0;
int PY=0;
person** MyArrayOfPointersToPeople = new person*[final_number_people];		// First 'person*' is a pointer (address) and 'new person' and space for x person which will point to actual person below
																			// Have to now change [init_pop] to [final_number_people] to give the final size of 'matrix'

//// --- EXTERNAL STUFF ---
extern double BirthCohortArray;
//// --- RUN THE MAIN MODEL ---
int main(){

	cout << "Hello, Mikaela!" << endl << endl ;								// Check if model is running
	D(cout << "The Macro is working" << endl);
	if (StartYear > 1954){
		cout << "Remeber that fertility at the beginning is based on a TRF_init of 0, based on GlobalTime being between 1950 and 1954" << endl;
	}


	//// --- Some pointers ---
	double GlobalTime=StartYear;											// Define Global Time and set it to 0 at the beginning of the model
	p_GT=&GlobalTime;														// Define the location the pointer to Global time is pointing to
	// REMOVE : p_SY=&StartYear;														// Define the location of the pointer to Start Year is pointing to
	srand(time(NULL));														// Random Number generator using PC time
	priority_queue<event*, vector<event*>, timeComparison> iQ;				// Define th ePriority Q
	p_PQ=&iQ;																// Define pointer to event Q
	p_PY=&PY;
	
	//// --- Making Population---
	for(int i=0; i<final_number_people; i++){								// REMEMBER: this needs to stay "final_number_people" or it will give error with CSV FILES!!!!
		MyArrayOfPointersToPeople[i]=new person();
	}							// The 'new person' the actual new person
	
	cout << "We got to section 1" << endl ;

	//// --- Assign Population Characteristics ---
	for(int i=0; i<total_population; i++){									// --- Assign PersonID ---
		int a=i;
		(MyArrayOfPointersToPeople[i])->PersonIDAssign(a);
	}

	cout << "We got to section 2" << endl ;

	for(int i=0; i<total_population; i++){									// --- Assign PersonID ---
		(MyArrayOfPointersToPeople[i])->Alive=1;
	}

	cout << "We got to section 3" << endl ;

	for(int i=0; i<total_population; i++){									// --- Assign Sex- ---
		(MyArrayOfPointersToPeople[i])->GenderDistribution();
	}

	cout << "We got to section 4" << endl;
	
	for (int i = 0; i < total_population; i++){
		if (MyArrayOfPointersToPeople[i]->Sex == 2){
			Female_pop++;
		};
	}

	D(cout << "Female population in " << *p_GT << " is " << Female_pop << endl;);
	double tt=0.48;
	D(cout << " TRF fraction: " << tt << endl;);
	Female_fraction = (Female_pop * tt);
	cout << "Female fraction: " << Female_fraction << endl;
	p_FF = &Female_fraction;


	cout << "We got to section 5" << endl;

	for(int i=0; i<total_population; i++){									// --- Assign DoB/Age --- 
		(MyArrayOfPointersToPeople[i])->GetMyDoB();
	}

	cout << "We got to section 6" << endl ;	

	int s = 0;
	p_CFP = &s;
	for (int i = 0; i < total_population; i++){									// --- Assign Birth of First Baby- ---
		if (MyArrayOfPointersToPeople[i]->Sex == 2) { (MyArrayOfPointersToPeople[i])->GetDateOfBaby(); s++; D(cout << "S: " << s << endl;); }
	}

	cout << "We got to section 7" << endl ;
	for(int i=0; i<total_population; i++){									// --- Assign date of death ---  
		(MyArrayOfPointersToPeople[i])->GetDateOfDeath();
	}
	cout << "We got to section 8" << endl ;
		//for(int i=0; i<total_population; i++){									// --- Assign Date of HIV
	//	(MyArrayOfPointersToPeople[i])->GetDateOfHIVInfection(1,2);}
	//cout << "We got to section 8" << endl ;
	D(cout << "We got to Stage 2 of the model " << endl << endl);			// Check for model run

	//// --- OUTPUT CHECKs --- 
	D(cout << endl << "The person profile...." << endl;					// --- Ouput all the peoples' IDs ---
	for(int i=0; i<init_pop; i++){
		(MyArrayOfPointersToPeople[i])->TellMyPerson();
	}	;)

	
	cout << "We got to section 9" << endl ;	
	//// --- EVENTQ ---
	for (int i = 0; i < total_population; i++){
		if (MyArrayOfPointersToPeople[i]->Alive == 1 && MyArrayOfPointersToPeople[i]->Sex == 2  && MyArrayOfPointersToPeople[i]->BirthChild.size()>0){
			int size = MyArrayOfPointersToPeople[i]->BirthChild.size();
			int index = 0;
			D(cout << "I will have " << size << " children and my age is: " << MyArrayOfPointersToPeople[i]->Age << endl;);
			while (index < size){
				D(cout << "The birth of my next child is: " << MyArrayOfPointersToPeople[i]->BirthChild.at(index) << " and index: " << index << endl;);
				if (MyArrayOfPointersToPeople[i]->BirthChild.at(index) >= *p_GT){
					event * BabyBirth = new event;												// --- Birthday of First Child ---
					BabyBirth->time = MyArrayOfPointersToPeople[i]->BirthChild.at(index);
					BabyBirth->p_fun = &EventBirth;
					BabyBirth->person_ID = MyArrayOfPointersToPeople[i];
					iQ.push(BabyBirth);
					D(cout << "We have just fed the birth into the EventQ" << endl;);
				}
				index++;
			}
		};
	}


	for(int i=0; i<total_population; i++){
	if(MyArrayOfPointersToPeople[i]->Alive==1){
	event * DeathEvent = new event;												// --- Include death into the Event Q  ---
	DeathEvent->time = MyArrayOfPointersToPeople[i]->DateOfDeath;													
	DeathEvent->p_fun = &EventMyDeathDate;
	DeathEvent->person_ID = MyArrayOfPointersToPeople[i];
	iQ.push(DeathEvent);}};

	
	event * TellNewYear = new event;											// --- Tell me every time  a new year start ---
	TellNewYear->time = StartYear;													// THINK ABOUT DOING DIFFERENT TYPES OF EVENTS!!!!					
	TellNewYear->p_fun = &EventTellNewYear;
	iQ.push(TellNewYear);


	event * TellBirthByAge = new event;											// --- For output of array on birth by age cohort ---
	TellBirthByAge->time = 1950.5;												// THINK ABOUT DOING DIFFERENT TYPES OF EVENTS!!!!					
	TellBirthByAge->p_fun = &EventTellBirthByAge;								// Being ALIVE here doesn't matter as its quantified when give birth and checks there if alive
	iQ.push(TellBirthByAge);

	
	event * TellAgeCohort = new event;											// --- For output of array on age categories of cohort ---
	TellAgeCohort->time = 1950.5;												// THINK ABOUT DOING DIFFERENT TYPES OF EVENTS!!!!					
	TellAgeCohort->p_fun = &EventTellAgeCohort;
	iQ.push(TellAgeCohort);

	

		
	////// --- GIVE OUTPUT OF QUEUE AS IT HAPPENS --- ////
	cout << endl << endl << "The characteristics of the event queue:" << endl;
	cout << "the first event will ocurr in " << iQ.top()->time << ".  " << endl;
	cout << "the size of the event queue is " << iQ.size() << endl;
	
	while(iQ.top()->time< 1951 /*|| !iQ.empty()*/){							// this loop throws up error because no recurrent birthday pushing gt over 5 yrs and iq.pop means gt cannot be updated after pop
		GlobalTime=iQ.top()->time;

		//cout << endl << endl << "An event has just ocurred.  " << endl;
		//cout << "it is " << iQ.top()->time << ".  " << endl;
		//if (iQ.top()->person_ID->Age==1)
						iQ.top()-> p_fun(iQ.top()->person_ID);
				
		
		//globaltime=iq.top()->time;										// careful with order of global time update - do not touch or touch and check!!
		
		iQ.pop();		
		//cout << endl << "this event has now been removed from the queue.  " << endl;
	} 


	//// --- Output the results in a csv file ---
	FILE* csv_out = fopen("test.csv","w");
	for (int i=0; i<total_population; i++) {								// Change the i< X here as well as the "%d!!
		fprintf(csv_out,"%d,%d,%f,%f,%d,%d, %f, %d \n",
			MyArrayOfPointersToPeople[i]->PersonID,
			MyArrayOfPointersToPeople[i]->Sex,
			MyArrayOfPointersToPeople[i]->DoB,
			MyArrayOfPointersToPeople[i]->Age,
			MyArrayOfPointersToPeople[i]->MotherID,
			MyArrayOfPointersToPeople[i]->ChildIndex,
			MyArrayOfPointersToPeople[i]->DateOfDeath,
			MyArrayOfPointersToPeople[i]->AgeAtDeath

			//MyArrayOfPointersToPeople[i]->DateOfDeath/*,
			//MyArrayOfPointersToPeople[i]->MyDateOfHIV*/
			);}
	fclose(csv_out);

		
	// Iq!!!!
	// --- End of code ---
    cout << endl << "Hi Jack, so sorry\n";
	system("pause");
    return 0;
}


