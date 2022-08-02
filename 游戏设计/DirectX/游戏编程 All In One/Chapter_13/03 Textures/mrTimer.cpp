 /* 'mrWindows.cpp' */

 /* Complement header file */
#include "mrTimer.h"

 /* Default constructor */
mrTimer::mrTimer (void)
{
  /* Get the hardware clock frequency and current count */
 QueryPerformanceFrequency (&m_iFrequency);
 QueryPerformanceCounter (&m_iLastQuery);
}

 /* Default destructor */
mrTimer::~mrTimer (void)
{
 m_iFrequency.QuadPart = 0;
 m_iLastQuery.QuadPart = 0;
}

 /* Update timer */
void mrTimer::Update (void)
{
 LARGE_INTEGER  kTempTimer;
 time_t         iTempTimeDate;

  /* Get current timer information and calculate difference */
 QueryPerformanceCounter (&kTempTimer);
 m_iDelta.QuadPart = kTempTimer.QuadPart - m_iLastQuery.QuadPart;

  /* Save current timer information */
 m_iLastQuery.QuadPart = kTempTimer.QuadPart;

  /* Get current time and date */
 time (&iTempTimeDate);
 m_pkTime = localtime (&iTempTimeDate);
}

 /* Get delta time from last update */
mrReal32 mrTimer::GetDelta (void)
{
  /* Convert to float and calculate delta in seconds */
 return (mrReal32)(m_iDelta.QuadPart) / 
        (mrReal32)(m_iFrequency.QuadPart);
}

 /* Get system seconds */
mrUInt32 mrTimer::GetSeconds (void)
{
 return m_pkTime->tm_sec;
}

 /* Get system minutes */
mrUInt32 mrTimer::GetMinutes (void)
{
 return m_pkTime->tm_min;
}

 /* Get system hours */
mrUInt32 mrTimer::GetHours (void)
{
 return m_pkTime->tm_hour;
}

 /* Get system day */
mrUInt32 mrTimer::GetDay (void)
{
 return m_pkTime->tm_mday;
}

 /* Get system month */
mrUInt32 mrTimer::GetMonth (void)
{
 return m_pkTime->tm_mon;
}

 /* Get system year */
mrUInt32 mrTimer::GetYear (void)
{
 return m_pkTime->tm_year;
}