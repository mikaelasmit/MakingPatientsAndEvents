//
//  Created by Mikaela Smit on 07/11/2014.
//  Copyright (c) 2014 Mikaela Smit. All rights reserved.
//  These event are added to the EventQ
//

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include "eventfunctions.h"
#include "event.h"														// Need to add these to be able to	
#include "eventQ.h"														// [...]run Global Time and Recurrent events pointers
#include "person.h"
using namespace std;


//// --- Outside Information ---
extern double *p_GT;													// Tell this .cpp that there is pointer to Global Time defined externally
extern priority_queue<event*, vector<event*>, timeComparison> *p_PQ;	// Tell this .cpp that there is a priorty_queue externall and define pointer to it

extern int final_number_people;											// To determine the final size of the total population to be modeled 
extern int no_patients;
extern int total_population;											// Update total population for output and for next new entry
extern double new_entry;	

extern void MakeNewPatient();
extern void MakeNewPatientID();
extern void MakeNewGenderDistribution();
extern void MakeNewYearOfBirth();
extern void MakeNewBirthdayM();


//// --- FUNCTIONS FOR EVENTS --- ////
void EventMyHivStatus(patient *MyPointerToPatient){						// The bit inside the bracket allows to link event to specific patient using patient pointer 						
	 cout << MyPointerToPatient->PatientID << " just got an HIV test.  " << endl;}


void EventMyDeathDate(patient *MyPointerToPatient){									
	 cout << MyPointerToPatient->PatientID << " just died.  "  << endl;}


void EventMyBirthDate(patient *MyPointerToPatient){									
	
	 event * RecurrentBirthdayDate = new event;							// --- Schedule recurrent Birthday ---
	 RecurrentBirthdayDate->time = *p_GT + 1;							// Re-use code as in main to add recurrent BD to the queue (incl time and function pointer)
	 RecurrentBirthdayDate->p_fun = &EventMyBirthDate;
	 RecurrentBirthdayDate->patient_ID=MyPointerToPatient;
	 p_PQ->push(RecurrentBirthdayDate);

	 MyPointerToPatient->Age=MyPointerToPatient->Age+1; 
	 	
	 cout << MyPointerToPatient->PatientID << " just had their birthday.  They are now " << MyPointerToPatient->Age << " years old.  " << endl;
	 cout << "Patient " << MyPointerToPatient->PatientID << " will have their next birthday " << *p_GT + 1 << " years after model start.  " << endl;
}


void EventNewEntry(patient *MyPointerToPatient){	

	cout << "New patients are being created" << endl;
	
	 //event * RecurrentNewEntry = new event;							// --- Schedule recurrent New Entry ---
	 //RecurrentNewEntry->time = *p_GT + 2;								// Re-use code as in main to add recurrent BD to the queue (incl time and function pointer)
	 //RecurrentNewEntry->p_fun = &EventNewEntry;
	 //RecurrentNewEntry->patient_ID=MyPointerToPatient;
	 //p_PQ->push(RecurrentNewEntry);

		
	//// --- CODE FOR NEW ENTRY (THE SIMPLE WAY!!) --- ////				// This 'for' loop gives the right numbers of birth by calendar time 
	if (*p_GT>=1950 & *p_GT<1955)			{new_entry=335;}			// [...] according to Un data
	if (*p_GT>=1955 & *p_GT<1960)			{new_entry=388;}
	if (*p_GT>=1960 & *p_GT<1965)			{new_entry=449;}
	if (*p_GT>=1965 & *p_GT<1970)			{new_entry=525;}
	if (*p_GT>=1970 & *p_GT<1975)			{new_entry=628;}
	if (*p_GT>=1975 & *p_GT<1980)			{new_entry=743;}
	if (*p_GT>=1980 & *p_GT<1985)			{new_entry=869;}
	if (*p_GT>=1985 & *p_GT<1990)			{new_entry=972;}
	if (*p_GT>=1990 & *p_GT<1995)			{new_entry=1006;}
	if (*p_GT>=1995 & *p_GT<2000)			{new_entry=1123;}
	if (*p_GT>=2000 & *p_GT<2005)			{new_entry=1304;}
	if (*p_GT>=2005 & *p_GT<2011)			{new_entry=1455;}

	cout << "The number of new entries is " << new_entry << " and it is " << *p_GT << endl;		// Check to make sure the number of New Entry is correct 

	MakeNewPatient();													// Make new patients in the Array.  The below functions give them characteristics
	MakeNewPatientID();
	MakeNewGenderDistribution();
	MakeNewYearOfBirth();
	MakeNewBirthdayM();

//	 total_population=no_patients+new_entry;								// Update total population for output and for next new entry
//
//	 cout << MyPointerToPatient->PatientID << " has just been created and is " << MyPointerToPatient->Age << " years old.  " << endl;
}


