/////////////////////////////////////////////////////////////////
//    Created by Mikaela Smit on 02/03/2015.				   //
//    Code from Jack Olney from 20/10/2014					   //
//    This script helps to switch cout statements on/off	   //
/////////////////////////////////////////////////////////////////

#ifndef priorityQ_macro_h
#define priorityQ_macro_h

	/* Macro header file */

#define DEBUG_MODE			// Comment this out to stop D(x) x cout statement

#ifdef DEBUG_MODE
#define D(x) x
#else
#define D(x)
#endif

#endif