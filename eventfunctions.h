/////////////////////////////////////////////////////////////////
//    Created by Mikaela Smit on 07/11/2014.				   //	
//    These event are added to the EventQ.					   //
/////////////////////////////////////////////////////////////////

#include <stdio.h>
#include "person.h"
using namespace std;


//// ---- NOTE: Think about having different types of events ----

	//// --- Demographic Events ---
	void EventMyDeathDate(person *MyPointerToPerson);			// Add deaths to eventQ
	void EventBirth(person *MyPointerToPerson);					// Add births to EventQ
	
	
	//// --- Calendar Events ---
	void EventTellNewYear(person *MyPointerToPerson);			// Tell us when a new year start an update calendar-related items
	
	