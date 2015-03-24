/////////////////////////////////////////////////////////////////
//    Created by Mikaela Smit on 22/10/2014.				   //
//    Copyright (c) 2014 Mikaela Smit. All rights reserved.	   //
//    This script makes the people in the cohort.			   //
/////////////////////////////////////////////////////////////////


#ifndef person_h									// If not defined then defines it  # are pre-compiler definitions
#define person_h	
#include <vector>

using namespace std;


//// --- CREATING PEOPLE --- ////

class person{										// Classes are considered private unless stated otherwise 
public:
    
    person();										// Class constructor or calling function for person
    

//// --- Persons Characteristics --- ////
	int PersonID;									// Basic variables
	int Sex;
	
	double DoB;										// Variables related to age
	double AgeT0;
	double Age; 

	int ChildIndex;									// Variables related to the birth of children
	vector<person*> ChildIDVector;					// ChildIDVector is its name <now holds 'people pointer'> of type vector which is the structure
	double BirthChild;								// Hold date of the birth of next child
	int MotherID;									// Holds ID of the mother
	int Breastfeeding;								// Status of breastfeeding
	
    double DateOfDeath;								// Variables related to death
	int Alive;
	int AgeAtDeath;

	int HIVStatus;									// Variables related to HIV
	int MyDateOfHIV;
	

//// --- FUNCTIONS ----				
	
	// --- FOR INITIAL POPULATION ---
	// --- Functions related to People ---
	void PersonIDAssign(int x);						// Function to get Person ID
	void TellMyPerson();							// Function to be executed when ID is assigned

	// --- Sex ---
	void GenderDistribution();						// Function to assign sex
								

	// --- Year of Birth ---						
	void GetMyYearOfBirth();						// Function to assign AGE/AGET0 and DOB (with months)
	
	// --- Birth of First Child ---
	void GetDateOfBaby();							// Function to get the date of the first babies in 1950
	
	// --- Date of Death ---
	void GetDateOfDeath();							// Function to get date of Death - this is done by using UN Life expectancy by age in 1950 and random numbers (see person.cpp)
	
	// --- HIV Infection Date ---					// TO DO: Make HIV status positive and expand to include various HIV-related things
	void GetDateOfHIVInfection(int x, int y);		// Function to get date of HIV infection
	//void TellMyHivDateSTART();						// Function to be executed when HIV infection occurs
	

	// --- FOR NEW ENTRY ---
	// --- Year of Birth for New Enrtry---			
	void GetMyYearOfBirthNewEntry();				// Function to assign age
	
};	

#endif
