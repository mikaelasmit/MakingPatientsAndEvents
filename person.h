//
//  Created by Mikaela Smit on 22/10/2014.
//  Copyright (c) 2014 Mikael Smit. All rights reserved.
//

#ifndef person_h									// If not defined then defines it  # are pre-compiler definitions
#define person_h				

using namespace std;


//// --- CREATING PATIENTS ---

class patient{										// Classes are considered private unless stated otherwise 
public:
    
    patient();										// Class constructor or calling function for patient
    

	//// --- PATIENT CHARACTERISTICS ---
	int PatientID;
	int Sex;

	int DoB;
	int AgeT0;
	int Age;
	double BirthdayM;
	double BirthdayY;
											// Need to assign an age and update it later
    
	int DateOfDeath;

	int HIVStatus;
	int MyDateOfHIV;
	

	//// --- FUNCTIONS ----

	// --- Patient ID ---
	void PatientIDAssign(int x);					// Function to get Patient ID
	void TellMyPatientID();							// Function to be executed when ID is assigned

	// --- Year of Birth ---						// TO DO: Convert to date of birth later?
	void GetMyYearOfBirth(int x, int y);			// Function to assign age
	void TellMyDob();								// Function to be executed when birthday

	// --- Birthday ---								// TO DO: Convert to date of birth later?
	void GetMyBirthday(int x, int y);				// Function to assign age
	void TellMyBD();								// Function to be executed when birthday
 
	// --- Sex ---
	void GenderDistribution();						// Function to assign sex
	void TellMySex();								// Function to be executed when sex is assigned

	// --- Date of Death ---
	void GetDateOfDeath(int x, int y);				// Function to get date of Death
	void TellMyExpectedDeathDate();					// Function to be executed when Death occurs
	
	// --- HIV Infection Date ---					// TO DO: Make HIV status positive
	void GetDateOfHIVInfection(int x, int y);		// Function to get date of HIV infection
	void TellMyHivDateSTART();						// Function to be executed when HIV infection occurs


};

#endif
