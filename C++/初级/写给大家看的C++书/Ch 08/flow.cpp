// flow.cpp - Script 8.2

// We need the iostream file in order
// to use cout and cin.
#include <iostream>

// We need the string file
// for the string functionality.
#include <string>

// Declare the BaseClass.
class BaseClass {	
public:
	
	// Constructor.
	BaseClass();
	
	// Destructor.
	~BaseClass();
	
	// Simple method.
	void doSomething();
	
};

// Declare a SubClass that
// inherits BaseClass.
class SubClass : public BaseClass {	
public:
	
	// Constructor.
	SubClass();
	
	// Destructor.
	~SubClass();

};

// Define the functions.
BaseClass::BaseClass() {
	std::cout << "Entering BaseClass::BaseClass()\n";
	
	// Do some initialization here.
	
	std::cout << "Leaving BaseClass::BaseClass()\n\n";	
}

BaseClass::~BaseClass() {
	std::cout << "Entering BaseClass::~BaseClass()\n";
	
	// Do some cleanup here.
	
	std::cout << "Leaving BaseClass::~BaseClass()\n\n";	
}

void BaseClass::doSomething() {
	std::cout << "Entering BaseClass::doSomething()\n";
	
	// Do something here.
	
	std::cout << "Leaving BaseClass::doSomething()\n\n";	
}


SubClass::SubClass() {
	std::cout << "Entering SubClass::SubClass()\n";
	
	// Do some initialization here.
	
	std::cout << "Leaving SubClass::SubClass()\n\n";	
}

SubClass::~SubClass() {
	std::cout << "Entering SubClass::~SubClass()\n";
	
	// Do some cleanup here.
	
	std::cout << "Leaving SubClass::~SubClass()\n\n";	
}

// Start the main() function.
int main() {

	// Indicate where we're at.
	std::cout << "Creating an instance of class SubClass...\n";
	
	// Create the object.
	SubClass subclass;
		
	// Call the method.
	std::cout << "Calling subclass.doSomething()...\n";
	subclass.doSomething();
	
	// End of the program.
	std::cout << "This is the second-to-last statement in main().\n";
	std::cout << "Press Enter or Return to continue.";
	std::cin.get();
	return 0;
}
