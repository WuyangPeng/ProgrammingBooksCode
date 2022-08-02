

//Listing 10-4

  #include "posix_process.h"
  #include <sys/wait.h>


  posix_process::posix_process(string Path,char **av,char **env)
  {

     argv = av;
     envp = env;
     ProgramPath = Path;
     posix_spawnattr_init(&SpawnAttr);
     posix_spawn_file_actions_init(&FileActions);


  }

  posix_process::posix_process(string Path,char **av,char **env, 
                                 posix_spawnattr_t  X, 
				   posix_spawn_file_actions_t Y)
  {
     argv = av;
     envp = env;
     ProgramPath = Path;
     SpawnAttr = X;
     FileActions = Y;
     posix_spawnattr_init(&SpawnAttr);
     posix_spawn_file_actions_init(&FileActions);



  }

  void posix_process::run(void)
  {

     posix_spawn(&Pid,ProgramPath.c_str(),&FileActions,
                   &SpawnAttr,argv,envp);


  }

  void posix_process::pwait(int &X)
  {

     wait(&X);
  }







