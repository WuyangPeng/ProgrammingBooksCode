// Listing 5-8
// This program uses global STL containers
// as interthread communication mechanisms

#include <iostream.h>
#include <windows.h>
#include <process.h>
#include "rational.h"
#include <set.h>
#include <algo.h>

rational M(3,4);
typedef set<rational,rational> rational_set;
typedef set<rational,rational>::iterator rational_iterator;
rational_set SetA,SetB,SetC;
rational_iterator A,B,C;

void threadA(void *X)
{
	 rational Z(5,4);
	 rational W(1,8);
	 SetA.insert(W);
	 SetA.insert(Z);
	 set_intersection(SetA.begin(),SetA.end(),SetB.begin(),SetB.end(),
							inserter(SetC,SetC.begin()),Z);
	 SetB.insert(W);
	 SetA.erase(SetA.begin(),SetA.end());
}

void threadB(void *X)
{

	rational Q(2,3);
	rational R(5,5);
	SetB.insert(Q);
	SetB.insert(R);
	SetA.insert(Q);
	SetA.insert(M);
	set_union(SetC.begin(),SetC.end(),SetB.begin(),SetB.end(),
				 inserter(SetA,SetA.begin()),Q);
}


void main(void)
{
	 HANDLE ThreadA,ThreadB;
	 DWORD ThreadAId, ThreadBId;
	 ThreadA = CreateThread(NULL,0, (LPTHREAD_START_ROUTINE)threadA,NULL,0,&ThreadAId);
	 ThreadB = CreateThread(NULL,0, (LPTHREAD_START_ROUTINE)threadB,NULL,0,&ThreadBId);
	 WaitForSingleObject(ThreadA,INFINITE);
	 WaitForSingleObject(ThreadB,INFINITE);
	 A = SetA.begin();
	 B = SetB.begin();
	 C = SetC.begin();
	 cout << "Set A contains ";
	 while(A != SetA.end())
	 {
		cout << *A << " ";
		A++;
	 }
	 cout << endl << "Set B contains ";
	 while(B != SetB.end())
	 {
		cout << *B << " ";
		B++;
	 }
	 cout << endl << "Set C contains ";
	 while(C != SetC.end())
	 {
		cout << *C << " ";
		C++;
	 }
	 cout << endl;
}











