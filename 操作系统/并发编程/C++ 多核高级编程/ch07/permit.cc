
//Listing 7-12

  #include "permit.h"


  permit:: permit(void)
  {
     int AValue,MValue;
     AValue = pthread_mutexattr_init(&PermitAttr);
     MValue = pthread_mutex_init(&Permit,&PermitAttr);
  }
  bool permit::available(void)
  {
     int RC;
     RC = pthread_mutex_lock(&Permit);
     return(true);
     
  }
  bool permit::not_in_use(void)
  {
     int RC;
     RC = pthread_mutex_unlock(&Permit);
     return(true);
     
  }
  bool permit::checkAvailability(void)
  {
     int RC;
     RC = pthread_mutex_trylock(&Permit);
     return(true);
  }
  bool permit::availableFor(int secs,int nanosecs)
  {
     //...
     struct timespec Time;
     return(true);
     
  }
