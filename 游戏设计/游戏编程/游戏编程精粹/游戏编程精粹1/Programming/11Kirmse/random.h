/* Copyright (C) Andrew Kirmse, 2000. 
 * All rights reserved worldwide.
 *
 * This software is provided "as is" without express or implied
 * warranties. You may freely copy and compile this source into
 * applications you distribute provided that the copyright text
 * below is included in the resulting source code, for example:
 * "Portions Copyright (C) Andrew Kirmse, 2000"
 */
// A simple pseudorandom number generator.  It's not that great, but at least it
// generates 32 bit random numbers (most rand()'s generate 15 bits).

// If no seed is given in the constructor, the state is set to a fixed value.
// This can be useful for reproducing a stream of random numbers.

// Adapted from the book "Inner Loops" by Rick Booth (Addison-Wesley: 1997).

#ifndef _RANDOM_H
#define _RANDOM_H

#include "defs.h"

class Random
{
public:
    Random();
    Random(uint32 seed);
    ~Random();

    // Generates a full 32 bit random number.
    uint32 Generate();

    // Generates a positive 32 bit random number.
    int32 GeneratePositive()
    {
        return Generate() & 0x7fffffff;
    }

protected:
    enum
    {
        TABLE_SIZE = 250,
    };

    // This single seed is used to initialize a simple generator that provides
    // the seeds to the real generator.
    uint32 state;

    int32 index1, index2;
    uint32 table[TABLE_SIZE];

    void GenerateSeeds();

    // Return a new number generated by a simple generator that depends only on state.
    uint32 GenerateSimple();
};

#endif
