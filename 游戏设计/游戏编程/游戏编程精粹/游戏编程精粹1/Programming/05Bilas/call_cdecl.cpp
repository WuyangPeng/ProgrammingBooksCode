/* Copyright (C) Scott Bilas, 2000. 
 * All rights reserved worldwide.
 *
 * This software is provided "as is" without express or implied
 * warranties. You may freely copy and compile this source into
 * applications you distribute provided that the copyright text
 * below is included in the resulting source code, for example:
 * "Portions Copyright (C) Scott Bilas, 2000"
 */

#include <windows.h>
#include <iostream>
#include <vector>
 
// Code from "Calling Conventions" Section
//
DWORD Call_cdecl(const void* args, size_t sz, DWORD func)
{
    DWORD rc;  // here's our return value... 这是我们的返回值…
    __asm
    {
        mov   ecx, sz  // get size of buffer 获得缓冲区大小
        mov   esi, args  // get buffer 获得缓冲区 
        sub   esp, ecx  // allocate stack space 分配栈空间
        mov   edi, esp  // start of destination stack frame 目标栈帧的起始地址
        shr   ecx, 2  // make it dwords 以双字为单位操作
        rep   movsd  // copy params to real stack 复制参数到真正的栈中
        call  [func]  // call the function 调用函数
        mov   rc,  eax  // save the return value 保存返回值
        add   esp, sz  // restore the stack pointer 恢复栈指针
    }
    return (rc);
}

DWORD Call_stdcall(const void* args, size_t sz, DWORD func)
{
    DWORD rc;  // here's our return value... 这是我们的返回值…
    __asm
    {
        mov   ecx, sz  // get size of buffer 获得缓冲区大小
        mov   esi, args  // get buffer 获得缓冲区
        sub   esp, ecx  // allocate stack space 分配栈空间
        mov   edi, esp  // start of destination stack frame 目标栈帧的起始地址
        shr   ecx, 2  // make it dwords 以双字为单位操作
        rep   movsd  // copy it 复制参数到真正的栈中
        call  [func]  // call the function 调用函数
        mov   rc,  eax  // save the return value 保存返回值
    }
    return (rc);
}

__declspec(naked) DWORD GetST0(void)
{
    DWORD f;  // temp var 临时变量
    __asm
    {
        fstp dword ptr [f]  // pop ST0 into f 弹出ST0到f
        mov eax, dword ptr [f]  // copy into eax 复制到eax
        ret  // done 完成
    }
}
