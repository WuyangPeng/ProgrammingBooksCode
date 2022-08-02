listing 1
// Demonstrate string streams. 
#include <iostream> 
#include <sstream> 
using namespace std; 
 
int main() 
{ 
  stringstream s("This is initial string."); 
 
  // get string 
  string str = s.str(); 
  cout << str << endl; 
 
  // output to string stream  
  s << "Numbers: " << 10 << " " << 123.2; 
 
  int i; 
  double d; 
  s >> str >> i >> d; 
  cout << str << " " << i << " " << d; 
 
  return 0; 
}

