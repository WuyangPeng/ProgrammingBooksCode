// pets.cpp - Script 8.1

// We need the iostream file in order
// to use cout and cin.
#include <iostream>

// We need the string file
// for the string functionality.
#include <string>

// Declare the Pet class.
class Pet {	
public:

	// Methods:
	void eat();
	void sleep();	
	void setName(std::string theName);
	
	// Attribute:
	std::string name;
	
};

// Declare a subclass Cat.
// Cats can also climb.
class Cat : public Pet {
public:
	void climb();
};

// Declare another inherited class.
// Dogs can also bark.
class Dog : public Pet {
public:
	void bark();
};

// Define the functions:
void Pet::setName(std::string theName) {
	name = theName;
}

void Pet::sleep() {
	std::cout << name << " sleeps\n";
}

void Pet::eat() {
	std::cout << name << " eats\n";
}

void Cat::climb() {
	std::cout << name << " climbs a tree\n";
}

void Dog::bark() {
	std::cout << name << " goes 'woof-woof'\n";
}

// Start the main() function.
int main() {

	// Create a cat and a dog.
	Cat cat;
	Dog dog;
	
	// Set their names.
	cat.setName("Garfield");
	dog.setName("Odie");
		
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
