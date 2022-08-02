// Ex10_11.cpp Using an array storing tuple objects
#include <array>
#include <tuple>
#include <string>
#include <iostream>
#include <iomanip>

const size_t maxRecords{ 100 };
using Record = std::tuple<int, std::string, std::string, int>;
using Records = std::array<Record, maxRecords>;

// Lists the contents of a Records array
void listRecords(const Records& people)
{
  const size_t ID{}, firstname{ 1 }, secondname{ 2 }, age{ 3 };
  std::cout << std::setiosflags(std::ios::left);
  Record empty;
  for (const auto& record : people)
  {
    if (record == empty) break;            // In case array is not full
    std::cout << "ID: " << std::setw(6) << std::get<ID>(record)
              << "Name: " << std::setw(25) << (std::get<firstname>(record) +" " + std::get<secondname>(record))
              << "Age: " << std::setw(5) << std::get<age>(record) << std::endl;
  }
}

int main()
{
  Records personnel{ Record(1001, "Arthur", "Dent", 35),
    Record{ 1002, "Mary", "Poppins", 55 },
    Record{ 1003, "David", "Copperfield", 34 },
    Record{ 1004, "James", "Bond", 44 } };
  personnel[4] = std::make_tuple(1005, "Harry", "Potter", 15);
  personnel.at(5) = Record{ 1006, "Bertie", "Wooster", 28 };

  listRecords(personnel);
}
