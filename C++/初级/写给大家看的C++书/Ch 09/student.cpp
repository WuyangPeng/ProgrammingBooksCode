// student.cpp - Script 9.7

#include <iostream>

#include <string>

// Declare the Person class.
class Person {	
public:
	Person(std::string theName);
	
	void introduce();
	
protected:
	std::string name;
};

// Declare the Teacher class.
// Teacher inherits Person.
class Teacher : public Person {
public:
	Teacher(std::string theName, std::string theClass);
	
	void teach();
	void introduce();
	
protected:
	std::string clazz;
};

// Declare the Student class.
// Student inherits Person.
class Student : public Person {
public:
	Student(std::string theName, std::string theClass);
	
	void attendClass();
	void introduce();
	
protected:
	std::string clazz;
};

// Declare the TeachingStudent class.
// TeachingStudent inherits both Student and Teacher.
class TeachingStudent : public Student, public Teacher {
public:

	// Constructor.
	TeachingStudent(
		std::string theName, 
		std::string classTeaching,
		std::string classAttending);	

	void introduce();
};

// Define the methods.
Person::Person(std::string theName) {
	name = theName;
}

void Person::introduce() {
	std::cout << "Hi, I'm " << name << "\n";
}    

Teacher::Teacher(std::string theName, std::string theClass)
: Person(theName) {
	clazz = theClass;
}

void Teacher::teach() {
	std::cout << name << " teaches ";
	std::cout << "'" << clazz << "'.\n";
}

void Teacher::introduce() {
	std::cout << "Hi, I'm " << name << ", and I teach '" << clazz << "'\n";
}    

Student::Student(std::string theName, std::string theClass)
: Person(theName) {
	clazz = theClass;
}

void Student::attendClass() {
	std::cout << name << " attends ";
	std::cout << "'" << clazz << "'.\n";
}

void Student::introduce() {
	std::cout << "Hi, I'm " << name << ", and I study '" << clazz << "'\n";
}    

// TeachingStudent's constructor must invoke 
// the constructors of all base classes!
TeachingStudent::TeachingStudent(
    std::string theName, 
    std::string classTeaching, 
    std::string classAttending)
: Teacher(theName, classTeaching), Student(theName, classAttending) 
{
}

void TeachingStudent::introduce() {
	// Because TeachingStudent inherits two copies of Person's
	// attributes (one from Teacher and one from Student), 
	// we must tell the compiler which copy to use.
	std::cout << "Hi, I'm " << Student::name << ". I teach '" << Teacher::clazz << "', ";
	std::cout <<  "and I study '" << Student::clazz << "'.\n";
}


int main() {

	// Create the objects.
	Teacher teacher("Jim", "C++ 101");
	Student student("Bob", "C++ 101");
	TeachingStudent teachingStudent("Mike", "C++ 101", "Advanced C++");
		
	// Make them do things.
	teacher.introduce();
	teacher.teach();
	student.introduce();
	student.attendClass();
	teachingStudent.introduce();
	teachingStudent.teach();
	teachingStudent.attendClass();	
	
	std::cout << "Press Enter or Return to continue.";
	std::cin.get();
	return 0;
}
