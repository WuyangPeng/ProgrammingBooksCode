 /* 'mrTimer.h' */

 /* Mirus base types header */
#include "mrDatatypes.h"
 /* Windows header file */
#include <windows.h> 
 /* Time header file */
#include <time.h> 

 /* Include this file only once */
#pragma once

 /* Mirus timer class */
class mrTimer
{
protected:
  /* Hardware timer variables */
 LARGE_INTEGER   m_iFrequency;
 LARGE_INTEGER   m_iLastQuery;
 LARGE_INTEGER   m_iDelta;

  /* Time and date variables */
 tm *            m_pkTime;

public:
  /* Constructor / Destructor */
 mrTimer (void);
 ~mrTimer (void);

  /* Update the time variables */
 void Update (void);

  /* Return the timer information */
 mrReal32 GetDelta (void);
 mrUInt32 GetSeconds (void);
 mrUInt32 GetMinutes (void);
 mrUInt32 GetHours (void);
 mrUInt32 GetDay (void);
 mrUInt32 GetMonth (void);
 mrUInt32 GetYear (void);
};
