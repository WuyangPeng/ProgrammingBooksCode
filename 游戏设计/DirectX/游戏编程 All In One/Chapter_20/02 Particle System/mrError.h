 /* 'mrError.h' */

 /* Include this file only once */
#pragma once

 /* Error codes */
enum mrError32
{
 mrNoError																													= 0,
 mrErrorRegisterClass																		= 1,
	 /* Graphics component */
 mrErrorInitDirect3D																			= 2,
	mrErrorGetAdapterDisplayMode										= 3,
	mrErrorCreateDevice																			= 4,
 mrErrorPresent																							 = 5,
 mrErrorBeginScene																					= 6,
 mrErrorEndScene																							= 7,
 mrErrorClear															 				 		 		= 8,
	mrErrorNotBitmapFile								 	  		 	 	= 9,
	mrErrorBitmapNotSupported				 								= 10,
	mrErrorTargaNotSupported						 							= 11,
	mrErrorInvalidRawImage									   				= 12,
	mrErrorCreateImageSurface													= 13,
	mrErrorCreateTexture																		= 14,
	mrErrorAddTexture																				 = 15,
	mrErrorDrawPrimitive																		= 16,
 mrErrorSetCooperativeLevel												= 17,

	 /* Input component */
	mrErrorDInputCreate																			= 18,
 mrErrorKeyboardCreateDevice											= 19,		
 mrErrorKeyboardSetDataFormat							   = 20,
	mrErrorKeyboardSetCooperativeLevel			 = 21,
 mrErrorKeyboardGetDeviceData								  = 22,
	mrErrorKeyboardAcquire													 	 = 23,
	mrErrorMouseCreateDevice														= 24,
	mrErrorMouseSetDataFormat													= 25,
	mrErrorMouseSetProperty															= 26,
	mrErrorMouseSetCooperativeLevel							= 27,
 mrErrorMouseGetDeviceData													= 28,
	mrErrorJoystickEnumDevices												= 29,
	mrErrorJoystickAcquire																= 30,
	mrErrorJoystickGetDeviceState									= 31,
	mrErrorJoystickSetDataFormat							 		= 32,
	mrErrorJoystickSetCooperativeLevel    = 33,
	mrErrorJoystickSetProperty									   = 34,

	 /* Sound component */
 mrErrorWaveNotSupported															= 35,
	mrErrorPlay																											= 36,
	mrErrorCreateSoundBuffer														= 37,
	mrErrorSoundBufferLock																= 38,
	mrErrorSoundSetVolume															 	= 39,
	mrErrorStop																											= 40,
 mrErrorCreateSoundDevice														= 41,

 mrError32_Force32																					= 0xFFFFFFFF
};


