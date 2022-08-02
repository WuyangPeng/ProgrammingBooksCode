// Listing 5-9
// This program demonstrates the use of
// parameter passing during the process
// of thread creation

#include <windows.h>
#include <iostream.h>
#include <process.h>
#include "rational.h"


rational M(1,2);

void threadA(void *X)
{
	 rational *Q;
	 Q = (rational *) X;
	 rational Z(3,4);
	 M = *Q + Z;
	 cout << "thread A"  << endl;
	 cout << *Q << " + " << Z <<  " = " << M << endl << endl;
}

void threadB(void *X)
{
	rational *N;
	rational Q(1,1);
	N = (rational *) X;
	Q = M + *N;
	cout << "thread B" << endl;
	cout << M << " + " << *N << " = " << Q << endl << endl;
}



void main(void)
{
	 HANDLE ThreadA;
	 HANDLE ThreadB;
	 DWORD ThreadAId, ThreadBId;
	 rational *N;
	 N = new rational(5,3);
	 ThreadA = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)threadA, (LPVOID)N, 0, &ThreadAId);
	 ThreadB = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)threadB, (LPVOID)N, 0, &ThreadBId);
	 WaitForSingleObject(ThreadA, INFINITE);
	 WaitForSingleObject(ThreadB, INFINITE);
	 delete N;
}











