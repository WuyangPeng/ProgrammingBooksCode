 /* 'mrCDPlayer.h' */

 /* Mirus base types header */
#include "mrDatatypes.h"
 /* Mirus error definitions header */
#include "mrError.h"
 /* Standard input/output header file */
#include <stdio.h>
 /* Windows header file */
#include <windows.h>
 /* Windows Multimedia header file */
#include <mmsystem.h>

 /* Include this file only once */
#pragma once

 /* Mirus CD Player class */
class mrCDPlayer
{
protected:
  /* CD information */
 mrUInt32         m_iNumberTracks;
 mrUInt32         m_iCurrentTrack;
 mrInt8           m_szLength [256];

public:
  /* Constructors / Destructor */
 mrCDPlayer (void);
 ~mrCDPlayer (void);

  /* CD player manipulation routines */
 void Eject (void);
 void Play (mrUInt32 iTrack);
 void Stop (void);
 void Update (void);

  /* CD player maintainance routines */
 mrUInt32 GetNumberOfTracks (void);
 mrInt8 * GetLength (void);
 mrUInt32 GetCurrentTrack (void);
 mrBool32 IsReady (void);
};