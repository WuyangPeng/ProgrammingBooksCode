/* Code for exercise 21.2.
 | 
 | "C++ Solutions--Companion to The C++ Programming Language, Third Edition"
 | by David Vandevoorde; Addison-Wesley 1998; ISBN 0-201-30965-3.
 |
 | Permission to use, copy, modify, distribute and sell this software
 | and its documentation for any purpose is hereby granted without fee.
 | The author makes no representations about the suitability of this
 | software for any purpose.  It is provided "as is" without express or
 | implied warranty.
 `----------------------------------------------------------------------*/

#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <string>

enum FieldType { kName = 0, kFamilyName = 0, kGivenNames = 1,
                 kStreet = 2, kStreetAddress = 2, kCity = 3,
                 kCityAndZip = 3, kCountry = 4 };

struct Name_and_address {
   Name_and_address() {}
   Name_and_address(std::string const &name, std::string const &given_names,
                    std::string const &street,
                    std::string const &city, std::string const &country) {
      field_[kName] = name;
      field_[kGivenNames] = given_names;
      field_[kStreetAddress] = street;
      field_[kCityAndZip] = city;
      field_[kCountry] = country;
   }

   void set_field(FieldType f, std::string const &field_value) {
      field_[f] = field_value;
   }

   std::string const& field(FieldType f) const {
      return field_[f];
   }
private:
   std::string field_[5];
};


std::ostream& operator<<(std::ostream &output, Name_and_address const &obj) {
   for (int k = kName; k!=kCountry+1; ++k)
      output << obj.field(FieldType(k)) << '\n';
   return output;
};


std::istream& operator>>(std::istream &input, Name_and_address &obj) {
   for (int k = kName; k!=kCountry+1; ++k) {
      std::string line;
      std::getline(input, line);
      obj.set_field(FieldType(k), line);
   }
   return input;
}


void error(char const *prog, char const *entity, char const *msg) {
   std::cerr << prog << ": " << entity << msg << '\n';
   exit(1);
}

int main(int argc, char *argv[]) {
   if (argc!=3)
      error(argv[0], "", ": unexpected number of arguments.");
   std::ifstream input(argv[1]);
   if (!input)
      error(argv[0], argv[1], ": cannot open file for reading.");
   std::ofstream output(argv[2]);
   if (!output)
      error(argv[0], argv[2], ": cannot open file for writing.");
   std::copy(std::istream_iterator<Name_and_address, char>(input),
             std::istream_iterator<Name_and_address, char>(),
             std::ostream_iterator<Name_and_address, char>(output));
   return 0;
}

