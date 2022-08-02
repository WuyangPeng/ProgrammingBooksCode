#ifndef DEFINES_H
#define DEFINES_H


#include <windows.h>



//------------------------------------------------------------------
//
//	general defines
//------------------------------------------------------------------
#define WINDOW_WIDTH				400	
#define WINDOW_HEIGHT				400

#define FRAMES_PER_SECOND		60

#define	PI						      3.14159265358979

#define MAX_ROTATION_PER_TICK     0.05
#define MAX_SCALE_PER_TICK        0.1
#define MAX_TRANSLATION_PER_TICK  1

//macros for the user input
#define KEYDOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
#define KEYUP(vk_code)   ((GetAsyncKeyState(vk_code) & 0x8000) ? 0 : 1)


#endif