/*********************************************************************

  Filename:  my_str.cpp
  Section:   11.7   Class Design
  Compiler:  Borland C++     Version 5.0       Summer 1996
  C++ Distilled: Descriptions, Prescriptions and Style  By Ira Pohl

*********************************************************************/

#include <string.h> //C string library
#include <iostream.h>
#include <assert.h>

class my_string {
public:
   my_string() : len(0)
      { s = new char[1];assert(s != 0); s[0] = 0; }
   explicit my_string(const int n);
   my_string(const my_string& str);  //copy constructor
   my_string(const char* p);         //conversion constructor
   ~my_string() { delete []s; }
   my_string& operator=(const my_string& str);
   my_string operator+(const my_string& str);
   friend ostream& operator<<(ostream& out, const my_string& str);
   void concat(const my_string& a, const my_string& b);
private:
   char* s;
   int   len;
};


//construct from char* type
my_string::my_string(const char* p)
{
   len = strlen(p);
   s = new char[len + 1];
   assert (s != 0);
   strcpy(s, p);
}

my_string::my_string(const int n)
{
   s = new char[n + 1];
   assert (s != 0);
   s[0] = 0;
   len = n;
}


//construct from an existing my_string
my_string::my_string(const my_string& str)
{
   len = str.len;
   s = new char[len + 1];
   assert (s != 0);
   strcpy(s, str.s);
}

//overloaded assignment
my_string& my_string::operator=(const my_string& str)
{
   if (this != &str) {    //check for assign to self
      delete []s;     //retrieve old string
      len = str.len;
      s = new char[len + 1];
      assert (s != 0);
      strcpy(s, str.s);
   }
   return (*this);
}

//string output always followed by newline
ostream& operator<<(ostream& out, const my_string& str)
{
   return (out << str.s << endl);
}

//concatenation is another way of doing addition
void my_string::concat(const my_string& a,
                       const my_string& b)
{
   len = a.len + b.len;
   delete s;
   s = new char[len + 1];
   assert (s != 0);
   strcpy(s, a.s);
   strcat(s, b.s);
}

//binary operator plus returns a temp string
my_string my_string::operator+(const my_string& str)
{
   int lens = len + str.len;  //length of new my_string
   my_string temp(lens);

   strcpy (temp.s, s);
   strcat (temp.s, str.s);
   return temp;
}

int main()
{
   char*  str = "The wheel that squeaks the loudest\n";
   my_string  a(str), b, author("Josh Billings\n");
   my_string  both, quote;

   b = "Is the one that gets the grease\n";
   both.concat(a, b);
   quote = both + author;
   cout << quote;
}

