#ifndef COLLISION_H
#define COLLISION_H

#include "utils.h"
#include <math.h>

//--------------------2LinesIntersection2D-------------------------
//
//	Given 2 lines in 2D space AB, CD this returns true if an 
//	intersection occurs and sets dist to the distance the intersection
//  occurs along AB
//----------------------------------------------------------------- 
bool LineIntersection2D(const SPoint A,
                        const SPoint B,
                        const SPoint C, 
                        const SPoint D,
                        double &dist);



#endif

						  