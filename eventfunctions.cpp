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



void EventBirth(person *MyPointerToPerson){	

	// Update the population count
	total_population=total_population+1;						// Update total population for output and for next new entry
	

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
		MyPointerToPerson->ChildID_1=(MyArrayOfPointersToPeople[total_population-1])->PersonID;		// Give mothers their child's ID
		//MyPointerToPerson->ChildIndex=MyPointerToPerson->ChildIndex+1;
		//cout << "This is my " <<  MyPointerToPerson->ChildIndex << " child!" << endl;}
	}
	
	if (MyPointerToPerson->ChildIndex==1){ 
		MyPointerToPerson->ChildID_2=(MyArrayOfPointersToPeople[total_population-1])->PersonID;		// Give mothers their child's ID
		/*cout << "This is my " <<  MyPointerToPerson->ChildIndex << " child!" << endl;*/}

		// Update my child Index (number of children I have) and reset BirthFirst Child so can have another chile
								// update Child Index so can give birth again
	MyPointerToPerson->ChildIndex=MyPointerToPerson->ChildIndex+1;
	MyPointerToPerson->BirthFirstChild=9999;							// Update "BirthFirstChild" so can give birth again
	cout << "I, " << MyPointerToPerson->PersonID << " have " << MyPointerToPerson->ChildIndex << " children!!! And The Birth of my next child is " <<  MyPointerToPerson->BirthFirstChild << endl;
	
	// Scheudle breastfeeding
	MyPointerToPerson->Breastfeeding=1;
	cout << "I, " << MyPointerToPerson->PersonID << " have just started breastfeeding after having my " << (MyArrayOfPointersToPeople[total_population-1])->ChildIndex << " child" << endl;

	//event * BreastfeedingFinish = new event;						// --- Schedule end of Breastfeeding ---
	//BreastfeedingFinish->time = *p_GT + 0.25;						// Re-use code as in main to add recurrent BD to the queue (incl time and function pointer)
	//BreastfeedingFinish->p_fun = &EventStopBreastfeeding;
	//BreastfeedingFinish->person_ID=MyPointerToPerson;
	//p_PQ->push(BreastfeedingFinish);

}

//void EventStopBreastfeeding(person *MyPointerToPerson){
//	MyPointerToPerson->Breastfeeding=1;								// Reset breastfeeding status to NOT feeding so woman can have a child
//	cout << "I, " << MyPointerToPerson->PersonID << " have just stopped breastfeeding after having my " << (MyArrayOfPointersToPeople[total_population-1])->ChildIndex << " child" << endl;}

//void person::GetDateOfMyFirstBaby(){						// Get My First Child's Birthday
//															// This method already calculates the child's month of birth by providing a year of birth with decimal
//	
//	double f = ((double) rand() / (RAND_MAX));

//for(int i=0; i<total_population; i++){									// --- Assign PersonID ---
//		int a=i;
//		(MyArrayOfPointersToPeople[i])->PersonIDAssign(a);}
//
//if Death>*p_GT && (MyArrayOfPointersToPeople[total_population-1])->BirthFirstChild==9999
////			
////		if (Sex==2 && Age>=15 && Age<20 && f<0.169071){BirthFirstChild=*p_GT+(RandomFirstBirth(Age*10,200)/10)-Age;
//						while (BirthFirstChild<1950){BirthFirstChild=*p_GT+(RandomFirstBirth(Age*10,200)/10)-Age;}}
//		
//		if (Sex==2 && Age>=20 && Age<25 && f<0.351607){BirthFirstChild=*p_GT+(RandomFirstBirth(Age*10,250)/10)-Age;
//						while (BirthFirstChild<1950){BirthFirstChild=*p_GT+(RandomFirstBirth(Age*10,250)/10)-Age;}}
//		
//		if (Sex==2 && Age>=25 && Age<30 && f<0.338141){BirthFirstChild=*p_GT+(RandomFirstBirth(Age*10,300)/10)-Age;
//						while (BirthFirstChild<1950){BirthFirstChild=*p_GT+(RandomFirstBirth(Age*10,300)/10)-Age;}}
//		
//		if (Sex==2 && Age>=30 && Age<35 && f<0.284278){BirthFirstChild=*p_GT+(RandomFirstBirth(Age*10,350)/10)-Age;
//						while (BirthFirstChild<1950){BirthFirstChild=*p_GT+(RandomFirstBirth(Age*10,350)/10)-Age;}}
//
//		if (Sex==2 && Age>=35 && Age<40 && f<0.203483){BirthFirstChild=*p_GT+(RandomFirstBirth(Age*10,400)/10)-Age;
//						while (BirthFirstChild<1950){BirthFirstChild=*p_GT+(RandomFirstBirth(Age*10,400)/10)-Age;}}
//
//		if (Sex==2 && Age>=40 && Age<45 && f<0.110719){BirthFirstChild=*p_GT+(RandomFirstBirth(Age*10,450)/10)-Age;
//						while (BirthFirstChild<1950){BirthFirstChild=*p_GT+(RandomFirstBirth(Age*10,450)/10)-Age;}}
//
//		if (Sex==2 && Age>=45 && Age<50 && f<0.038901){BirthFirstChild=*p_GT+(RandomFirstBirth(Age*10,500)/10)-Age;
//						while (BirthFirstChild<1950){BirthFirstChild=*p_GT+(RandomFirstBirth(Age*10,500)/10)-Age;}}}


