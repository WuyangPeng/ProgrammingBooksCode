

//Listing 7-11

  #ifndef _CT_MUTEX_H
  #define_CT_MUTEX_H
  #include <pthread.h>
  #include <time.h>
  class permit{
  protected:
     pthread_mutex_t Permit; 
     pthread_mutexattr_t PermitAttr;
  public:
     permit(void);
     bool available(void);
     bool not_in_use(void);
     bool checkAvailability(void);
     bool  availableFor(int secs,int nanosecs);   
  };


  #endif/* _CT_MUTEX_H */

