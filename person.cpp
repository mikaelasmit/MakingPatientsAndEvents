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
#include <vector>


//// --- OUTSIDE INFORMATION --- ////
extern double *p_GT;								// Tell this .cpp that there is pointer to Global Time defined externally 
extern double *p_SY;								// Include here to be able to calculate peoples' age
extern double StartYear;							// Include Start Year so only have to change it once in main()

int RandomAge(int min, int max){					// Provide function for random number generator to asisgn age
	return rand()%(max-min+1)+min;}

double RandomMonthBD(int min, int max){				// Provides function for random number generator to assign birthdya month 
	return rand()%(max-min+1)+min;}

double RandomLifeExpect(int min, int max){			// Provides function for random number generator to assign Life expectancy
	return rand()%(max-min+1)+min;}


//// --- CLASS (POPULATION) CONSTRUCTOR --- ////

person::person()									// First 'person' class second constructor/variable and no return type means its a constructor
{
    PersonID=0;										// Peoples' basic information
	Sex=-999;

	DoB=-999;										// Varibales related to peoples' age and birthday
	AgeT0=-999;
	Age=-999;

	ChildIndex=0;									// Variables related to birth of children
	ChildIDVector.resize(0);						// Vector to store pointer to children.  Make sure it's starting size is 0 at the beginning
	BirthChild=9999;								// VERY IMPORTANT  this number needs to be HIGH as it entres EventQ...
	MotherID=-999;									// Dummy value (i.e. those born before 1950 will not have the ID of mother)
	Breastfeeding=0;								// Where 0=No and 1=Yes

	DateOfDeath=9999;								// Varibles related to death VERY IMPORTANT this number needs to be HIGH as it entres EventQ
	Alive=-999;										// Variable to update eventQ - global check to see if person is still alive
	AgeAtDeath=-999;
		
	HIVStatus=-999;									// Variables related to HIV-infection
	MyDateOfHIV=-999;
}


// --- FUNCTIONS TO CREATE OUTPUT ---
void person::TellMyPerson(){						// --- Tell Patient Profile (can be switched on and off in macro) ---
	cout << "Patient ID: \t" << PersonID << " \t Sex: \t\t" << Sex << "\t Alive: \t" << Alive << endl << endl << "Death: \t\t" << DateOfDeath << "\t Age at Death:  " << AgeAtDeath << endl << endl;
	cout << "DoB: \t\t" << DoB << "\t Age: \t\t" << Age << endl << endl;
	cout << "ChildIndex: \t" << ChildIndex << "\t FirstChild: \t" << BirthChild << "\t Childre IDs: \t " << ChildIDVector.size() << endl << endl << endl;}


//// --- FUNCTION TO ASSIGN CHARACTERISTIC FOR INITIAL POPULATION --- ////
void person::PersonIDAssign(int x){					// --- Assign Person ID ---
	PersonID=x+1;}


void person::GenderDistribution(){					// --- Assign Gender Distribution ---
double	r = ((double) rand() / (RAND_MAX)) ;
	if (r<=0/*0.5043*/){Sex=1;}									
	else {Sex=2;}}


void person::GetMyYearOfBirth(){					// --- Assign Year Of Birth, Age, etc ---		
double a = ((double) rand() / (RAND_MAX));

	double Age1950Array[2][17] = {
						{0.1729813, 0.2885448, 0.3952457, 0.4984330, 0.5870602, 0.6623300, 0.7275660, 0.7861866, 0.8383183, 0.8815241, 0.9174181, 0.9459054, 0.9680306, 0.9836036, 0.9929412, 0.9977840, 1},
						{0.1746637, 0.2917179, 0.4002065, 0.5020936, 0.5866883, 0.6556006, 0.7150133, 0.7665365, 0.8131972, 0.8565411, 0.8951191, 0.9273211, 0.9533403, 0.9733055, 0.9866050, 0.9952995, 1}};
	int ArratMin[17] =  {0, 5, 10, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60, 65, 70, 75, 80};
	int ArratMax[17] =  {4, 9, 14, 19, 24, 29, 34, 39, 44, 49, 54, 59, 64, 69, 74, 79, 100};
	int i=0;

	while (a>Age1950Array[Sex-1][i] && i<17){i++;}  
	AgeT0 = RandomAge(ArratMin[i],ArratMax[i]);
		
	int GetMonth=RandomMonthBD(1,12);				// Helps 'distribute' birthdays across the year
	double GetYearFraction=GetMonth/12.1;			// Assign year fraction of birth month, e.g. June is 0.5 of the year
		
	Age=AgeT0+GetYearFraction;
	AgeT0=Age;										// To make sure that age at T0 also has a fraction in it
	DoB=(StartYear-Age);
}


void person::GetDateOfBaby(){						// Get My First Child's Birthday - This method already calculates the child's month of birth by providing a year of birth with decimal
	
	if (Sex==2){
	
	double f = ((double) rand() / (RAND_MAX));		// to see if they will have a baby this year - the next bit assigns the birth over the year.  
	double AgeArray[7]=			{20,25,30,35,40,45,50};														// Use this array to get age of person
	double FertilityArray[7] =  {0.169071, 0.351607, 0.338141, 0.284278, 0.203483, 0.110719, 0.038901};		// Yearly fertility for 1950-1955
	int i=0;
	
	if (Age>=15 && Age<50){while (Age > AgeArray[i] && i < 7){i++;}											// Find the right age cat to find corresponding fertility cut-off - CAREFULL WITH > and <!!!
	if (f<FertilityArray[i]){BirthChild=*p_GT+((RandomMonthBD(1,12))/12.1);};};}							// Assigns next birth over the next 12 months
}
	

void person::GetDateOfDeath(){						// --- Assign Date of death ---	// This is done by assigning life expactancy according to age in 1950
													
	Age=*p_GT-DoB;									// Make sure age is up to date

	double OneMonth=(float)1 / (float)12;;			// Define length of a month for below
	double	d = ((double) rand() / (RAND_MAX)) ;	// get a random number to determine Life Expectancy
	
	int AgeArray1950[19]	= { 1,		5,		 10,	  15,	   20,		25,		 30,	  35,	   40,		45,		 50,	  55,	   60,		65,		 70,	  75,	   80,		85,		 100};			
	double DeathArray[2][19]	= {
		{0.84051, 0.73751, 0.69947, 0.68085, 0.66001, 0.63158, 0.60280, 0.57351, 0.54204, 0.50629, 0.46639, 0.42032, 0.36683, 0.30307, 0.22953, 0.14912, 0.07713, 0.02794, 0},
		{0.86584, 0.76647, 0.72864, 0.70934, 0.68923, 0.66662, 0.64111, 0.61281, 0.58197, 0.54948, 0.51601, 0.47711, 0.42895, 0.36682, 0.28877, 0.19851, 0.11204, 0.04643, 0}};
	int MinArray[19]		= {0,		1,		 5,		  10,	   15,		20,		 25,	  30,	   35,		40,		 45,	  50,	   55,		60,		 65,	  70,	   75,		80,		 85};
	int MaxArray[19]		= {1,		5,		 10,	  15,	   20,		25,		 30,	  35,	   40,		45,		 50,	  55,	   60,		65,		 70,	  75,	   80,		85,		 100};
	int i=0;
	int j=0;
	
	while(Age>AgeArray1950[i] && i<19){i++;}							// First get the age cat "i" to make sure d (life expectancy) is not below age using AGEARRAY above
	while (d>DeathArray[Sex-1][i]){d = (double) rand() / (RAND_MAX);}	// Make sure d is higher than current age/life expectancy, with Sex-1 indicating the position in the vector
	while(d<DeathArray[Sex-1][j] && j<19){j++;}							// Now get exact d to get min and max for life expactancy assignment

	DateOfDeath=DoB+(RandomLifeExpect(MinArray[j],MaxArray[j]));		// Use Life Expectancy to get date of death using corresponding min and max age from MinArray and MaxArray
	if(DateOfDeath<*p_GT){DateOfDeath=(*p_GT+OneMonth);	}				// Make sure date of death is not in the past
	
	AgeAtDeath= DateOfDeath-DoB;
}
	

void person::GetDateOfHIVInfection(int min, int max){					// --- Assign Date of HIV infection ---		
	MyDateOfHIV=*p_GT + (rand()%(max-min+1)+min);}


//// --- FUNCTIONS FOR NEW ENTRY --- ////
void person::GetMyYearOfBirthNewEntry(){								// --- Assign Age for New Entry ---
	AgeT0=0;															// Set all new entries as 'newborns' 
	Age=AgeT0;
	DoB=(*p_GT-AgeT0);}

