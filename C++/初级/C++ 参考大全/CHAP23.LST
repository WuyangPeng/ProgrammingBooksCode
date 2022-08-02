listing 1
namespace CounterNameSpace {
  int upperbound;
  int lowerbound;

  class counter {
     int count;
   public:
     counter(int n) { 
       if(n <= upperbound) count = n;
       else count = upperbound;
     }

     void reset(int n) {
       if(n <= upperbound) count = n;
     }

     int run() {
       if(count > lowerbound) return count--;
       else return lowerbound;
     }
  };
}

listing 2
if(count > lowerbound) return count--;

listing 3
CounterNameSpace::upperbound = 10;

listing 4
CounterNameSpace::counter ob;

listing 5
// Demonstrate a namespace.
#include <iostream>
using namespace std;

namespace CounterNameSpace {
  int upperbound;
  int lowerbound;

  class counter {
     int count;
   public:
     counter(int n) { 
       if(n <= upperbound) count = n;
       else count = upperbound;
     }

     void reset(int n) {
       if(n <= upperbound) count = n;
     }

     int run() {
       if(count > lowerbound) return count--;
       else return lowerbound;
     }
  };
}

int main()
{
  CounterNameSpace::upperbound = 100;
  CounterNameSpace::lowerbound = 0;

  CounterNameSpace::counter ob1(10);
  int i;

  do {
    i = ob1.run();
    cout << i << " ";
  } while(i > CounterNameSpace::lowerbound);
  cout << endl;

  CounterNameSpace::counter ob2(20);

  do {
    i = ob2.run();
    cout << i << " ";
  } while(i > CounterNameSpace::lowerbound);
  cout << endl;

  ob2.reset(100);
  CounterNameSpace::lowerbound = 90;
  do {
    i = ob2.run();
    cout << i << " ";
  } while(i > CounterNameSpace::lowerbound);

  return 0;
}

listing 6
using CounterNameSpace::lowerbound; // only lowerbound is visible
lowerbound = 10; // OK because lowerbound is visible

using namespace CounterNameSpace; // all members are visible
upperbound = 100; // OK because all members are now visible

listing 7
// Demonstrate using.
#include <iostream>
using namespace std;

namespace CounterNameSpace {
  int upperbound;
  int lowerbound;

  class counter {
     int count;
   public:
     counter(int n) { 
       if(n <= upperbound) count = n;
       else count = upperbound;
     }

     void reset(int n) {
       if(n <= upperbound) count = n;
     }

     int run() {
       if(count > lowerbound) return count--;
       else return lowerbound;
     }
  };
}

int main()
{
  // use only upperbound from CounterNameSpace
  using CounterNameSpace::upperbound; 

  // now, no qualification needed to set upperbound 
  upperbound = 100;

  // qualification still needed for lowerbound, etc.
  CounterNameSpace::lowerbound = 0;

  CounterNameSpace::counter ob1(10);
  int i;

  do {
    i = ob1.run();
    cout << i << " ";
  } while(i > CounterNameSpace::lowerbound);
  cout << endl;

  // now, use entire CounterNameSpace
  using namespace CounterNameSpace;

  counter ob2(20);

  do {
    i = ob2.run();
    cout << i << " ";
  } while(i > lowerbound);
  cout << endl;

  ob2.reset(100);
  lowerbound = 90;
  do {
    i = ob2.run();
    cout << i << " ";
  } while(i > lowerbound);

  return 0;
}

listing 8
#include <iostream>
using namespace std;

namespace NS {
  int i;
}

// ...

namespace NS {
  int j;
}

int main()
{
  NS::i = NS::j = 10;

  // refer to NS specifically
  cout << NS::i * NS::j << "\n";

  // use NS namespace
  using namespace NS;

  cout << i * j;

  return 0;
}

listing 9
#include <iostream>
using namespace std;

namespace NS1 {
  int i;
  namespace NS2 { // a nested namespace
    int j;
  }
}

int main()
{
  NS1::i = 19;
  // NS2::j = 10; Error, NS2 is not in view
  NS1::NS2::j = 10; // this is right

  cout << NS1::i << " "<<  NS1::NS2::j << "\n";

  // use NS1
  using namespace NS1;

  /* Now that NS1 is in view, NS2 can be used to
     refer to j. */
  cout << i * NS2::j;

  return 0;
}

listing 10
using namespace NS1;

listing 11
using namespace std;

listing 12
// Use explicit std:: qualification.
#include <iostream>

int main()
{
  int val;

  std::cout << "Enter a number: ";

  std::cin >> val;

  std::cout << "This is your number: ";
  std::cout << std::hex << val;

  return 0;
}

listing 13
// Bring only a few names into the global namespace.
#include <iostream>

// gain access to cout, cin, and hex
using std::cout;
using std::cin;
using std::hex;

int main()
{
  int val;

  cout << "Enter a number: ";

  cin >> val;
  cout << "This is your number: ";
  cout << hex << val; 
  return 0;
}

listing 14
operator int() { return tos; }

listing 15
#include <iostream>
using namespace std;

const int SIZE=100;

// this creates the class stack
class stack {
  int stck[SIZE];
  int tos;
public:
  stack() { tos=0; }
  void push(int i);
  int pop(void);
  operator int() { return tos; } // conversion of stack to int
};

void stack::push(int i)
{
  if(tos==SIZE) {
    cout << "Stack is full.\n";
    return;
  }
  stck[tos] = i;
  tos++;
}

int stack::pop()
{
  if(tos==0) {
    cout << "Stack underflow.\n";
    return 0;
  }
  tos--;
  return stck[tos];
}

int main()
{
  stack stck;
  int i, j;

  for(i=0; i<20; i++)  stck.push(i);

  j = stck; // convert to integer

  cout << j << " items on stack.\n";

  cout << SIZE - stck << " spaces open.\n";
  return 0;
}

listing 16
#include <iostream>
using namespace std;

class pwr {
  double b;
  int e;
  double val;
public:
  pwr(double base, int exp);
  pwr operator+(pwr o) {
    double base;
    int exp;
    base = b + o.b;
    exp = e + o.e;

    pwr temp(base, exp);
    return temp;
  }
  operator double() { return val; } // convert to double
};

pwr::pwr(double base, int exp)
{
  b = base;
  e = exp;
  val = 1;
  if(exp==0) return;
  for( ; exp>0; exp--) val = val * b;
}

int main()
{
  pwr x(4.0, 2);
  double a;

  a = x; // convert to double
  cout << x + 100.2; // convert x to double and add 100.2
  cout << "\n";

  pwr y(3.3, 3), z(0, 0);

  z = x + y;  // no conversion
  a = z;  // convert to double
  cout << a;

  return 0;
}

listing 17
class X {
  int some_var;
public:
  int f1() const; // const member function
};

listing 18
/*
   Demonstrate const member functions.
   This program won't compile.
*/
#include <iostream>
using namespace std;

class Demo {
  int i;
public:
  int geti() const {
    return i; // ok
  }

  void seti(int x) const {
    i = x; // error!
  }
};

int main()
{
  Demo ob;

  ob.seti(1900); 
  cout << ob.geti();

  return 0;
}

listing 19
// Demonstrate mutable.
#include <iostream>
using namespace std;

class Demo {
  mutable int i;
  int j;
public:
  int geti() const {
    return i; // ok
  }

  void seti(int x) const {
    i = x; // now, OK.
  }

/* The following function won't compile.
  void setj(int x) const {
    j = x; // Still Wrong!
  }
*/
};

int main()
{
  Demo ob;

  ob.seti(1900); 
  cout << ob.geti();

  return 0;
}

listing 20
class X {
public:
  void f2(int a) volatile; // volatile member function
};

listing 21
#include <iostream>
using namespace std;

class myclass {
  int a;
public:
  myclass(int x) { a = x; } 
  int geta() { return a; }
};
 
int main()
{
  myclass ob = 4; // automatically converted into myclass(4)

  cout << ob.geta();

  return 0;
}

listing 22
myclass ob = 4; // automatically converted into myclass(4)

listing 23
myclass ob(4);

listing 24
#include <iostream>
using namespace std;

class myclass {
  int a;
public:
  explicit myclass(int x) { a = x; } 
  int geta() { return a; }
};

listing 25
myclass ob(4); 

listing 26
myclass ob = 4; // now in error

listing 27
#include <iostream>  
using namespace std;  
  
class MyClass {  
  int numA;  
  int numB;  
public:  
  /* Initialize numA and numB inside the MyClass constructor  
     using normal syntax. */  
  MyClass(int x, int y) {  
    numA = x;  
    numB = y;  
  }  
  
  int getNumA() { return numA; }  
  int getNumB() { return numB; }  
};  
  
int main()  
{  
  MyClass ob1(7, 9), ob2(5, 2);  
  
  cout << "Values in ob1 are " << ob1.getNumB() << 
          " and " << ob1.getNumA() << endl;  
  
  cout << "Values in ob2 are " << ob2.getNumB() << 
          " and " << ob2.getNumA() << endl; 
   
  return 0;  
}

listing 28
#include <iostream>  
using namespace std;  
  
class MyClass {  
  const int numA; // const member 
  const int numB; // const member 
public:  
  // Initialize numA and numB using initialization syntax. 
  MyClass(int x, int y) : numA(x), numB(y) { }  
  
  int getNumA() { return numA; }  
  int getNumB() { return numB; }  
};  
  
int main()  
{  
  MyClass ob1(7, 9), ob2(5, 2);  
  
  cout << "Values in ob1 are " << ob1.getNumB() << 
          " and " << ob1.getNumA() << endl;  
  
  cout << "Values in ob2 are " << ob2.getNumB() << 
          " and " << ob2.getNumA() << endl; 
   
  return 0;  
}

listing 29
// This program is in error and won't compile.  
#include <iostream>  
using namespace std;  
  
class IntPair {  
public:  
  int a;  
  int b;  
  
  IntPair(int i, int j) : a(i), b(j) { }  
};  
  
class MyClass {  
  IntPair nums; // Error: no default constructor for IntPair!  
public:  
  // This won't work!  
  MyClass(int x, int y) { 
    nums.a = x; 
    nums.b = y; 
  }  
  
  int getNumA() { return nums.a; }  
  int getNumB() { return nums.b; }  
};  
  
int main()  
{  
  MyClass ob1(7, 9), ob2(5, 2);  
  
  cout << "Values in ob1 are " << ob1.getNumB() << 
          " and " << ob1.getNumA() << endl;  
  
  cout << "Values in ob2 are " << ob2.getNumB() << 
          " and " << ob2.getNumA() << endl; 
   
  return 0;  
}

listing 30
// This program is now correct. 
#include <iostream>  
using namespace std;  
  
class IntPair {  
public:  
  int a;  
  int b;  
  
  IntPair(int i, int j) : a(i), b(j) { }  
};  
  
class MyClass {  
  IntPair nums; // now OK 
public:  
  // Initialize nums object using initialization syntax. 
  MyClass(int x, int y) : nums(x,y) { }  
  
  int getNumA() { return nums.a; }  
  int getNumB() { return nums.b; }  
};  
  
int main()  
{  
  MyClass ob1(7, 9), ob2(5, 2);  
  
  cout << "Values in ob1 are " << ob1.getNumB() << 
          " and " << ob1.getNumA() << endl;  
  
  cout << "Values in ob2 are " << ob2.getNumB() << 
          " and " << ob2.getNumA() << endl; 
   
  return 0;  
} 



listing 31
#include <iostream>
using namespace std;

int main()
{
  asm int 5; // generate intertupt 5
  
  return 0;
}

listing 32
#include <iostream>
using namespace std;

extern "C" void myCfunc();

int main()
{
  myCfunc();

  return 0;
}

// This will link as a C function.
void myCfunc()
{
  cout << "This links as a C function.\n";
}

listing 33
#include <strstream>
#include <iostream>
using namespace std;

int main()
{
  char str[80];

  ostrstream outs(str, sizeof(str));

  outs << "C++ array-based I/O. ";
  outs << 1024 << hex << " ";
  outs.setf(ios::showbase);
  outs << 100 << ' ' << 99.789 << ends;

  cout << str;  // display string on console

  return 0;
}

listing 34
#include <strstream>
#include <iostream>
using namespace std;

int main()
{
  char str[80];

  ostrstream outs(str, sizeof(str));

  outs << "abcdefg ";
  outs << 27 << " "  << 890.23;
  outs << ends;  // null terminate

  cout << outs.pcount(); // display how many chars in outs

  cout << " " << str;

  return 0;
}

listing 35
#include <iostream>
#include <strstream>
using namespace std;

int main()
{
  char s[] = "10 Hello 0x75 42.73 OK";

  istrstream ins(s);

  int i;
  char str[80];
  float f;

  // reading: 10 Hello
  ins >> i;
  ins >> str;
  cout << i << " " << str << endl;

  // reading 0x75 42.73 OK
  ins >> hex >> i;
  ins >> f;
  ins >> str;

  cout << hex << i << " " << f << " " << str;

  return 0;
}

listing 36
/* This program shows how to read the contents of any
   array that contains text. */
#include <iostream>
#include <strstream>
using namespace std;

int main()
{
  char s[] = "10.23 this is a test <<>><<?!\n";

  istrstream ins(s);

  char ch;

  /* This will read and display the contents
     of any text array. */

  ins.unsetf(ios::skipws); // don't skip spaces
  while (ins) { // false when end of array is reached
    ins >> ch;
    cout << ch;
  }

  return 0;
}

listing 37
// Perform both input and output.
#include <iostream>
#include <strstream>
using namespace std;

int main()
{
  char iostr[80];

  strstream strio(iostr, sizeof(iostr), ios::in | ios::out);

  int a, b;
  char str[80];

  strio << "10 20 testing ";
  strio >> a >> b >> str;
  cout << a << " " << b << " " << str << endl;

  return 0;
}

listing 38
#include <strstream>
#include <iostream>
using namespace std;

int main()
{
  char *p;

  ostrstream outs;  // dynamically allocate array

  outs << "C++ array-based I/O ";
  outs << -10 << hex << " ";
  outs.setf(ios::showbase);
  outs << 100 << ends;

  p = outs.str(); // Freeze dynamic buffer and return
                  // pointer to it.

  cout << p;

  return 0;
}

listing 39
#include <iostream>
#include <strstream>
using namespace std;

int main()
{
  char *p = "this is a test\1\2\3\4\5\6\7";

  istrstream ins(p);

  char ch;

  // read and display binary info
  while (!ins.eof()) {
    ins.get(ch);
    cout << hex << (int) ch << ' ';
 
 }
  return 0;
}


