/////////////////////////////////////////////////////////////////
//    Created by Mikaela Smit on 22/10/2014.				   //
//    Copyright (c) 2014 Mikaela Smit. All rights reserved.	   //
//    This script makes the people in the cohort.			   //
/////////////////////////////////////////////////////////////////


#ifndef person_h									// If not defined then defines it  # are pre-compiler definitions
#define person_h				
using namespace std;


//// --- CREATING PEOPLE --- ////

class person{										// Classes are considered private unless stated otherwise 
public:
    
    person();										// Class constructor or calling function for person
    

//// --- Persons Characteristics --- ////
	int PersonID;									// Basic variables
	int Sex;
	
	double DoB;										// Variables related to age
	int AgeT0;
	double Age; 

	int ChildID;									// Variables related to the first birth
	int ChildID_1;									// TURN THIS WHOLE CHILDID_1 to 10 INTO AN EXPANDING VECTOR WITH POINTER
	int ChildID_2;
	int ChildID_3;
	int ChildID_4;
	int ChildID_5;
	int ChildID_6;
	int ChildID_7;
	int ChildID_8;
	int ChildID_9;
	int ChildID_10;
	int ChildIndex;
	double BirthFirstChild; 
	int MotherID;
	int Breastfeeding;
	
    double DateOfDeath;								// Variables related to death
	int Alive;

	int HIVStatus;									// Variables related to HIV
	int MyDateOfHIV;
	

//// --- FUNCTIONS ----				
	
	// --- FOR INITIAL POPULATION ---
	// --- Person ID ---
	void PersonIDAssign(int x);						// Function to get Person ID
	//void TellMyPersonID();						// Function to be executed when ID is assigned

	// --- Sex ---
	void GenderDistribution();						// Function to assign sex
	//void TellMySex();								// Function to be executed when sex is assigned

	// --- Year of Birth ---						// TO DO: Convert to date of birth later?
	void GetMyYearOfBirth();						// Function to assign AGE/AGET0 and DOB (with months)
	//void TellMyYearOfBirth();						// Function to be executed when birthday
 
	// --- Birth of First Child ---
	void GetDateOfMyFirstBaby();					// Function to get the date of the first babies in 1950
	//void TellMyFirstChildBirth();					// Function to be executed when birth is assigned

	// --- Date of Death ---
	void GetDateOfDeath();							// Function to get date of Death - this is done by using UN Life expectancy by age in 1950 and random numbers (see person.cpp)
	//void TellMyExpectedDeathDate();					// Function to be executed when Death occurs
	//void TellMyLifeStatus();						// Assigns each patient as Alive=0/1 where 0=dead and 1= alive.  This allows to ensure events olny happen if people are still alive.  
	
	// --- HIV Infection Date ---					// TO DO: Make HIV status positive and expand to include various HIV-related things
	void GetDateOfHIVInfection(int x, int y);		// Function to get date of HIV infection
	//void TellMyHivDateSTART();						// Function to be executed when HIV infection occurs
	

	// --- FOR NEW ENTRY ---
	// --- Year of Birth for New Enrtry---			// TO DO: Convert to date of birth later?
	void GetMyYearOfBirthNewEntry();				// Function to assign age
	void GetNewDateOfDeath();						// Function to assign date of death to every new person - done by using UN data for LE in 1950-1955 for <1 year olds
};	

#endif
