//
//  Created by Mikael Smit on 30/10/2014. 
//  Copyright (c) 2014 Mikaela Smit. All rights reserved.
//


#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "event.h"
#include "person.h"


//// --- CLASS (EVENT) CONSTRUCTOR ---
event::event()			
	{

	time=0;														// Miki Notes: Could also write with class constructor
																// [...] event::event():time(0),sex(2) 
																// [...] this is the same thing but could be 'clearner' if lots of functions in constructor
	}



