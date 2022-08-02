
//Listing 7-8

  using namespace std;
  #include <iostream>
  #include <pthread.h>
  #include "thread_tasks.h"
  #include <queue>
  #include <fstream>
  #include <string>
  
  


  queue<string> FilteredText;
  queue<string> SourceText;

  int main(int argc, char *argv[])
  {

     ifstream Infile;
     queue<string> QText;
     string Str;
     int Size = 0;
      
   
     pthread_t ThreadA, ThreadB;

     Infile.open("book_text.txt");
     for(int Count = 0;Count < 16;Count++)
     {
        getline(Infile,Str);
        QText.push(Str);
   
     }
      
     pthread_create(&ThreadA,NULL,task1,&QText);
     pthread_join(ThreadA,NULL);
    
     pthread_create(&ThreadB,NULL,task2,NULL);
     pthread_join(ThreadB,NULL);
   
     Size = FilteredText.size();
   
     for(int Count = 0;Count < Size ;Count++)
     {
        cout << FilteredText.front() << endl;
        FilteredText.pop();
   
     }
      
     Infile.close();

     return(0);

  }

