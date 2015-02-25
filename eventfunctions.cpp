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
extern int total_population;											// Update total population for output and for next new entry
extern person** MyArrayOfPointersToPeople;

double RandomBirthsNewYear(int min, int max){							// Provides function for random number generator to assign first birth for women
	return rand()%(max-min+1)+min;}


//// --- FUNCTIONS FOR EVENTS --- ////

void EventTellNewYear(person *MyPointerToPerson){						// Function to output every time a new year starts - to make sure the model is actually running
	
	cout << " A new year has started, it is now " << *p_GT << endl;

	event * RecurrentTellNewYear = new event;											
	RecurrentTellNewYear->time = *p_GT + 1;													
	RecurrentTellNewYear->p_fun = &EventTellNewYear;
	p_PQ->push(RecurrentTellNewYear);
}


void EventMyHivStatus(person *MyPointerToPerson){						// The bit inside the bracket allows to link event to specific person using person pointer 						
	 cout << "Person " << MyPointerToPerson->PersonID << " just got an HIV test.  " << endl;}


void EventMyDeathDate(person *MyPointerToPerson){									
	 cout << "Person " << MyPointerToPerson->PersonID << " just died.  "  << endl;}


void EventBirth(person *MyPointerToPerson){	

	if (MyPointerToPerson->Alive==1 && MyPointerToPerson->BirthFirstChild<9999){
	
	// Update the population count
	total_population=total_population+1;								// Update total population for output and for next new entry
	
	// Creating a new person 
	MyArrayOfPointersToPeople[total_population-1]=new person();
	(MyArrayOfPointersToPeople[total_population-1])->PersonIDAssign(total_population-1);
	(MyArrayOfPointersToPeople[total_population-1])->Alive=1;
	(MyArrayOfPointersToPeople[total_population-1])->GenderDistribution();
	(MyArrayOfPointersToPeople[total_population-1])->GetMyYearOfBirthNewEntry();
	(MyArrayOfPointersToPeople[total_population-1])->GetNewDateOfDeath();
	////(MyArrayOfPointersToPeople[total_population-1])->GetDateOfHIVInfection(1,2); 
	

	// Link Mother and Child
	(MyArrayOfPointersToPeople[total_population-1])->MotherID=MyPointerToPerson->PersonID;			// Give child their mothers ID
	MyPointerToPerson->ChildID=(MyArrayOfPointersToPeople[total_population-1])->PersonID;			// Give mothers their child's ID
	
	if (MyPointerToPerson->ChildIndex==0){ 
		MyPointerToPerson->ChildID_1=(MyArrayOfPointersToPeople[total_population-1])->PersonID;}	// Give mothers their child's ID
		
	if (MyPointerToPerson->ChildIndex==1){ 
		MyPointerToPerson->ChildID_2=(MyArrayOfPointersToPeople[total_population-1])->PersonID;}	// Give mothers their child's ID

	if (MyPointerToPerson->ChildIndex==2){ 
		MyPointerToPerson->ChildID_3=(MyArrayOfPointersToPeople[total_population-1])->PersonID;}	// Give mothers their child's ID

	if (MyPointerToPerson->ChildIndex==3){ 
		MyPointerToPerson->ChildID_4=(MyArrayOfPointersToPeople[total_population-1])->PersonID;}	// Give mothers their child's ID

	if (MyPointerToPerson->ChildIndex==4){ 
		MyPointerToPerson->ChildID_5=(MyArrayOfPointersToPeople[total_population-1])->PersonID;}	// Give mothers their child's ID

	if (MyPointerToPerson->ChildIndex==5){ 
		MyPointerToPerson->ChildID_6=(MyArrayOfPointersToPeople[total_population-1])->PersonID;}	// Give mothers their child's ID

	if (MyPointerToPerson->ChildIndex==6){ 
		MyPointerToPerson->ChildID_7=(MyArrayOfPointersToPeople[total_population-1])->PersonID;}	// Give mothers their child's ID

	if (MyPointerToPerson->ChildIndex==7){ 
		MyPointerToPerson->ChildID_8=(MyArrayOfPointersToPeople[total_population-1])->PersonID;}	// Give mothers their child's ID

	if (MyPointerToPerson->ChildIndex==8){ 
		MyPointerToPerson->ChildID_9=(MyArrayOfPointersToPeople[total_population-1])->PersonID;}	// Give mothers their child's ID

	if (MyPointerToPerson->ChildIndex==9){ 
		MyPointerToPerson->ChildID_10=(MyArrayOfPointersToPeople[total_population-1])->PersonID;}	// Give mothers their child's ID
		

	// Update my child Index (number of children I have) and reset BirthFirst Child so can have another chile
	MyPointerToPerson->ChildIndex=MyPointerToPerson->ChildIndex+1;		// update Child Index so can give birth again
	

	// Scheudle breastfeeding
	MyPointerToPerson->Breastfeeding=1;
	

	event * BreastfeedingFinish = new event;														// --- Schedule end of Breastfeeding ---
	BreastfeedingFinish->time = *p_GT + 0.25;														// Re-use code as in main to add recurrent BD to the queue (incl time and function pointer)
	BreastfeedingFinish->p_fun = &EventStopBreastfeeding;
	BreastfeedingFinish->person_ID=MyPointerToPerson;
	p_PQ->push(BreastfeedingFinish);

	//cout << "I, patient number " << MyPointerToPerson->PersonID << " have had my " << MyPointerToPerson->ChildIndex << " child and I am now breastfeeding " << MyPointerToPerson->Breastfeeding << endl;

	}}

void EventStopBreastfeeding(person *MyPointerToPerson){
	MyPointerToPerson->Breastfeeding=0;																// Reset breastfeeding status to NOT feeding so woman can have a child
	MyPointerToPerson->BirthFirstChild=9999;														// Reset BirthOfChild so can have another Child
	//cout << "I, " << MyPointerToPerson->PersonID << " have just stopped breastfeeding after having my " << MyPointerToPerson->ChildIndex << " child" << endl;
}
							

void EventBirthForTheYear(person *MyPointerToPerson){												// Set births for the coming year

	//cout << "I, patient number " << MyPointerToPerson->PersonID << "have a fertility status of: " << MyPointerToPerson->BirthFirstChild << " and my age is " << MyPointerToPerson->Age << endl; 

	MyPointerToPerson->Age= (*p_GT - MyPointerToPerson->DoB);

	if (MyPointerToPerson->Sex==2 && MyPointerToPerson->Alive==1 && MyPointerToPerson->BirthFirstChild==9999 && MyPointerToPerson->Age>=15 && MyPointerToPerson->Age<50 && MyPointerToPerson->ChildIndex<10){					// Only set fertily for those not scheduled to give birth this year and those not breastfeeding
			
		double f = ((double) rand() / (RAND_MAX));

		if (MyPointerToPerson->Age>=15 && MyPointerToPerson->Age<20 && f<0.169071){MyPointerToPerson->BirthFirstChild=*p_GT+(RandomBirthsNewYear(MyPointerToPerson->Age*10,200)/10)-MyPointerToPerson->Age;
				while (MyPointerToPerson->BirthFirstChild<*p_GT){MyPointerToPerson->BirthFirstChild=*p_GT+(RandomBirthsNewYear(MyPointerToPerson->Age*10,200)/10)-MyPointerToPerson->Age;}}

		if (MyPointerToPerson->Age>=20 && MyPointerToPerson->Age<25 && f<0.351607){MyPointerToPerson->BirthFirstChild=*p_GT+(RandomBirthsNewYear(MyPointerToPerson->Age*10,250)/10)-MyPointerToPerson->Age;
				while (MyPointerToPerson->BirthFirstChild<1950){MyPointerToPerson->BirthFirstChild=*p_GT+(RandomBirthsNewYear(MyPointerToPerson->Age*10,250)/10)-MyPointerToPerson->Age;}}
		
		if (MyPointerToPerson->Age>=25 && MyPointerToPerson->Age<30 && f<0.338141){MyPointerToPerson->BirthFirstChild=*p_GT+(RandomBirthsNewYear(MyPointerToPerson->Age*10,300)/10)-MyPointerToPerson->Age;
				while (MyPointerToPerson->BirthFirstChild<1950){MyPointerToPerson->BirthFirstChild=*p_GT+(RandomBirthsNewYear(MyPointerToPerson->Age*10,300)/10)-MyPointerToPerson->Age;}}
		
		if (MyPointerToPerson->Age>=30 && MyPointerToPerson->Age<35 && f<0.284278){MyPointerToPerson->BirthFirstChild=*p_GT+(RandomBirthsNewYear(MyPointerToPerson->Age*10,350)/10)-MyPointerToPerson->Age;
				while (MyPointerToPerson->BirthFirstChild<1950){MyPointerToPerson->BirthFirstChild=*p_GT+(RandomBirthsNewYear(MyPointerToPerson->Age*10,350)/10)-MyPointerToPerson->Age;}}

		if (MyPointerToPerson->Age>=35 && MyPointerToPerson->Age<40 && f<0.203483){MyPointerToPerson->BirthFirstChild=*p_GT+(RandomBirthsNewYear(MyPointerToPerson->Age*10,400)/10)-MyPointerToPerson->Age;
				while (MyPointerToPerson->BirthFirstChild<1950){MyPointerToPerson->BirthFirstChild=*p_GT+(RandomBirthsNewYear(MyPointerToPerson->Age*10,400)/10)-MyPointerToPerson->Age;}}

		if (MyPointerToPerson->Age>=40 && MyPointerToPerson->Age<45 && f<0.110719){MyPointerToPerson->BirthFirstChild=*p_GT+(RandomBirthsNewYear(MyPointerToPerson->Age*10,450)/10)-MyPointerToPerson->Age;
				while (MyPointerToPerson->BirthFirstChild<1950){MyPointerToPerson->BirthFirstChild=*p_GT+(RandomBirthsNewYear(MyPointerToPerson->Age*10,450)/10)-MyPointerToPerson->Age;}}

		if (MyPointerToPerson->Age>=45 && MyPointerToPerson->Age<50 && f<0.038901){MyPointerToPerson->BirthFirstChild=*p_GT+(RandomBirthsNewYear(MyPointerToPerson->Age*10,500)/10)-MyPointerToPerson->Age;
				while (MyPointerToPerson->BirthFirstChild<1950){MyPointerToPerson->BirthFirstChild=*p_GT+(RandomBirthsNewYear(MyPointerToPerson->Age*10,500)/10)-MyPointerToPerson->Age;}}
	
			
			if (MyPointerToPerson->BirthFirstChild<9999){
			event * BabyBirth = new event;											// --- Add new births to EventQ ---									
			BabyBirth->time = MyPointerToPerson->BirthFirstChild;
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








////////// OLDER CODE AND FUNCTIONS   ///////////////////

//void EventMyBirthDate(person *MyPointerToPerson){									
//	
//	 event * RecurrentBirthdayDate = new event;							// --- Schedule recurrent Birthday ---
//	 RecurrentBirthdayDate->time = *p_GT + 1;							// Re-use code as in main to add recurrent BD to the queue (incl time and function pointer)
//	 RecurrentBirthdayDate->p_fun = &EventMyBirthDate;
//	 RecurrentBirthdayDate->person_ID=MyPointerToPerson;
//	 p_PQ->push(RecurrentBirthdayDate);
//
//	 MyPointerToPerson->Age=MyPointerToPerson->Age+1; 
//	 	
//	 cout << "Person " << MyPointerToPerson->PersonID << " just had their birthday.  They are now " << MyPointerToPerson->Age << " years old.  " << endl;
//	 cout << "Person " << MyPointerToPerson->PersonID << " will have their next birthday on " << *p_GT + 1 << ".  " << endl;
//}


	
		

