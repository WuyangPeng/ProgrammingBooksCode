
//Listing 7-1

  using namespace std;
  #include <iostream>
  #include <fstream>
  #include <sys/wait.h>
  #include <sys/types.h>
  #include <sys/stat.h>

  int main(int argc,char *argv[],char *envp[])
  {

     fstream Pipe;
   
     if(mkfifo("Channel-one",S_IRUSR | S_IWUSR 
                                     | S_IRGRP 
                                     | S_IWGRP) == -1){
        cerr << "could not make fifo" << endl;
     }
    
     Pipe.open("Channel-one",ios::out);
     if(Pipe.bad()){
        cerr << "could not open fifo" << endl;
     }
     else{
            Pipe << "2 3 4 5 6 7 " << endl;  
   
     }
  
     return(0);
  }

