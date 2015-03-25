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

double RandomMonth2(int min, int max){				// Provides function for random number generator to assign birthdya month 
	return rand()%(max-min+1)+min;}

// !!! Vector for births by age group - can be removed late on!!!!!
vector<double>BirthCohortArray(7);
vector<double>AgeCohortMen(17);
vector<double>AgeCohortWomen(17);
int SumDeath=0;


//// --- FUNCTIONS FOR EVENTS --- ////
void EventTellNewYear(person *MyPointerToPerson){						//// --- NEW YEAR FUNCTION --- ////
																		
	cout << "A new year has started, it is now " << *p_GT << endl;		// This whole function to output every time a new year starts - to make sure the model is actually running

	event * RecurrentTellNewYear = new event;											
	RecurrentTellNewYear->time = *p_GT + 1;													
	RecurrentTellNewYear->p_fun = &EventTellNewYear;
	p_PQ->push(RecurrentTellNewYear);
}



void EventMyDeathDate(person *MyPointerToPerson){						//// --- DEATH EVENT --- ////	
	MyPointerToPerson->Alive=0;
	D(cout << "Person " << MyPointerToPerson->PersonID << " just died. Their life status now is: " << MyPointerToPerson->Alive << endl;);}


void EventBirth(person *MyPointerToPerson){								//// --- BIRTH EVENT AND MAKING NEW PERSON --- ////

	// Update key information
	total_population=total_population+1;								// Update total population for output and for next new entry
	MyPointerToPerson->Age= (*p_GT - MyPointerToPerson->DoB);			// Update Age  - very important!!
	

	// Code to keep track of the birth cohort for model validation
	int i=0;
	int AgeArray1950[7]	= {20,    25,    30,    35,    40,    45,    51};			
	while(MyPointerToPerson->Age>AgeArray1950[i] && i<7){i++;}							// First get the age cat "i" to make sure d (life expectancy) is not below age using AGEARRAY above
	BirthCohortArray.at(i)=BirthCohortArray.at(i)++;
	D(cout << "My age is : " << MyPointerToPerson->Age << " Fertility: " << MyPointerToPerson->BirthChild << " and my i is: " << i << endl;
	cout << "15-20: " << BirthCohortArray.at(0) << " \t\ 20-25: " << BirthCohortArray.at(1) << " \t\ 25-30: " << BirthCohortArray.at(2) << "\t\ 30-35: " << BirthCohortArray.at(3) << "\t\ 35-40: " << BirthCohortArray.at(4) << "\t\ 40-45: " << BirthCohortArray.at(5) << "\t\ 45-50: " << BirthCohortArray.at(6) << endl);
	

	// Creating a new person 
	MyArrayOfPointersToPeople[total_population-1]=new person();			
	(MyArrayOfPointersToPeople[total_population-1])->PersonIDAssign(total_population-1);
	(MyArrayOfPointersToPeople[total_population-1])->Alive=1;
	(MyArrayOfPointersToPeople[total_population-1])->GenderDistribution();
	(MyArrayOfPointersToPeople[total_population-1])->GetMyYearOfBirthNewEntry();
	(MyArrayOfPointersToPeople[total_population-1])->GetDateOfDeath();
	////(MyArrayOfPointersToPeople[total_population-1])->GetDateOfHIVInfection(1,2); 
	D(cout << "A new person is born and its: " << *p_GT << endl;
	  cout << "ID: " << MyArrayOfPointersToPeople[total_population-1]->PersonID << "\t\tAlive: " << MyArrayOfPointersToPeople[total_population-1]->Alive << endl;
	  cout << "Sex: " << MyArrayOfPointersToPeople[total_population-1]->Sex << "\t\tDoB: " << MyArrayOfPointersToPeople[total_population-1]->DoB << "\tAge: " << MyArrayOfPointersToPeople[total_population-1]->Age << endl;
	  cout << "Death: " << MyArrayOfPointersToPeople[total_population-1]->DateOfDeath << "\tAge at Death: " << MyArrayOfPointersToPeople[total_population-1]->AgeAtDeath << endl << endl;);


	// Incldue death of baby into Event Q
	event * DeathEvent = new event;										// --- Include death of new baby into the Event Q  ---
	DeathEvent->time = MyArrayOfPointersToPeople[total_population-1]->DateOfDeath;													
	DeathEvent->p_fun = &EventMyDeathDate;
	DeathEvent->person_ID = MyArrayOfPointersToPeople[total_population-1];
	p_PQ->push(DeathEvent);

	
	// Link Mother and Child
	(MyArrayOfPointersToPeople[total_population-1])->MotherID=MyPointerToPerson->PersonID;			// Give child their mothers ID
	MyPointerToPerson->ChildIDVector.push_back((MyArrayOfPointersToPeople[total_population-1]));	// Give mothers their child's ID
		
	
	// Update my child Index (number of children I have) and reset BirthFirst Child so can have another chile
	MyPointerToPerson->ChildIndex=MyPointerToPerson->ChildIndex+1;		// update Child Index so can give birth again
	

	// Scheudle breastfeeding 
	//MyPointerToPerson->Breastfeeding=1; 
	MyPointerToPerson->BirthChild=9999;									// Use this when Breastfeeding is commented out
	

	//event * BreastfeedingFinish = new event;							// --- Schedule end of Breastfeeding ---
	//BreastfeedingFinish->time = *p_GT + 0.25;							// Re-use code as in main to add recurrent BD to the queue (incl time and function pointer)
	//BreastfeedingFinish->p_fun = &EventStopBreastfeeding;
	//BreastfeedingFinish->person_ID=MyPointerToPerson;
	//p_PQ->push(BreastfeedingFinish);
	
	//D(cout << "My child is " << MyPointerToPerson->ChildIDVector.at(MyPointerToPerson->ChildIndex) << endl);		// FIX THIS!!
	D(cout << "Nr 1: " << MyPointerToPerson->ChildIndex << "\t\tNr 2: " << MyPointerToPerson->ChildIDVector.size() << "\t\tBreastfeeding " << MyPointerToPerson->Breastfeeding << endl << endl);
	
}

void EventStopBreastfeeding(person *MyPointerToPerson){
	MyPointerToPerson->Breastfeeding=0;									// Reset breastfeeding status to NOT feeding so woman can have a child
	MyPointerToPerson->BirthChild=9999;									// Reset BirthOfChild so can have another Child
	D(cout << "Breastfeeding: " << endl;
	  cout << "I, " << MyPointerToPerson->PersonID << " have just stopped breastfeeding after having my " << MyPointerToPerson->ChildIndex << " child" << endl);
}
							

void EventBirthForTheYear(person *MyPointerToPerson){					// Set births for the coming year
		
	cout << "A new year has started and fertility is being evaluated, it is now " << *p_GT << endl;
	
	for(int p=0; p<total_population; p++){
	if(MyArrayOfPointersToPeople[p]->Alive==1 && MyArrayOfPointersToPeople[p]->Sex==2 && MyArrayOfPointersToPeople[p]->BirthChild==9999 && MyArrayOfPointersToPeople[p]->Age>=15 && MyArrayOfPointersToPeople[p]->Age<50){	// Only set fertily for those not scheduled to give birth this year and those not breastfeeding
	MyArrayOfPointersToPeople[p]->Age= (*p_GT - MyArrayOfPointersToPeople[p]->DoB);			// Update Age  - very important!!

	
	// Basic things to schedule annual fertiliy 
	double f = ((double) rand() / (RAND_MAX));
	double Fertility1950[7] = {0.169071, 0.351607, 0.338141, 0.284278, 0.203483, 0.110719, 0.038901};
	int	   AgeArray[7]		= {20,		 25,	   30,		 35,	   40,		 45,	   50};
	int i=0;

	while (MyArrayOfPointersToPeople[p]->Age>AgeArray[i] && i<7){i++;D(cout <<  "The loop is running " << endl);} ;
	if (f < Fertility1950[i]){MyArrayOfPointersToPeople[p]->BirthChild=*p_GT+((RandomMonth2(1,12)/12.1));};

	D(cout << "Schedule fertility for the year:" << endl;
	  cout << "The value of i is: " << i << endl;
	  cout << "ID: " << MyPointerToPerson[p]->PersonID << "\t\tSex: " << MyPointerToPerson[p]->Sex << "Age: " << MyPointerToPerson[p]->Age << endl; 
	  cout << "F: " << f << "\tBirth: " << MyPointerToPerson[p]->BirthChild << endl << endl);
			
			//// --- Add new birth to Event Q --- ////
			if (MyArrayOfPointersToPeople[p]->BirthChild<9999){
			event * BabyBirth = new event;																			
			BabyBirth->time = MyArrayOfPointersToPeople[p]->BirthChild;
			BabyBirth->p_fun = &EventBirth;
			BabyBirth->person_ID = MyArrayOfPointersToPeople[p];
			p_PQ->push(BabyBirth);}
	}}
			//// --- Schedule fertility scan for next year --- ////
			event * EventBirthForTheYear2 = new event;																			
			EventBirthForTheYear2->time = *p_GT+1;
			EventBirthForTheYear2->p_fun = &EventBirthForTheYear;
			EventBirthForTheYear2->person_ID = MyPointerToPerson;
			p_PQ->push(EventBirthForTheYear2);
			 
}


//////// HIV EVENTS ///////////////////			TO DO!!!
//void EventMyHivStatus(person *MyPointerToPerson){						// The bit inside the bracket allows to link event to specific person using person pointer 						
//	 cout << "Person " << MyPointerToPerson->PersonID << " just got an HIV test.  " << endl;}


////// SPIT OUT RESULTS /////  

void EventTellAgeCohort(person *MyPointerToPerson){

	cout << "Tell me the age cohort" << endl;
	// Make a Birth Array for age at birth for validation
	for(int p=0; p<total_population; p++){
		if(MyArrayOfPointersToPeople[p]->Alive==1){	// Only set fertily for those not scheduled to give birth this year and those not breastfeeding
	MyArrayOfPointersToPeople[p]->Age= (*p_GT - MyArrayOfPointersToPeople[p]->DoB);

	int i=0;
	int ArrayArray1950[17] =  {5, 10, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60, 65, 70, 75, 80, 110};	
	while(MyArrayOfPointersToPeople[p]->Age>ArrayArray1950[i] && i<17){i++;};
	D(cout << "Age is : " << MyArrayOfPointersToPeople[p]->Age << " Sex: " << MyArrayOfPointersToPeople[p]->Sex << " i: " << i << endl);
	
	if(MyArrayOfPointersToPeople[p]->Alive==1 && MyArrayOfPointersToPeople[p]->DateOfDeath>*p_GT){
		if(MyArrayOfPointersToPeople[p]->Sex==1){
			AgeCohortMen.at(i)=AgeCohortMen.at(i)++;};
		if (MyArrayOfPointersToPeople[p]->Sex==2){
			AgeCohortWomen.at(i)=AgeCohortWomen.at(i)++;};}

			if(MyArrayOfPointersToPeople[p]->Alive==0){SumDeath=SumDeath++;};
		};}; 

cout << "We have fdinished telling the age of cohort " << endl;} 



	

void EventTellBirthByAge(person *MyPointerToPerson){
	
	cout << "The birth cohort 1950-1955: " << endl;
	cout << "15-20: " << BirthCohortArray.at(0) << "\t\ 20-25: " << BirthCohortArray.at(1) << endl;
	cout << "25-30: " << BirthCohortArray.at(2) << "\t\ 30-35: " << BirthCohortArray.at(3) << endl;
	cout << "35-40: " << BirthCohortArray.at(4) << "\t\ 40-45: " << BirthCohortArray.at(5) << endl;
	cout << "45-50: " << BirthCohortArray.at(6) << endl << endl;
	
	cout << "MEN: " << endl;
	cout << "0-4: " << AgeCohortMen.at(0) << "\t\ 5-10: " << AgeCohortMen.at(1) << endl;
	cout << "10-15: " << AgeCohortMen.at(2) << "\t\ 15-20: " << AgeCohortMen.at(3) << endl;
	cout << "20-25: " << AgeCohortMen.at(4) << "\t\ 325-30: " << AgeCohortMen.at(5) << endl;
	cout << "30-35: " << AgeCohortMen.at(6) << "\t\ 35-40: " << AgeCohortMen.at(7) << endl;
	cout << "40-45: " << AgeCohortMen.at(8) << "\t\ 45-50: " << AgeCohortMen.at(9) << endl;
	cout << "50-55: " << AgeCohortMen.at(10) << "\t\ 55-60: " << AgeCohortMen.at(11) << endl;
	cout << "60-65: " << AgeCohortMen.at(12) << "\t\ 65-70: " << AgeCohortMen.at(13) << endl;
	cout << "70-75: " << AgeCohortMen.at(14) << "\t\ 75-80: " << AgeCohortMen.at(15) << endl;
	cout << "Over 80: " << AgeCohortMen.at(16)  << endl << endl;;

	cout << "WomEN: " << endl;
	cout << "0-4: " << AgeCohortWomen.at(0) << "\t\ 5-10: " << AgeCohortWomen.at(1) << endl;
	cout << "10-15: " << AgeCohortWomen.at(2) << "\t\ 15-20: " << AgeCohortWomen.at(3) << endl;
	cout << "20-25: " << AgeCohortWomen.at(4) << "\t\ 325-30: " << AgeCohortWomen.at(5) << endl;
	cout << "30-35: " << AgeCohortWomen.at(6) << "\t\ 35-40: " << AgeCohortWomen.at(7) << endl;
	cout << "40-45: " << AgeCohortWomen.at(8) << "\t\ 45-50: " << AgeCohortWomen.at(9) << endl;
	cout << "50-55: " << AgeCohortWomen.at(10) << "\t\ 55-60: " << AgeCohortWomen.at(11) << endl;
	cout << "60-65: " << AgeCohortWomen.at(12) << "\t\ 65-70: " << AgeCohortWomen.at(13) << endl;
	cout << "70-75: " << AgeCohortWomen.at(14) << "\t\ 75-80: " << AgeCohortWomen.at(15) << endl;
	cout << "Over 80: " << AgeCohortWomen.at(16)  << endl;


	cout << "Deaths until 1st Jul 9150: " << SumDeath << endl;}







