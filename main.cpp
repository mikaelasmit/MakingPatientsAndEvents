////////////////////////////////////////////////////////////////
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
using namespace std;   


//    To Do List:
//  1.	Making a population (i.e. more than one person) and assign variables (Person ID, Sex, HIV status, Birthday, Date of Death,…) - DONE
//  2.	Use simple distributions (e.g. uniform distribution, etc) to assign characteristics - DONE
//  3.	Develop EventQ and play around with it – DONE
//  4.	Insert events into the EventQ, e.g. HIV-infection, Death and Birthdays – DONE
//  5.	Separate EventQ code into different .h and .cpp files – TOOK A WHILE BUT DONE
//  6.	Insert a global time counter into the model to record time – DONE
//  7.	Add global time to the EventQ – DONE
//  8.	Make birthdays into recurrent event using pointers and global time  - DONE
//  9.	Remove repeat code for EventQ and from main() and make into self-contained loop – DONE
//  10.	Add stop time into the model for EventQ – DONE
//  11.	Merge MakingPatients and EventQ code to make events happen to two different people – DONE
//
//  Worked on in the last few days:
//  12.	Give people an age using birthday and vice versa – DONE
//  13.	Include Age at T0 to record age at start of model – DONE
//  14.	Add ages to the EventQ and update every year – DONE
//  15.	Make C++ output .csv  files to be able to run large populations and generate graphs – DONE
//  16.	Find Kanyan age-distribution in 1950 - DONE
//  17.	Add Kenyan age-distribution as per 1950s – DONE
//  18.	Run model with this age distribution and generate population pyramids – DONE
//  19.   Add new entries to run population forward and simulate population growth - DONE IN SIMPLE WAY
//  20.	Make C++ run with Matlab – THIS IS TAKING A WHILE AND I AM STILL BUSY WITH THIS.  I am looking at SJ’s code today to see how her model is set up with Matlab
//
//  Still to do:
//  21.	Link deaths to age using a linear equation (increase age->increase death)
//  22.	Compare mortality to data in Kenya, improve mortality as necessary
//  23.	Improve new entry and discuss population 'vector' with Tim (deal with bigger size)
//  24.	Add HIV status and update it as a function of HIV test 
//  25.	Add more aspects of HIV care cascade (diagnosis, start cART,…)
//  26. Think about class destructors



//// --- Function related to event - to be available externally ---
double *p_GT;																// Pointer to global time
double *p_SY;																// Pointer to start year of the model
double StartYear=1950;														// Define Start Year if the model and set it to year of choice
priority_queue<event*, vector<event*>, timeComparison> *p_PQ;				// Pointer to event queue so as to be able to push-in/pop-out new events that are ocurreing

																			// [...] as a result of 'primary' events in the queue, e.g. recurrent birthdays

//// --- Function relating to New Entry - to be available externally ---
const int final_number_people=10000;												// To determine the final size of the total population to be modeled 
int init_pop = 100;
int total_population=init_pop;											// Update total population for output and for next new entry
double new_entry=1;															// To add new people

person** MyArrayOfPointersToPeople = new person*[final_number_people];		// First 'person*' is a pointer (address) and 'new person' and space for x person which will point to actual person below
																			// Have to now change [init_pop] to [final_number_people] to give the final size of 'matrix'

//// --- RUN THE MAIN MODEL ---
int main(){

	cout << "Hello, Mikaela!" << endl << endl ;								// Check if model is running


	//// --- Some pointers ---
	double GlobalTime=StartYear;											// Define Global Time and set it to 0 at the beginning of the model
	p_GT=&GlobalTime;														// Define the location the pointer to Global time is pointing to
	p_SY=&StartYear;														// Define the location of the pointer to Start Year is pointing to
	srand(time(NULL));														// Random Number generator using PC time
	priority_queue<event*, vector<event*>, timeComparison> iQ;				// Define th ePriority Q
	p_PQ=&iQ;																// Define pointer to event Q
	
		
	//// --- Making Population---
	for(int i=0; i<final_number_people; i++){								// REMEMBER: this needs to stay "final_number_people" or it will give error with CSV FILES!!!!
		MyArrayOfPointersToPeople[i]=new person();}							// The 'new person' the actual new person
	

	//// --- Assign Population Characteristics ---
	for(int i=0; i<total_population; i++){											// --- Assign PersonID ---
		int a=i;
		(MyArrayOfPointersToPeople[i])->PersonIDAssign(a);}

	for(int i=0; i<total_population; i++){											// --- Assign PersonID ---
		(MyArrayOfPointersToPeople[i])->Alive=1;}

	for(int i=0; i<total_population; i++){											// --- Assign Sex- ---
		(MyArrayOfPointersToPeople[i])->GenderDistribution();}

	for(int i=0; i<total_population; i++){											// --- Assign DoB/Age --- 
		(MyArrayOfPointersToPeople[i])->GetMyYearOfBirth();}

	for(int i=0; i<total_population; i++){											// --- Assign Birth of First Baby- ---
		if (MyArrayOfPointersToPeople[i]->Sex==2) {(MyArrayOfPointersToPeople[i])->GetDateOfMyFirstBaby();}}

	for(int i=0; i<total_population; i++){											// --- Assign date of death ---  
		(MyArrayOfPointersToPeople[i])->GetDateOfDeath();}

	for(int i=0; i<total_population; i++){											// --- Assign Date of HIV
		(MyArrayOfPointersToPeople[i])->GetDateOfHIVInfection(1,2);}


	//// --- OUTPUT CHECKs --- 
	//cout << endl << "The person's ID...." << endl;							// --- Ouput all the peoples' IDs ---
	//for(int i=0; i<init_pop; i++){
	//	(MyArrayOfPointersToPeople[i])->TellMyPersonID();}	

	//cout << endl << "The Life Status of person...." << endl;						// --- Ouput all the peoples' gender ---
	//for(int i=0; i<init_pop; i++){
	//	(MyArrayOfPointersToPeople[i])->TellMyLifeStatus(); }
	//
	//cout << endl << "The sex of person...." << endl;						// --- Ouput all the peoples' gender ---
	//for(int i=0; i<init_pop; i++){
	//   (MyArrayOfPointersToPeople[i])->TellMySex(); }

	cout << endl << "The date of the persons first child... " << endl;		// --- Output all the peoples' date of first child ---
	for(int i=0; i<total_population; i++){
		(MyArrayOfPointersToPeople[i])->TellMyFirstChildBirth();}

	cout << endl << "The year of birth of the person..." << endl;			// --- Ouput all the peoples' year of birth ---
	for(int i=0; i<init_pop; i++){
		(MyArrayOfPointersToPeople[i])->TellMyYearOfBirth(); }	

	//cout << endl << "The year of the person' death..." << endl;					// --- Ouput all the peoples' date of deaths ---
	//for(int i=0; i<init_pop; i++){
	//	(MyArrayOfPointersToPeople[i])->TellMyExpectedDeathDate(); }			
	//
	//cout << endl << "The dates of the person's HIV infection..." << endl;
	//for(int i=0; i<init_pop; i++){
	//	(MyArrayOfPointersToPeople[i])->TellMyHivDateSTART();}

		
	//// --- EVENTQ ---
	
	//for(int i=0; i<init_pop; i++){
	//event * DeathDate = new event;										// --- Date of Death ---
	//DeathDate->time = MyArrayOfPointersToPerson[i]->DateOfDeath;
	//DeathDate->p_fun = &EventMyDeathDate;
	//DeathDate->person_ID = MyArrayOfPointersToPerson[i];
	//iQ.push(DeathDate);	}												
	
	//for(int i=0; i<init_pop; i++){
	//event * BirthdayDate = new event;										// --- Birthday ---
	//BirthdayDate->time = StartYear + MyArrayOfPointersToPeople[i]->Age - MyArrayOfPointersToPeople[i]->AgeT0;
	//BirthdayDate->p_fun = &EventMyBirthDate;
	//BirthdayDate->person_ID = MyArrayOfPointersToPeople[i];
	//cout << "My next birthday of patient " << MyArrayOfPointersToPeople[i]->PersonID << " is " << BirthdayDate->time << endl;
	//iQ.push(BirthdayDate);}		

	//cout << endl;

	for(int i=0; i<total_population; i++){
	event * BabyBirth = new event;										// --- Birthday of First Child ---
	BabyBirth->time = MyArrayOfPointersToPeople[i]->BirthFirstChild;
	BabyBirth->p_fun = &EventNewEntry;
	BabyBirth->person_ID = MyArrayOfPointersToPeople[i];
	//cout << "My birth of patient " << MyArrayOfPointersToPeople[i]->PersonID << " first child is " << BabyBirth->time << endl;
	iQ.push(BabyBirth);}	

	
	//for(int i=init_pop; i<init_pop+new_entry; i++){
	//event * NewEntry = new event;											// --- New Entry ---
	//NewEntry->time = GlobalTime+1;
	//NewEntry->p_fun = &EventNewEntry;
	//NewEntry->person_ID = MyArrayOfPointersToPeople[i];
	//iQ.push(NewEntry);}	

	//for(int i=0; i<init_pop; i++){
	//event * HivTest = new event;											// --- HIV Testing ---
	//HivTest->time = MyArrayOfPointersToPeople[i]->MyDateOfHIV;
	//HivTest->p_fun = &TellMyHivStatus;
	//HivTest->person_ID = MyArrayOfPointersToPerson[i];
	//iQ.push(HivTest);}													// Add HIVTest to queue
	//
		
	
	// --- give output of queue as it progresses ---
	cout << endl << endl << "The characteristics of the event queue:" << endl;
	cout << "the first event will ocurr in " << iQ.top()->time << ".  " << endl;
	cout << "the size of the event queue is " << iQ.size() << endl;
	
	while(iQ.top()->time< 1952 /*|| !iQ.empty()*/){								// this loop throws up error because no recurrent birthday pushing gt over 5 yrs and iq.pop means gt cannot be updated after pop
		GlobalTime=iQ.top()->time;

		cout << endl << endl << "An event has just ocurred.  " << endl;
		cout << "it is " << iQ.top()->time << ".  " << endl;
	 //if (iQ.top()->person_ID->Age==1)
						iQ.top()-> p_fun(iQ.top()->person_ID);
				
		
		//globaltime=iq.top()->time;										// careful with order of global time update - do not touch or touch and check!!
		
		iQ.pop();		
		cout << endl << "this event has now been removed from the queue.  " << endl;}


	//// --- Output the results in a csv file ---
	FILE* csv_out = fopen("test.csv","w");
	for (int i=0; i<total_population; i++) {								// Change the i< X here as well as the "%d!!
		fprintf(csv_out,"%d,%d,%d,%f,%f,%d,%d,%f \n",
			MyArrayOfPointersToPeople[i]->PersonID,
			MyArrayOfPointersToPeople[i]->Sex,
			MyArrayOfPointersToPeople[i]->DoB,
			MyArrayOfPointersToPeople[i]->Age,
			MyArrayOfPointersToPeople[i]->BirthFirstChild,
			MyArrayOfPointersToPeople[i]->MotherID,
			MyArrayOfPointersToPeople[i]->ChildID, 
			MyArrayOfPointersToPeople[i]->DateOfDeath

			//MyArrayOfPointersToPeople[i]->DateOfDeath/*,
			//MyArrayOfPointersToPeople[i]->MyDateOfHIV*/
			);}
	fclose(csv_out);


	// --- End of code ---
    cout << endl << "Hi Jack, so sorry\n";
	system("pause");
    return 0;
}



