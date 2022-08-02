// Soln6_02.cpp
#include <iostream>
#include <cstring>

int equal(int a, int b)
{
   return (a == b) ? 1 : 0;
}

int equal(double a, double b)
{
   return (a == b) ? 1 : 0;
}

int equal(char a,char b)
{
   return (a == b) ? 1 : 0;
}

int equal(char* a, char* b)
{
   return strcmp(a,b) == 0 ? 1 : 0;
}

int main()
{
  int iA{ 3 }, iB{ 5 };
  std::cout << "Comparing iA = " << iA << " and iB = " << iB << std::endl;
   if (equal(iA, iB))
     std::cout << "iA and iB are the same" << std::endl;
   else
     std::cout << "iA and iB are different" << std::endl;

   double dA{ 3.5 }, dB{ 3.5 };
   std::cout << "Comparing dA = " << dA << " and dB = " << dB << std::endl;
   if (equal(dA, dB))
     std::cout << "dA and dB are the same" << std::endl;
   else
     std::cout << "dA and dB are different" << std::endl;

   char* pA{ "hello" };
   char* pB{ "mickey" };
   std::cout << "Comparing pA = \"" << pA << "\" and pB = \"" << pB << "\"" << std::endl;
   if (equal(pA, pB))
     std::cout << "pA and pB are the same" << std::endl;
   else
     std::cout << "pA and pB are different" << std::endl;

   char* pC{ "mickey" };
   std::cout << "Comparing pB = \"" << pB << "\" and pC = \"" << pC << "\"" << std::endl;
   if (equal(pB, pC))
     std::cout << "pB and pC are the same" << std::endl;
   else
     std::cout << "pB and pC are different" << std::endl;
}
