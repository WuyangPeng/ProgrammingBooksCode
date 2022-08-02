// Soln7_04.cpp

#include <iostream>                   // For stream input/output

using std::cin;
using std::cout;
using std::endl;

class CRecord
{
public:
  bool getRecord();
  void putRecord();

private:
   int number;
   char name[15];
};

//Read a record
bool CRecord::getRecord()
{
   cout << "Enter a number: ";
   cin >> number;

   if (number)
   {
      cout << "And a name: ";
      cin >> name;
      return true;
   }
   return false;
}

// Output a record
void CRecord::putRecord()
{
   cout << "The number and name are " << number 
        << " and \"" << name << "\"" << endl;
}

int main()
{
  CRecord record;
  while (record.getRecord())
    record.putRecord();
}
