// Ex8_11.cpp
// Perfect forwarding
#include <iostream>
#include <utility>
#include <string>
using std::string;
using std::cout;
using std::endl;

class Name
{
public:
  Name(const string& aName) : name{ aName }
  {
    cout << "Lvalue Name constructor." << endl;
  }

  Name(string&& aName) : name{ std::move(aName) }
  {
    cout << "Rvalue Name constructor." << endl;
  }

  const string& getName() const { return name; }

private:
  string name;
};

class Person
{
public:
  // Constructor template
  template<typename T1, typename T2>
  Person(T1&& first, T2&& second) :
    firstname{ std::forward<T1>(first) }, secondname{ std::forward<T2>(second) } {}
  //    firstname {first}, secondname {second} {}

  // Access the name
  string getName() const
  {
    return firstname.getName() + " " + secondname.getName();
  }

private:
  Name firstname;
  Name secondname;
};

int main()
{
  cout << "Creating Person {string {\"Ivor\"} , string {\"Horton\"}} - rvalue arguments:"
    << endl;
  Person me { string{ "Ivor" }, string{ "Horton" } };
  cout << "Person is " << me.getName() << endl << endl;
  string first{ "Fred" };
  string second{ "Fernackerpan" };
  cout << "Creating Person {first , second} - lvalue arguments:" << endl;
  Person other{ first, second };
  cout << "Person is " << other.getName() << endl << endl;
  cout << "Creating Person {first , string {\"Bloggs\"} - lvalue, rvalue arguments:"
    << endl;
  Person brother{ first, string{ "Bloggs" } };
  cout << "Person is " << brother.getName() << endl << endl;
  cout << "Creating Person {\"Richard\" , \"Horton\"} - rvalue const char* arguments:"
    << endl;
  Person another{ "Richard", "Horton" };
  cout << "Person is " << another.getName() << endl;
  return 0;
}
