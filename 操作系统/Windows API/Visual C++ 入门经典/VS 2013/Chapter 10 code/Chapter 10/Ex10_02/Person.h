// Person.h in Ex10_02
// A class defining people by their names
#pragma once
#include <cstring>
#include <iostream>

class Person
{
public:
  // Constructor, includes no-arg constructor
  Person(const char* first = "John", const char* second = "Doe")
  {
    initName(first, second);
  }

  // Copy constructor
  Person(const Person& p)
  {
    initName(p.firstname, p.secondname);
  }

  // Move constructor
  Person(Person&& p)
  {
    firstname = p.firstname;
    secondname = p.secondname;
    // Reset rvalue object pointers to prevent deletion
    p.firstname = nullptr;
    p.secondname = nullptr;
  }

  // Destructor
  virtual ~Person()
  {
    delete[] firstname;
    delete[] secondname;
  }

  // Assignment operator
  Person& operator=(const Person& p)
  {
    // Deal with p = p assignment situation
    if (&p != this)
    {
      delete[] firstname;
      delete[] secondname;
      initName(p.firstname, p.secondname);
    }
    return *this;
  }

  // Move assignment operator
  Person& operator=(Person&& p)
  {
    // Deal with p = p assignment situation
    if (&p != this)
    {
      // Release current memory        
      delete[] firstname;
      delete[] secondname;
      firstname = p.firstname;
      secondname = p.secondname;
      p.firstname = nullptr;
      p.secondname = nullptr;
    }
    return *this;
  }
  // Less-than operator
  bool operator<(const Person& p) const
  {
    int result{ strcmp(secondname, p.secondname) };
    return (result < 0 || result == 0 && strcmp(firstname, p.firstname) < 0);
  }

  // Output a person
  void showPerson() const
  {
    std::cout << firstname << " " << secondname << std::endl;
  }

private:
  char* firstname{};
  char* secondname{};

  // Private helper function to avoid code duplication
  void initName(const char* first, const char* second)
  {
    size_t length{ strlen(first) + 1 };
    firstname = new char[length];
    strcpy_s(firstname, length, first);
    length = strlen(second) + 1;
    secondname = new char[length];
    strcpy_s(secondname, length, second);
  }
};
