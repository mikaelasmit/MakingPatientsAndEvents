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
	int PersonID;
	int Sex;


	int DoB;										// Variables related to age
	int AgeT0;
	double Age; 

	int ChildID;									// Variables related to the first birth
	int ChildID_1;
	int ChildID_2;
	int ChildIndex;
	double BirthFirstChild; 
	int MotherID;
	

    double DateOfDeath;								// Variables related to death
	int Alive;

	int HIVStatus;									// Variables to HIV
	int MyDateOfHIV;
	

//// --- FUNCTIONS ----				
	
	// --- FOR INITIAL POPULATION ---
	// --- Person ID ---
	void PersonIDAssign(int x);						// Function to get Person ID
	void TellMyPersonID();							// Function to be executed when ID is assigned

	// --- Sex ---
	void GenderDistribution();						// Function to assign sex
	void TellMySex();								// Function to be executed when sex is assigned

	// --- Year of Birth ---						// TO DO: Convert to date of birth later?
	void GetMyYearOfBirth();						// Function to assign age
	void TellMyYearOfBirth();								// Function to be executed when birthday
 
	// --- Birth of First Child ---
	void GetDateOfMyFirstBaby();
	void TellMyFirstChildBirth();

	// --- Date of Death ---
	void GetDateOfDeath();							// Function to get date of Death
	void TellMyExpectedDeathDate();					// Function to be executed when Death occurs
	void TellMyLifeStatus();
	
	// --- HIV Infection Date ---					// TO DO: Make HIV status positive
	void GetDateOfHIVInfection(int x, int y);		// Function to get date of HIV infection
	void TellMyHivDateSTART();						// Function to be executed when HIV infection occurs
	

	// --- FOR NEW ENTRY ---
	// --- Year of Birth for New Enrtry---			// TO DO: Convert to date of birth later?
	void GetMyYearOfBirthNewEntry();				// Function to assign age
	void GetNewDateOfDeath();
};

#endif
