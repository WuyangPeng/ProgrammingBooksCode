/*********************************************************************

  Filename:  vect_ex.cpp
  Section:   14     Exceptions
  Compiler:  Borland C++     Version 5.0       Summer 1996
  C++ Distilled: Descriptions, Prescriptions and Style  By Ira Pohl

*********************************************************************/

//Safe array type vect with exceptions
#include  <iostream.h>
#include  <stdlib.h>       //for abort
#include  <new.h>          //for set_new_handler
#include  <strstrea.h>    //build string for messages

class vect {
public:
   //constructors and destructor
   explicit vect(int n = 10);       //default constructor
   vect(const vect& v);    //copy constructor
   vect(const int a[], int n);  //init by array
   ~vect() { delete [] p; }
   int   ub() const { return (size - 1); }
   int&  operator[](int i) const;      //range checked
   vect& operator=(const vect& v);
   friend vect  operator+(const vect&, const vect&);
   friend ostream& operator <<(ostream& out,
                              const vect& v);
private:
   int*  p;                //base pointer
   int   size;             //number of elements
};

//default constructor
vect::vect(int n) : size(n)
{  if (n < 1) {
      strstream s;
      s << "Default constructor parameter is bad: "
        << n << ends;
      throw (s.str());
   }
   p = new int[n];         //set new handler for error
}

//copy constructor
vect::vect(const vect& v) : size(v.size)
{
   p = new int[size];
   for (int i = 0; i < size; ++i)
      p[i] = v.p[i];
}

//constructor for initializing vect from an array
vect::vect(const int a[], int n) : size(n)
{
   if (n <= 0) {
      strstream s;
      s << "\nArray init parameter is bad: "
        << n << ends;
      throw (s.str());      //give size error
   }
   p = new int[size];
   for (int i = 0; i < size; ++i)
      p[i] = a[i];
}

//overloaded subscript operator
int& vect::operator[](int i) const
{
     if (i < 0 || i > (size - 1) ) {
      strstream s;
      s << "\nBad index: vect[" <<  i << "]" << ends;
      throw (s.str());      //throw index error
   }
   return (p[i]);
}

//overloaded output operator
ostream& operator<<(ostream& out, const vect& v)
{
   for (int i = 0; i <= (v.size-1); ++i)
      out << v.p[i] << '\t';
   return (out << endl);
}

//overloaded assignment operator
vect& vect::operator=(const vect& v)
{
   if (this != &v) {        //check for assign to self
      int  s = (size < v.size) ? size : v.size;
      if (v.size != size)
         cerr << "copying different size arrays "
              << size << " and " << v.size << endl;
      for (int i = 0; i < s; ++i)
          p[i] = v.p[i];
   }
   return (*this);
}

vect operator+(const vect& v1, const vect& v2)
{
   int   s = (v1.size < v2.size) ? v1.size : v2.size;
   vect  sum(s);
   if (v1.size != v2.size)
      cerr << "adding different size arrays "
           << v1.size << " and " << v2.size << endl;
   for (int i = 0; i < s; ++i)
      sum.p[i] = v1.p[i] + v2.p[i];
   return sum;
}

void init_vect(vect& v, int start, int incr)
{
   for (int i = 0; i <= v.ub(); ++i) {
      v[i] = start;
      start += incr;
   }
}

//simple memory error routine which aborts
void Out_Of_Memory()
{
   cerr << "\nFREE STORE EXHAUSTED\n";
   abort();
}

int main()
{
   try {
   int    array[6] = { 5, 10, 15, 20, 25, 30 };
   vect   v1, v2(5);       //use default constructor
   vect   v3 (array, 5);   //init from 1st 5 elements
   vect   v4 (v3);         //use copy constructor
   set_new_handler(Out_Of_Memory);

   //  cout << v3[20];         //force index error
   //  vect   v5(-5);          //force size error
   //  vect   v6(array, -3)    //force array error

   init_vect(v1, 1, 1);
   cout << "\nvector v1 is " << v1;
   init_vect(v2, 0, 2);
   cout << "\nvector v2 is " << v2;
   cout << "\nvector v3 is " << v3;
   v4 = v1 + v3;    //force add differenct size arrays
     cout << "\nvector v4 is " << v4;
   }
    //catch any errors thrown with msg
   catch (const char* msg)
   {
      cerr << endl << msg << endl;
      abort();
   }
}

