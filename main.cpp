////////////////////////////////////////////////////////////
//  Mikaela Epidemiology Model							  //
//														  //
//  Created by Mikaela Smit on 7/11/2014.				  //
//  Copyright (c) 2014 Mikael Smit. All rights reserved.  //
////////////////////////////////////////////////////////////

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "person.h"
#include <ctime>
#include "event.h"
#include "eventQ.h"
#include "eventfunctions.h"

using namespace std;   


// --- FUNCTIONS RELATED TO EVENTS ---
double *p_GT;															// Pointer to global time
priority_queue<event*, vector<event*>, timeComparison> *p_PQ;			// Pointer to event queue so as to be able to push-in/pop-out new events that are ocurreing
																		// [...] as a result of 'primary' events in the queue, e.g. recurrent birthdays

//// --- RUN THE MAIN MODEL ---
int main(){

	double GlobalTime=0;												// Define Global Time and set it to 0 at the beginning of the model
	p_GT=&GlobalTime;													// Define the location the pointer to Global time is pointing to
	srand(time(NULL));													// Random Number generator using PC time
	priority_queue<event*, vector<event*>, timeComparison> iQ;			// Define th ePriority Q
	p_PQ=&iQ;															// Define pointer to event Q

	cout << "Hello, Mikaela!" << endl << endl ;							// Check if model is running
	

	//// --- MAKING PATIENTS ---
	patient** MyArrayOfPointersToPatients = new patient*[2];			// First 'patient*' is a pointer (address) and 'new patient' and space for 4 patients which will point to actual patienbt below
    
	for(int i=0; i<2; i++){
		MyArrayOfPointersToPatients[i]=new patient();}					// The 'new patient' the actual new patient
					
	
	
  	//// --- ASSIGN PATIENT CHARACTERISTICS ---
	for(int i=0; i<2; i++){												// --- Assign PatientID ---
		int a=i;
		(MyArrayOfPointersToPatients[i])->PatientIDAssign(a);}

	for(int i=0; i<2; i++){												// --- Assign Sex- ---
		(MyArrayOfPointersToPatients[i])->GenderDistribution();}
	
	for(int i=0; i<2; i++){												// --- Assign DoB/Age --- 
		(MyArrayOfPointersToPatients[i])->GetMyYearOfBirth(28,28);}

	for(int i=0; i<2; i++){												// --- Assign DoB/Age --- 
		(MyArrayOfPointersToPatients[i])->GetMyBirthday(1,12);}

	for(int i=0; i<2; i++){												// --- Assign date of death ---  
		(MyArrayOfPointersToPatients[i])->GetDateOfDeath(18,80);}

	for(int i=0; i<2; i++){												// --- Assign Date of HIV
		(MyArrayOfPointersToPatients[i])->GetDateOfHIVInfection(1,2);}


	//// --- OUTPUT CHECKs ---
	cout<<endl<<"The patient's ID...."<< endl;							// --- Ouput all the patients' IDs ---
	for(int i=0; i<2; i++){
		(MyArrayOfPointersToPatients[i])->TellMyPatientID();}		
	
	cout<<endl<<"The sex of patients...."<< endl;						// --- Ouput all the patients' gender ---
	for(int i=0; i<2; i++){
        (MyArrayOfPointersToPatients[i])->TellMySex(); }

    cout<<endl<<"The year of birth of the patients..." << endl;			// --- Ouput all the patients' ages ---
	for(int i=0; i<2; i++){
		(MyArrayOfPointersToPatients[i])->TellMyDob(); }	

	cout<<endl<<"The birthday of the patients..." << endl;				// --- Ouput all the patients' ages ---
	for(int i=0; i<2; i++){
		(MyArrayOfPointersToPatients[i])->TellMyBD(); }
	
	cout<<endl<<"The year of the patients' death..." << endl;			// --- Ouput all the patients' date of deaths ---
	for(int i=0; i<2; i++){
		(MyArrayOfPointersToPatients[i])->TellMyExpectedDeathDate(); }			
	
	cout<<endl<<"The dates of HIV infection..." << endl;
	for(int i=0; i<2; i++){
		(MyArrayOfPointersToPatients[i])->TellMyHivDateSTART();}
	
		
	//// --- EVENTQ ---
	for(int i=0; i<2; i++){
	event * HivTest = new event;										// --- HIV Testing ---
	HivTest->time = MyArrayOfPointersToPatients[i]->MyDateOfHIV;
	HivTest->p_fun = &TellMyHivStatus;
	HivTest->patient_ID = MyArrayOfPointersToPatients[i];
	iQ.push(HivTest);}													// Add HIVTest to queue
	
	for(int i=0; i<2; i++){
	event * DeathDate = new event;										// --- Date of Death ---
	DeathDate->time = MyArrayOfPointersToPatients[i]->DateOfDeath;
	DeathDate->p_fun = &TellMyDeathDate;
	DeathDate->patient_ID = MyArrayOfPointersToPatients[i];
	iQ.push(DeathDate);	}												// Add Date of Death to queue
	
	for(int i=0; i<2; i++){
	event * BirthdayDate = new event;									// --- HIV Testing ---
	BirthdayDate->time = MyArrayOfPointersToPatients[i]->Birthday;
	BirthdayDate->p_fun = &TellMyBirthDate;
	BirthdayDate->patient_ID = MyArrayOfPointersToPatients[i];
	iQ.push(BirthdayDate);}												// Add HIVTest to queue
	
	
	//// --- GIVE OUTPUT OF QUEUE AS IT PROGRESSES ---
	cout << endl << endl << "Characteristics of the event queue:" << endl;
	cout << "The first event will ocurr  " << iQ.top()->time << " years after the start of model." << endl;
	cout << "The size of the event queue is " << iQ.size() << endl;
	
	while( GlobalTime< 80 /*|| !iQ.empty()*/){								// This loop throws up error because no recurrent birthday pushing GT over 5 yrs and iQ.pop means GT cannot be updated after pop
		GlobalTime=iQ.top()->time;

		cout << endl << endl << "An event has just ocurred.  " << endl;
		cout << "It is " << iQ.top()->time << " years after the start of the model.  " << endl 
			 << "Patient " ; iQ.top()-> p_fun(iQ.top()->patient_ID);
		
		GlobalTime=iQ.top()->time;											// CAREFUL WITH ORDER OF GLOBAL TIME UPDATE - DO NOT TOUCH OR TOUCH AND CHECK!!
		
		iQ.pop();		
		cout << endl << "This event has now been removed from the queue.  " << endl;}


	// --- END CODE ---
    cout << endl << "Hi Jack, so sorry\n";
	system("pause");
    return 0;
    
}
