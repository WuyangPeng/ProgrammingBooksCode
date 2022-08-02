/////////////////////////////////////////////////////////////////////////
// conversionsLib.h
// by Dustin Clingman  1/15/04
//
// Purpose: The header for the conversion functions.
//
//////////////////////////////////////////////////////////////////////////

//Some useful defines for our conversions.
#define KM_TO_MILES 1.609
#define KM_TO_METERS 1000
#define DAYS_TO_WEEK 7
#define HOURS_TO_DAY 24
#define HOURS_TO_MIN 60
#define MIN_TO_SEC 60

float convertAccelMilesToMeters(float miles);
float convertDaysToSeconds(float days);
float convertMilesToMeters(float miles);
float convertSpeed(float miles);

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