/////////////////////////////////////////////////////////////////
//    Created by Mikaela Smit on 22/10/2014.				   //
//    Copyright (c) 2014 Mikaela Smit. All rights reserved.    //
//    This script makes the people in the cohort.			   //
/////////////////////////////////////////////////////////////////


#include <stdio.h>									// Include some essential libraries and files
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include "person.h"
#include "event.h"
#include "eventfunctions.h"
#include"errorcoutmacro.h"
#include "coutmacro.h"
#include "demographmacro.h"


//// --- OUTSIDE INFORMATION --- ////
extern double *p_GT;								// Tell this .cpp that there is pointer to Global Time defined externally 
extern double StartYear;							// Include Start Year so only have to change it once in main()
extern int *p_PY;									// Pointer to show which year range we are on

double** BirthArray;
double** DeathArray_Women;
double** DeathArray_Men;


void loadBirthArray() {							// Load birth array
  FILE* f = fopen("birth_array.bin","rb");
  BirthArray = new double*[200];
  for (int i=0; i<200; i++) {
    BirthArray[i]=new double[35];
	for (int j=0; j<35; j++) {
	  fread(&BirthArray[i][j],8,1,f);
	}
  }
  fclose(f);
}

void loadDeathArray_Women() {					// Load Death Array for women
  FILE* f = fopen("mortality_array_women.bin","rb");
  DeathArray_Women = new double*[301];
  for (int i=0; i<301; i++) {
    DeathArray_Women[i]=new double[121];
	for (int j=0; j<121; j++) {
	  fread(&DeathArray_Women[i][j],8,1,f);
	}
  }
  fclose(f);
}



void loadDeathArray_Men() {						// Load Death Array for men
  FILE* f = fopen("mortality_array_men.bin","rb");
  DeathArray_Men = new double*[301];
  for (int i=0; i<301; i++) {
    DeathArray_Men[i]=new double[121];
	for (int j=0; j<121; j++) {
	  fread(&DeathArray_Men[i][j],8,1,f);
	}
  }
  fclose(f);
}

int RandomMinMax(int min, int max){					// Provide function for random number generator between min and max number 
	return rand()%(max-min+1)+min;					// !!!!Note: if min=0 and max=4 it will generate 0,1,2,3,4
}


//// --- CLASS (POPULATION) CONSTRUCTOR --- ////

person::person()									// First 'person' class second constructor/variable and no return type means its a constructor
{
    PersonID=0;										// --- Peoples' basic information ---
	Sex=-999;

	DoB=-999;										// --- Varibales related to peoples' age and birthday ---
	Age=-999;
													// --- Variables related to birth of children ---
	MotherID=-999;									// Dummy value (i.e. those born before 1950 will not have the ID of mother)
	ChildIDVector.resize(0);						// Vector to store pointer to children.  Make sure it's starting size is 0 at the beginning
	DatesBirth.resize(0);							// This will be used to push in all births of every child
		
	DateOfDeath=9999;								// --- Varibles related to death ---
	AgeAtDeath=-999;								// NOTE: VERY IMPORTANT this number needs to be HIGH as it entres EventQ
	Alive=-999;										// Variable to update eventQ - global check to see if person is still alive
}


//// --- FUNCTION TO ASSIGN CHARACTERISTIC FOR INITIAL POPULATION --- ////

// --- Assign Person ID ---
void person::PersonIDAssign(int x){					
	E(cout << "We are assigning Patient ID!" << endl;)
	PersonID=x+1;
}


// --- Assign Gender Distribution ---
void person::GenderDistribution(){					
	E(cout << "We are assigning gender!" << endl;)
	double	r = ((double) rand() / (RAND_MAX)) ;
	if (r<=0.5043){Sex=1;}							// Where 1 = man and 2= woman					
	else {Sex=2;}
	E(cout << "We finished assigning gender!" << endl;)
}


// --- Assign Year Of Birth, Age, etc ---
void person::GetMyDoB(){									
	
	E(cout << "We are assigning DoB!" << endl;)
		
	double a = ((double) rand() / (RAND_MAX));
	double Age1950Array[2][17] = {					// Where the first row is men and the second is women 				
		{0.172981, 0.288545, 0.395246, 0.498433, 0.587060, 0.662330, 0.727566, 0.786187, 0.838318, 0.881524, 0.917418, 0.945905, 0.968031, 0.983604, 0.992941, 0.997784, 1},
		{0.174664, 0.291718, 0.400206, 0.502094, 0.586688, 0.655601, 0.715013, 0.766536, 0.813197, 0.856541, 0.895119, 0.927321, 0.953340, 0.973306, 0.986605, 0.995300, 1}};
	int ArrayMin[17] =  {0, 5, 10, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60, 65, 70, 75, 80};
	int ArrayMax[17] =  {4, 9, 14, 19, 24, 29, 34, 39, 44, 49, 54, 59, 64, 69, 74, 79, 100};
	
	int i=0;
	while (a>Age1950Array[Sex-1][i] && i<17){i++;}  
	Age = RandomMinMax(ArrayMin[i],ArrayMax[i]);
	double YearFraction=(RandomMinMax(1,12))/12.1;	// This gets month of birth as a fraction of a year
	Age=Age+YearFraction;							// This 'distributes' birthdays across the year as per month of birth (see above)
	DoB=(StartYear-Age);

	E(cout << "We finished assigning DoB!" << endl;)
}


// --- Get Dates of all my future babies ---
void person::GetDateOfBaby(){						// This method already calculates the child's month of birth by providing a year of birth with decimal
	
	E(cout << "We are assigning Births!" << endl;)

	Age= (*p_GT - DoB);								// Update age ... just in case
	if (Sex == 2 && Alive == 1 && Age<50 && AgeAtDeath>=15){
	
	//// --- Lets first see how many children I will have --- ////
	double r_nr=RandomMinMax(0,100)*0.01;			// To get a random number to later assign whether a woman gets min or max nr of children for time period
	int index=DoB-1901+15;							// index for large arrays, related to year the patient will be 15 and ready for birth
	int NrChildren;

	double NrChildrenArray[3][200] = {				// Min first, second Max, third proportion with min and max children
		{7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 6, 6, 6, 6, 6, 6, 6, 6, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4},
		{8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 7, 7, 7, 7, 7, 7, 7, 7, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5},
		{0.48, 0.48, 0.48, 0.48, 0.48, 0.48, 0.48, 0.48, 0.48, 0.48, 0.48, 0.48, 0.48, 0.48, 0.48, 0.48, 0.48, 0.48, 0.48, 0.48, 0.48, 0.48, 0.49, 0.49, 0.49, 0.49, 0.50, 0.51, 0.51, 0.52, 0.53, 0.54, 0.56, 0.57, 0.58, 0.60, 0.62, 0.64, 0.66, 0.68, 0.70, 0.72, 0.74, 0.77, 0.79, 0.81, 0.82, 0.84, 0.86, 0.88, 0.88, 0.87, 0.87, 0.87, 0.87, 0.85, 0.84, 0.83, 0.81, 0.80, 0.71, 0.62, 0.53, 0.44, 0.35, 0.25, 0.15, 0.06, 0.96, 0.86, 0.73, 0.60, 0.47, 0.34, 0.21, 0.10, 0.99, 0.88, 0.77, 0.66, 0.58, 0.51, 0.43, 0.36, 0.28, 0.22, 0.16, 0.10, 0.03, 0.97, 0.95, 0.93, 0.91, 0.89, 0.87, 0.86, 0.85, 0.84, 0.83, 0.82, 0.82, 0.81, 0.81, 0.80, 0.80, 0.80, 0.80, 0.80, 0.80, 0.80, 0.80, 0.80, 0.80, 0.80, 0.80, 0.80, 0.80, 0.80, 0.80, 0.80, 0.80, 0.80, 0.80, 0.80, 0.80, 0.80, 0.80, 0.80, 0.80, 0.80, 0.80, 0.80, 0.80, 0.80, 0.80, 0.80, 0.80, 0.80, 0.80, 0.80, 0.80, 0.80, 0.80, 0.80, 0.80, 0.80, 0.80, 0.80, 0.80, 0.80, 0.80, 0.80, 0.80, 0.80, 0.80, 0.80, 0.80, 0.80, 0.80, 0.80, 0.80, 0.80, 0.80, 0.80, 0.80, 0.80, 0.80, 0.80, 0.80, 0.80, 0.80, 0.80, 0.80, 0.80, 0.80, 0.80, 0.80, 0.80, 0.80, 0.80, 0.80, 0.80, 0.80, 0.80, 0.80, 0.80, 0.80, 0.80, 0.80, 0.80, 0.80, 0.80, 0.80, 0.80, 0.80, 0.80, 0.80, 0.80, 0.80, 0.80}
		};
	
	if (r_nr<NrChildrenArray[2][index]){NrChildren=NrChildrenArray[0][index];}
	if (r_nr>=NrChildrenArray[2][index]){NrChildren=NrChildrenArray[1][index];}
	
	
	//// --- Lets see when I will having all my children --- ////
	

	int m=0;														// Count of how many children I will have - can be used to manage ChildVector and loop
	double DateOfBirthTest=-9999;
	int ChildBearingYears=AgeAtDeath-15;
	
	
	//// --- Just in case the person is going to die early, lets let her have as many kdis as possible first --- ////
	if(ChildBearingYears<NrChildren){
		NrChildren=ChildBearingYears;
	}
	

	//// --- Let's see when the first birth will happen and check it doesn' ocurr before death --- ////
	while (m<NrChildren){
		double	f = ((double)rand() / (RAND_MAX));					// Get random fertility value
		int j=0;
		while (f>BirthArray[index][j] && j<35){ j++; };				// Find out in which age group I will have my child
		
		DateOfBirthTest = DoB + 15 +j;
		
		
		while (DateOfBirthTest>=DateOfDeath){						// Run this loop in case birth ocurrs before birth
			double	f = ((double)rand() / (RAND_MAX));
			int j = 0;
			while (f>BirthArray[index][j] && j<35){ j++; };
			DateOfBirthTest = DoB + 15+j;

			};

		DatesBirth.push_back(DateOfBirthTest);						// Once we checked birth doesn't happen before birth lets push that in
			  	
		
		//// --- Lets check if I am already giving birth at this age --- ////
		if (DatesBirth.size()>1){									// Only need to check if there are already more than 1 child
			int n=0;												// Index to count past births with this newly assigned birth
			
			while (n<m){
				double Diff_1 = DatesBirth.at(n) - DatesBirth.at(m);	// This Diff is the original difference
				double Diff_2 = DatesBirth.at(n) - DatesBirth.at(m);	// This Diff is the new one if new one is needed.  
																		// [...] If both the same we can move on, if not we need to check the new Birth against births 1 to max again
				while ((DatesBirth.at(n) - DatesBirth.at(m) > -0.75 && DatesBirth.at(n) - DatesBirth.at(m)<0.75) || DatesBirth.at(m)>=DateOfDeath){
						double	f = ((double)rand() / (RAND_MAX));
						int j = 0;
						while (f>BirthArray[*p_PY][j] && j<35){ j++; };
						
						DateOfBirthTest = DoB + 15+j;
						DatesBirth.at(m)=DateOfBirthTest;
						Diff_2 = DatesBirth.at(n) - DatesBirth.at(m);
					};
					if (Diff_1 == Diff_2){ n++;};						// If we didn't have to change BirthOfDate we can check against next birth
					if (Diff_1 != Diff_2){n = 0;};						// If we have changed DateOfBirth we need to check this new Date against all existing ones
					
			}
		}

		m++; 
	}
	

	}
	E(cout << "We have finished assigning births!" << endl;)
};

	  

// --- Assign Date of death ---	
void person::GetDateOfDeath(){						// This is done by assigning life expactancy according to age in 1950

	E(cout << "We are assigning deaths!" << endl;)
	
	double OneMonth=(float)1 / (float)12;;				// Define length of a month for below
		
	
	
	int i=(DoB-1800);										// To find corresponding year of birth from mortality array
	int j=0;												// This will be matched to probability taken from random number generator
	double	d = ((double) rand() / (RAND_MAX)) ;			// get a random number to determine Life Expectancy
	
	if (Sex==1){
		while(d>DeathArray_Men[i][j] && j<121){j++;}
		DateOfDeath=(DoB+j);
		while (DateOfDeath<*p_GT){							// Run this again if Death happens in the past (important for 1950)
			double	d = ((double) rand() / (RAND_MAX)) ;	// get a random number to determine Life Expectancy
			while(d>DeathArray_Men[i][j] && j<121){j++;}
			DateOfDeath=(DoB+j);}
	}
	
	if (Sex==2) {
		while(d>DeathArray_Women[i][j] && j<121){j++;}
		DateOfDeath=(DoB+j);
		while (DateOfDeath<*p_GT){							// Run this again if Death happens in the past (important for 1950)
			double	d = ((double) rand() / (RAND_MAX)) ;	// get a random number to determine Life Expectancy
			while(d>DeathArray_Women[i][j] && j<121){j++;}
			DateOfDeath=(DoB+j);};
	}
		AgeAtDeath=DateOfDeath-DoB;

	E(cout << "We have finished assigning death dates!" << endl;)
	
}


//// --- FUNCTIONS FOR NEW ENTRY --- ////
void person::GetMyDoBNewEntry(){							// --- Assign Age for New Entry ---
	E(cout << "We are assigning births to babies!" << endl;)
	Age=0;													// Set all new entries as 'newborns' 
	DoB=*p_GT;
};

 