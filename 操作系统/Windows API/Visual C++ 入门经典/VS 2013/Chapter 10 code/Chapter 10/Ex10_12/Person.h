// Person.h
// A class defining a person
#pragma once
#include <string>

class Person
{
public:
  Person(const std::string& first = "", const std::string& second = "") : firstname{ first }, secondname{ second } {}
  // Move constructor
  Person(std::string&& first, std::string&& second) :
    firstname{ std::move(first) }, secondname{ std::move(second) }  {}

  // Move constructor
  Person(Person&& person) : firstname{ std::move(person.firstname) }, secondname{ std::move(person.secondname) } {}

  // Move assignment operator
  Person& operator=(Person&& person)
  {
    firstname = std::move(person.firstname);
    secondname = std::move(person.secondname);
  }

  // Less-than operator
  bool operator<(const Person& p)const
  {
    return (secondname < p.secondname ||
      ((secondname == p.secondname) && (firstname < p.firstname)));
  }

  // Get the name
  std::string getName()const
  {
    return firstname + " " + secondname;
  }

private:
  std::string firstname;
  std::string secondname;
};
