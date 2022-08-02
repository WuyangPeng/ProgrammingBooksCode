// Soln6_02.cpp
#include <iostream>
#include <cstring>
using std::cin;
using std::cout;
using std::endl;

int equal(int a,int b)
{
   return (a==b) ? 1 : 0;
}

int equal(double a,double b)
{
   return (a==b) ? 1 : 0;
}

int equal(char a,char b)
{
   return (a==b) ? 1 : 0;
}

int equal(char* a,char* b)
{
   return strcmp(a,b)==0 ? 1 : 0;
}

int main()
{
  int iA(3), iB(5);
   cout << "Comparing iA = " << iA << " and iB = " << iB << endl;
   if (equal(iA,iB))
      cout << "iA and iB are the same" << endl;
   else
      cout << "iA and iB are different" << endl;

   double dA(3.5), dB(3.5);
   cout << "Comparing dA = " << dA << " and dB = " << dB << endl;
   if (equal(dA,dB))
      cout << "dA and dB are the same" << endl;
   else
      cout << "dA and dB are different" << endl;

   char* pA = "hello";
   char* pB = "mickey";
   cout << "Comparing pA = \"" << pA << "\" and pB = \"" << pB << "\"" << endl;
   if (equal(pA,pB))
      cout << "pA and pB are the same" << endl;
   else
      cout << "pA and pB are different" << endl;

   char* pC = "mickey";
   cout << "Comparing pB = \"" << pB << "\" and pC = \"" << pC << "\"" << endl;
   if (equal(pB,pC))
      cout << "pB and pC are the same" << endl;
   else
      cout << "pB and pC are different" << endl;

   return 0;
}
