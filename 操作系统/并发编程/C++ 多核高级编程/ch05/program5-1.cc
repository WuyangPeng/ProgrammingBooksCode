
//Listing 5-1


  using namespace std;
  #include <iostream>
  #include <string>
  #include <spawn.h>
  #include <sys/wait.h>

  int main(int argc,char *argv[],char *envp[])
  {

     pid_t ChildProcess;
     pid_t ChildProcess2;
     int RetCode1;
     int RetCode2;
     int Value;
     RetCode1 = posix_spawn(&ChildProcess,"find_code",NULL,
                              NULL,argv,envp);
     RetCode2 = posix_spawn(&ChildProcess2,"find_code",NULL,
                              NULL,argv,envp);
     wait(&Value);
     wait(&Value);
     return(0);
  }
