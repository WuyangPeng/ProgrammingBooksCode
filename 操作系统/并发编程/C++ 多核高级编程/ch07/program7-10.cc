
//Listing 7-10

  using namespace std;
  #include <semaphore.h>
  #include <iostream>
  #include <fstream>
  #include <string>


  int main(int argc, char *argv[])
  {

     string Str;
     const char *Name;
     sem_t *Sem;
     ifstream Infile("out_text.txt");

     if(Infile.is_open()){
        Name = argv[1];
        Sem = sem_open(Name,O_CREAT,O_RDWR,1); 
        sem_unlink(Name);

        while(!Infile.eof() && Infile.good()){
           sem_wait(Sem);
           getline(Infile,Str);
           cout << Str << endl;
           sem_post(Sem);
        
        }
        cout << "--------------------------------" << endl;

        Infile.close();

     }

     exit(0);



  }

