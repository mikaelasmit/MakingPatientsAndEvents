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


//To Do List:
//1.	Making a patient population (i.e. more than one) and assign variables (Patient ID, Sex, HIV status, Birthday, Date of Death,…) - DONE
//2.	Use simple distributions (e.g. uniform distribution, etc) to assign characteristics - DONE
//3.	Develop EventQ and play around with it – DONE
//4.	Insert events into the EventQ, e.g. HIV-infection, Death and Birthdays – DONE
//5.	Separate EventQ code into different .h and .cpp files – TOOK A WHILE BUT DONE
//6.	Insert a global time counter into the model to record time – DONE
//7.	Add global time to the EventQ – DONE
//8.	Make birthdays into recurrent event using pointers and global time  - DONE
//9.	Remove repeat code for EventQ and from main() and make into self-contained loop – DONE
//10.	Add stop time into the model for EventQ – DONE
//11.	Merge MakingPatients and EventQ code to make events happen to two different patients – DONE
//
//Worked on in the last few days:
//12.	Give patients an age using birthday and vice versa – DONE
//13.	Include Age at T0 to record age at start of model – DONE
//14.	Add ages to the EventQ and update every year – DONE
//15.	Make C++ output .csv  files to be able to run large populations and generate graphs – DONE
//16.	Find Kanyan age-distribution in 1950 - DONE
//17.	Add Kenyan age-distribution as per 1950s – DONE
//18.	Run model with this age distribution and generate population pyramids – DONE
//19.   Add new entries to run population forward and simulate population growth - DONE IN SIMPLE WAY
//20.	Make C++ run with Matlab – THIS IS TAKING A WHILE AND I AM STILL BUSY WITH THIS.  I am looking at SJ’s code today to see how her model is set up with Matlab
//
//Still to do:
//21.	Link deaths to age using a linear equation (increase age->increase death)
//22.	Compare mortality to data in Kenya, improve mortality as necessary
//23.	Improve new entry and discuss patient 'vector' with Tim (deal with bigger size)
//24.	Add HIV status and update it as a function of HIV test 
//25.	Add more aspects of HIV care cascade (diagnosis, start cART,…)


//// --- Function related to event - to be available externally ---
double *p_GT;																// Pointer to global time
double *p_SY;																// Pointer to start year of the model
double StartYear=1950;														// Define Start Year if the model and set it to year of choice
priority_queue<event*, vector<event*>, timeComparison> *p_PQ;				// Pointer to event queue so as to be able to push-in/pop-out new events that are ocurreing

																			// [...] as a result of 'primary' events in the queue, e.g. recurrent birthdays

//// --- Function relating to new entry - to be available externally ---
int final_number_people=10000;												// To determine the final size of the total population to be modeled 
int no_patients = 3;
int total_population=3;														// Update total population for output and for next new entry
double new_entry=1;															// To add new people

patient** MyArrayOfPointersToPatients = new patient*[final_number_people];	// First 'patient*' is a pointer (address) and 'new patient' and space for x patients which will point to actual patienbt below
																			// Have to now change [no_patients] to [final_number_people] to give the final size of 'matrix'

void MakeNewPatient(){
	for(int i=no_patients+1; i<no_patients+new_entry; i++){
		MyArrayOfPointersToPatients[i]=new patient();}}

void MakeNewPatientID(){
	for(int i=no_patients; i<no_patients+new_entry; i++){					// --- Assign NEW PatientID ---
		int a=i; (MyArrayOfPointersToPatients[i])->PatientIDAssign(a);}}

void MakeNewGenderDistribution(){
	for(int i=no_patients; i<no_patients+new_entry; i++){					// --- Assign NEW Sex- ---
		(MyArrayOfPointersToPatients[i])->GenderDistribution();}}

void MakeNewYearOfBirth(){
	for(int i=no_patients; i<no_patients+new_entry; i++){					// --- Assign NEW DoB/Age --- 
		(MyArrayOfPointersToPatients[i])->GetMyYearOfBirthNewEntry();}}

void MakeNewBirthdayM(){
	for(int i=no_patients; i<no_patients+new_entry; i++){					// --- Assign NEW DoB/Age --- 
		(MyArrayOfPointersToPatients[i])->GetMyBirthday(1,12);}}

//	for(int i=no_patients; i<no_patients+new_entry; i++){					// --- Assign NEW date of death ---  
//		(MyArrayOfPointersToPatients[i])->GetDateOfDeath(18,80);}
//
//	//for(int i=no_patients; i<no_patients+new_entry; i++){					// --- Assign NEW Date of HIV
//	//	(MyArrayOfPointersToPatients[i])->GetDateOfHIVInfection(1,2);}



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
	
		
	//// --- Making Patients ---
	for(int i=0; i<final_number_people; i++){								// Remember to aslo give final size or it will give error 
		MyArrayOfPointersToPatients[i]=new patient();}						// The 'new patient' the actual new patient
	

	//// --- Assign Patient Characteristics ---
	for(int i=0; i<no_patients; i++){										// --- Assign PatientID ---
		int a=i;
		(MyArrayOfPointersToPatients[i])->PatientIDAssign(a);}

	for(int i=0; i<no_patients; i++){										// --- Assign Sex- ---
		(MyArrayOfPointersToPatients[i])->GenderDistribution();}
	
	for(int i=0; i<no_patients; i++){										// --- Assign DoB/Age --- 
		(MyArrayOfPointersToPatients[i])->GetMyYearOfBirth();}

	for(int i=0; i<no_patients; i++){										// --- Assign DoB/Age --- 
		(MyArrayOfPointersToPatients[i])->GetMyBirthday(1,12);}

	for(int i=0; i<no_patients; i++){										// --- Assign date of death ---  
		(MyArrayOfPointersToPatients[i])->GetDateOfDeath(18,80);}

	for(int i=0; i<no_patients; i++){										// --- Assign Date of HIV
		(MyArrayOfPointersToPatients[i])->GetDateOfHIVInfection(1,2);}

		
	//// --- EVENTQ ---
	
	//for(int i=0; i<no_patients; i++){
	//event * DeathDate = new event;										// --- Date of Death ---
	//DeathDate->time = MyArrayOfPointersToPatients[i]->DateOfDeath;
	//DeathDate->p_fun = &EventMyDeathDate;
	//DeathDate->patient_ID = MyArrayOfPointersToPatients[i];
	//iQ.push(DeathDate);	}												// Add Date of Death to queue
	//
	//for(int i=0; i<no_patients; i++){
	//event * BirthdayDate = new event;										// --- HIV Testing ---
	//BirthdayDate->time = StartYear + MyArrayOfPointersToPatients[i]->BirthdayY;
	//BirthdayDate->p_fun = &EventMyBirthDate;
	//BirthdayDate->patient_ID = MyArrayOfPointersToPatients[i];
	//iQ.push(BirthdayDate);}												// Add HIVTest to queue

	for(int i=no_patients; i<no_patients+new_entry; i++){
	event * NewEntry = new event;											// --- New Entry ---
	NewEntry->time = GlobalTime+1;
	NewEntry->p_fun = &EventNewEntry;
	NewEntry->patient_ID = MyArrayOfPointersToPatients[i];
	iQ.push(NewEntry);}	

	//for(int i=0; i<no_patients; i++){
	//event * HivTest = new event;											// --- HIV Testing ---
	//HivTest->time = MyArrayOfPointersToPatients[i]->MyDateOfHIV;
	//HivTest->p_fun = &TellMyHivStatus;
	//HivTest->patient_ID = MyArrayOfPointersToPatients[i];
	//iQ.push(HivTest);}													// Add HIVTest to queue
	//
		
	
	//// --- GIVE OUTPUT OF QUEUE AS IT PROGRESSES ---
	cout << endl << endl << "Characteristics of the event queue:" << endl;
	cout << "The first event will ocurr  " << iQ.top()->time << " years after the start of model." << endl;
	cout << "The size of the event queue is " << iQ.size() << endl;
	
	while(GlobalTime< 1951 /*|| !iQ.empty()*/){								// This loop throws up error because no recurrent birthday pushing GT over 5 yrs and iQ.pop means GT cannot be updated after pop
		GlobalTime=iQ.top()->time;

		cout << endl << endl << "An event has just ocurred.  " << endl;
		cout << "It is " << iQ.top()->time << " years after the start of the model.  " << endl 
			 << "Patient " ; iQ.top()-> p_fun(iQ.top()->patient_ID);
		
		//GlobalTime=iQ.top()->time;											// CAREFUL WITH ORDER OF GLOBAL TIME UPDATE - DO NOT TOUCH OR TOUCH AND CHECK!!
		
		iQ.pop();		
		cout << endl << "This event has now been removed from the queue.  " << endl;}


	//// --- Output the results in a csv file ---
	FILE* csv_out = fopen("test.csv","w");
	for (int i=0; i<total_population; i++) {							// Change the i< X here as well as the "%d!!
		fprintf(csv_out,"%d,%d,%d,%d \n",
			MyArrayOfPointersToPatients[i]->PatientID,
			MyArrayOfPointersToPatients[i]->Sex,
			MyArrayOfPointersToPatients[i]->DoB,
			MyArrayOfPointersToPatients[i]->Age
			//, 
			//MyArrayOfPointersToPatients[i]->DateOfDeath/*,
			//MyArrayOfPointersToPatients[i]->MyDateOfHIV*/
			);}
	fclose(csv_out);


	// --- End of code ---
    cout << endl << "Hi Jack, so sorry\n";
	system("pause");
    return 0;
}



// --- OUTPUT CHECKs --- 
	//cout<<endl<<"The patient's ID...."<< endl;							// --- Ouput all the patients' IDs ---
	//for(int i=0; i<no_patients; i++){
	//	(MyArrayOfPointersToPatients[i])->TellMyPatientID();}		
	//
	//cout<<endl<<"The sex of patients...."<< endl;							// --- Ouput all the patients' gender ---
	//for(int i=0; i<no_patients; i++){
	//   (MyArrayOfPointersToPatients[i])->TellMySex(); }

	//cout<<endl<<"The year of birth of the patients..." << endl;			// --- Ouput all the patients' ages ---
	//for(int i=0; i<no_patients; i++){
	//	(MyArrayOfPointersToPatients[i])->TellMyDob(); }	

	//cout<<endl<<"The birthday of the patients..." << endl;				// --- Ouput all the patients' ages ---
	//for(int i=0; i<no_patients; i++){
	//	(MyArrayOfPointersToPatients[i])->TellMyBD(); }
	//
	//cout<<endl<<"The year of the patients' death..." << endl;				// --- Ouput all the patients' date of deaths ---
	//for(int i=0; i<no_patients; i++){
	//	(MyArrayOfPointersToPatients[i])->TellMyExpectedDeathDate(); }			
	//
	//cout<<endl<<"The dates of HIV infection..." << endl;
	//for(int i=0; i<no_patients; i++){
	//	(MyArrayOfPointersToPatients[i])->TellMyHivDateSTART();}
