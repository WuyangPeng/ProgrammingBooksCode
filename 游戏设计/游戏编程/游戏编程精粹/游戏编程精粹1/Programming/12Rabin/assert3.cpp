/* Copyright (C) Steve Rabin, 2000. 
 * All rights reserved worldwide.
 *
 * This software is provided "as is" without express or implied
 * warranties. You may freely copy and compile this source into
 * applications you distribute provided that the copyright text
 * below is included in the resulting source code, for example:
 * "Portions Copyright (C) Steve Rabin, 2000"
 */

#include <cassert>

#define Assert(a, b) assert(a&& b)

void Test3()
{
    [[maybe_unused]] int src = 0;

    Assert(src != 0, "VectorNormalize: src vector pointer is NULL");
    Assert(0, "VectorNormalize: The code should never get here");
}
