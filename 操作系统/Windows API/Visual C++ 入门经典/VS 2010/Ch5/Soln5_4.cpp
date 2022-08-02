// Soln5_4.cpp
#include <iostream>
using std::cin;
using std::cout;
using std::endl;
 
// Read a number and a name
void GetData(int& number, char name[])
{
   cout << "Enter a number: ";
   cin >> number;

   if (number != 0)
   {
      cout << endl << "And a name less than 15 characters: ";
      cin >> name;
   }
}

void PutData(const int number, const char name[])
{
   cout << endl << "Thank you. Your number and name were " 
        << number << " and \"" << name << "\"" << endl;
}

int main()
{
   int number(0);
   char name[15];

   for (;;)
   {
      GetData(number, name);

      if (!number)
         break;

      PutData(number, name);
   }

   return 0;
}
