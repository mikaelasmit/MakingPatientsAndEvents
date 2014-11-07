//
//  Created by Mikaela Smit on 22/10/2014.
//  Copyright (c) 2014 Mikael Smit. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "person.h"
#include "event.h"




//// --- CLASS (PATIENT) CONSTRUCTOR ---

patient::patient()											// First 'patient' class second constructor/variable and no return type means its a constructor
	{
    PatientID=0;
	HIVStatus=-999;
	MyDateOfHIV=-999;
	//Sex=-999;
	//DoB=-999;
	//CD4CellCountCat=-999;
	}


// --- FUNCTIONS TO CREATE OUTPUT ---
void patient::TellMyPatientID(){							// --- Tell PatientID ---
	cout <<" My Patient ID is..." << PatientID << endl;}

void patient::TellMyHivDate(){									
	cout << "I will acquiere HIV " << MyDateOfHIV << " years after the start of the model" << endl;}

	
// --- FUNCTIONS TO ASSIGN CHARACTERISTICS ---	
void patient::PatientIDAssign(int x){						// --- Assign Patient ID ---
	PatientID=x+1;}

void patient::GetDateOfHIVInfection(int min, int max){			
	MyDateOfHIV= (rand()%(max-min+1)+min);}

