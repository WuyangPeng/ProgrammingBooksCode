
// Listing 6-2
// Multithreaded search example
// This program expects two text files
// as arguments.  The first text file
// contains the list of words to find
// The second text file will be used to save
// the file names that contain the keywords


#include <dirent.h>
#include <set.h>
#include <cstring.h>
#include <windows.h>
#include <fstream.h>
#include <algo.h>
#include <string.h>
#include <list.h>
#include <stack.h>
#include <stddef.h>
#include <process.h>




queue< list<string> > TextFiles;
set<string,less<string> > KeyWords;
set<string,less<string> > SearchWords;
void threadA(void *X);
HANDLE SemHandle;
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
	while(TextFiles.empty())
	{

	}
	while(!TextFiles.empty())
	{
		 WaitForSingleObject(SemHandle,5000);
		 FileName = TextFiles.front();
		 TextFiles.pop();
		 ReleaseMutex(SemHandle);
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
			 WaitForSingleObject(SemHandle,5000);
			 cout << "Thread A match found in " << FileName << endl;
			 Out << FileName << endl;
			  ReleaseMutex(SemHandle);
		 }
	}

	Out.close();
}


void main(int argc, char *argv[])
{

  DIR *DirP;
  DWORD ThreadId = 0;
  struct dirent *EntryP;
  DirP = opendir(argv[1]);
  InFile = argv[2];
  OutFile = argv[3];
  HANDLE ThreadHandle;
  if(argc == 4){
	  string Temp;
	  SemHandle = CreateMutex(NULL,TRUE,NULL);
	  ThreadHandle = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)threadA,NULL,0,&ThreadId);
	  if(DirP == NULL){
	cerr << " Could Not Open " << argv[1] << endl;
	exit(1);
	  }
	  do{
	  EntryP = readdir(DirP);
	  if(EntryP){
		  Temp = EntryP->d_name;
		  if(Temp.contains(".TXT")){
		WaitForSingleObject(SemHandle,5000);
		cout << "Found " << EntryP->d_name << " in Main Thread " << endl;
		TextFiles.push(EntryP->d_name);
		ReleaseMutex(SemHandle);
		  }
	  }
	  }while(EntryP);
	  closedir(DirP);
	  WaitForSingleObject(ThreadHandle,INFINITE);
	  CloseHandle(SemHandle);
  }

}



