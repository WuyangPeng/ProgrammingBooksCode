 /* 'mrError.h' */

 /* Include this file only once */
#pragma once

 /* Error codes */
enum mrError32
{
 mrNoError                    = 0,
 mrErrorRegisterClass         = 1,
 mrErrorInitDirect3D,
	mrErrorGetAdapterDisplayMode,
	mrErrorCreateDevice,
 mrErrorPresent,
 mrErrorBeginScene,
 mrErrorEndScene,
 mrErrorClear,

 mrError32_Force32            = 0xFFFFFFFF
};


