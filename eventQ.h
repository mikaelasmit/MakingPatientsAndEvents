//
//  Created by Mikaela Smit on 30/10/2014.
//  Copyright (c) 2014 Mikael Smit. All rights reserved.
//

#ifndef eventQ_h							
#define eventQ_h				

#include <stdio.h>							// Refers to C StandarD Input Output library - uses streams to operate with physical devices including keyboards
#include <queue>							// Needed for the priorityQ

using namespace std;



//// --- DEFINE THE COMPARISON CLASS AND DEFINE OPERATOR() ---
struct timeComparison {bool operator()(const event *lhs, const event *rhs) const;};	


//// --- CREATING EVENTQ ---
class eventQ{
public:

	eventQ();								// Constructor

};

#endif		

