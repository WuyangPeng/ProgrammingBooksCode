
//Listing 4-4


  #ifndef __THREAD_OBJECT_H
  #define __THREAD_OBJECT_H

  using namespace std;
  #include <iostream>
  #include <pthread.h>
  #include <string>
  #include "posix_queue.h"

  class thread_object{
     pthread_t Tid;
     string Name;
  protected:
     virtual void do_something(void) = 0;
  public:
     thread_object(void);
     ~thread_object(void);
     void name(string X);
     string name(void);
     void run(void);
     void join(void);
     friend void *thread(void *X);
  };



  class user_thread : public thread_object{
     private:
     posix_queue *PosixQueue;
  protected:
     virtual void do_something(void);
  public:
     user_thread(void);
     ~user_thread(void);
  };

 
  #endif

