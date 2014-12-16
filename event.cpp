//
//  Created by Mikael Smit on 30/10/2014. 
//  Copyright (c) 2014 Mikaela Smit. All rights reserved.
//  This script provides the properties of the new 'events' that are added to the EventQ 
//


#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "event.h"
#include "person.h"

//// --- Outside Information ---
extern double StartYear;									// Include Start Year so only have to change it once in main()

//// --- CLASS (EVENT) CONSTRUCTOR ---
event::event()			
	{
			time=StartYear;									// Miki Notes: Could also write with class constructor
															// [...] event::event():time(0),sex(2) 
															// [...] this is the same thing but could be 'clearner' if lots of functions in constructor
	} 



