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


//// --- MAKE SOME USEFUL POINTERS TO BE ABLE TO SCHEDULE RECURRENT EVENTS ---

extern double *p_GT;													// Tell this .cpp that there is pointer to Global Time defined externally
extern priority_queue<event*, vector<event*>, timeComparison> *p_PQ;	// Tell this .cpp that there is a priorty_queue externall and define pointer to it


//// --- FUNCTIONS FOR EVENTS ---

// --- HIV Testing ---
void TellMyHivStatus(patient *MyPointerToPatient){									// The bit inside the bracket allows to link event to specific patient using patient pointer 						
	 cout << MyPointerToPatient->PatientID << " just got an HIV test.  " << endl;}

void TellMyDeathDate(patient *MyPointerToPatient){									
	 cout << MyPointerToPatient->PatientID << " just died.  "  << endl;}

void TellMyBirthDate(patient *MyPointerToPatient){									
	
	 event * RecurrentBirthdayDate = new event;							// --- Schedule recurrent Birthday ---
	 RecurrentBirthdayDate->time = *p_GT + 1;							// Re-use code as in main to add recurrent BD to the queue (incl time and function pointer)
	 RecurrentBirthdayDate->p_fun = &TellMyBirthDate;
	 RecurrentBirthdayDate->patient_ID=MyPointerToPatient;
	 p_PQ->push(RecurrentBirthdayDate);

	 MyPointerToPatient->Age=MyPointerToPatient->Age+1; 
	 	
	 cout << MyPointerToPatient->PatientID << " just had their birthday.  They are now " << MyPointerToPatient->Age << " years old.  " << endl;
	 cout << "Patient " << MyPointerToPatient->PatientID << " will have their next birthday " << *p_GT + 1 << " years after model start.  " << endl;
}
