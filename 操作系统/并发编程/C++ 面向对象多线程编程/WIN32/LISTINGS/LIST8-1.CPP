// Listing 8-1
// This program demonstrates the
// use of a lockable global variable Number updated by
// two threads
#include <windows.h>
#include <stddef.h>
#include <process.h>
#include <iostream.h>
#include "mtration.h"
#include <math.h>

DWORD WINAPI threadB(void *X);
DWORD WINAPI threadA(void *X);

mt_rational *Number;

DWORD WINAPI threadA(void *X)
{
	 long int Q;
	 try{
	 for(Q =2; Q < 500;Q += 4)
	 {
		  Number->assign((Q/2),Q);
		  cout << " Thread A: " << *Number << endl;
	 }
	 return(0);
	 }
	 catch(general_exception &M)
	 {
		cout << M.message() << endl;
	 }
}

DWORD WINAPI threadB(void *X)
{
	long int Y;
	try{
		 for(Y = 5;Y < 500;Y += 5){
				Number->assign((Y/5),Y);
				cout << " Thread B " << *Number << endl;
		 }
		 return 0;
	}
	catch(general_exception &M){
	 cout << M.message() << endl;
	}
}



void main(void)
{

    HANDLE ThreadA;
	 HANDLE ThreadB;
    DWORD ThreadAId;
    DWORD ThreadBId;
	 int X = 0;
	 try{
			Number = new mt_rational(1,1);
			ThreadA = CreateThread(NULL,0,threadA,(LPVOID) &X,0,&ThreadAId);
			ThreadA = CreateThread(NULL,0,threadB,(LPVOID) &X,0,&ThreadBId);
			WaitForSingleObject(ThreadA,INFINITE);
			WaitForSingleObject(ThreadB,INFINITE);
			delete Number;
	 }
	 catch(general_exception &X)
	 {
	      cout << "From main( ) " << X.message() << endl;
	 }
}










