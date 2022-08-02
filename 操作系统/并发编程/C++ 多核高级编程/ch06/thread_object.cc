

//Listing 6-3

    #include "thread_object.h"
 	
    thread_object::thread_object(void)
    {
       pthread_attr_init(&SchedAttr);
       pthread_attr_setinheritsched(&SchedAttr,PTHREAD_EXPLICIT_SCHED);
       NewState = PTHREAD_CREATE_JOINABLE;
       NewScope = PTHREAD_SCOPE_PROCESS;
       NewPolicy = SCHED_OTHER;
  }
	
  thread_object::~thread_object(void)
  {
	  
  }   
	
  void thread_object::join(void)
  {
     if(NewState == PTHREAD_CREATE_JOINABLE){
        pthread_join(Tid,NULL);
     }
  }
	
  void thread_object::setPriority(int Priority)
  {
     int Policy;
     struct sched_param Param;
	      
     Param.sched_priority = Priority;
     pthread_attr_setschedparam(&SchedAttr,&Param);   
  }  
	
	
  void thread_object::setSchedPolicy(int Policy)
  {
     if(Policy == 1){
        pthread_attr_setschedpolicy(&SchedAttr,SCHED_RR);
        pthread_attr_getschedpolicy(&SchedAttr,&NewPolicy);
     }
	   
     if(Policy == 2){
        pthread_attr_setschedpolicy(&SchedAttr,SCHED_FIFO);
        pthread_attr_getschedpolicy(&SchedAttr,&NewPolicy);
     }
  } 
	
	
  void thread_object::setContentionScope(int Scope)
  {   
     if(Scope == 1){
        pthread_attr_setscope(&SchedAttr,PTHREAD_SCOPE_SYSTEM);
        pthread_attr_getscope(&SchedAttr,&NewScope);
     }
	   
     if(Scope == 2){     
        pthread_attr_setscope(&SchedAttr,PTHREAD_SCOPE_PROCESS);
        pthread_attr_getscope(&SchedAttr,&NewScope);
     }
  } 
	
	
  void thread_object::setDetached(void)
  {
     pthread_attr_setdetachstate(&SchedAttr,PTHREAD_CREATE_DETACHED);   
     pthread_attr_getdetachstate(&SchedAttr,&NewState);
	  
  } 
	
  void thread_object::setJoinable(void)
  {
     pthread_attr_setdetachstate(&SchedAttr,PTHREAD_CREATE_JOINABLE);
     pthread_attr_getdetachstate(&SchedAttr,&NewState);  
  }  
	
	
  void thread_object::run(void)
  {
     pthread_create(&Tid,&SchedAttr,thread,this); 
  }
	
	
  void thread_object::name(string X)
  {
     Name = X;
  }    
	
	
  void *  thread (void * X)
  {
     thread_object *Thread;
     Thread = static_cast<thread_object *>(X);
     Thread->do_something();  
     return(NULL);
  }


