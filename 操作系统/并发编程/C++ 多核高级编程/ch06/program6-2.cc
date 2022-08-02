
//Listing 6-5


  #include "thread_object.h"
  #include <unistd.h>


  int main(int argc,char *argv[])
  {
     filter_thread  MyThread[4];
    
     MyThread[0].name("Proteus");
     MyThread[0].setSchedPolicy(2);
     MyThread[0].setPriority(7);
     MyThread[0].setDetached();
      
     MyThread[1].name("Stand Alone Complex");
     MyThread[1].setContentionScope(1);
     MyThread[1].setPriority(5);
     MyThread[1].setSchedPolicy(2);
        
     MyThread[2].name("Krell Space");
     MyThread[2].setPriority(3);
        
     MyThread[3].name("Cylon Space");
     MyThread[3].setPriority(2);
     MyThread[3].setSchedPolicy(2);
     
     for(int N = 0;N < 4;N++)
     {
        MyThread[N].run();
        MyThread[N].join();
     } 
     return (0);
  }    

