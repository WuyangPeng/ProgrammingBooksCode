// Soln 9_01.cpp

/*
Member initializations in the initialization list for a constructor are executed in the
sequence in which the members appear in the class definition, not the sequence in the initialization list.
As written the initializtion of len will fail because it is initialized before p.
If the class member sequence was reversed initializing len would then work.

CBadClass initializes the member p in the contructor with the address passed as the argument.
The argument to the constructor could be a string allocated on the heap that could be
destroyed externally. This would leave the object with an invalid pointer.
The constructor should copy the argument and there should be a destructor to release the memory for p.

It is also possible the argument to the constructor could be nullptr.

The default constructor does not initialize the members at all.

The class allocates memory on the heap so it shuold implement a destructor, a copy constructor and an assignment operator.
It is also desirable that the class implementa a move constructor and a move assignment operator.
The class would be better defined as below.

*/
#include <cstring>

class CBadClass
{
private:
  char* p{};
  int len{};
public:
  CBadClass(const char* str = nullptr)
  {
    if (str)
    {
      len = strlen(str) + 1;
      p = new char[len];
      strcpy_s(p, len, str);
    }
  }

  // Copy constructor
  CBadClass(const CBadClass& obj)
  {
    if (obj.p)
    {
      len = strlen(obj.p) + 1;
      p = new char[len];
      strcpy_s(p, len, obj.p);
    }
  }

  // Move copy constructor
  CBadClass(CBadClass&& obj)
  {
    len = obj.len;
    p = obj.p;
    obj.p = nullptr;
  }

  // Destructor
  ~CBadClass()
  {
    delete[] p;
  }

  // Assignment operator
  CBadClass& operator=(const CBadClass& obj)
  {
    if (this != &obj)
    {
      delete[] p;
      p = nullptr;
      len = 0;
      if (obj.p)
      {
        len = obj.len + 1;
        p = new char[len];
        strcpy_s(p, len, obj.p);
      }
    }
    return *this;
  }

  // Move assignment operator
  CBadClass& operator=(CBadClass&& obj)
  {
    delete[] p;
    len = obj.len;
    p = obj.p;
    obj.p = nullptr;
    return *this;
  }
};

// This is here so you can compile the class
int main()
{
  CBadClass obj{ "Test it!" };
}
