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
#include "coutmacro.h"
#include "errorcoutmacro.h"
#include "demographmacro.h"

using namespace std;


//// --- OUTSIDE INFORMATION --- ////
extern double *p_GT;													// Tell this .cpp that there is pointer to Global Time defined externally
extern priority_queue<event*, vector<event*>, timeComparison> *p_PQ;	// Tell this .cpp that there is a priorty_queue externall and define pointer to it
extern int total_population;											// Update total population for output and for next new entry
extern person** MyArrayOfPointersToPeople;								// Pointer to MyArrayOfPointersToPeople
extern int *p_PY;														// Pointer to show which year range we are on
extern vector<event*> Events;


//////////////////////////////////////
//// --- FUNCTIONS FOR EVENTS --- ////
//////////////////////////////////////

//// --- NEW YEAR FUNCTION --- ////
void EventTellNewYear(person *MyPointerToPerson){						
																		
	cout << "A new year has started, it is now " << *p_GT << endl;		// This whole function to output every time a new year starts - to make sure the model is actually running
	
	// Lets get the pointer to the right year range
	if (*p_GT<1955){*p_PY = 0; };										 
	if (*p_GT >= 1955 && *p_GT<1960){*p_PY = 1; };
	if (*p_GT >= 1960 && *p_GT<1965){*p_PY = 2; };
	if (*p_GT >= 1965 && *p_GT<1970){*p_PY = 3; };
	if (*p_GT >= 1970 && *p_GT<1975){*p_PY = 4; };
	if (*p_GT >= 1975 && *p_GT<1980){*p_PY = 5; };
	if (*p_GT >= 1980 && *p_GT<1985){*p_PY = 6; };
	if (*p_GT >= 1985 && *p_GT<1990){*p_PY = 7; };
	if (*p_GT >= 1990 && *p_GT<1995){*p_PY = 8; };
	if (*p_GT >= 1995 && *p_GT<2000){*p_PY = 9; };
	if (*p_GT >= 2000 && *p_GT<2005){*p_PY = 10;};
	if (*p_GT >= 2005){*p_PY = 11; };
	E(cout << "Let's check relevant things have been updated... *p_PY: " << *p_PY << " and Global Time: " << *p_GT << endl;)

	// Schedule event for next year
	event * RecurrentTellNewYear = new event;	
	Events.push_back(RecurrentTellNewYear);
	RecurrentTellNewYear->time = *p_GT + 1;													
	RecurrentTellNewYear->p_fun = &EventTellNewYear;
	p_PQ->push(RecurrentTellNewYear);

	E(cout << "We have finished telling you the new year and setting fertility variables for the year." << endl;)		 
}


//// --- DEATH EVENT --- ////	
void EventMyDeathDate(person *MyPointerToPerson){						
	MyPointerToPerson->Alive=0;
	E(cout << "Person " << MyPointerToPerson->PersonID << " just died. Their life status now is: " << MyPointerToPerson->Alive << endl;)
}


//// --- BIRTH EVENT AND MAKING NEW PERSON --- ////
void EventBirth(person *MyPointerToPerson){								

	E(cout << "A birth is about to happen and my life status: " << endl;)
	
	if(MyPointerToPerson->Alive == 1) {										// Only let woman give birth if she is still alive 
	
		total_population=total_population+1;								// Update total population for output and for next new entry
		MyPointerToPerson->Age= (*p_GT - MyPointerToPerson->DoB);			// Update age to get age at birth for output


		// Creating a new person 
		MyArrayOfPointersToPeople[total_population-1]=new person();			
		(MyArrayOfPointersToPeople[total_population-1])->PersonIDAssign(total_population-1);
		(MyArrayOfPointersToPeople[total_population-1])->Alive=1;
		(MyArrayOfPointersToPeople[total_population-1])->GenderDistribution();
		(MyArrayOfPointersToPeople[total_population-1])->GetMyDoBNewEntry();
		(MyArrayOfPointersToPeople[total_population-1])->GetDateOfDeath();
		(MyArrayOfPointersToPeople[total_population-1])->GetDateOfBaby();

	
		// Include death of baby into Event Q
		event * DeathEvent = new event;										
		Events.push_back(DeathEvent);
		DeathEvent->time = MyArrayOfPointersToPeople[total_population-1]->DateOfDeath;													
		DeathEvent->p_fun = &EventMyDeathDate;								
		DeathEvent->person_ID = MyArrayOfPointersToPeople[total_population-1];				// NOTE: next line related to '->person_ID' is asking for ArrayPointer[nr] not Person ID, i.e its looking for pointer to person not identity	
		p_PQ->push(DeathEvent);
		E(cout << "We have just fed the baby's death into the EventQ" << endl;);


		// Include future births of this new baby that has just been created into EventQ
		int NrChildren=MyArrayOfPointersToPeople[total_population-1]->DatesBirth.size();	// Find number of children woman will have 
		for (int i = 0; i < NrChildren; i++){												// Add each of babies a woman will have to the EventQ
			if (MyArrayOfPointersToPeople[total_population-1]->DatesBirth.at(i) >= *p_GT){	// Only add the ones that are in future to EventQ
				event * BabyBirth = new event;												
				Events.push_back(BabyBirth);
				BabyBirth->time = MyArrayOfPointersToPeople[total_population-1]->DatesBirth.at(i);
				BabyBirth->p_fun = &EventBirth;
				BabyBirth->person_ID = MyArrayOfPointersToPeople[total_population-1];
				p_PQ->push(BabyBirth);
				E(cout << "We have just fed the birth of the babies into the EventQ" << endl;);
				}
		}
	

		// Link Mother and Child
		(MyArrayOfPointersToPeople[total_population-1])->MotherID=MyPointerToPerson->PersonID;			// Give child their mothers ID
		MyPointerToPerson->ChildIDVector.push_back((MyArrayOfPointersToPeople[total_population-1]));	// Give mothers their child's ID
			
		E(cout << "We have finished giving birth " << endl;)
	
	}
}

	








