 /* 'mrSoundPlayer.h' */

 /* Mirus base types header */
#include "mrDatatypes.h"
 /* Mirus error definitions header */
#include "mrError.h"
 /* Windows header file */
#include <windows.h>
 /* Direct Music header file */
#include <dsound.h>
/* Assert header file */
#include <assert.h> 

 /* Include this file only once */
#pragma once

 /* Mirus Sound Player class */
class mrSoundPlayer
{
protected:
  /* DirectSound objects */
 LPDIRECTSOUND8         m_lpkDSound;

  /* Singleton */
 static mrSoundPlayer * m_pkSingleton;

public:
  /* Constructors / Destructor */
 mrSoundPlayer (void);
 ~mrSoundPlayer (void);

  /* Sound player manipulation routines */
 mrError32 Init (HWND hWindow);

  /* Sound player maintenance routines */
 LPDIRECTSOUND8 GetSound (void);

  /* Singleton */
 static mrSoundPlayer * GetSingleton (void);
};