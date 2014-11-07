//
//  Created by Mikaela Smit on 03/11/2014.
//  Modified by Mikaela Smit on 05/11/2014.  
//  Copyright (c) 2014 Mikaela Smit. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include "eventfunctions.h"
#include "event.h"							// Need to add these to be able to	
#include "eventQ.h"							// [...]run Global Time and Recurrent events pointers

using namespace std;


//// --- MAKE SOME USEFUL POINTERS TO BE ABLE TO SCHEDULE RECURRENT EVENTS ---

extern double *p_GT;													// Tell this .cpp that there is pointer to Global Time defined externally
extern priority_queue<event*, vector<event*>, timeComparison> *p_PQ;	// Tell this .cpp that there is a priorty_queue externall and define pointer to it


//// --- FUNCTIONS FOR EVENTS ---

// --- HIV Testing ---
void TellMyHivDate(){									
	cout << "I just got an HIV test.  " << endl;}

