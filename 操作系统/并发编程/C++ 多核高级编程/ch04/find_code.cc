
//Listing 4-2

  #include <pthread.h>
  using namespace std;
  #include <iostream>
  #include <fstream>
  #include "posix_queue.h"
  string MagicCode("yyzzz");
  ofstream Fout1;
  ofstream Fout2;
  bool Found = false;
  bool magicCode(string X)
  {
      //...
    
     return(X == MagicCode);
  }



  void *task1(void *X)
  {
     posix_queue PosixQueue;
     string FileName;
     string Value;
     if(PosixQueue.open()){
        PosixQueue.receive(FileName);
        ifstream Fin(FileName.c_str());
        string FileOut(FileName);
        FileOut.append(".out");
        Fout1.open(FileOut.c_str());
        while(!Fin.eof() && !Fin.fail() && !Found)
        {
           getline(Fin,Value);
           if(!Fin.eof() && !Fin.fail() && !Found){    
              if(magicCode(Value)){
                 Found = true;
              }
           }
        }
        Fin.close();
        Fout1.close();
     }
     return(NULL);
  }



  void *task2(void *X)
  {

     posix_queue PosixQueue;
     string FileName;
     string Value;
     if(PosixQueue.open()){
        PosixQueue.receive(FileName);
        ifstream Fin(FileName.c_str());
        string FileOut(FileName);
        FileOut.append(".out");
        Fout2.open(FileOut.c_str());
        while(!Fin.eof() && !Fin.fail()  && !Found)
        {
           getline(Fin,Value);
           if(!Fin.eof() && !Fin.fail()  && !Found){
              if(magicCode(Value)){
                 Found = true;
              }
           }
        }
        Fin.close();
        Fout2.close();
     }
     return(NULL);
  }





  int main(int argc, char *argv[])
  {

     pthread_t ThreadA, ThreadB;
     pthread_create(&ThreadA,NULL,task1,NULL);
     pthread_create(&ThreadB,NULL,task2,NULL);
     pthread_join(ThreadA,NULL);
     pthread_join(ThreadB,NULL);
     return(0);

  } 
