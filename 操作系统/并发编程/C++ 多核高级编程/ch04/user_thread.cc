
//Listing 4-6

  #include "thread_object.h"
  #include <iostream>
  #include <fstream>

  bool Found = false;
  string MagicCode("yyzzz");

  user_thread::user_thread(void)
  {

     PosixQueue = new posix_queue("queue_name");
     PosixQueue->queueFlags(O_RDONLY);
     PosixQueue->messageSize(14);
     PosixQueue->maxMessages(4);

  }


  user_thread::~user_thread(void)
  {

     delete PosixQueue;

  }


  void user_thread::do_something(void)
  {
     ofstream Fout;
     string FileName;
     string Value;

     if(PosixQueue->open()){
        PosixQueue->receive(FileName);  
        ifstream Fin(FileName.c_str());
        string FileOut(FileName);
        FileOut.append(".out");
        Fout.open(FileOut.c_str());
    
        while(!Fin.eof() && !Fin.fail() && !Found)
        {
           getline(Fin,Value);
           if(!Fin.eof() && !Fin.fail() && !Found){    
              if(Value == MagicCode){
        
                 Found = true;

              }

           }
        }  
        Fin.close();
        Fout.close();
     }

  }

