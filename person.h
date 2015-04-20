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
	double Age; 

	int ChildIndex;									// Variables related to the birth of children - ChildIndex holds how many Children a mother has
	int MotherID;									// Holds ID of the mother
	vector<person*> ChildIDVector;					// ChildIDVector is its name <now holds 'people pointer'> of type vector which is the structure
	vector<double> BirthChild;						// Hold dates of the birth of all children - vector
	
	
    double DateOfDeath;								// Variables related to death
	int Alive;
	int AgeAtDeath;

	
//// --- FUNCTIONS ----				
	
	// --- FOR INITIAL POPULATION ---
	// --- Functions related to People ---
	void PersonIDAssign(int x);						// Function to get Person ID
	void TellMyPerson();							// Function to tell all patient's characteristics


	// --- Sex ---
	void GenderDistribution();						// Function to assign sex
								

	// --- Year of Birth ---						
	void GetMyDoB();								// Function to assign AGE and DOB (with months)
	

	// --- Birth of First Child ---
	void GetDateOfBaby();							// Function to get the date of the children
	

	// --- Date of Death ---
	void GetDateOfDeath();							// Function to get date of Death - this is done by using UN Life expectancy by age in 1950 and random numbers (see person.cpp)
	






	// --- FOR NEW ENTRY ---
	void GetMyDoBNewEntry();				// Function to assign age
	
};	

#endif
