////
////  Created by Mikaela Smit on 07/11/2014.   
////  Copyright (c) 2014 Mikaela Smit. All rights reserved.
////  This script provides the properties of the new 'events' that are added to the EventQ 
////
//
//#ifndef event_h										
//#define event_h	
//
//#include <stdio.h>
//#include "person.h"										// Need to include patient header as we make pointer to patient below
//
//using namespace std;
//
//
// class externevent {
// public:
//
//	//// --- EVENT Q SPECIFIC ---
//
//
//	event();											//class constructor
// 	
// 	double time;	
//
// 	void (*p_fun)(patient *MyPointerToPatient);			// Function pointer - when an event is called in the Q it can point to what functions need to be executed
//														// [...] e.g. If patient gets pos HIVTest tell him to schedule GP appointment
//														// [...] the bit inside the brackets "(patient *MyPointerToPatient) means function can carry argument which is pointer 'pointer' to class 'patient'.  
//	
//	patient * patient_ID;		 						// This means that there is a pointer called 'patient_ID' which is pointing to class 'patient'
//														// [...] allows to make sure all events, including new ones, point to the correct patient to whom this event is occurring.  
//
//	};
//
//#endif 
//
//
//
//
//
