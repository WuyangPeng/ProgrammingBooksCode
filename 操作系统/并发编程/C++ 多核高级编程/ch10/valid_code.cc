
//Listing 10-3

  #include "valid_code.h"
  #include "posix_process.h"
  #include "posix_queue.h"

  extern char **av;
  extern char **env;


  bool valid_code::operator()(void)
  {
     int Status;    
     int N;
     string Result;
     posix_process Child[4];
     for(N = 0; N < 2; N++)
     {      
        Child[N].binary(Determination);
        Child[N].arguments(av);
        Child[N].environment(env);
        Child[N].run();
        Child[N].pwait(Status);
     }  
     posix_queue PosixQueue("queue_name");
     PosixQueue.receive(Result);
     if((Result == Code) && InTime){     
        return(true);
     } 
     return(false);
  }    

      
  void valid_code::determination(string X)
  {
     Determination = X;
  }

