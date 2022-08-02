// Person.h
// A class defining a person
#pragma once
#include <iostream>
#include <string>

class Person
{
public:
  Person(const std::string first, const std::string second) :
    firstname{ std::move(first) }, secondname{ std::move(second) } {}

  Person() = default;

  // Less-than operator
  bool operator<(const Person& p)const
  {
    return (secondname < p.secondname ||
      ((secondname == p.secondname) && (firstname < p.firstname)));
  }

  // Greater-than operator
  bool operator>(const Person& p)const
  {
    return p < *this;
  }

  // Output a person
  void showPerson() const
  {
    std::cout << firstname << " " << secondname << std::endl;
  }

private:
  std::string firstname;
  std::string secondname;
};
