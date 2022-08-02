/* Copyright (C) Steven Ranck, 2000. 
 * All rights reserved worldwide.
 *
 * This software is provided "as is" without express or implied
 * warranties. You may freely copy and compile this source into
 * applications you distribute provided that the copyright text
 * below is included in the resulting source code, for example:
 * "Portions Copyright (C) Steven Ranck, 2000"
 */
#include "frame.h"
#include <malloc.h>
#include <cassert>
#include <cstdio>

#define _HEAPNUM 1  // Arbitrary. We'll use the upper heap (1). 随你的便，这里我们将使用高堆(1)。

static void* _pObject1;  // Where our CopCar object will be loaded. 我们的CopCar将被读到这里
static void* _pObject2;  // Where our RobberCar object will be loaded. RobberCar将被读到这里。

void* LoadMyObject(const char*);

// Loads the CopCar and RobberCar objects from disk into _HEAPNUM.
// Returns 0 if successful, or 1 if not successful.
// 把CopCar和RobberCar对象从磁盘读到_HEAPNUM中
// 如果成功传回0，否则传回1
int LoadCarObjects(void)
{
    Frame_t Frame;

    // Get a frame handle:
    // 得到一个帧柄：
    Frame = GetFrame(_HEAPNUM);

    // Attempt to load the CopCar object:
    // 尝试读取CopCar对象
    _pObject1 = LoadMyObject("CopCar");
    if (_pObject1 == 0)
    {
        // Object couldn't be loaded. Release memory:
        // 不能读取对象。释放内存。
        ReleaseFrame(Frame);
        return 1;
    }

    // Attempt to load the RobberCar object:
    // 尝试读取RobberCar对象：
    _pObject2 = LoadMyObject("RobberCar");
    if (_pObject2 == 0)
    {
        // Object couldn't be loaded. Release memory:
        // 不能读取对象。释放内存
        ReleaseFrame(Frame);
        return 1;
    }

    // Objects loaded ok. Keep the memory around:
    // 对象读取成功。保持已分配的内存：
    return 0;
}

// Allocates memory from _HEAPNUM and loads the specified object
// from disk into the allocated memory. Returns a pointer to the
// object if successful, or 0 if not successful.
// 从_HEAPNUM分配内存，同时把指定的对象从磁盘读到已分配的内存中。
// 如果成功，传回对象指针，否则传回0
void* LoadMyObject(const char* pszObjectName)
{
    int nObjectSize;
    void* pObject;

    nObjectSize = GetObjectSize(pszObjectName);
    if (nObjectSize == 0)
    {
        // Trouble getting object size:
        // 不能准确得到对象大小
        return 0;
    }

    pObject = AllocFrameMemory(nObjectSize, _HEAPNUM);
    if (pObject == 0)
    {
        // Insufficient memory:
        // 内存不足
        return 0;
    }

    if (LoadFromDisk(pszObjectName, pObject))
    {
        // Trouble loading object from disk:
        // 不能从磁盘上读取对象。
        return 0;
    }

    // Object loaded successfully:
    // 对象读取成功
    return pObject;
}
