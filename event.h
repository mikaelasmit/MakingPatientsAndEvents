//
//  Created by Mikaela Smit on 07/11/2014.   
//  Copyright (c) 2014 Mikaela Smit. All rights reserved.
//  This script provides the properties of the new 'events' that are added to the EventQ 
//

#ifndef event_h										
#define event_h	

#include <stdio.h>
#include "person.h"										// Need to include person header as we make pointer to persons in below
using namespace std;


class event {
public:

//// --- EVENT Q SPECIFIC --- ////

	event();											// Class constructor
 	
 	double time;	

 	void (*p_fun)(person *MyPointerToPerson);			// Function pointer - when an event is called in the Q it can point to what functions need to be executed
														// [...] e.g. If person gets pos HIVTest tell him to schedule GP appointment
														// [...] the bit inside the brackets "(person *MyPointerToPerson) means function can carry argument which is pointer 'pointer' to class 'person'.  
	
	person * person_ID;		 							// This means that there is a pointer called 'person_ID' which is pointing to class 'person'
														// [...] allows to make sure all events, including new ones, point to the correct person to whom this event is occurring.  
	};

#endif													





