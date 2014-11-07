//
//  Created by Mikaela Smit on 22/10/2014.
//  Copyright (c) 2014 Mikael Smit. All rights reserved.
//

#ifndef person_h				// If not defined then defines it  # are pre-compiler definitions
#define person_h				

using namespace std;


//// --- CREATING PATIENTS ---

class patient{							// Classes are considered private unless stated otherwise 
public:
    
    patient();							// Class constructor or calling function for patient
    

	//// --- PATIENT CHARACTERISTICS ---
	int PatientID;
	int HIVStatus;
	int MyDateOfHIV;
	
	void TellMyPatientID();
    void PatientIDAssign(int x);

	//// ---- HIV EVENTS ---
	void GetDateOfHIVInfection(int x, int y);		// Function to get date of HIV infection
	void TellMyHivDate();							// Function to be executed when HIV infection occurs

 
};

#endif
