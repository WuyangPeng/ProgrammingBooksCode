
#include <windows.h>
#include <process.h>
#include "ctthread.h"
#include <stddef.h>



ct_thread::ct_thread(DWORD SSize)
{
	StackSize = SSize;
	ThreadId = 0;
}

ct_thread::~ct_thread(void)
{
	 TerminateThread(ThreadHandle, ExitCode);
}


void ct_thread::begin(FunctionPtr PFN, void *X)
{
	ThreadHandle =  CreateThread(NULL, StackSize,(LPTHREAD_START_ROUTINE)PFN,X,0,&ThreadId);
}

void ct_thread::wait(void)
{
	  WaitForSingleObject(ThreadHandle,INFINITE);
}


unsigned long ct_thread::threadId(void)
{

	  return(ThreadId);

}

