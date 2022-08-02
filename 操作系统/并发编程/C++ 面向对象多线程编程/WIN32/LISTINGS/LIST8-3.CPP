
// Listing 8-3

#include <cstring.h>
#include <windows.h>
#include <dirent.h>
#include <set.h>
#include <fstream.h>
#include <algo.h>
#include <string.h>
#include <stddef.h>
#include <process.h>
#include "ctqueue.cpp"

lqueue<string> *TextFiles;
set<string,less<string> > KeyWords;
set<string,less<string> > SearchWords;
void threadA(void *X);
string InFile;
string OutFile;


void threadA(void *X)
{
	string Temp;
	string FileName;
	less<string> Comp;
	ifstream In;
	ofstream Out;
	In.open(InFile.c_str());
	Out.open(OutFile.c_str());
	while(!In.eof())
	{
		In >> Temp;
		if(!In.eof()){
			 KeyWords.insert(Temp);
		}
	}
	In.close();
	TextFiles->wait();
	while(!TextFiles->empty())
	{
		 FileName = TextFiles->remove();
		 In.open(FileName.c_str());
		 SearchWords.erase(SearchWords.begin(),SearchWords.end());
		 while(!In.eof() && In.good())
		 {
			In >> Temp;
			SearchWords.insert(Temp);
		 }
		 In.close();
		 if(includes(SearchWords.begin(),SearchWords.end(),
			 KeyWords.begin(),KeyWords.end(),Comp)){
			 cout << "Thread A match found in " << FileName << endl;
			 Out << FileName << endl;
		 }
	}

	Out.close();
}


void main(int argc, char *argv[])
{

  DIR *DirP;
  HANDLE Result;
  DWORD ThreadAId;
  struct dirent *EntryP;
  DirP = opendir(argv[1]);
  InFile = argv[2];
  OutFile = argv[3];
  try{
	TextFiles =  new lqueue<string>("",0,"",0,INFINITE);
	if(argc == 4){
		string Temp;
		Result = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)threadA,NULL,0,&ThreadAId);
		if(DirP == NULL){
			cerr << " Could Not Open " << argv[1] << endl;
			exit(1);
		}
		do{
		EntryP = readdir(DirP);
		if(EntryP){
			Temp = EntryP->d_name;
			if(Temp.contains(".TXT")){
				cout << "Found " << EntryP->d_name << " in Main Thread " << endl;
				TextFiles->insert(EntryP->d_name);
				TextFiles->broadCast();
			}
		}
	  }while(EntryP);
	  closedir(DirP);
	  WaitForSingleObject(Result, INFINITE);
	  delete TextFiles;
	  }
  }
  catch(general_exception &X)
  {
		cout << X.message() << endl;
  }

}



