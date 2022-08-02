// copyctor.cpp - Script 11.5

#include <iostream>

#include <string>

// Declare a class MyClass.
class MyClass {
public:

	// The "regular" constructor expects 
	// a pointer to an integer.
	MyClass(int *p);

	// This is the copy constructor.
	MyClass(const MyClass &rhs);
	
	// The class owns the allocated memory,
	// so we need a destructor that frees it.
	~MyClass();
	
	// Declare the assignment operator.
	MyClass &operator=(const MyClass &rhs);
	
private:
	// Member that holds the pointer to int.
	int *ptr;
};

// Implement the constructor.
MyClass::MyClass(int *p) {
	std::cout << "Entering regular constructor of object " 
	<< this << "\n";
	// This is the regular constructor, so we
	// just store the passed pointer in ptr.
	ptr = p;
	std::cout << "Leaving regular constructor of object " 
	<< this << "\n";
}

// Implement the copy constructor.
MyClass::MyClass(const MyClass &rhs) {
	std::cout << "Entering copy constructor of object " 
	<< this << "\n";
	std::cout << "rhs is object " << &rhs << "\n";

	// This is the copy constructor. To create a copy
	// of rhs, we just assign rhs to *this.
	*this = rhs;

	std::cout << "Leaving copy constructor of object " 
	<< this << "\n";
}

// Implement the destructor.
MyClass::~MyClass() {
	std::cout << "Entering destructor of object " 
	<< this << "\n";

	// Just delete ptr.
	delete ptr;

	std::cout << "Leaving destructor of object " 
	<< this << "\n";
}

// Implement the assignment operator.
MyClass &MyClass::operator=(const MyClass &rhs) {
	std::cout << "Entering assignment operator of object " 
	<< this << "\n";
	std::cout << "rhs is object " << &rhs << "\n";
	
	// Check if the user wrote something like 
	// "obj1 = obj1;". If so, do nothing.
	if (this != &rhs) {
	
		// Free the memory this->ptr points to.
		std::cout << "deleting this->ptr\n";
		delete ptr;
	
		// Create a copy of rhs.ptr
		std::cout << "allocate a new int and assign value of *rhs.ptr\n";
		ptr = new int;
		*ptr = *rhs.ptr;
		
	} else {	
		std::cout << "this and rhs are the same object, we're doing nothing!\n";
	}
	
	std::cout << "Leaving assignment operator of object " 
	<< this << "\n";

	// Return a reference to the object.
	return *this;
}


int main() {

	// Print a visual separator.
	std::cout << "---------------------------------------------\n";
	{ // Create a block of code for scoping purposes.
	
		// Create two objects obj1 and obj2.
		// Assign obj1 to obj2.
		MyClass obj1(new int(1));
		MyClass obj2(new int(2));
		obj2 = obj1;
		
	}
	
	std::cout << "---------------------------------------------\n";	
	
	{
		// Create an object obj3.
		MyClass obj3(new int(1));
		
		// Create an object obj4.
		// Initialize it with obj3.
		MyClass obj4 = obj3;
		
	}
	
	std::cout << "---------------------------------------------\n";
	
	{
	
		// Create an object obj5.
		// Try to assign the object to itself.
		MyClass obj5(new int(1));
		obj5 = obj5;
		
	}
	
	std::cout << "---------------------------------------------\n";
			
	std::cout << "Press Enter or Return to continue.";
	std::cin.get();
	return 0;
}
