
//Listing 7-2

  using namespace std;
  #include <iostream>
  #include <fstream>
  #include <string>
  #include <sys/wait.h>
  #include <sys/types.h>
  #include <sys/stat.h>


  int main(int argc, char *argv[])
  {
     int type;
     fstream NamedPipe;
     string Input;
   
     NamedPipe.open("Channel-one",ios::in | ios::out);
   
     if(NamedPipe.bad()){
        cerr << "could not open Channel-one" << endl;
     }
   
     while(!NamedPipe.eof() && NamedPipe.good()){
  
        getline(NamedPipe,Input);
        cout << Input << endl;
     }
     NamedPipe.close();
     unlink("Channel-one");   
     return(0);

  }
