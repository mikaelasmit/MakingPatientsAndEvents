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
using namespace std;


//// --- OUTSIDE INFORMATION --- ////
extern double *p_GT;													// Tell this .cpp that there is pointer to Global Time defined externally
extern priority_queue<event*, vector<event*>, timeComparison> *p_PQ;	// Tell this .cpp that there is a priorty_queue externall and define pointer to it
extern int total_population;											// Update total population for output and for next new entry
extern person** MyArrayOfPointersToPeople;

double RandomBirthsNewYear(int min, int max){							// Provides function for random number generator to assign first birth for women
	return rand()%(max-min+1)+min;}



//// --- FUNCTIONS FOR EVENTS --- ////
void EventTellNewYear(person *MyPointerToPerson){						//// --- NEW YEAR FUNCTION --- ////
																		
	cout << " A new year has started, it is now " << *p_GT << endl;		// This whole function to output every time a new year starts - to make sure the model is actually running

	event * RecurrentTellNewYear = new event;											
	RecurrentTellNewYear->time = *p_GT + 1;													
	RecurrentTellNewYear->p_fun = &EventTellNewYear;
	p_PQ->push(RecurrentTellNewYear);
}



void EventMyDeathDate(person *MyPointerToPerson){						//// --- DEATH EVENT --- ////					
	 D(cout << "Person " << MyPointerToPerson->PersonID << " just died.  "  << endl;);}


void EventBirth(person *MyPointerToPerson){								//// --- BIRTH EVENT AND MAKING NEW PERSON --- ////

	if (MyPointerToPerson->Alive==1 && MyPointerToPerson->BirthChild<9999){
	
	total_population=total_population+1;								// Update total population for output and for next new entry
	
	// Creating a new person 
	MyArrayOfPointersToPeople[total_population-1]=new person();			
	(MyArrayOfPointersToPeople[total_population-1])->PersonIDAssign(total_population-1);
	(MyArrayOfPointersToPeople[total_population-1])->Alive=1;
	(MyArrayOfPointersToPeople[total_population-1])->GenderDistribution();
	(MyArrayOfPointersToPeople[total_population-1])->GetMyYearOfBirthNewEntry();
	(MyArrayOfPointersToPeople[total_population-1])->GetDateOfDeath();
	////(MyArrayOfPointersToPeople[total_population-1])->GetDateOfHIVInfection(1,2); 


	// Incldue death of baby into Event Q
	event * DeathEvent = new event;										// --- Include death of new baby into the Event Q  ---
	DeathEvent->time = MyArrayOfPointersToPeople[total_population-1]->DateOfDeath;													
	DeathEvent->p_fun = &EventMyDeathDate;
	DeathEvent->person_ID = MyArrayOfPointersToPeople[total_population-1];
	p_PQ->push(DeathEvent);

	
	// Link Mother and Child
	(MyArrayOfPointersToPeople[total_population-1])->MotherID=MyPointerToPerson->PersonID;			// Give child their mothers ID
	MyPointerToPerson->ChildIDVector.push_back((MyArrayOfPointersToPeople[total_population-1]));	// Give mothers their child's ID
	cout << "The size is " << MyPointerToPerson->ChildIDVector.size() << " and the ID of patient " << MyPointerToPerson->ChildIDVector.at(0) << endl;
	
	
	// Update my child Index (number of children I have) and reset BirthFirst Child so can have another chile
	MyPointerToPerson->ChildIndex=MyPointerToPerson->ChildIndex+1;		// update Child Index so can give birth again
	

	// Scheudle breastfeeding 
	MyPointerToPerson->Breastfeeding=1;
	

	event * BreastfeedingFinish = new event;														// --- Schedule end of Breastfeeding ---
	BreastfeedingFinish->time = *p_GT + 0.25;														// Re-use code as in main to add recurrent BD to the queue (incl time and function pointer)
	BreastfeedingFinish->p_fun = &EventStopBreastfeeding;
	BreastfeedingFinish->person_ID=MyPointerToPerson;
	p_PQ->push(BreastfeedingFinish);
	
	D(cout << "!!!!I, patient " << MyPointerToPerson->PersonID << " have had my " << MyPointerToPerson->ChildIndex << " child" << "and I am now breastfeeding " << MyPointerToPerson->Breastfeeding << endl);
	D(cout << "My child is " << MyPointerToPerson->ChildIDVector.at(MyPointerToPerson->ChildIndex) << endl);
	D(cout << "I, patient " << MyPointerToPerson->PersonID << " have had my " << MyPointerToPerson->ChildIndex << " child who is "  << "and I am now breastfeeding " << MyPointerToPerson->Breastfeeding << endl);

	}}

void EventStopBreastfeeding(person *MyPointerToPerson){
	MyPointerToPerson->Breastfeeding=0;																// Reset breastfeeding status to NOT feeding so woman can have a child
	MyPointerToPerson->BirthChild=9999;														// Reset BirthOfChild so can have another Child
	//cout << "I, " << MyPointerToPerson->PersonID << " have just stopped breastfeeding after having my " << MyPointerToPerson->ChildIndex << " child" << endl;
}
							

void EventBirthForTheYear(person *MyPointerToPerson){												// Set births for the coming year

	//cout << "I, patient number " << MyPointerToPerson->PersonID << "have a fertility status of: " << MyPointerToPerson->BirthFirstChild << " and my age is " << MyPointerToPerson->Age << endl; 

	MyPointerToPerson->Age= (*p_GT - MyPointerToPerson->DoB);

	if (MyPointerToPerson->Sex==2 && MyPointerToPerson->Alive==1 && MyPointerToPerson->BirthChild==9999 && MyPointerToPerson->Age>=15 && MyPointerToPerson->Age<50 && MyPointerToPerson->ChildIndex<10){					// Only set fertily for those not scheduled to give birth this year and those not breastfeeding
			
		double f = ((double) rand() / (RAND_MAX));

		if (MyPointerToPerson->Age>=15 && MyPointerToPerson->Age<20 && f<0.169071){MyPointerToPerson->BirthChild=*p_GT+(RandomBirthsNewYear(MyPointerToPerson->Age*10,200)/10)-MyPointerToPerson->Age;
				while (MyPointerToPerson->BirthChild<*p_GT){MyPointerToPerson->BirthChild=*p_GT+(RandomBirthsNewYear(MyPointerToPerson->Age*10,200)/10)-MyPointerToPerson->Age;}}

		if (MyPointerToPerson->Age>=20 && MyPointerToPerson->Age<25 && f<0.351607){MyPointerToPerson->BirthChild=*p_GT+(RandomBirthsNewYear(MyPointerToPerson->Age*10,250)/10)-MyPointerToPerson->Age;
				while (MyPointerToPerson->BirthChild<1950){MyPointerToPerson->BirthChild=*p_GT+(RandomBirthsNewYear(MyPointerToPerson->Age*10,250)/10)-MyPointerToPerson->Age;}}
		
		if (MyPointerToPerson->Age>=25 && MyPointerToPerson->Age<30 && f<0.338141){MyPointerToPerson->BirthChild=*p_GT+(RandomBirthsNewYear(MyPointerToPerson->Age*10,300)/10)-MyPointerToPerson->Age;
				while (MyPointerToPerson->BirthChild<1950){MyPointerToPerson->BirthChild=*p_GT+(RandomBirthsNewYear(MyPointerToPerson->Age*10,300)/10)-MyPointerToPerson->Age;}}
		
		if (MyPointerToPerson->Age>=30 && MyPointerToPerson->Age<35 && f<0.284278){MyPointerToPerson->BirthChild=*p_GT+(RandomBirthsNewYear(MyPointerToPerson->Age*10,350)/10)-MyPointerToPerson->Age;
				while (MyPointerToPerson->BirthChild<1950){MyPointerToPerson->BirthChild=*p_GT+(RandomBirthsNewYear(MyPointerToPerson->Age*10,350)/10)-MyPointerToPerson->Age;}}

		if (MyPointerToPerson->Age>=35 && MyPointerToPerson->Age<40 && f<0.203483){MyPointerToPerson->BirthChild=*p_GT+(RandomBirthsNewYear(MyPointerToPerson->Age*10,400)/10)-MyPointerToPerson->Age;
				while (MyPointerToPerson->BirthChild<1950){MyPointerToPerson->BirthChild=*p_GT+(RandomBirthsNewYear(MyPointerToPerson->Age*10,400)/10)-MyPointerToPerson->Age;}}

		if (MyPointerToPerson->Age>=40 && MyPointerToPerson->Age<45 && f<0.110719){MyPointerToPerson->BirthChild=*p_GT+(RandomBirthsNewYear(MyPointerToPerson->Age*10,450)/10)-MyPointerToPerson->Age;
				while (MyPointerToPerson->BirthChild<1950){MyPointerToPerson->BirthChild=*p_GT+(RandomBirthsNewYear(MyPointerToPerson->Age*10,450)/10)-MyPointerToPerson->Age;}}

		if (MyPointerToPerson->Age>=45 && MyPointerToPerson->Age<50 && f<0.038901){MyPointerToPerson->BirthChild=*p_GT+(RandomBirthsNewYear(MyPointerToPerson->Age*10,500)/10)-MyPointerToPerson->Age;
				while (MyPointerToPerson->BirthChild<1950){MyPointerToPerson->BirthChild=*p_GT+(RandomBirthsNewYear(MyPointerToPerson->Age*10,500)/10)-MyPointerToPerson->Age;}}
	
			
			if (MyPointerToPerson->BirthChild<9999){
			event * BabyBirth = new event;											// --- Add new births to EventQ ---									
			BabyBirth->time = MyPointerToPerson->BirthChild;
			BabyBirth->p_fun = &EventBirth;
			BabyBirth->person_ID = MyPointerToPerson;
			p_PQ->push(BabyBirth);}
			//cout << "I, patient number " << MyPointerToPerson->PersonID << "have just scheduled by next birth for " << MyPointerToPerson->BirthFirstChild << endl; 
	}

			event * EventBirthForTheYear2 = new event;											// --- Add new births to EventQ ---									
			EventBirthForTheYear2->time = *p_GT+1;
			EventBirthForTheYear2->p_fun = &EventBirthForTheYear;
			EventBirthForTheYear2->person_ID = MyPointerToPerson;
			p_PQ->push(EventBirthForTheYear2);
			//cout << "I, patient number "<< MyPointerToPerson->PersonID << "will have my fertily next evaluated in " << EventBirthForTheYear2->time << " and my fertility is " << MyPointerToPerson->BirthFirstChild << endl; 
}


//////// HIV EVENTS ///////////////////
//void EventMyHivStatus(person *MyPointerToPerson){						// The bit inside the bracket allows to link event to specific person using person pointer 						
//	 cout << "Person " << MyPointerToPerson->PersonID << " just got an HIV test.  " << endl;}








