/////////////////////////////////////////////////////////////////////////
// conversionsLib.cpp
// by Dustin Clingman  1/15/04
//
// Purpose: The header for the conversion functions.
//
//////////////////////////////////////////////////////////////////////////

#include "conversionsLib.h"

float convertAccelMilesToMeters(float miles)
    {
     float accelMeters;
     accelMeters = (miles*KM_TO_MILES*KM_TO_METERS) / (HOURS_TO_MIN*MIN_TO_SEC*HOURS_TO_MIN*MIN_TO_SEC);
     return accelMeters;
    }

float convertDaysToSeconds(float days)
    {
      float seconds;
      seconds = days*HOURS_TO_DAY*HOURS_TO_MIN*MIN_TO_SEC;  
      return seconds;
    }

float convertMilesToMeters(float miles)
    {
      float meters;
      meters = miles*KM_TO_MILES*KM_TO_METERS;
      return meters;
    }

float convertSpeed(float miles)
    {
      float meters;
      meters = (miles*KM_TO_MILES*KM_TO_METERS) / (HOURS_TO_MIN*MIN_TO_SEC);
      return meters;
    }