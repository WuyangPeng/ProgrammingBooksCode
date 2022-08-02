/* $XConsortium: Keyboard.c /main/4 1996/09/28 17:13:49 rws $ */
/*

Copyright 1993 by Davor Matic

Permission to use, copy, modify, distribute, and sell this software
and its documentation for any purpose is hereby granted without fee,
provided that the above copyright notice appear in all copies and that
both that copyright notice and this permission notice appear in
supporting documentation.  Davor Matic makes no representations about
the suitability of this software for any purpose.  It is provided "as
is" without express or implied warranty.

*/
#define NEED_EVENTS
#include "X.h"
#include "Xproto.h"
#include "keysym.h"
#include "screenint.h"
#include "inputstr.h"
#include "misc.h"
#include "scrnintstr.h"
#include "servermd.h"

#include "Xnest.h"

#include "Display.h"
#include "Screen.h"
#include "Keyboard.h"
#include "Args.h"

void xnestBell(volume, pDev, ctrl, cls)
     int volume;
     DeviceIntPtr pDev;
     pointer ctrl;
     int cls;
{
  XBell(xnestDisplay, volume);
}

void xnestChangeKeyboardControl(pDev, ctrl)
     DeviceIntPtr pDev;
     KeybdCtrl *ctrl;
{
  unsigned long value_mask;
  XKeyboardControl values;
  int i;

  value_mask = KBKeyClickPercent |
               KBBellPercent |
	       KBBellPitch |
	       KBBellDuration |
	       KBAutoRepeatMode;

  values.key_click_percent = ctrl->click;
  values.bell_percent = ctrl->bell;
  values.bell_pitch = ctrl->bell_pitch;
  values.bell_duration = ctrl->bell_duration;
  values.auto_repeat_mode = ctrl->autoRepeat ? 
                             AutoRepeatModeOn : AutoRepeatModeOff;

  XChangeKeyboardControl(xnestDisplay, value_mask, &values);

  /*
  value_mask = KBKey | KBAutoRepeatMode;
  At this point, we need to walk through the vector and compare it
  to the current server vector.  If there are differences, report them.
  */

  value_mask = KBLed | KBLedMode;
  for (i = 1; i <= 32; i++) {
    values.led = i;
    values.led_mode = (ctrl->leds & (1 << (i - 1))) ? LedModeOn : LedModeOff;
    XChangeKeyboardControl(xnestDisplay, value_mask, &values);
  }
}

int xnestKeyboardProc(pDev, onoff, argc, argv)
     DevicePtr pDev;
     int onoff, argc;
     char *argv[];
{
  XModifierKeymap *modifier_keymap;
  KeySym *keymap;
  int mapWidth;
  int min_keycode, max_keycode;
  KeySymsRec keySyms;
  CARD8 modmap[256];
  int i, j;

  switch (onoff)
    {
    case DEVICE_INIT: 
      modifier_keymap = XGetModifierMapping(xnestDisplay);
      XDisplayKeycodes(xnestDisplay, &min_keycode, &max_keycode);
#ifdef _XSERVER64
      {
	KeySym64 *keymap64;
	int i, len;
	keymap64 = XGetKeyboardMapping(xnestDisplay,
				     min_keycode,
				     max_keycode - min_keycode + 1,
				     &mapWidth);
	len = (max_keycode - min_keycode + 1) * mapWidth;
	keymap = (KeySym *)xalloc(len * sizeof(KeySym));
	for(i = 0; i < len; ++i)
	  keymap[i] = keymap64[i];
	XFree(keymap64);
      }
#else
      keymap = XGetKeyboardMapping(xnestDisplay, 
				   min_keycode,
				   max_keycode - min_keycode + 1,
				   &mapWidth);
#endif
      
      for (i = 0; i < 256; i++)
	modmap[i] = 0;
      for (j = 0; j < 8; j++)
	for(i = 0; i < modifier_keymap->max_keypermod; i++) {
	  CARD8 keycode;
	  if (keycode = 
	      modifier_keymap->
	        modifiermap[j * modifier_keymap->max_keypermod + i])
	    modmap[keycode] |= 1<<j;
	}
      XFreeModifiermap(modifier_keymap);
      
      keySyms.minKeyCode = min_keycode;
      keySyms.maxKeyCode = max_keycode;
      keySyms.mapWidth = mapWidth;
      keySyms.map = keymap;
      InitKeyboardDeviceStruct(pDev, &keySyms, modmap,
			       xnestBell, xnestChangeKeyboardControl);
      XFree(keymap);
      break;
    case DEVICE_ON: 
      xnestEventMask |= XNEST_KEYBOARD_EVENT_MASK;
      for (i = 0; i < xnestNumScreens; i++)
	XSelectInput(xnestDisplay, xnestDefaultWindows[i], xnestEventMask);
      break;
    case DEVICE_OFF: 
      xnestEventMask &= ~XNEST_KEYBOARD_EVENT_MASK;
      for (i = 0; i < xnestNumScreens; i++)
	XSelectInput(xnestDisplay, xnestDefaultWindows[i], xnestEventMask);
      break;
    case DEVICE_CLOSE: 
      break;
    }
  return Success;
}

Bool LegalModifier(key, pDev)
     unsigned int key;
     DevicePtr pDev;
{
  return TRUE;
}
