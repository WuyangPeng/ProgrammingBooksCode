#include <iostream>
#include <vector>
#include <string>

using std::vector;
using std::string;

void f(vector<string>& vec) { // Pass vec by reference (or
                              // pointer, if you have to)
   // ...
}

int main( ) {

   vector<string> vec(500); // Tell the vector that you plan on
                            // putting a certain number of objects
                            // in it at construction
   vector<string> vec2;

   // Fill up vec...
   f(vec);

   vec2.reserve(500);       // Or, after the fact, tell the vector
                            // that you want the buffer to be big
                            // enough to hold this many objects

   // Fill up vec2...
}
