
//Listing 10-1

  #include "posix_process.h"
  #include "posix_queue.h"
  #include "valid_code.h"


  char **av;
  char **env;


  int main(int argc,char *argv[],char *envp[])
  {
 
     valid_code  ValidCode;
     ValidCode.determination("ofind_code");   
     cout <<  (ValidCode() ? "you win" : "you lose");
     return(0);
  }
