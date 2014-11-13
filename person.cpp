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
	Sex=-999;
	DoB=-999;
	DateOfDeath=-999;
	HIVStatus=-999;
	MyDateOfHIV=-999;
	}


// --- FUNCTIONS TO CREATE OUTPUT ---
void patient::TellMyPatientID(){							// --- Tell PatientID ---
	cout << "The ID of patient " << PatientID << " is " << PatientID << endl;}

void patient::TellMySex(){									// --- Tell Sex ---
	cout << "The sex of patient " << PatientID << " is " << Sex << endl;}	

void patient::TellMyDob(){									// --- Tell Date of Birth ---	// Convert to date of birth later???
	cout << "The age of patient " << PatientID << " is " << DoB << endl;}

void patient::TellMyExpectedDeathDate(){									
	cout << "I, patient " << PatientID << ", will die " << DateOfDeath << " after the start of the model.  "  << endl;}

void patient::TellMyHivDateSTART(){									
	cout << "I, patient " << PatientID << ", will acquiere HIV " << MyDateOfHIV << " years after the start of the model" << endl;}


	
// --- FUNCTIONS TO ASSIGN CHARACTERISTICS ---	
void patient::PatientIDAssign(int x){						// --- Assign Patient ID ---
	PatientID=x+1;}

void patient::GenderDistribution(){							// --- Assign Gender Distribution ---
double	r = ((double) rand() / (RAND_MAX)) ;
	if (r<=0.7){  
		Sex=1;}												// No need to define in patient as first line of this chunk already states this is taking place in 'patient'
	else {Sex=2;}}

void patient::GetMyDateOfBirth(int min, int max){			// --- Assign Date Of Birth ---		
	DoB=(rand()%(max-min+1)+min)/**365*/;}					// Deal with birthday in years versus years later

void patient::GetDateOfDeath(int min, int max){				
	DateOfDeath=(rand()%(max-min+1)+min);}

void patient::GetDateOfHIVInfection(int min, int max){			
	MyDateOfHIV= (rand()%(max-min+1)+min);}

