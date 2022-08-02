#include <cstring.h>
#include <windows.h>
#include <process.h>
#include <string.h>
#include "ctmutex.h"
#include <iostream.h>


mutex::mutex(void)
{
	 Mutex = CreateMutex(NULL,0,NULL);
	 if(!Mutex){
		 SemException.message("Could Not Create Mutex");
		 throw SemException;
	 }
	  Duration = INFINITE;
}


mutex::~mutex(void)
{
	 if(!CloseHandle(Mutex)){
		 SemException.message("Could Not Destroy Mutex");
		 throw SemException;
	 }
}



void mutex::lock(void)
{
		WaitForSingleObject(Mutex,Duration);
}


void mutex::unlock(void)
{
	 ReleaseMutex(Mutex);
}


named_mutex::named_mutex(void)
{
	Mutex = CreateMutex(NULL,0,NULL);
	if(!Mutex){
		 SemException.message("Could Not Create Mutex");
		 throw SemException;
	 }
	 Duration = INFINITE;
}

named_mutex::named_mutex(char *MName,BOOL Owned)
{

	 strcpy(MutexName,MName);
	 InitiallyOwned = Owned;
	 Mutex = CreateMutex(NULL,InitiallyOwned, MutexName);
	 if(!Mutex){
		 SemException.message("Could Not Create Mutex");
		 throw SemException;
	 }
	 Duration = INFINITE;
}


named_mutex::named_mutex(string MName)
{


	 strcpy(MutexName,MName.c_str());
	 InitiallyOwned = 0;
	 Mutex = OpenMutex(SYNCHRONIZE,TRUE,MutexName);
	 if(!Mutex){
		 SemException.message("Could Not open Mutex");
		 throw SemException;
	 }
	 Duration = INFINITE;
}
DWORD named_mutex::lockDuration(void)
{
	 return(Duration);
}

void named_mutex::lockDuration(DWORD Dur)
{
	 Duration = Dur;
}




