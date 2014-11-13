//
//  Created by Mikaela Smit on 07/11/2014.   
//  Copyright (c) 2014 Mikaela Smit. All rights reserved.
//

#ifndef event_h										
#define event_h	

#include <stdio.h>

using namespace std;


 class event {
 public:

	//// --- EVENT Q SPECIFIC ---

	event();										//class constructor
 	
 	double time;	

 	void (*p_fun)();								// Function pointer - when an event is called in the Q it can point to what functions need to be executed
													// [...] e.g. If patient gets pos HIVTest tell him to schedule GP appointment
	int patientID;		 					// Jack notes: - make private eventually. - function to what to excexute when event happens

	};

#endif 





