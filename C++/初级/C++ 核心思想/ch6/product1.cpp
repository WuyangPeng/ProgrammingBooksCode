/* 
   This program compiles but doesn't run. 
   See product2.cpp for the complete program.
*/

#include <iostream>
#include <string>

using namespace std;

class Product
{
public:
   Product();

   void read();

   bool is_better_than(Product b) const;
   void print() const;
private:
};

int main()
{  
   Product best;

   bool more = true;
   while (more)
   {  
      Product next;
      next.read();
      if (next.is_better_than(best)) best = next;

      cout << "More data? (y/n) ";
      string answer;
      getline(cin, answer);
      if (answer != "y") more = false;
   }

   cout << "The best value is ";
   best.print();

   return 0;
}
