
//Listing 4-3


  #include "thread_object.h"


  int main(int argc, char *argv[])
  {



     user_thread Thread[2];
     Thread[0].name("ThreadA");
     Thread[1].name("ThreadB");
     for(int N = 0; N < 2;N++)
     {
        Thread[N].run();
        Thread[N].join();
     }         
     return(0);

  } 
