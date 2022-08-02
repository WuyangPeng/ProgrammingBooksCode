

//Listing 5-2

  #ifndef __POSIX_PROCESS_H
  #define __POSIX_PROCESS_H
  using namespace std;

  #include <spawn.h>
  #include <errno.h>
  #include <iostream>
  #include <string>


  class posix_process{
  protected:
     pid_t  Pid;
     posix_spawnattr_t   SpawnAttr;
     posix_spawn_file_actions_t   FileActions;
     char **argv;
     char **envp;
     string ProgramPath;
  public:
     posix_process(string Path,char **av,char **env);
     posix_process(string Path,char **av,char **env, posix_spawnattr_t X,
                     posix_spawn_file_actions_t Y);
     void run(void);
     void pwait(int &X);
  };


  #endif
