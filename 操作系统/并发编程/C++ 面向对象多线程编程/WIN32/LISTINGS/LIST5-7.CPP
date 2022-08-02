// Listing 5-7
// This program demonstrates the
// use of a global variable Count updated by
// two threads

#include <windows.h>
#include <iostream.h>
#include <process.h>

int Count = 0;

void threadA(void *X)
{

	 Count += 2;
	 cout << Count << endl;
}

void threadB(void *X)
{
	Count += 4;
	cout << Count << endl;
}


void main(void)
{
	 DWORD ThreadAId;
	 DWORD ThreadBId;
	 HANDLE ThreadA;
	 HANDLE ThreadB;
	 ThreadA = CreateThread(NULL,0, (LPTHREAD_START_ROUTINE)threadA, NULL,0,&ThreadAId);
	 ThreadB = CreateThread(NULL,0, (LPTHREAD_START_ROUTINE)threadB, NULL,0,&ThreadBId);
	 WaitForSingleObject(ThreadA,INFINITE);
	 WaitForSingleObject(ThreadB,INFINITE);
    
}

