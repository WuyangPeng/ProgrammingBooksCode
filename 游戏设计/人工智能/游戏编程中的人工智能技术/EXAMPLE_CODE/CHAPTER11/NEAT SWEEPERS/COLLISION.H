#ifndef COLLISION_H
#define COLLISION_H

#include "utils.h"
#include <math.h>


//--------------------2LinesIntersection2D-------------------------
//
//	Given 2 lines in 2D space AB, CD this returns true if an 
//	intersection occurs and sets dist to the distance the intersection
//  occurs along AB
//
//----------------------------------------------------------------- 
inline bool LineIntersection2D(const SPoint A,
                               const SPoint B,
                               const SPoint C, 
                               const SPoint D,
                               double &dist)
{
  //first test against the bounding boxes of the lines
  if ( (((A.y > D.y) && (B.y > D.y)) && ((A.y > C.y) && (B.y > C.y))) ||
       (((B.y < C.y) && (A.y < C.y)) && ((B.y < D.y) && (A.y < D.y))) ||
       (((A.x > D.x) && (B.x > D.x)) && ((A.x > C.x) && (B.x > C.x))) ||
       (((B.x < C.x) && (A.x < C.x)) && ((B.x < D.x) && (A.x < D.x))) )
  { 
    dist = 0;

    return false;
  }
       
  double rTop = (A.y-C.y)*(D.x-C.x)-(A.x-C.x)*(D.y-C.y);
	double rBot = (B.x-A.x)*(D.y-C.y)-(B.y-A.y)*(D.x-C.x);

	double sTop = (A.y-C.y)*(B.x-A.x)-(A.x-C.x)*(B.y-A.y);
	double sBot = (B.x-A.x)*(D.y-C.y)-(B.y-A.y)*(D.x-C.x);


  double rTopBot = rTop*rBot;
  double sTopBot = sTop*sBot;

  if ((rTopBot>0) && (rTopBot<rBot*rBot) && (sTopBot>0) && (sTopBot<sBot*sBot))
  {

    dist = rTop/rBot;

    return true;
  }


  else
  {
    dist = 0;

    return false;
  }

}


#endif

						  