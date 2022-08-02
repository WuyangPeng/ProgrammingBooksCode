// Soln7_04.cpp

#include <iostream>                   // For stream input/output

using std::cin;
using std::cout;
using std::endl;

class CRecord
{
public:
  int getRecord();
  void putRecord();

private:
   int number;
   char name[15];
};

//Read a record
int CRecord::getRecord()
{
   cout << "Enter a number: ";
   cin >> number;

   if (number != 0)
   {
      cout << "And a name: ";
      cin >> name;
   }
   return number;
}

// Output a record
void CRecord::putRecord()
{
   cout << "The number and name are " << number 
        << " and \"" << name << "\"" << endl;
}

int main()
{
  while (true)
  {
    CRecord record;
    if(record.getRecord() == 0)
      break;
    record.putRecord();
  }
   
  return 0;
}
