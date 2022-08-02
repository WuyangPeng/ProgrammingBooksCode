#ifndef UTILS_H
#define UTILS_H

/////////////////////////////////////////////////////////////////////////
//
//		File: Utils.h
//
//		Author: Mat Buckland
//
//		Desc: useful utilities
//
/////////////////////////////////////////////////////////////////////////

#include <stdlib.h>
#include <math.h>
#include <sstream>
#include <string>

using namespace std;

//-----------------------------------------------------------------------
//	some random number functions.
//-----------------------------------------------------------------------
inline int	  RandInt(int x,int y) {return rand()%(y-x+1)+x;}

inline double RandFloat()		   {return (rand())/(RAND_MAX+1.0);}

inline bool   RandBool()
{
	if (RandInt(0,1)) return true;

	else return false;
}

//returns a random float in the range -1 < n < 1
inline double RandomClamped()	   {return RandFloat() - RandFloat();}

//-----------------------------------------------------------------------
// useful string functions
//-----------------------------------------------------------------------

//int to string function
string itos(int arg);




#endif