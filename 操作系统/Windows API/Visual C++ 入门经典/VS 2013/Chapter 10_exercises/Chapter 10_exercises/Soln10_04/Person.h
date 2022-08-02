// Person.h
// A class defining a person
#pragma once
#include <string>
using std::string;

class Person
{
public:
  Person(const string& first = "", const string& second = "") : firstname(first), secondname(second) {}

  // Move constructor
  Person(string&& first, string&& second) : firstname(std::move(first)), secondname(std::move(second))  {}

  // Less-than operator
  bool operator<(const Person& p)const
  {
    return (secondname < p.secondname || ((secondname == p.secondname) && (firstname < p.firstname)));
  }

  // Get the name
  string getName()const
  {
    return firstname + " " + secondname;
  }

private:
  string firstname;
  string secondname;
};
