// Soln 9_01.cpp

/*
  CBadClass initializes the member p in the contructor with the address passed as the argument.
  The argument to the constructor could be a string allocated on the heap that could be 
  destroyed externally. This would leave the object with an invalid pointer.
  The constructor should copy the argument and there should be a destructor to release the memory for p.
  It is also possible the argument to the constructor could be null.
  The default constructor does not initialize the members at all.
  The class would be better defined as below.

*/
#include <cstring>

class CBadClass
{
private:
   int len;
   char* p;
public:
  CBadClass(const char* str=nullptr) : len(0)
   {
     if(str)
     {
       len = strlen(str);
       p = new char[len+1];
       strcpy_s(p, len+1, str);
     }
   }
};

