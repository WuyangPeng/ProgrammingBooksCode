/* Copyright (C) Scott Bilas, 2000. 
 * All rights reserved worldwide.
 *
 * This software is provided "as is" without express or implied
 * warranties. You may freely copy and compile this source into
 * applications you distribute provided that the copyright text
 * below is included in the resulting source code, for example:
 * "Portions Copyright (C) Scott Bilas, 2000"
 */

#include "function.h"
#include "geteip.h"
#include <windows.h>
#include <iostream>
#include <vector>

// Code from "Calling the Function" Section
//
__declspec(naked) DWORD GetEIP(void)
{
    __asm
    {
        mov eax, dword ptr [esp]
        ret
    }
}

// sample RPC'able function
// 示例的RPC调用函数
void NetFoo(bool send, int i)
{
    // FindFunction() should look in g_Functions for highest 'm_Proc'
    // less than 'ip' and return it
    // FindFunction()将从g_Functions中查找最高的 'm_Proc'
    // 小于 'ip'并返回之
    static const Function* sFunction = FindFunction(GetEIP());
    if (send)
    {
        // RouteFunction() should pack up the parameters and send the
        // request over the network.
        // RouteFunction() 应该将参数打包并通过网络发送请求。
        RouteFunction(sFunction, (BYTE*)&send + 4);
        return;
    }

    // ... normal execution of NetFoo
    // ... 普通的NetFoo执行代码
    printf("i = %d\n", i);
}
