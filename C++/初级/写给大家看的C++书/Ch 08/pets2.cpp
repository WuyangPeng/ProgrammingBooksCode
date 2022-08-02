// pets2.cpp - Script 8.3

// We need the iostream file in order
// to use cout and cin.
#include <iostream>

// We need the string file
// for the string functionality.
#include <string>

// Declare the Pet class.
class Pet {	
public:

	// Constructor:
	Pet(std::string theName);
	
	// Methods.
	void eat();
	void sleep();	
	
protected:
	std::string name;
	
};

// Declare a subclass Cat.
class Cat : public Pet {
public:

	// Constructor:
	Cat(std::string theName);
	
	void climb();
	
};

// Declare another inherited class.
class Dog : public Pet {
public:

	// Constructor:
	Dog(std::string theName);
	
	void bark();
	
};


// Define the functions:
Pet::Pet(std::string theName) {
	name = theName;
}

void Pet::sleep() {
	std::cout << name << " sleeps\n";
}

void Pet::eat() {
	std::cout << name << " eats\n";
}

// Cat constructor.
Cat::Cat(std::string theName) : Pet(theName) {
}

void Cat::climb() {
	std::cout << name << " climbs a tree\n";
}

// Dog constructor.
Dog::Dog(std::string theName) : Pet(theName) {
}

void Dog::bark() {
	std::cout << name << " goes 'woof-woof'\n";
}

// Start the main() function.
int main() {

	// Create a cat and a dog.
	Cat cat("Garfield");
	Dog dog("Odie");
		
	// Make them do things.
	cat.sleep();
	cat.eat();
	cat.climb();
		
	dog.sleep();
	dog.eat();
	dog.bark();
		
	// Complete the program.
	std::cout << "Press Enter or Return to continue.";
	std::cin.get();
	return 0;

} // End of main().
