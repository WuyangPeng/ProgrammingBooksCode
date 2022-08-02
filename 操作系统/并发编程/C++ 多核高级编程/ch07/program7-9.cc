//Listing 7-9

  using namespace std;
  #include <semaphore.h>
  #include <iostream>
  #include <fstream>


  int main(int argc, char *argv[])
  {

     int Loop, PN;
     sem_t *Sem;
     const char *Name;
     ofstream Outfile("out_text.txt",ios::app);

     PN = atoi(argv[1]);
     Loop = atoi(argv[2]);
     Name = argv[3];

     Sem = sem_open(Name,O_CREAT,O_RDWR,1); 
     sem_unlink(Name);


     for (int Count = 1; Count < Loop; ++Count) {
        sem_wait(Sem);
        Outfile << "Process:" << PN << " counting " << Count << endl; 
        sem_post(Sem);
        
     }
     Outfile.close();

     exit(0);



  }

