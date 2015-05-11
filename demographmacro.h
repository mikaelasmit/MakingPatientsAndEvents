/////////////////////////////////////////////////////////////////
//    Created by Mikaela Smit on 30/04/2015.				   //
//    Code from Jack Olney from 20/10/2014					   //
//    This script helps to switch cout statements on/off	   //
/////////////////////////////////////////////////////////////////

#ifndef priorityQ_demographmacro_h
#define priorityQ_demographmacro_h

/* Macro header file */

#define DEBUG_MODE3			// Comment this out to stop DM(x) x cout statement

#ifdef DEBUG_MODE3
#define DM(x) x
#else
#define DM(x)
#endif

#endif