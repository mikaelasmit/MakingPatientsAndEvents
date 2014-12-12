//
//  Created by Mikaela Smit on 07/11/2014. 
//  Copyright (c) 2014 Mikaela Smit. All rights reserved.
//  These event are added to the EventQ
//

#include <stdio.h>
#include "person.h"

using namespace std;


	//// ---- HIV EVENTS ---
	
	//double GetDateOfHIVInfection(int x, int y);						// Function to get date of HIV infection
	void TellMyHivStatus(patient *MyPointerToPatient);					// Function to be executed when HIV infection occurs
	void TellMyDeathDate(patient *MyPointerToPatient);
	void TellMyBirthDate(patient *MyPointerToPatient);