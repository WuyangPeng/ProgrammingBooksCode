

//Listing 6-4


    #include "thread_object.h"

 
    filter_thread::filter_thread(void)
    {
       pthread_attr_init(&SchedAttr);
    
 
    }


  filter_thread::~filter_thread(void)
  {
      
  }   

  void filter_thread::do_something(void)
  {
     struct sched_param Param;
     int Policy;
     pthread_t thread_id = pthread_self();
     string Schedule;
     string State;
     string Scope;
   
     pthread_getschedparam(thread_id,&Policy,&Param);   
     if(NewPolicy == SCHED_RR){Schedule.assign("RR");}
     if(NewPolicy == SCHED_FIFO){Schedule.assign("FIFO");}
     if(NewPolicy == SCHED_OTHER){Schedule.assign("OTHER");}
     if(NewState == PTHREAD_CREATE_DETACHED){State.assign("DETACHED");}
     if(NewState == PTHREAD_CREATE_JOINABLE){State.assign("JOINABLE");}
     if(NewScope == PTHREAD_SCOPE_PROCESS){Scope.assign("PROCESS");}
     if(NewScope == PTHREAD_SCOPE_SYSTEM){Scope.assign("SYSTEM");}
     cout << Name << ":" << thread_id << endl
          << "----------------------" << endl
          << " priority:  "<< Param.sched_priority   << endl 
          << " policy:    "<< Schedule               << endl
          << " state:     "<< State                  << endl
          << " scope:     "<< Scope                  << endl << endl;

  }
