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
#include <iostream>
#include <vector>

// Code from "Completing the Solution" Section
//
float Foo(int, const char*);
int Bar(void);

void SetupFunctionExports(void)
{
    {
        Function function;

        function.m_Name = "Foo";
        function.m_Proc = Foo;
        function.m_SerialID = g_Functions.size();

        function.m_ReturnType = Function::VAR_FLOAT;
        function.m_ParamTypes.push_back(Function::VAR_INT);
        function.m_ParamTypes.push_back(Function::VAR_STRING);
        function.m_CallType = Function::CALL_CDECL;

        g_Functions.push_back(function);
    }

    {
        Function function;

        function.m_Name = "Bar";
        function.m_Proc = Bar;
        function.m_SerialID = g_Functions.size();

        function.m_ReturnType = Function::VAR_INT;
        function.m_CallType = Function::CALL_CDECL;

        g_Functions.push_back(function);
    }
}
