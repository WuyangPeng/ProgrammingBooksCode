/*******************************************************************
 *         Advanced 3D Game Programming with DirectX 10.0
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *	
 *	See license.txt for modification and distribution information
 *		copyright (c) 2007 by Peter Walsh, Wordware
 ******************************************************************/

#if !defined(AFX_STDAFX_H__A9DB83DB_A9FD_11D0_BFD1_444553540000__INCLUDED_)
#define AFX_STDAFX_H__A9DB83DB_A9FD_11D0_BFD1_444553540000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#define DIRECTINPUT_VERSION 0x0800
#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers

#include <windows.h>
#include <mmsystem.h>

// Local Header Files

#include <d3d10.h>
#include <d3dx10.h>
#include <mmsystem.h>
#include <dsound.h>
#include <dinput.h>

#include "..\GameLib\GraphicsLayer.h"
#include "..\GameLib\Application.h"
#include "..\GameLib\Window.h"
#include "..\GameLib\GameGlobals.h"
#include "..\GameLib\GameTypes.h"
#include "..\GameLib\sound.h"
#include "..\GameLib\soundlayer.h"

// TODO: reference additional headers your program requires here

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__A9DB83DB_A9FD_11D0_BFD1_444553540000__INCLUDED_)
