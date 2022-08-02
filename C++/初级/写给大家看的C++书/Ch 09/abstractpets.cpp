// abstractpets.cpp - Script 9.4

#include <iostream>

#include <string>

// Declare the class.
class Pet {	
public:
	Pet(std::string theName);
	
	virtual void eat();
	virtual void sleep();
	
	// By adding "= 0" we tell the compiler that
	// this is an abstract method.
	virtual void play() = 0;
	
protected:
	std::string name;
};

// Declare the inherited classes.
class Cat : public Pet {
public:
	Cat(std::string theName);
	
	// play() must be overridden,
	// if we want to create a Cat!
	void play();
	void climb();
};

class Dog : public Pet {
public:
	Dog(std::string theName);
	
	// play() must be overridden,
	// if we want to create a Dog!
	void play();
	void bark();
};


// Define the methods.
Pet::Pet(std::string theName) {
	name = theName;
}

void Pet::sleep() {
	std::cout << name << " sleeps\n";
}

void Pet::eat() {
	std::cout << name << " eats\n";
}

Cat::Cat(std::string theName) : Pet(theName) {
	// There's nothing to do here except
	// pass theName to Pet's constructor.
}

void Cat::climb() {
	std::cout << name << " climbs a tree\n";
}

void Cat::play() {
	std::cout << name << " catches a ball of wool\n";
}

Dog::Dog(std::string theName) : Pet(theName) {
	// There's nothing to do here except
	// pass theName to Pet's constructor.
}

void Dog::bark() {
	std::cout << name << " goes 'woof-woof'\n";
}

void Dog::play() {
	std::cout << name << " chases cats\n";
}

int main() {

	// Create two instances of Pet: a dog and a cat.
	// Store the addresses of these instances in
	// pointers to Pet. 
	Pet *cat = new Cat("Garfield");
	Pet *dog = new Dog("Odie");
	
	// Make the cat sleep, eat and play.
	cat->sleep();
	cat->eat();
	cat->play();
		
	// Make the dog sleep, eat and play.
	dog->sleep();
	dog->eat();
	dog->play();

	// We don't need the pets anymore, so
	// we have to delete them.
	delete cat;
	delete dog;

	std::cout << "Press Enter or Return to continue.";
	std::cin.get();
	return 0;
}
