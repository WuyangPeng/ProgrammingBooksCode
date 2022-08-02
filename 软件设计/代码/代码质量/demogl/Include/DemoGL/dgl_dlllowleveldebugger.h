//////////////////////////////////////////////////////////////////////
// FILE: dgl_dlllowleveldebugger.h
// PURPOSE: include file of dgl_dlllowleveldebugger.cpp
//////////////////////////////////////////////////////////////////////
// Part of DemoGL Demo System sourcecode. See version information
//////////////////////////////////////////////////////////////////////
// COPYRIGHTS:
// Copyright (c)1999-2001 Solutions Design. All rights reserved.
// Central DemoGL Website: www.demogl.com.
// 
// Released under the following license: (BSD)
// -------------------------------------------
// Redistribution and use in source and binary forms, with or without modification, 
// are permitted provided that the following conditions are met: 
//
// 1) Redistributions of source code must retain the above copyright notice, this list of 
//    conditions and the following disclaimer. 
// 2) Redistributions in binary form must reproduce the above copyright notice, this list of 
//    conditions and the following disclaimer in the documentation and/or other materials 
//    provided with the distribution. 
// 
// THIS SOFTWARE IS PROVIDED BY SOLUTIONS DESIGN ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, 
// INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A 
// PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL SOLUTIONS DESIGN OR CONTRIBUTORS BE LIABLE FOR 
// ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT 
// NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR 
// BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, 
// STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE 
// USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. 
//
// The views and conclusions contained in the software and documentation are those of the authors 
// and should not be interpreted as representing official policies, either expressed or implied, 
// of Solutions Design. 
//
// See also License.txt in the sourcepackage.
//
//////////////////////////////////////////////////////////////////////
// Contributers to the code:
//		- Frans Bouma [FB]
//////////////////////////////////////////////////////////////////////
// VERSION INFORMATION.
//
// v1.3: Added to codebase.
// v1.2: -
// v1.1: -
//////////////////////////////////////////////////////////////////////

#ifndef _DGL_DLLLOWLEVELDEBUGGER_H
#define _DGL_DLLLOWLEVELDEBUGGER_H

////////////////////////////////////////////////////////////////////////
//                          
//						DEFINES
//
////////////////////////////////////////////////////////////////////////

#define	DGLDBG_LOGFILENAME		"DemoGL_log.txt"
#define DGLDBG_MAXCALLLEVELS	10

////////////////////////////////////////////////////////////////////////
//                          
//						FUNCTION DEFINITIONS
//
////////////////////////////////////////////////////////////////////////
extern	void	_dgldbg_OpenLogFile(void);
extern	void	_dgldbg_CloseLogFile(void);
extern	void	_dgldbg_EnteredRoutine(char *pszRoutineName);
extern	void	_dgldbg_LeftRoutine(char *pszRoutineName);
extern	void	_dgldbg_LeftRoutine(char *pszRoutineName, void *pReturnVal);
extern	void	_dgldbg_LeftRoutine(char *pszRoutineName, char *pszReturnValue);
extern	void	_dgldbg_LeftRoutine(char *pszRoutineName, int iReturnValue);
extern	void	_dgldbg_LogMessage(HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam);
extern	void	_dgldbg_LogString(char *pszToLog, char *pszCallerName);

//////////////////////////////////////////////////////////////////////
//
//                        FILE SCOPE FUNCTION DEFINITIONS
//
//////////////////////////////////////////////////////////////////////
char			*_dgldbg_Message2String(UINT uiMsg);
char			*_dgldbg_CallLevel2String(void);
char			*_dgldbg_SystemState2String(void);

#endif	// _DGL_DLLLOWLEVELDEBUGGER_H

