// Soln5_4.cpp
#include <iostream>
 
// Read a number and a name
void GetData(int& number, char name[])
{
  std::cout << "Enter a number, or 0 to end: ";
  std::cin >> number;

  if (number != 0)
  {
    std::cout << std::endl << "And a name less than 15 characters: ";
    std::cin >> name;
  }
}

void PutData(const int number, const char name[])
{
  std::cout << std::endl << "Thank you. Your number and name were "
            << number << " and \"" << name << "\"" << std::endl;
}

int main()
{
  int number{};
   char name[15];

   for (;;)
   {
      GetData(number, name);

      if (!number)
         break;

      PutData(number, name);
   }
}
