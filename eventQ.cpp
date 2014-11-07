//
//  Created by Mikaela Smit on 30/10/2014.
//  Copyright (c) 2014 Mikael Smit. All rights reserved.
//

#include "event.h"
#include "eventQ.h"

//// --- USE TIME COMPARISON AND OPERATOR ---
bool timeComparison::operator()(const event *lhs, const event *rhs) const{
	return lhs->time > rhs->time;}
 	
//// --- CLASS (EVENTQ) CONSTRUCTOR ---- 
eventQ::eventQ()
{}


