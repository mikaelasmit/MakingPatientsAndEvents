/////////////////////////////////////////////////////////////////
//    Created by Mikaela Smit on 24/04/2015.				   //
//    Code from Jack Olney from 20/10/2014					   //
//    This script helps to switch cout statements on/off	   //
/////////////////////////////////////////////////////////////////

#ifndef priorityQ_errormacro_h
#define priorityQ_errormacro_h

/* Macro header file */

#define DEBUG_MODE2			// Comment this out to stop D(x) x cout statement

#ifdef DEBUG_MODE2
#define E(x) x
#else
#define E(x)
#endif

#endif