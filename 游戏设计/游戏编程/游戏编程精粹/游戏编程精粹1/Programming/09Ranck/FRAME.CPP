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

static int _nByteAlignment;  // Memory alignment in bytes 内存对齐的字节数
static u8* _pMemoryBlock;  // Value returned by malloc() malloc()返回值
static u8* _apBaseAndCap[2];  // [0]=Base pointer, [1]=Cap pointer [0]=基指针，[1]=顶指针
static u8* _apFrame[2];  // [0]=Lower frame pointer, [1]=Upper frame pointer [0]=低帧指针，[1]=高帧指针

// Must be called exactly once at game initialization time.
// nByteAlignment must be a power-of-2.
// Returns 0 if successful, or 1 if an error occurred.
// 必须在游戏初始化时调用一次且最多一次
// nByteAlignment必须是2的幂
// 成功时返回0，错误发生时返回1
int InitFrameMemorySystem(int nSizeInBytes, int nByteAlignment)
{
    // Make sure nSizeInBytes is a multiple of nByteAlignment:
    // 必须保证nSizeInBytes是nByteAlignment的整数倍：
    nSizeInBytes = ALIGNUP(nSizeInBytes, nByteAlignment);

    // First allocate our Memory Block:
    // 首先分配我们的内存块：
    _pMemoryBlock = (u8*)malloc(nSizeInBytes + nByteAlignment);
    if (_pMemoryBlock == 0)
    {
        // Not enough memory. Return error flag:
        // 没有足够内存，返回错误标志：
        return 1;
    }

    _nByteAlignment = nByteAlignment;

    // Set up Base pointer:
    // 设置基指针：
    _apBaseAndCap[0] = (u8*)ALIGNUP(_pMemoryBlock, nByteAlignment);

    // Set up Cap pointer:
    // 设置顶指针：
    _apBaseAndCap[1] = (u8*)ALIGNUP(_pMemoryBlock + nSizeInBytes, nByteAlignment);

    // Finally, initialize the Lower and Upper frame pointers:
    // 最后，初始化低帧指针和高帧指针
    _apFrame[0] = _apBaseAndCap[0];
    _apFrame[1] = _apBaseAndCap[1];

    // Successful!
    // 成功
    return 0;
}

void ShutdownFrameMemorySystem(void)
{
    free(_pMemoryBlock);
}

// Returns a pointer to the base of the memory block,
// or returns 0 if there was insufficient memory.
// nHeapNum is the heap number: 0=lower, 1=upper.
// 返回内存块的基指针，或者在没有足够内存时返回0
// nHeapNum是堆编号：0=低，1=高
void* AllocFrameMemory(int nBytes, int nHeapNum)
{
    u8* pMem;

    // First, align the requested size:
    // 首先，将请求大小内存对齐：
    nBytes = ALIGNUP(nBytes, _nByteAlignment);

    // Check for available memory:
    // 检查可用内存
    if (_apFrame[0] + nBytes > _apFrame[1])
    {
        // Insufficient memory:
        // 没有足够内存
        return 0;
    }

    // Now perform the memory allocation:
    // 现在完成内存分配操作

    if (nHeapNum)
    {
        // Allocating from upper heap, down:
        // 从高堆向下分配：

        _apFrame[1] -= nBytes;
        pMem = _apFrame[1];
    }
    else
    {
        // Allocating from lower heap, up:
        // 从低堆向上分配：

        pMem = _apFrame[0];
        _apFrame[0] += nBytes;
    }

    return (void*)pMem;
}

// Returns a Frame handle which can be used to
// later release memory allocated henceforth.
// nHeapNum is the heap number: 0=lower, 1=upper.
// 返回一个可以在以后用于释放内存的帧句柄
// nHeapNum是堆的编号：0=低, 1=高。
Frame_t GetFrame(int nHeapNum)
{
    Frame_t Frame;

    Frame.pFrame = _apFrame[nHeapNum];
    Frame.nHeapNum = nHeapNum;

    return Frame;
}

void ReleaseFrame(Frame_t Frame)
{
    // Check validity if releasing in lower heap (0):
    // 检测低堆中释放操作的有效性。
    assert(Frame.nHeapNum == 1 || (uint)Frame.pFrame <= (uint)_apFrame[0]);

    // Check validity if releasing in upper heap (1):
    // 检测高堆中释放操作的有效性。
    assert(Frame.nHeapNum == 0 || (uint)Frame.pFrame >= (uint)_apFrame[1]);

    // Release frame:
    // 释放帧
    _apFrame[Frame.nHeapNum] = Frame.pFrame;
}
