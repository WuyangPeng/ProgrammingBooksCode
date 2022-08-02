#include <iostream> 

#include <string> 

using namespace std; 

int main() 
{ 
   cout << "Enter coin name: "; 
   string name; 
   cin >> name; 
   double value = 0; 

   if (name == "penny") 
      value = 0.01; 
   else if (name == "nickel") 
      value = 0.05; 
   else if (name == "dime")
      value = 0.10; 
   else if (name == "quarter") 
      value = 0.25; 
   else 
      cout << name << " is not a valid coin name\n"; 
   cout << "Value = " << value << "\n"; 

   return 0;
}
