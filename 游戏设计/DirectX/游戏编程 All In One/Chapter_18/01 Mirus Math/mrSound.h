 /* 'mrSound.h' */

 /* Mirus base types header */
#include "mrDatatypes.h"
 /* Mirus error definitions header */
#include "mrError.h"
 /* Mirus sound player header file */
#include "mrSoundPlayer.h"
 /* Windows header file */
#include <windows.h>
 /* C++ file stream header file */
#include <fstream.h>
 /* Direct Music header file */
#include <dsound.h>

 /* Include this file only once */
#pragma once

 /* Mirus Sound class */
class mrSound
{
protected:
  /* DirectSound objects */
 LPDIRECTSOUNDBUFFER          m_lpkSound;

public:
  /* Constructors / Destructor */
 mrSound (void);
 ~mrSound (void);

  /* Sound manipulation routines */
 mrError32 LoadFromFile (LPSTR lpszFilename);
 mrError32 SetVolume (mrUInt32 iVolume);
 mrError32 Play (mrUInt32 iLoop);
 mrError32 Stop (void);
};