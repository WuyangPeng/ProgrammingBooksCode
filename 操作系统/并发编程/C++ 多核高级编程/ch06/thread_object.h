
//Listing 6-2

    #ifndef __THREAD_OBJECT_H
    #define __THREAD_OBJECT_H
 	
    using namespace std;
    #include <iostream>
    #include <pthread.h>
    #include <string>
 	
    class thread_object{
         pthread_t Tid;
	    
  protected:
       virtual void do_something(void) = 0;
       pthread_attr_t SchedAttr;
       struct sched_param SchedParam; 
       string Name;
       int NewPolicy;
       int NewState;
       int NewScope;  
  public:
       thread_object(void);
       ~thread_object(void);
       void setPriority(int Priority);
       void setSchedPolicy(int Policy);
       void setContentionScope(int Scope);
       void setDetached(void);
       void setJoinable(void);
	
       void name(string X);
       void run(void);
       void join(void);
       friend void *thread(void *X);
  };
	
	
  class filter_thread : public thread_object{
  protected:
       void do_something(void);
  public:
       filter_thread(void);
       ~filter_thread(void); 
  };
	
  #endif
	
