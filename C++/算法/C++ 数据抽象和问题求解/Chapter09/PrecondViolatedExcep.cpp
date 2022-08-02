//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.

/** Listing 7-6.
    @file PrecondViolatedExcep.cpp */
#include "PrecondViolatedExcep.h"  

PrecondViolatedExcep::PrecondViolatedExcep(const string& message): logic_error("Precondition Violated Exception: " + message)
{
}  // end constructor

// End of implementation file.

