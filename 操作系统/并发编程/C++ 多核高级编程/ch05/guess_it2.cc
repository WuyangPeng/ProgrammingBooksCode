
//Listing 5-3

  #include "posix_process.h"

  int main(int argc,char *argv[],char *envp[])
  {
     int Value;
     posix_process  Child1("ofind_code",argv,envp);
     posix_process  Child2("ofind_code",argv,envp);
     Child1.run();
     Child2.run();
     Child1.pwait(&Value);
     Child2.pwait(&Value);
     return(0);
  }

