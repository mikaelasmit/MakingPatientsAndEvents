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
#include "coutmacro.h"


//// --- OUTSIDE INFORMATION --- ////
extern double *p_GT;								// Tell this .cpp that there is pointer to Global Time defined externally 
extern double *p_SY;								// Include here to be able to calculate peoples' age
extern double StartYear;							// Include Start Year so only have to change it once in main()

int RandomAge(int min, int max){					// Provide function for random number generator to asisgn age
	return rand()%(max-min+1)+min;}

double RandomMonth(int min, int max){				// Provides function for random number generator to assign birthdya month 
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
	if (r<=0.5043){Sex=1;}								// 0.5043 is original UN value
	else {Sex=2;}}


void person::GetMyYearOfBirth(){					// --- Assign Year Of Birth, Age, etc ---		
double a = ((double) rand() / (RAND_MAX));

	double Age1950Array[2][17] = {					// Note these will give random age between 0-4 (for example) but then year fraction (up to 4 yrs and 11 months) is added late to correct
						{0.172981, 0.288545, 0.395246, 0.498433, 0.587060, 0.662330, 0.727566, 0.786187, 0.838318, 0.881524, 0.917418, 0.945905, 0.968031, 0.983604, 0.992941, 0.997784, 1},
						{0.174664, 0.291718, 0.400206, 0.502094, 0.586688, 0.655601, 0.715013, 0.766536, 0.813197, 0.856541, 0.895119, 0.927321, 0.953340, 0.973306, 0.986605, 0.995300, 1}};
	int ArrayMin[17] =  {0, 5, 10, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60, 65, 70, 75, 80};
	int ArrayMax[17] =  {4, 9, 14, 19, 24, 29, 34, 39, 44, 49, 54, 59, 64, 69, 74, 79, 100};
	int i=0;

	while (a>Age1950Array[Sex-1][i] && i<17){i++;}  
	AgeT0 = RandomAge(ArrayMin[i],ArrayMax[i]);
		
	int GetMonth=RandomMonth(1,12);				// HeTellBirthByAgelps 'distribute' birthdays across the year
	double GetYearFraction=GetMonth/12.1;			// Assign year fraction of birth month, e.g. June is 0.5 of the year
	//	
	//Age=RandomMonth(100,110);						// Dummy code to test different ages - comment out above and line below
	Age=AgeT0+GetYearFraction;
	AgeT0=Age;										// To make sure that age at T0 also has a fraction in it
	DoB=(StartYear-Age);

	D(cout << "Schedule Age and DoB for initial population:" << endl << "Sex: " << Sex << "\t\tA: " << a << "Age: " << Age << endl);
	D(cout << "Min: " << ArrayMin[i] << "\tMax: " << ArrayMax[i] << endl << "Age: " << Age << "\t\tDoB: " << DoB << endl << endl);
	
}


void person::GetDateOfBaby(){						// Get My First Child's Birthday - This method already calculates the child's month of birth by providing a year of birth with decimal
	
	if (Sex==2 && Age>=15 && Age<50 ){
	
		double f = ((double) rand() / (RAND_MAX));		// to see if they will have a baby this year - the next bit assigns the birth over the year.  
		double AgeArray[7]=			{20,	   25,		 30,	   35,		 40,	   45,		 50};			// Use this array to get age of person
		double FertilityArray[7] =  {0.169071, 0.351607, 0.338141, 0.284278, 0.203483, 0.110719, 0.038901};		// Yearly fertility for 1950-1955
		int i=0;

		while (Age > AgeArray[i] && i < 7){i++;D(cout <<  "The loop is running " << endl);};									// Find the right age cat to find corresponding fertility cut-off - CAREFULL WITH > and <!!!
		if (f<FertilityArray[i]){BirthChild=*p_GT+((RandomMonth(1,12))/12.1);};								// Assigns next birth over the next 12 months
			
	D(cout << "Schedule Date of First Baby:" << endl;
	  cout << "The value of i is: " << i << endl;
	  cout << "ID: " << PersonID << "\t\tSex: " << Sex << "\t\tAge: " << Age << endl; 
	  cout << "F: " << f << "\tBirth: " << BirthChild << endl << endl);
	  
	
	}
	  

}
	

void person::GetDateOfDeath(){						// --- Assign Date of death ---	// This is done by assigning life expactancy according to age in 1950
													
	Age=*p_GT-DoB;									// Make sure age is up to date

	double OneMonth=(float)1 / (float)12;;			// Define length of a month for below
	double	d = ((double) rand() / (RAND_MAX)) ;	// get a random number to determine Life Expectancy
	
	int AgeArray1950[19]	= { 1,		5,		 10,	  15,	   20,		25,		 30,	  35,	   40,		45,		 50,	  55,	   60,		65,		 70,	  75,	   80,		85,		 100};			
	double DeathArray[2][19]	= {
		{0.15949, 0.10300, 0.03804, 0.01862, 0.02084, 0.02843, 0.02877, 0.02930, 0.03147, 0.03575, 0.03989, 0.04607, 0.05349, 0.06376, 0.07354, 0.08041, 0.07199, 0.04919, 0.02794},
		{0.13416, 0.09937, 0.03783, 0.01930, 0.02011, 0.02261, 0.02551, 0.02830, 0.03084, 0.03249, 0.03347, 0.03890, 0.04816, 0.06213, 0.07805, 0.09025, 0.08649, 0.06561, 0.04643}};

	
	double SurvivalArray[2][19]	= {
		{0.84051, 0.73751, 0.69947, 0.68085, 0.66001, 0.63158, 0.60280, 0.57351, 0.54204, 0.50629, 0.46639, 0.42032, 0.36683, 0.30307, 0.22953, 0.14912, 0.07713, 0.02794, 0},
		{0.86584, 0.76647, 0.72864, 0.70934, 0.68923, 0.66662, 0.64111, 0.61281, 0.58197, 0.54948, 0.51601, 0.47711, 0.42895, 0.36682, 0.28877, 0.19851, 0.11204, 0.04643, 0}};
	
	
	 
	int MinArray[19]		= {0,		1,		 5,		  10,	   15,		20,		 25,	  30,	   35,		40,		 45,	  50,	   55,		60,		 65,	  70,	   75,		80,		 85};
	int MaxArray[19]		= {1,		5,		 10,	  15,	   20,		25,		 30,	  35,	   40,		45,		 50,	  55,	   60,		65,		 70,	  75,	   80,		85,		 100};
	int i=0;
	int j=0;
	
	if (Age<=100){
	while(Age>AgeArray1950[i] && i<19){i++;}							// First get the age cat "i" to make sure d (life expectancy) is not below age using AGEARRAY above
	int c=0;
	double sum=0;
	for (c=0+i; c<19; c++){sum+=DeathArray[Sex-1][c];}

	D(cout << "Age: " << Age << " Sex: " << Sex << " i: " << i << " sum: " << sum << endl << endl);

	double NewProportion;
	if (sum>0) { NewProportion=1/sum;};
	if (sum==0) { NewProportion=0.0001;};
	if (NewProportion>1){NewProportion==1;}
	int length=19-i;

	D(cout << "The length is: " << length << endl << endl);

	D(cout << "New Proportion: " << NewProportion << endl<<endl);

	vector<double> FinalDeathArray;
	FinalDeathArray.resize(0);
	int f=0;
	int a=i;

	if(i<17) {while (f<(length)){FinalDeathArray.push_back(SurvivalArray[Sex-1][a]*NewProportion); D(cout << "The loop is running. I: " << a << " F: " << f << " New element is: " << FinalDeathArray[f] << endl); a++; f++;};};
	if (i==18){FinalDeathArray.resize(0);FinalDeathArray.push_back(0); D(cout << "The First nr: " << FinalDeathArray.at(0)  << endl << endl);};
	if (i==17){FinalDeathArray.resize(0);FinalDeathArray.push_back(0.5); D(cout << "The First nr: " << FinalDeathArray.at(0)); FinalDeathArray.push_back(0); D(cout << "The Second nr: " << FinalDeathArray.at(1) << endl << endl);};
	while(d<FinalDeathArray[j] && j<length){j++;}							// Now get exact d to get min and max for life expactancy assignment
		
	D(cout << "D: " << d << "\t\tJ: " << j << "\t\ti+j=: " << i + j << endl << endl);

	double LE=RandomLifeExpect(MinArray[i+j],MaxArray[i+j]);

	D(cout << "Random LE: " << LE << endl); 


	DateOfDeath=DoB+(LE);		// Use Life Expectancy to get date of death using corresponding min and max age from MinArray and MaxArray
	if(DateOfDeath<*p_GT){DateOfDeath=(*p_GT+OneMonth);	}				// Make sure date of death is not in the past
	}
	if (Age>100){DateOfDeath=*p_GT+OneMonth;};
	
	AgeAtDeath= DateOfDeath-DoB;

	D(cout << "Date of Death: " << DateOfDeath << "\t\tMin " << MinArray[i+j] << endl << endl);
}
	

void person::GetDateOfHIVInfection(int min, int max){					// --- Assign Date of HIV infection ---		
	MyDateOfHIV=*p_GT + (rand()%(max-min+1)+min);}


//// --- FUNCTIONS FOR NEW ENTRY --- ////
void person::GetMyYearOfBirthNewEntry(){								// --- Assign Age for New Entry ---
	AgeT0=0;															// Set all new entries as 'newborns' 
	Age=AgeT0;
	DoB=(*p_GT-AgeT0);}



