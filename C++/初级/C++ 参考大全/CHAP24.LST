listing 1
vector<int> iv;           // create zero-length int vector
vector<char> cv(5);       // create 5-element char vector
vector<char> cv(5,  'x'); // initialize a 5-element char vector 
vector<int> iv2(iv);      // create int vector from an int vector

listing 2
// Demonstrate a vector.
#include <iostream>
#include <vector>
#include <cctype>
using namespace std;

int main()
{
  vector<char> v(10); // create a vector of length 10
  unsigned int i;

  // display original size of v
  cout << "Size = " << v.size() << endl;

  // assign the elements of the vector some values
  for(i=0; i<10; i++) v[i] = i + 'a';

  // display contents of vector
  cout << "Current Contents:\n";
  for(i=0; i<v.size(); i++) cout << v[i] << " ";
  cout << "\n\n";

  cout << "Expanding vector\n";
  /* put more values onto the end of the vector,
     it will grow as needed */
  for(i=0; i<10; i++) v.push_back(i + 10 + 'a');

  // display current size of v
  cout << "Size now = " << v.size() << endl;

  // display contents of vector
  cout << "Current contents:\n";
  for(i=0; i<v.size(); i++) cout << v[i] << " ";
  cout << "\n\n";

  // change contents of vector
  for(i=0; i<v.size(); i++) v[i] = toupper(v[i]);
  cout << "Modified Contents:\n";
  for(i=0; i<v.size(); i++) cout << v[i] << " ";
  cout << endl;

  return 0;
}

listing 3
// Access the elements of a vector through an iterator.
#include <iostream>
#include <vector>
#include <cctype>
using namespace std;

int main()
{
  vector<char> v(10); // create a vector of length 10
  vector<char>::iterator p; // create an iterator
  int i;

  // assign elements in vector a value
  p = v.begin();
  i = 0;
  while(p != v.end()) {
    *p = i + 'a';
    p++;
    i++;
  }

  // display contents of vector
  cout << "Original contents:\n";
  p = v.begin();
  while(p != v.end()) {
    cout << *p << " ";
    p++;
  }
  cout << "\n\n";

  // change contents of vector
  p = v.begin();
  while(p != v.end()) {
    *p = toupper(*p);
    p++;
  }

  // display contents of vector
  cout << "Modified Contents:\n";
  p = v.begin();
  while(p != v.end()) {
    cout << *p << " ";
    p++;
  }
  cout << endl;

  return 0;
}

listing 4
// Demonstrate insert and erase.
#include <iostream>
#include <vector>
using namespace std;

int main()
{
  vector<char> v(10);
  vector<char> v2;
  char str[] = "<Vector>";
  unsigned int i;

  // initialize v
  for(i=0; i<10; i++) v[i] = i + 'a';

  // copy characters in str into v2
  for(i=0; str[i]; i++) v2.push_back(str[i]);
  
  // display original contents of vector
  cout << "Original contents of v:\n";
  for(i=0; i<v.size(); i++) cout << v[i] << " ";
  cout << "\n\n";

  vector<char>::iterator p = v.begin();
  p += 2; // point to 3rd element

  // insert 10 X's into v
  v.insert(p, 10, 'X');

  // display contents after insertion
  cout << "Size after inserting X's = " << v.size() << endl;
  cout << "Contents after insert:\n";
  for(i=0; i<v.size(); i++) cout << v[i] << " ";
  cout << "\n\n";

  // remove those elements
  p = v.begin();
  p += 2; // point to 3rd element
  v.erase(p, p+10); // remove next 10 elements

  // display contents after deletion
  cout << "Size after erase = " << v.size() << endl;
  cout << "Contents after erase:\n";
  for(i=0; i<v.size(); i++) cout << v[i] << " ";
  cout << "\n\n";

  // Insert v2 into v
  v.insert(p, v2.begin(), v2.end());
  cout << "Size after v2's insertion = ";
  cout << v.size() << endl;
  cout << "Contents after insert:\n";
  for(i=0; i<v.size(); i++) cout << v[i] << " ";
  cout << endl;

  return 0;
} 

listing 5
// Store a class object in a vector. 
#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;

class DailyTemp {
  int temp;
public:
  DailyTemp() { temp = 0; }
  DailyTemp(int x) { temp = x; }

  DailyTemp &operator=(int x) {
    temp = x; return *this;
  }

  double get_temp() { return temp; }
};

bool operator<(DailyTemp a, DailyTemp b)
{
  return a.get_temp() < b.get_temp();
}

bool operator==(DailyTemp a, DailyTemp b)
{
  return a.get_temp() == b.get_temp();
}

int main()
{
  vector<DailyTemp> v;
  unsigned int i;

  for(i=0; i<7; i++)
    v.push_back(DailyTemp(60 + rand()%30));

  cout << "Farenheit temperatures:\n";
  for(i=0; i<v.size(); i++)
    cout << v[i].get_temp() << " ";

  cout << endl;

  // convert from Farenheit to Centigrade
  for(i=0; i<v.size(); i++)
    v[i] = (int) (v[i].get_temp()-32) * 5/9 ;

  cout << "Centigrade temperatures:\n";
  for(i=0; i<v.size(); i++)
    cout << v[i].get_temp() << " ";

  return 0;
}


listing 6
// List basics.
#include <iostream>
#include <list>
using namespace std;

int main()
{
  list<int> lst; // create an empty list
  int i;

  for(i=0; i<10; i++) lst.push_back(i);

  cout << "Size = " << lst.size() << endl;

  cout << "Contents: ";
  list<int>::iterator p = lst.begin();
  while(p != lst.end()) {
    cout << *p << " ";
    p++;
  }
  cout << "\n\n";

  // change contents of list
  p = lst.begin();
  while(p != lst.end()) {
    *p = *p + 100;
    p++;
  }

  cout << "Contents modified: ";
  p = lst.begin();
  while(p != lst.end()) {
    cout << *p << " ";
    p++;
  }

  return 0;
}

listing 7
list<int>::iterator p = lst.begin();
while(p != lst.end()) {
  cout << *p << " ";
  p++;
}

listing 8
// Understanding end().
#include <iostream>
#include <list>
using namespace std;

int main()
{
  list<int> lst; // create an empty list
  int i;

  for(i=0; i<10; i++) lst.push_back(i);

  cout << "List printed forwards:\n";
  list<int>::iterator p = lst.begin();
  while(p != lst.end()) {
    cout << *p << " ";
    p++;
  }
  cout << "\n\n";

  cout << "List printed backwards:\n";
  p = lst.end();
  while(p != lst.begin()) {
    p--; // decrement pointer before using
    cout << *p << " ";
  }

  return 0;
}

listing 9
/* Demonstrating the difference between 
   push_back() and push_front(). */
#include <iostream>
#include <list>
using namespace std;

int main()
{
  list<int> lst1, lst2;
  int i;

  for(i=0; i<10; i++) lst1.push_back(i);
  for(i=0; i<10; i++) lst2.push_front(i);
  
  list<int>::iterator p;
  
  cout << "Contents of lst1:\n";
  p = lst1.begin();  
  while(p != lst1.end()) {
    cout << *p << " ";
    p++;
  }
  cout << "\n\n";

  cout << "Contents of lst2:\n";
  p = lst2.begin();  
  while(p != lst2.end()) {
    cout << *p << " ";
    p++;
  }
    
  return 0;
}


listing 10
// Sort a list.
#include <iostream>
#include <list>
#include <cstdlib>
using namespace std;

int main()
{
  list<int> lst;
  int i;

  // create a list of random integers
  for(i=0; i<10; i++)
    lst.push_back(rand());

  cout << "Original contents:\n";
  list<int>::iterator p = lst.begin();
  while(p != lst.end()) {
    cout << *p << " ";
    p++;
  }
  cout << endl << endl;

  // sort the list
  lst.sort();

  cout << "Sorted contents:\n";
  p = lst.begin();
  while(p != lst.end()) {
    cout << *p << " ";
    p++;
  }
  
  return 0;
}

listing 11
// Merge two lists.
#include <iostream>
#include <list>
using namespace std;

int main()
{
  list<int> lst1, lst2;
  int i;

  for(i=0; i<10; i+=2) lst1.push_back(i);
  for(i=1; i<11; i+=2) lst2.push_back(i);

  cout << "Contents of lst1:\n";
  list<int>::iterator p = lst1.begin();
  while(p != lst1.end()) {
    cout << *p << " ";
    p++;
  }
  cout << endl << endl;

  cout << "Contents of lst2:\n";
  p = lst2.begin();
  while(p != lst2.end()) {
    cout << *p << " ";
    p++;
  }
  cout << endl << endl;

  // now, merge the two lists
  lst1.merge(lst2);
  if(lst2.empty())
    cout << "lst2 is now empty\n";

  cout << "Contents of lst1 after merge:\n";
  p = lst1.begin();
  while(p != lst1.end()) {
    cout << *p << " ";
    p++;
  }

  return 0;
}

listing 12
// Store class objects in a list.
#include <iostream>
#include <list>
#include <cstring>
using namespace std;

class myclass {
  int a, b;
  int sum;
public:
  myclass() { a = b = 0; }
  myclass(int i, int j) {
    a = i;
    b = j;
    sum = a + b;
  }
  int getsum() { return sum; }

  friend bool operator<(const myclass &o1,
                        const myclass &o2);
  friend bool operator>(const myclass &o1,
                        const myclass &o2);
  friend bool operator==(const myclass &o1,
                        const myclass &o2);
  friend bool operator!=(const myclass &o1,
                        const myclass &o2);
};

bool operator<(const myclass &o1, const myclass &o2)
{
  return o1.sum < o2.sum;
}

bool operator>(const myclass &o1, const myclass &o2)
{
  return o1.sum > o2.sum;
}

bool operator==(const myclass &o1, const myclass &o2)
{
  return o1.sum == o2.sum;
}

bool operator!=(const myclass &o1, const myclass &o2)
{
  return o1.sum != o2.sum;
}

int main()
{
  int i;

  // create first list
  list<myclass> lst1;
  for(i=0; i<10; i++) lst1.push_back(myclass(i, i));

  cout << "First list: ";
  list<myclass>::iterator p = lst1.begin();
  while(p != lst1.end()) {
    cout << p->getsum() << " ";
    p++;
  }
  cout << endl;

  // create a second list
  list<myclass> lst2;
  for(i=0; i<10; i++) lst2.push_back(myclass(i*2, i*3));

  cout << "Second list: ";
  p = lst2.begin();
  while(p != lst2.end()) {
    cout << p->getsum() << " ";
    p++;
  }
  cout << endl;

  // now, merget lst1 and lst2
  lst1.merge(lst2);

  // display merged list
  cout << "Merged list: ";
  p = lst1.begin();
  while(p != lst1.end()) {
    cout << p->getsum() << " ";
    p++;
  }

  return 0;
}


listing 13
// A simple map demonstration.
#include <iostream>
#include <map>
using namespace std;

int main()
{
  map<char, int> m;
  int i;

  // put pairs into map
  for(i=0; i<26; i++) {
    m.insert(pair<char, int>('A'+i, 65+i));
  }

  char ch;
  cout << "Enter key: ";
  cin >> ch;

  map<char, int>::iterator p;
  
  // find value given key
  p = m.find(ch);
  if(p != m.end()) 
    cout << "Its ASCII value is  " << p->second;
  else
    cout << "Key not in map.\n";

  return 0;
}

listing 14
m.insert(make_pair((char)('A'+i), 65+i));

listing 15
// Use a map to create a phone directory.
#include <iostream>
#include <map>
#include <cstring>
using namespace std;

class name {
  char str[40];
public:
  name() { strcpy(str, ""); }
  name(char *s) { strcpy(str, s); }
  char *get() { return str; }

};

// Must define less than relative to name objects.
bool operator<(name a, name b)
{
   return strcmp(a.get(), b.get()) < 0;
}

class phoneNum {
  char str[80];
public:
  phoneNum() { strcmp(str, ""); }
  phoneNum(char *s) { strcpy(str, s); }
  char *get() { return str; }
};


int main()
{
  map<name, phoneNum> directory;

 // put names and numbers into map
  directory.insert(pair<name, phoneNum>(name("Tom"),
                    phoneNum("555-4533")));
  directory.insert(pair<name, phoneNum>(name("Chris"),
                    phoneNum("555-9678")));
  directory.insert(pair<name, phoneNum>(name("John"),
             phoneNum("555-8195")));
  directory.insert(pair<name, phoneNum>(name("Rachel"),
                    phoneNum("555-0809")));

  // given a name, find number
  char str[80];
  cout << "Enter name: ";
  cin >> str;

  map<name, phoneNum>::iterator p;
  
  p = directory.find(name(str));
  if(p != directory.end()) 
    cout << "Phone number: " <<  p->second.get();
  else
    cout << "Name not in directory.\n";

  return 0;
}

listing 16
// Demonstrate count().
#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>
using namespace std;

int main()
{
  vector<bool> v;
  unsigned int i;
  
  for(i=0; i < 10; i++) {
   if(rand() % 2) v.push_back(true);
   else v.push_back(false);
  }

  cout << "Sequence:\n";
  for(i=0; i<v.size(); i++)
    cout << boolalpha << v[i] << " ";
  cout << endl;

  i = count(v.begin(), v.end(), true);
  cout << i << " elements are true.\n";

  return 0;
}


listing 17
// Demonstrate count_if().
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/* This is a unary predicate that determines 
   if number is divisible by 3. */
bool dividesBy3(int i) 
{
  if((i%3) == 0) return true;

  return false;
}

int main()
{
  vector<int> v;
  unsigned int i;

  for(i=1; i < 20; i++) v.push_back(i);

  cout << "Sequence:\n";
  for(i=0; i<v.size(); i++)
    cout << v[i] << " ";
  cout << endl;

  i = count_if(v.begin(), v.end(), dividesBy3);
  cout << i << " numbers are divisible by 3.\n";

  return 0;
}

listing 18
// Demonstrate remove_copy and replace_copy.
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
  char str[] = "The STL is power programming.";
  vector<char> v, v2(30); 
  unsigned int i;

  for(i=0; str[i]; i++) v.push_back(str[i]);

  // **** demonstrate remove_copy ****
  cout << "Input sequence:\n";
  for(i=0; i<v.size(); i++) cout << v[i];
  cout << endl;

  // remove all spaces
  remove_copy(v.begin(), v.end(), v2.begin(), ' ');

  cout << "Result after removing spaces:\n";
  for(i=0; i<v2.size(); i++) cout << v2[i];
  cout << endl << endl;

  // **** now, demonstrate replace_copy ****
  cout << "Input sequence:\n";
  for(i=0; i<v.size(); i++) cout << v[i];
  cout << endl;

  // replace spaces with colons
  replace_copy(v.begin(), v.end(), v2.begin(), ' ', ':');

  cout << "Result after repacing spaces with colons:\n";
  for(i=0; i<v2.size(); i++) cout << v2[i];
  cout << endl << endl;

  return 0;
}

listing 19
// Demonstrate reverse.
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
  vector<int> v;
  unsigned int i;

  for(i=0; i<10; i++) v.push_back(i);

  cout << "Initial: ";
  for(i=0; i<v.size(); i++) cout << v[i] << " ";
  cout << endl;

  reverse(v.begin(), v.end());

  cout << "Reversed: ";
  for(i=0; i<v.size(); i++) cout << v[i] << " ";

  return 0;
}

listing 20
// An example of the transform algorithm.
#include <iostream>
#include <list>
#include <algorithm>
using namespace std;

// A simple transformation function.
double reciprocal(double i) {
  return 1.0/i; // return reciprocal
}

int main()
{
  list<double> vals;
  int i;

  // put values into list
  for(i=1; i<10; i++) vals.push_back((double)i);

  cout << "Original contents of vals:\n";
  list<double>::iterator p = vals.begin();
  while(p != vals.end()) {
    cout << *p << " ";
    p++;
  }

  cout << endl;
 
  // transform vals
  p = transform(vals.begin(), vals.end(),
                vals.begin(), reciprocal);

  cout << "Transformed contents of vals:\n";
  p = vals.begin();
  while(p != vals.end()) {
    cout << *p << " ";
    p++;
  }

  return 0;
}

listing 21
plus<float>()

listing 22
// Use a unary function object.
#include <iostream>
#include <list>
#include <functional>
#include <algorithm>
using namespace std;

int main()
{
  list<double> vals;
  int i;

  // put values into list
  for(i=1; i<10; i++) vals.push_back((double)i);

  cout << "Original contents of vals:\n";
  list<double>::iterator p = vals.begin();
  while(p != vals.end()) {
    cout << *p << " ";
    p++;
  }
  cout << endl;
 
  // use the negate function object
  p = transform(vals.begin(), vals.end(),
                vals.begin(),
                negate<double>()); // call function object

  cout << "Negated contents of vals:\n";
  p = vals.begin();
  while(p != vals.end()) {
    cout << *p << " ";
    p++;
  }

  return 0;
}

listing 23
// Use a binary function object.
#include <iostream>
#include <list>
#include <functional>
#include <algorithm>
using namespace std;

int main()
{
  list<double> vals;
  list<double> divisors;
  int i;

  // put values into list
  for(i=10; i<100; i+=10) vals.push_back((double)i);
  for(i=1; i<10; i++) divisors.push_back(3.0);

  cout << "Original contents of vals:\n";
  list<double>::iterator p = vals.begin();
  while(p != vals.end()) {
    cout << *p << " ";
    p++;
  }

  cout << endl;
 
  // transform vals
  p = transform(vals.begin(), vals.end(),
                divisors.begin(), vals.begin(),
                divides<double>()); // call function object

  cout << "Divided contents of vals:\n";
  p = vals.begin();
  while(p != vals.end()) {
    cout << *p << " ";
    p++;
  }

  return 0;
}

listing 24
template <class Argument, class Result> struct unary_function {
  typedef Argument argument_type;
  typedef Result result_type;
};

template <class Argument1, class Argument2, class Result>
struct binary_function {
  typedef Argument1 first_argument_type;
  typedef Argument2 second_argument_type;
  typedef Result result_type;
};

listing 25
// Create a reciprocal function object.
#include <iostream>
#include <list>
#include <functional>
#include <algorithm>
using namespace std;

// A simple function object.
class reciprocal: unary_function<double, double> {
public:
  result_type operator()(argument_type i)
  { 
    return (result_type) 1.0/i; // return reciprocal
  }
};

int main()
{
  list<double> vals;
  int i;

  // put values into list
  for(i=1; i<10; i++) vals.push_back((double)i);

  cout << "Original contents of vals:\n";
  list<double>::iterator p = vals.begin();
  while(p != vals.end()) {
    cout << *p << " ";
    p++;
  }
  cout << endl;
 
  // use reciprocal function object
  p = transform(vals.begin(), vals.end(),
                vals.begin(),
                reciprocal()); // call function object

  cout << "Transformed contents of vals:\n";
  p = vals.begin();
  while(p != vals.end()) {
    cout << *p << " ";
    p++;
  }

  return 0;
}


listing 26
// Demonstrate bind2nd().
#include <iostream>
#include <list>
#include <functional>
#include <algorithm>
using namespace std;

int main()
{
  list<int> lst;
  list<int>::iterator p, endp;

  int i;

  for(i=1; i < 20; i++) lst.push_back(i);

  cout << "Original sequence:\n";
  p = lst.begin();
  while(p != lst.end()) {
    cout << *p << " ";
    p++;
  }
  cout << endl;

  endp = remove_if(lst.begin(), lst.end(),
                   bind2nd(greater<int>(), 8));

  cout << "Resulting sequence:\n";
  p = lst.begin();
  while(p != endp) {
    cout << *p << " ";
    p++;
  }

  return 0;
}

listing 27
  endp = remove_if(lst.begin(), lst.end(),
                   not1(bind2nd(greater<int>(), 8)));

listing 28
char s1[80], s2[80], s3[80];

s1 = "Alpha"; // can't do
s2 = "Beta"; // can't do 
s3 = s1 + s2; // error, not allowed

listing 29
strcpy(s1, "Alpha");
strcpy(s2, "Beta");
strcpy(s3, s1);
strcat(s3, s2);

listing 30
// A short string demonstration.
#include <iostream>
#include <string>
using namespace std;

int main()
{
  string str1("Alpha");
  string str2("Beta");
  string str3("Omega");
  string str4;

  // assign a string
  str4 = str1; 
  cout << str1 << "\n" << str3 << "\n";

  // concatenate two strings
  str4 = str1 + str2; 
  cout << str4 << "\n";

  // concatenate a string with a C-string
  str4 = str1 + " to " + str3;
  cout << str4 << "\n";

  // compare strings
  if(str3 > str1) cout << "str3 > str1\n";
  if(str3 == str1+str2)
    cout << "str3 == str1+str2\n";

  /* A string object can also be 
     assigned a normal string. */
  str1 = "This is a null-terminated string.\n";
  cout << str1;

  // create a string object using another string object
  string str5(str1);
  cout << str5;

  // input a string
  cout << "Enter a string: ";
  cin >> str5;
  cout << str5;

  return 0;
}

listing 31
// Demonstrate insert(), erase(), and replace().
#include <iostream>
#include <string>
using namespace std;

int main()
{
  string str1("String handling C++ style.");
  string str2("STL Power");

  cout << "Initial strings:\n";
  cout << "str1: " << str1 << endl;
  cout << "str2: " << str2 << "\n\n";

  // demonstrate insert()
  cout << "Insert str2 into str1:\n";
  str1.insert(6, str2);
  cout << str1 << "\n\n";

  // demonstrate erase()
  cout << "Remove 9 characters from str1:\n";
  str1.erase(6, 9);
  cout << str1 <<"\n\n";

  // demonstrate replace 
  cout << "Replace 8 characters in str1 with str2:\n";
  str1.replace(7, 8, str2);
  cout << str1 << endl;

  return 0;
}


listing 32
#include <iostream>
#include <string>
using namespace std;

int main()
{
  int i;
  string s1 =
    "Quick of Mind, Strong of Body, Pure of Heart";
  string s2;

  i = s1.find("Quick");
  if(i!=string::npos) {
    cout << "Match found at " << i << endl;
    cout << "Remaining string is:\n";
    s2.assign(s1, i, s1.size());
    cout << s2;
  }
  cout << "\n\n";

  i = s1.find("Strong");
  if(i!=string::npos) {
    cout << "Match found at " << i << endl;
    cout << "Remaining string is:\n";
    s2.assign(s1, i, s1.size());
    cout << s2;
  }
  cout << "\n\n";

  i = s1.find("Pure");
  if(i!=string::npos) {
    cout << "Match found at " << i << endl;
    cout << "Remaining string is:\n";
    s2.assign(s1, i, s1.size());
    cout << s2;
  }
  cout << "\n\n";

  // find list "of"
  i = s1.rfind("of");
  if(i!=string::npos) {
    cout << "Match found at " << i << endl;
    cout << "Remaining string is:\n";
    s2.assign(s1, i, s1.size());
    cout << s2;
  }

  return 0;
}


listing 33
// Strings as containers.
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int main()
{
  string str1("Strings handling is easy in C++");
  string::iterator p;
  unsigned int i;

  // use size()
  for(i=0; i<str1.size(); i++)
    cout << str1[i];
  cout << endl;

  // use iterator
  p = str1.begin();
  while(p != str1.end()) 
    cout << *p++;
  cout << endl;

  // use the count() algorithm
  i = count(str1.begin(), str1.end(), 'i');
  cout << "There are " << i << " i's in str1\n";

  // use transform() to upper case the string
  transform(str1.begin(), str1.end(), str1.begin(),
            toupper);
  p = str1.begin();
  while(p != str1.end()) 
    cout << *p++;
  cout << endl;


  return 0;
}

listing 34
// Use a map of strings to create a phone directory.
#include <iostream>
#include <map>
#include <string>
using namespace std;

int main()
{
  map<string, string> directory;

  directory.insert(pair<string, string>("Tom", "555-4533"));
  directory.insert(pair<string, string>("Chris", "555-9678"));
  directory.insert(pair<string, string>("John", "555-8195"));
  directory.insert(pair<string, string>("Rachel", "555-0809"));

  string s;
  cout << "Enter name: ";
  cin >> s;

  map<string, string>::iterator p;
  
  p = directory.find(s);
  if(p != directory.end()) 
    cout << "Phone number: " << p->second;
  else
    cout << "Name not in directory.\n";

  return 0;
}

