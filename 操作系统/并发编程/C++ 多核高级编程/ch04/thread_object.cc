
//Listing 4-5

  #include "thread_object.h"


  thread_object::thread_object(void)
  {



  }
  thread_object::~thread_object(void)
  {
     pthread_join(Tid,NULL);
  }


  void thread_object::run(void)
  {
     pthread_create(&Tid,NULL,thread,this);
  }

  void thread_object::join(void)
  {
     pthread_join(Tid,NULL);
  }


  void thread_object::name(string X)
  {
     Name = X;
  }

  string thread_object::name(void)
  {
     return(Name);
  }


  void *  thread (void * X)
  {

     thread_object *Thread;
     Thread = static_cast<thread_object *>(X);
     Thread->do_something();
     return(NULL);


  }

