// pets4.cpp - Script 8.5

// We need the iostream file in order
// to use cout and cin.
#include <iostream>

// We need the string file
// for the string functionality.
#include <string>

// Declare the Pet class.
class Pet {	
public:
	Pet(std::string theName);
	void eat();
	void sleep();
	void play();
	
protected:
	std::string name;

};

// Declare a subclass Cat.
class Cat : public Pet {
public:
	Cat(std::string theName);
	void play();
	void climb();
};

// Declare another inherited class.
class Dog : public Pet {
public:
	Dog(std::string theName);
	void play();
	void bark();
	
	// Overloaded method:
	void bark(int count);
	
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

void Pet::play() {
	std::cout << name << " is playing\n";
}

// Cat constructor.
Cat::Cat(std::string theName) : Pet(theName) {
}

void Cat::climb() {
	std::cout << name << " climbs a tree\n";
}

// Override the method:
void Cat::play() {
	Pet::play();
	std::cout << name << " catches a ball of wool\n";
}

// Dog constructor.
Dog::Dog(std::string theName) : Pet(theName) {
}

void Dog::bark() {
	std::cout << name << " goes 'woof-woof'\n";
}

// Override the method:
void Dog::play() {
	Pet::play();
	std::cout << name << " chases cats\n";
}

// Overload the method:
void Dog::bark(int count) {
	std::cout << name << " barks " << count << " times\n";
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
	cat.play();
		
	dog.sleep();
	dog.eat();
	dog.bark();
	dog.play();
	dog.bark(15);
		
	std::cout << "Press Enter or Return to continue.";
	std::cin.get();
	return 0;
	
} // End of main().
