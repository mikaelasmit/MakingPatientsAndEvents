//
//  Mikaela Epidemiology Model
//
//  Created by Mikaela Smit on 15/10/2014.
//  Copyright (c) 2014 Mikael Smit. All rights reserved.
//


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
double *p_GT;														// Pointer to global time
priority_queue<event*, vector<event*>, timeComparison> *p_PQ;		// Pointer to event queue so as to be able to push-in/pop-out new events that are ocurreing
																	// [...] as a result of 'primary' events in the queue, e.g. recurrent birthdays

//// --- RUN THE MAIN MODEL ---
int main(){

	double GlobalTime=0;											// Define Global Time and set it to 0 at the beginning of the model
	p_GT=&GlobalTime;												// Define the location the pointer to Global time is pointing to
	
	srand(time(NULL));												// Random Number generator using PC time
	
	cout << "Hello, Mikaela!" << endl;								// Check if model is running
	priority_queue<event*, vector<event*>, timeComparison> iQ;
	
	p_PQ=&iQ;	

	
	//// --- MAKING POINTER TO ARRAY OF PATIENTS ---
	patient** MyArrayOfPointersToPatients = new patient*[1];		// first 'patient*' is a pointer (address) and 'new patient' and space for 4 patients which will point to actual patienbt below
    
	
    for(int i=0; i<1; i++){
        MyArrayOfPointersToPatients[i]=new patient();				// 'new patient' the actual new patient
		cout<<"Tell me I am a new patient " << i << endl;}			// Output that new patient was made
	
	
  	//// --- ASSIGN PATIENT CHARACTERISTICS ---
	for(int i=0; i<1; i++){											// --- Assign PatientID ---
		int a=i;
		(MyArrayOfPointersToPatients[i])->PatientIDAssign(a);}

	for(int i=0; i<1; i++){											// --- Assign PatientID ---
		(MyArrayOfPointersToPatients[i])->GetDateOfHIVInfection(1,2);}

	//// --- OUTPUT BEFORE - CHECK ---
	for(int i=0; i<1; i++){
		(MyArrayOfPointersToPatients[i])->TellMyPatientID();}		// Is better because it can only tell me my date of birth, whereas above it oculd accidenelty change it ...or something like that
	
	
	for(int i=0; i<1; i++){
		(MyArrayOfPointersToPatients[i])->TellMyHivDate();}
	

	for(int i=0; i<1; i++){
	event * HivTest = new event;									// --- HIV Testing ---
	HivTest->time = MyArrayOfPointersToPatients[i]->MyDateOfHIV;
	HivTest->p_fun = &TellMyHivDate;
	//HivTest->p_patient = &PatientID;
	iQ.push(HivTest);												// Add HIVTest to queue
	
	}

	//// --- GIVE OUTPUT OF QUEUE AS IT PROGRESSES ---
	// Lets check the queue
	cout << endl <<"Characteristics of the event queue:" << endl;
	cout << "The event at the top of the queue will ocurr  " << iQ.top()->time << " years after the start of model." << endl;
	cout << "The size of the event queue is " << iQ.size() << endl;
	
//while(GlobalTime<5)
//	{
//	cout << endl << "An event has just ocurred.  " << endl;
//	cout << "It is " << iQ.top()->time << " years after the start of the model and "; iQ.top()-> p_fun();
//	GlobalTime=iQ.top()->time;
//	cout << endl << "Global Time after this event is " << GlobalTime << endl;
//	
//	iQ.pop();
//	cout << endl << "An event has been removed from the queue.  " << endl;
//
//	GlobalTime=iQ.top()->time;										// Update Global time to make functions below correct
//	}

	// insert code here...
    cout << "Hi Jack, so sorry\n";
	system("pause");
    return 0;
    
}
