//
//  Created by Mikaela Smit on 07/11/2014.
//  Copyright (c) 2014 Mikaela Smit. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include "eventfunctions.h"
#include "event.h"							// Need to add these to be able to	
#include "eventQ.h"							// [...]run Global Time and Recurrent events pointers
#include "person.h"

using namespace std;


//// --- MAKE SOME USEFUL POINTERS TO BE ABLE TO SCHEDULE RECURRENT EVENTS ---

extern double *p_GT;													// Tell this .cpp that there is pointer to Global Time defined externally
extern priority_queue<event*, vector<event*>, timeComparison> *p_PQ;	// Tell this .cpp that there is a priorty_queue externall and define pointer to it


//// --- FUNCTIONS FOR EVENTS ---

// --- HIV Testing ---
void TellMyHivStatus(){									
	cout << " just got an HIV test.  " << endl;}

void TellMyDeathDate(){									
	cout << " just died.  "  << endl;}

void TellMyBirthDate(){									
	cout << "I just had my birthday.  "  << endl;

	event * RecurrentBirthdayDate = new event;							// --- Schedule recurrent Birthday ---
	RecurrentBirthdayDate->time = *p_GT + 1;							// Re-use code as in main to add recurrent BD to the queue (incl time and function pointer)
	RecurrentBirthdayDate->p_fun = &TellMyBirthDate;	
	p_PQ->push(RecurrentBirthdayDate);
	cout << "My next Birthday will be " << *p_GT + 1 << " after the start of the model.  " << endl;
}
