// petcount.cpp - Script 9.1

#include <iostream>

#include <string>

// Declare the class.
class Pet {	
public:

	// Constructor and destructor.
	Pet(std::string theName);
	~Pet();
	
	void eat();
	void sleep();	
	
	// Static method that will
	// return the current value of count:
	static int getCount();
	
protected:
	std::string name;
	
private:
	// count will store the number of pets.
	static int count;
};

// Declare the inherited classes.
class Cat : public Pet {
public:
	Cat(std::string theName);
	void climb();
};

class Dog : public Pet {
public:
	Dog(std::string theName);
	void bark();
};

// Allocate space for the static variable.
int Pet::count = 0;

// Define the methods.
Pet::Pet(std::string theName) {
	name = theName;
	
	// A new pet is being created so increment the counter.
	count++;
	
	std::cout << "Creating a pet named '" << name << "'\n";
}

Pet::~Pet() {
	// The destructor is called when the object ceases to exist
	// therefore, decrement the counter.
	count--;
	std::cout << "Deleting the pet named '" << name << "'\n";
}

int Pet::getCount() {
	return count;
}

void Pet::sleep() {
	std::cout << name << " sleeps\n";
}

void Pet::eat() {
	std::cout << name << " eats\n";
}

int Pet::getCount() {
    return count;
}

Cat::Cat(std::string theName) : Pet(theName) {
}

void Cat::climb() {
	std::cout << name << " climbs a tree\n";
}

Dog::Dog(std::string theName) : Pet(theName) {
}

void Dog::bark() {
	std::cout << name << " goes 'woof-woof'\n";
}


int main() {

	// Create two objects.
	Cat cat("Garfield");
	Dog dog("Odie");

	// Print the current pet count.
	std::cout << "You own " << Pet::getCount() << " pets\n";
    
    // Create another object
    // within a separate code block.
	{
		Cat anotherCat("Geraldine");		
		std::cout << "Now, you own " << anotherCat.getCount() << " pets\n";
	
		// anotherCat goes out of scope. 
		// The compiler will call anotherCat's destructor.
	}
    
    // Repeat the count.
	std::cout << "And you're back to " << Pet::getCount() << " pets\n";
	
	std::cout << "Press Enter or Return to continue.";
	std::cin.get();
	return 0;
}
