//
//  Created by Mikaela Smit on 22/10/2014.
//  Copyright (c) 2014 Mikael Smit. All rights reserved.
//  This script makes the people in the cohort
//

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "person.h"
#include "event.h"
#include "eventfunctions.h"


//// --- Outside Information ---
extern double *p_GT;										// Tell this .cpp that there is pointer to Global Time defined externally
extern double *p_SY;										// Include here to be able to calculate peoples' age
extern double StartYear;									// Include Start Year so only have to change it once in main()
int RandomAge(int min, int max){							// Provide function for random number generator to asisgn age
	return rand()%(max-min+1)+min;}


//// --- Class (Population) Constructor --- ////

person::person()											// First 'person' class second constructor/variable and no return type means its a constructor
	{
    PersonID=0;
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


// --- Functions to create Output ---
void person::TellMyPersonID(){								// --- Tell PersonID ---
	cout << "The ID of person " << PersonID << " is " << PersonID << endl;}

void person::TellMySex(){									// --- Tell Sex ---
	cout << "The sex of person " << PersonID << " is " << Sex << endl;}	

void person::TellMyDob(){									// --- Tell Date of Birth ---	// Convert to date of birth later???
	cout << "The year of birth of person " << PersonID << " is " << DoB << " and their age is " << Age << endl;}

void person::TellMyBD(){									// --- Tell Birthday ---	// Convert to date of birth later???
	cout << "The birthday of person " << PersonID << " is " << BirthdayY << " and Birthday month is " << BirthdayM << endl;}

void person::TellMyExpectedDeathDate(){									
	cout << "I, person " << PersonID << ", will die in" << DateOfDeath << endl;}

void person::TellMyHivDateSTART(){									
	cout << "I, person " << PersonID << ", will acquiere HIV is" << MyDateOfHIV << endl;}



// --- Funcitons to assign characteristics ---	
void person::PersonIDAssign(int x){							// --- Assign Person ID ---
	PersonID=x+1;}

void person::GenderDistribution(){							// --- Assign Gender Distribution ---
double	r = ((double) rand() / (RAND_MAX)) ;
	if (r<=0.5043){Sex=1;}									
	else {Sex=2;}

	//if (Sex==2) {&person::GetDateBirthFirstChild;}
}


void person::GetMyYearOfBirth(){							// --- Assign Year Of Birth, Age, etc ---		
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

void person::GetMyYearOfBirthNewEntry(){					// --- Assign Age for New Entry ---
	AgeT0=0;
	Age=AgeT0;
	DoB=(*p_GT-AgeT0);}


void person::GetMyBirthday(int min, int max){				// --- Assign Month of Birthday ---		
	BirthdayM=((rand()%(max-min+1)+min));					// Helps 'distribute' birthdays across the year
	BirthdayY=BirthdayM/12.1;}

void person::GetDateOfDeath(int min, int max){				// --- Assign Date of death ---	
	DateOfDeath=*p_GT + (rand()%(max-min+1)+min);}			// INSERT FUNCTION FOR DEATH HERE

void person::GetDateOfHIVInfection(int min, int max){		// --- Assign Date of HIV infection ---		
	MyDateOfHIV=*p_GT + (rand()%(max-min+1)+min);}


