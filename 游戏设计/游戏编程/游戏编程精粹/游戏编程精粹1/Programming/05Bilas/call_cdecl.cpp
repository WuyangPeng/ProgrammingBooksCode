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
    DWORD rc;  // here's our return value... �������ǵķ���ֵ��
    __asm
    {
        mov   ecx, sz  // get size of buffer ��û�������С
        mov   esi, args  // get buffer ��û����� 
        sub   esp, ecx  // allocate stack space ����ջ�ռ�
        mov   edi, esp  // start of destination stack frame Ŀ��ջ֡����ʼ��ַ
        shr   ecx, 2  // make it dwords ��˫��Ϊ��λ����
        rep   movsd  // copy params to real stack ���Ʋ�����������ջ��
        call  [func]  // call the function ���ú���
        mov   rc,  eax  // save the return value ���淵��ֵ
        add   esp, sz  // restore the stack pointer �ָ�ջָ��
    }
    return (rc);
}

DWORD Call_stdcall(const void* args, size_t sz, DWORD func)
{
    DWORD rc;  // here's our return value... �������ǵķ���ֵ��
    __asm
    {
        mov   ecx, sz  // get size of buffer ��û�������С
        mov   esi, args  // get buffer ��û�����
        sub   esp, ecx  // allocate stack space ����ջ�ռ�
        mov   edi, esp  // start of destination stack frame Ŀ��ջ֡����ʼ��ַ
        shr   ecx, 2  // make it dwords ��˫��Ϊ��λ����
        rep   movsd  // copy it ���Ʋ�����������ջ��
        call  [func]  // call the function ���ú���
        mov   rc,  eax  // save the return value ���淵��ֵ
    }
    return (rc);
}

__declspec(naked) DWORD GetST0(void)
{
    DWORD f;  // temp var ��ʱ����
    __asm
    {
        fstp dword ptr [f]  // pop ST0 into f ����ST0��f
        mov eax, dword ptr [f]  // copy into eax ���Ƶ�eax
        ret  // done ���
    }
}
