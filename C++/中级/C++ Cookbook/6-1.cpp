#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main( ) {

   vector<int>    intVec;
   vector<string> strVec;

   // Add elements to the "back" of the vector with push_back
   intVec.push_back(3);
   intVec.push_back(9);
   intVec.push_back(6);

   string s = "Army";

   strVec.push_back(s);
   s = "Navy";
   strVec.push_back(s);
   s = "Air Force";
   strVec.push_back(s);

   // You can access them with operator[], just like an array
   for (vector<string>::size_type i = 0; i < intVec.size( ); ++i) {
      cout << "intVec[" << i << "] = " << intVec[i] << '\n';
   }

   // Or you can use iterators
   for (vector<string>::iterator p = strVec.begin( );
        p != strVec.end( ); ++p) {
      cout << *p << '\n';
   }

   // If you need to be safe, use at( ) instead of operator[].  It
   // will throw out_of_range if the index you use is > size( ).
   try {
      intVec.at(300) = 2;
   }
   catch(out_of_range& e) {
      cerr << "out_of_range: " << e.what( ) << endl;
   }
}
