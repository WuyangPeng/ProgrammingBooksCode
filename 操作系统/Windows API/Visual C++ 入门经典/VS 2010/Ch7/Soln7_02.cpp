// Soln7_02.cpp

#include <iostream>                   // For stream input/output

using std::cout;
using std::endl;

struct Sample
{
   int one;
   int two;
   char* sptr;
};

int main()
{
   Sample a;
   Sample b;
   char* s = "hello World!";
   a.one = 1;
   a.two = 2;
   a.sptr = new char[strlen(s)+1];
   strcpy_s(a.sptr, strlen(s)+1, s);

   b.one = b.two = 9999;
   b.sptr = "rubbish";

   cout << "a=(" << a.one << "," << a.two << "," << a.sptr << ")" << endl;

   // b contains values 9999 and a pointer to "rubbish"
   cout << "b=(" << b.one << "," << b.two << "," << b.sptr << ")" << endl;

   b = a;
   cout << "\nAfter copying a to b:" << endl;
   cout << "b=(" << b.one << "," << b.two <<"," << b.sptr << ")" << endl;

   a.sptr[0] = 'H';                           // Change string in a
   cout << "\nAfter modifying the string in a to start with 'H', b has also changed:" << endl;
   cout << "a=(" << a.one << "," << a.two << "," << a.sptr << ")" << endl;
   cout << "b=(" << b.one << "," << b.two << "," << b.sptr << ")" << endl;


   // To avoid the two structs pointing to the same string you
   // must create a copy of the string from a, and store its address in b.sptr
   b.one = a.one;
   b.two = a.two;
   b.sptr = new char[strlen(a.sptr)+1];
   strcpy_s(b.sptr, strlen(a.sptr)+1, a.sptr);

   cout << "\nAfter copying members of a to b, replicating the string:" << endl;
   cout << "a=(" << a.one << "," << a.two << "," << a.sptr << ")" << endl;
   cout << "b=(" << b.one << "," << b.two <<"," << b.sptr << ")" << endl;

   a.sptr[0] = 'h';
   cout << "\nAfter modifying the string in a once more to start with 'h', b has not changed:" << endl;
   cout << "a=(" << a.one << "," << a.two << "," << a.sptr << ")" << endl;
   cout << "b=(" << b.one << "," << b.two << "," << b.sptr << ")" << endl;
   
   return 0;
}
