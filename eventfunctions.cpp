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

using namespace std;


//// --- OUTSIDE INFORMATION --- ////
extern double *p_GT;													// Tell this .cpp that there is pointer to Global Time defined externally
extern priority_queue<event*, vector<event*>, timeComparison> *p_PQ;	// Tell this .cpp that there is a priorty_queue externall and define pointer to it
extern int total_population;											// Update total population for output and for next new entry
extern person** MyArrayOfPointersToPeople;								// Pointer to MyArrayOfPointersToPeople
extern int *p_PY;														// Pointer to show which year range we are on


//// --- Other important information to be centrally available --- ////
double RandomMinMax(int min, int max){									// Provides function for random number generator using min and max number
	return rand()%(max-min+1)+min;
	}

int BirthCohortArray[12][7];
vector<double>AgeCohortMen(17);											// !!! Vector for births by age group - can be removed late on!!!!!
vector<double>AgeCohortWomen(17);


//// --- FUNCTIONS FOR EVENTS --- ////
void EventTellNewYear(person *MyPointerToPerson){						//// --- NEW YEAR FUNCTION --- ////
																		
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
	if (*p_GT >= 2000 && *p_GT<2005){*p_PY = 10; };
	if (*p_GT >= 2005){*p_PY = 11; };

	cout << "Let's check relevant things have been updated... *p_PY: " << *p_PY << " and Global Time: " << *p_GT << endl;

	event * RecurrentTellNewYear = new event;							// Schedule event for next year								
	RecurrentTellNewYear->time = *p_GT + 1;													
	RecurrentTellNewYear->p_fun = &EventTellNewYear;
	p_PQ->push(RecurrentTellNewYear);

	cout << "We have finished telling you the new year and setting fertility variables for the year." << endl;		// Code in case something goes wrong, to check where error is happening 
}


void EventMyDeathDate(person *MyPointerToPerson){						//// --- DEATH EVENT --- ////	
	MyPointerToPerson->Alive=0;
	E(cout << "Person " << MyPointerToPerson->PersonID << " just died. Their life status now is: " << MyPointerToPerson->Alive << endl;)

}


void EventBirth(person *MyPointerToPerson){								//// --- BIRTH EVENT AND MAKING NEW PERSON --- ////

	E(cout << "A birth is about to happen and my life status: " << MyPointerToPerson->Alive << endl;)
	// Update key information
	if(MyPointerToPerson->Alive == 1) {									// Only let woman give birth if she is still alive 
	total_population=total_population+1;								// Update total population for output and for next new entry
	MyPointerToPerson->Age= (*p_GT - MyPointerToPerson->DoB);			// Update age to get age at birth for output


	// Code to keep track of the birth cohort for model validation
	int i=0;
	int j=0;
	int AgeArray[7]	= {20,    25,    30,    35,    40,    45,    51};			
	while(MyPointerToPerson->Age>=AgeArray[i] && i<7){i++;}							// First get the age cat "i" to make sure d (life expectancy) is not below age using AGEARRAY above
	D(cout << "*p_PY: " << *p_PY << " i: " << i << " Age: " << MyPointerToPerson->Age << endl;)
	BirthCohortArray[*p_PY][i] = BirthCohortArray[*p_PY][i]++;
	D(cout << "My age is : " << MyPointerToPerson->Age << " and my i is: " << i << endl;)
		

	// Creating a new person 
	MyArrayOfPointersToPeople[total_population-1]=new person();			
	(MyArrayOfPointersToPeople[total_population-1])->PersonIDAssign(total_population-1);
	(MyArrayOfPointersToPeople[total_population-1])->Alive=1;
	(MyArrayOfPointersToPeople[total_population-1])->GenderDistribution();
	(MyArrayOfPointersToPeople[total_population-1])->GetMyDoBNewEntry();
	(MyArrayOfPointersToPeople[total_population-1])->GetDateOfDeath();
	(MyArrayOfPointersToPeople[total_population-1])->GetDateOfBaby();
	
	// Describe the new baby
	D(cout << "A new person is born and its: " << *p_GT << endl;
	cout << "ID: " << MyArrayOfPointersToPeople[total_population-1]->PersonID << "\t\tAlive: " << MyArrayOfPointersToPeople[total_population-1]->Alive << endl;
	cout << "Sex: " << MyArrayOfPointersToPeople[total_population-1]->Sex << "\t\tDoB: " << MyArrayOfPointersToPeople[total_population-1]->DoB << "\tAge: " << MyArrayOfPointersToPeople[total_population-1]->Age << endl;
	cout << "Death: " << MyArrayOfPointersToPeople[total_population-1]->DateOfDeath << "\tAge at Death: " << MyArrayOfPointersToPeople[total_population-1]->AgeAtDeath << endl << endl;)


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
	

	E(cout << "We have finished giving birth " << endl;)
	}
}

			
////// SPIT OUT RESULTS /////
void EventTellAgeCohort(person *MyPointerToPerson){

	E(cout << "This section is counting age " << endl;)
	
		
	// Let's reset the agearrays
	int nr=0;
	while (nr<17){
		E(cout << "Before, Men: " << AgeCohortMen.at(nr) << " and Women: " << AgeCohortWomen.at(nr) << endl;)
		AgeCohortMen.at(nr)=0;
		AgeCohortWomen.at(nr)=0;
		E(cout << "After, Men: " << AgeCohortMen.at(nr) << " and Women: " << AgeCohortWomen.at(nr) << endl;)
		nr++;}
	
	E(cout << "We finished resetting age" << endl;)
		
	// Make a Birth Array for age at birth for validation
	E(cout << "Total population" << total_population << endl;)
	for(int p=0; p<total_population; p++){
	if(MyArrayOfPointersToPeople[p]->Alive==1){
		E(cout << "Patient ID: " << MyArrayOfPointersToPeople[p]->PersonID << "\tAlive: " << MyArrayOfPointersToPeople[p]->Alive << "\tSex: " << MyArrayOfPointersToPeople[p]->Sex << endl;)
	MyArrayOfPointersToPeople[p]->Age= (*p_GT - MyArrayOfPointersToPeople[p]->DoB);			// Update age to get age at birth for output
	int i=0;
	int ArrayArray1950[17] =  {5, 10, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60, 65, 70, 75, 80, 110};	
	while(MyArrayOfPointersToPeople[p]->Age>=ArrayArray1950[i] && i<17){i++;};
	//D(cout << "Age is : " << MyPointerToPerson[p]->Age << " Sex: " << MyPointerToPerson[p]->Sex << " i: " << i << endl);
	
		if(MyArrayOfPointersToPeople[p]->Sex==1){
			AgeCohortMen.at(i)=AgeCohortMen.at(i)++;};
		if (MyArrayOfPointersToPeople[p]->Sex==2){
			AgeCohortWomen.at(i)=AgeCohortWomen.at(i)++;};
	};}

	
	E(cout << "We have finished counting age and will now report it" << endl;)

	cout << "Age groups in " << *p_GT << endl;
	cout << "MEN: " << endl;
	cout << "0-4: " << AgeCohortMen.at(0) << "\t\ 5-10: " << AgeCohortMen.at(1) << endl;
	cout << "10-15: " << AgeCohortMen.at(2) << "\t\ 15-20: " << AgeCohortMen.at(3) << endl;
	cout << "20-25: " << AgeCohortMen.at(4) << "\t\ 25-30: " << AgeCohortMen.at(5) << endl;
	cout << "30-35: " << AgeCohortMen.at(6) << "\t\ 35-40: " << AgeCohortMen.at(7) << endl;
	cout << "40-45: " << AgeCohortMen.at(8) << "\t\ 45-50: " << AgeCohortMen.at(9) << endl;
	cout << "50-55: " << AgeCohortMen.at(10) << "\t\ 55-60: " << AgeCohortMen.at(11) << endl;
	cout << "60-65: " << AgeCohortMen.at(12) << "\t\ 65-70: " << AgeCohortMen.at(13) << endl;
	cout << "70-75: " << AgeCohortMen.at(14) << "\t\ 75-80: " << AgeCohortMen.at(15) << endl;
	cout << "Over 80: " << AgeCohortMen.at(16)  << endl << endl;;

	cout << "WOMEN: " << endl;
	cout << "0-4: " << AgeCohortWomen.at(0) << "\t\ 5-10: " << AgeCohortWomen.at(1) << endl;
	cout << "10-15: " << AgeCohortWomen.at(2) << "\t\ 15-20: " << AgeCohortWomen.at(3) << endl;
	cout << "20-25: " << AgeCohortWomen.at(4) << "\t\ 25-30: " << AgeCohortWomen.at(5) << endl;
	cout << "30-35: " << AgeCohortWomen.at(6) << "\t\ 35-40: " << AgeCohortWomen.at(7) << endl;
	cout << "40-45: " << AgeCohortWomen.at(8) << "\t\ 45-50: " << AgeCohortWomen.at(9) << endl;
	cout << "50-55: " << AgeCohortWomen.at(10) << "\t\ 55-60: " << AgeCohortWomen.at(11) << endl;
	cout << "60-65: " << AgeCohortWomen.at(12) << "\t\ 65-70: " << AgeCohortWomen.at(13) << endl;
	cout << "70-75: " << AgeCohortWomen.at(14) << "\t\ 75-80: " << AgeCohortWomen.at(15) << endl;
	cout << "Over 80: " << AgeCohortWomen.at(16)  << endl << endl;

	int stop;
    cout << "Press any key to continue: ";
    cin >> stop;
	
	event * TellAgeCohort = new event;											// --- For output of array on age categories of cohort ---
	TellAgeCohort->time = *p_GT+5;												// THINK ABOUT DOING DIFFERENT TYPES OF EVENTS!!!!					
	TellAgeCohort->p_fun = &EventTellAgeCohort;
	p_PQ->push(TellAgeCohort);

	E(cout << "We have finished reporting age" << endl;)
}
	

void EventTellBirthByAge(person *MyPointerToPerson){
	
	E(cout << "We are about to tell you how many babies were born in this period" << endl;)
		
	cout << "The birth cohort from " <<  *p_GT-5 << " to " << *p_GT << endl;
	cout << "15-20: " << BirthCohortArray[*p_PY][0] << "\t\ 20-25: " << BirthCohortArray[*p_PY][1] << endl;
	cout << "25-30: " << BirthCohortArray[*p_PY][2] << "\t\ 30-35: " << BirthCohortArray[*p_PY][3] << endl;
	cout << "35-40: " << BirthCohortArray[*p_PY][4] << "\t\ 40-45: " << BirthCohortArray[*p_PY][5] << endl;
	cout << "45-50: " << BirthCohortArray[*p_PY][6] << endl << endl;
	
	int stop;
    cout << "Press any key to continue: ";
    cin >> stop;
	
	event * TellBirthByAge = new event;											// --- For output of array on birth by age cohort ---
	TellBirthByAge->time = *p_GT + 5;												// THINK ABOUT DOING DIFFERENT TYPES OF EVENTS!!!!					
	TellBirthByAge->p_fun = &EventTellBirthByAge;								// Being ALIVE here doesn't matter as its quantified when give birth and checks there if alive
	p_PQ->push(TellBirthByAge);
	
	E(cout << "We have finished telling you how many babies were born in this period" << endl;)
}






