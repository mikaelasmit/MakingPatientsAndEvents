/////////////////////////////////////////////////////////////////
//    Created by Mikaela Smit on 22/10/2014.				   //
//    Copyright (c) 2014 Mikaela Smit. All rights reserved.    //
//    This script makes the people in the cohort.			   //
/////////////////////////////////////////////////////////////////


#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "person.h"
#include "event.h"
#include "eventfunctions.h"



//// --- OUTSIDE INFORMATION --- ////
extern double *p_GT;							// Tell this .cpp that there is pointer to Global Time defined externally
extern double *p_SY;										// Include here to be able to calculate peoples' age
extern double StartYear;						// Include Start Year so only have to change it once in main()

int RandomAge(int min, int max){				// Provide function for random number generator to asisgn age
	return rand()%(max-min+1)+min;}

double RandomFirstBirth(int min, int max){		// Provides function for random number generator to assign first birth for women
	return rand()%(max-min+1)+min;}

double GetMonthBD(int min, int max){		// Provides function for random number generator to assign birthdya month
	return rand()%(max-min+1)+min;}



////// TO BE DELETED LATER _ JUST CHECKING
//int GetMonth;									// Helps 'distribute' birthdays across the year
//double GetYearFraction;								// Assign year fraction of birth month, e.g. June is 0.5 of the year
//	


//// --- CLASS (POPULATION) CONSTRUCTOR --- ////

person::person()								// First 'person' class second constructor/variable and no return type means its a constructor
{
    PersonID=0;									// Peoples' basic information
	Sex=-999;

	DoB=-999;									// Varibales related to peoples' age and birthday
	AgeT0=-999;
	Age=-999;

	ChildID=-999;								// Variables related to birth of first child
	BirthFirstChild=9999;						// VERY IMPORTANT  this number needs to be HIGH as it entres EventQ...
	MotherID=-999;

	DateOfDeath=-999;							// Varibles related to death 
	Alive=-999;									// Variable to update eventQ - global check to see if person is still alive
		
	HIVStatus=-999;								// Variables related to HIV-infection
	MyDateOfHIV=-999;
}



//// --- FUNCTION TO GENERATE OUTPUT --- ////
void person::TellMyPersonID(){																		// --- Tell PersonID ---
	cout << "The ID of person " << PersonID << " is " << PersonID << endl;}

void person::TellMyLifeStatus(){
	cout << "The Life Status of person " << PersonID << " is " << Alive << endl;}

void person::TellMySex(){																			// --- Tell Sex ---
	cout << "The sex of person " << PersonID << " is " << Sex << endl;}	

void person::TellMyFirstChildBirth(){																// --- Tell Birth My First Child ---
	cout << "My Sex is " << Sex << " and I will have my first baby on " << BirthFirstChild << endl;}

void person::TellMyYearOfBirth(){																	// --- Tell Year of Birth ---	
	cout << "The year of birth of person " << PersonID << " is " << DoB << " and their age is " << Age << endl;}

void person::TellMyExpectedDeathDate(){																// --- Tell Expected Date of Death ---		
	cout << "I, person " << PersonID << ", will die in" << DateOfDeath << endl;}

void person::TellMyHivDateSTART(){																	// --- Tell Date of HIV Infection ---					
	cout << "I, person " << PersonID << ", will acquiere HIV is" << MyDateOfHIV << endl;}



//// --- FUNCTION TO ASSIGN CHARACTERISTIC FOR INITIAL POPULATION --- ////
void person::PersonIDAssign(int x){							// --- Assign Person ID ---
	PersonID=x+1;}

void person::GenderDistribution(){							// --- Assign Gender Distribution ---
double	r = ((double) rand() / (RAND_MAX)) ;
	if (r<=0/*0.5043*/){Sex=1;}									
	else {Sex=2;}
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

	int GetMonth=GetMonthBD(1,12);									// Helps 'distribute' birthdays across the year
	double GetYearFraction=GetMonth/12.1;								// Assign year fraction of birth month, e.g. June is 0.5 of the year
	
	//cout << "The Birthday will be  at " << GetYearFraction << " or Month " << GetMonth << endl;  /// POssible check code
	
	Age=AgeT0+GetYearFraction;
	DoB=(StartYear-Age);
	
}

void person::GetDateOfMyFirstBaby(){						// Get My First Child's Birthday
															// This method already calculates the child's month of birth by providing a year of birth with decimal
	double f = ((double) rand() / (RAND_MAX));

		if (Age>=15 && Age<20 && f<1/*0.169071*/){BirthFirstChild=*p_GT+(RandomFirstBirth(Age*10,199)/10)-Age;}
		if (Age>=20 && Age<25 && f<1/*0.351607*/){BirthFirstChild=*p_GT+(RandomFirstBirth(Age*10,249)/10)-Age;}
		if (Age>=25 && Age<30 && f<1/*0.338141*/){BirthFirstChild=*p_GT+(RandomFirstBirth(Age*10,299)/10)-Age;}
		if (Age>=30 && Age<35 && f<1/*0.284278*/){BirthFirstChild=*p_GT+(RandomFirstBirth(Age*10,349)/10)-Age;}
		if (Age>=35 && Age<40 && f<1/*0.203483*/){BirthFirstChild=*p_GT+(RandomFirstBirth(Age*10,399)/10)-Age;}
		if (Age>=40 && Age<45 && f<1/*0.110719*/){BirthFirstChild=*p_GT+(RandomFirstBirth(Age*10,449)/10)-Age;}
		if (Age>=45 && Age<50 && f<1/*0.038901*/){BirthFirstChild=*p_GT+(RandomFirstBirth(Age*10,499)/10)-Age;}

}

void person::GetDateOfDeath(int min, int max){				// --- Assign Date of death ---	
	DateOfDeath=*p_GT + (rand()%(max-min+1)+min);}			// INSERT FUNCTION FOR DEATH HERE


void person::GetDateOfHIVInfection(int min, int max){		// --- Assign Date of HIV infection ---		
	MyDateOfHIV=*p_GT + (rand()%(max-min+1)+min);}



//// --- FUNCTIONS FOR NEW ENTRY --- ////
void person::GetMyYearOfBirthNewEntry(){					// --- Assign Age for New Entry ---
	AgeT0=0;												// Set all new entries as 'newborns' 
	Age=AgeT0;
	DoB=(*p_GT-AgeT0);}

