//
//  Created by Mikaela Smit on 30/10/2014.
//  Copyright (c) 2014 Mikaela Smit. All rights reserved.
//  This script is to make the EventQ itself - can add personalised 'push' 'pop' etc here as Jack did if necessary
//

#include "event.h"
#include "eventQ.h"

//// --- Outside Information ---
bool timeComparison::operator()(const event *lhs, const event *rhs) const{
	return lhs->time > rhs->time;}
 	
//// --- Class (EventQ) Constructor ---- 
eventQ::eventQ()
{} 


