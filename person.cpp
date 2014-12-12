//
//  Created by Mikaela Smit on 22/10/2014.
//  Copyright (c) 2014 Mikael Smit. All rights reserved.
//  This script makes the patients in the cohort
//

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "person.h"
#include "event.h"


extern double *p_SY;										// Include here to be able to calculate patients' age
extern double StartYear;									// Include Start Year so only have to change it once in main()
int RandomAge(int min, int max){							// Provide function for random number generator to asisgn age
	return rand()%(max-min+1)+min;}


//// --- CLASS (PATIENT) CONSTRUCTOR ---

patient::patient()											// First 'patient' class second constructor/variable and no return type means its a constructor
	{
    PatientID=0;
	Sex=-999;

	DoB=-999;
	AgeT0=-999;
	Age=-999;
	BirthdayM=-999;
	BirthdayY=-999;

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
	cout << "The year of birth of patient " << PatientID << " is " << DoB << " and their age is " << Age << endl;}

void patient::TellMyBD(){									// --- Tell Birthday ---	// Convert to date of birth later???
	cout << "The birthday of patient " << PatientID << " is " << BirthdayY << " and Birthday month is " << BirthdayM << endl;}

void patient::TellMyExpectedDeathDate(){									
	cout << "I, patient " << PatientID << ", will die " << DateOfDeath << " after the start of the model.  "  << endl;}

void patient::TellMyHivDateSTART(){									
	cout << "I, patient " << PatientID << ", will acquiere HIV " << MyDateOfHIV << " years after the start of the model" << endl;}



// --- FUNCTIONS TO ASSIGN CHARACTERISTICS ---	
void patient::PatientIDAssign(int x){						// --- Assign Patient ID ---
	PatientID=x+1;}

void patient::GenderDistribution(){							// --- Assign Gender Distribution ---
double	r = ((double) rand() / (RAND_MAX)) ;
	if (r<=0.5043){Sex=1;}									
	else {Sex=2;}}

void patient::GetMyYearOfBirth(int min, int max){			// --- Assign Year Of Birth, Age, etc ---		
	double a = ((double) rand() / (RAND_MAX));

	if (Sex==1);
	if (a<=0.1729813){AgeT0 = RandomAge(0,4);}				// Using the Kenyan age-distribution as per UN data
	if (a>0.1729813 && a<=0.2885448){AgeT0 = RandomAge(5,9);}
	if (a>0.2885448 && a<=0.3952457){AgeT0 = RandomAge(10,14);}
	if (a>0.3952457 && a<=0.4984330){AgeT0 = RandomAge(15,19);}
	if (a>0.4984330 && a<=0.5870602){AgeT0 = RandomAge(20,24);}
	if (a>0.5870602 && a<=0.6623300){AgeT0 = RandomAge(25,29);}
	if (a>0.6623300 && a<=0.7275660){AgeT0 = RandomAge(30,34);}
	if (a>0.7275660 && a<=0.7861866){AgeT0 = RandomAge(35,39);}
	if (a>0.7861866 && a<=0.8383183){AgeT0 = RandomAge(40,44);}
	if (a>0.8383183 && a<=0.8815241){AgeT0 = RandomAge(45,49);}
	if (a>0.8815241 && a<=0.9174181){AgeT0 = RandomAge(50,54);}
	if (a>0.9174181 && a<=0.9459054){AgeT0 = RandomAge(55,59);}
	if (a>0.9459054 && a<=0.9680306){AgeT0 = RandomAge(60,64);}
	if (a>0.9680306 && a<=0.9836036){AgeT0 = RandomAge(65,69);}
	if (a>0.9836036 && a<=0.9929412){AgeT0 = RandomAge(70,74);}
	if (a>0.9929412 && a<=0.9977840){AgeT0 = RandomAge(75,79);}
	if (a>0.9977840 && a<=1){AgeT0 = RandomAge(80,100);}

	if (Sex==2);
	if (a<=0.1746637){AgeT0 = RandomAge(0,4);}
	if (a>0.1746637 && a<=0.2917179){AgeT0 = RandomAge(5,9);}
	if (a>0.2917179 && a<=0.4002065){AgeT0 = RandomAge(10,14);}
	if (a>0.4002065 && a<=0.5020936){AgeT0 = RandomAge(15,19);}
	if (a>0.5020936 && a<=0.5866883){AgeT0 = RandomAge(20,24);}
	if (a>0.5866883 && a<=0.6556006){AgeT0 = RandomAge(25,29);}
	if (a>0.6556006 && a<=0.7150133){AgeT0 = RandomAge(30,34);}
	if (a>0.7150133 && a<=0.7665365){AgeT0 = RandomAge(35,39);}
	if (a>0.7665365 && a<=0.8131972){AgeT0 = RandomAge(40,44);}
	if (a>0.8131972 && a<=0.8565411){AgeT0 = RandomAge(45,49);}
	if (a>0.8565411 && a<=0.8951191){AgeT0 = RandomAge(50,54);}
	if (a>0.8951191 && a<=0.9273211){AgeT0 = RandomAge(55,59);}
	if (a>0.9273211 && a<=0.9533403){AgeT0 = RandomAge(60,64);}
	if (a>0.9533403 && a<=0.9733055){AgeT0 = RandomAge(65,69);}
	if (a>0.9733055 && a<=0.9866050){AgeT0 = RandomAge(70,74);}
	if (a>0.9866050 && a<=0.9952995){AgeT0 = RandomAge(75,79);}
	if (a>0.9952995 && a<=1){AgeT0 = RandomAge(80,100);}
		
	DoB=(StartYear-AgeT0);
	Age=AgeT0; 
	}	 				

void patient::GetMyBirthday(int min, int max){				// --- Assign Month of Birthday ---		
	BirthdayM=((rand()%(max-min+1)+min));					// Helps 'distribute' birthdays across the year
	BirthdayY=BirthdayM/12.1;}

void patient::GetDateOfDeath(int min, int max){				
	DateOfDeath=(rand()%(max-min+1)+min);}

void patient::GetDateOfHIVInfection(int min, int max){			
	MyDateOfHIV= (rand()%(max-min+1)+min);}

