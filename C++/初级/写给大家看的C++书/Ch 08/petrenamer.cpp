// petrenamer.cpp - Script 8.6

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
	
protected:
	std::string name;
	
	// Make a friend:
	friend class PetRenamer;
};

// Declare a subclass Cat.
class Cat : public Pet {
public:
	Cat(std::string theName);
	void climb();
};

// Declare another inherited class.
class Dog : public Pet {
public:
	Dog(std::string theName);	
	void bark();
};

// Make the PetRenamer class.
// This class does NOT inherit from Pet.
class PetRenamer {
public:

	// Constructor:
	PetRenamer(std::string theName);

	// Rename method.
	// Requires a pointer to the pet
	// and the new pet name.
	void rename(Pet *pet, std::string newName);
	
private: 
	std::string name;
};

// PetRenamer constructor:
PetRenamer::PetRenamer(std::string theName) {
	name = theName;
}

// PetRenamer rename() function:
void PetRenamer::rename(Pet *pet, std::string newName) {

	// Introduce what's happening.
	std::cout << name << " is going to rename ";
	
	// Print the pet's current name.
	std::cout << pet->name;
	
	// Print the pet's new name.
	std::cout << " to " << newName << "\n";
	
	// Change the pet's name.
	pet->name = newName;
	
}


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
	
	// Create a friend.
	PetRenamer petRenamer("Jon");
		
	// Make them do things.
	cat.sleep();
	
	// Rename the cat.
	petRenamer.rename(&cat, "Geraldine");
	cat.eat();
	cat.climb();
		
	dog.sleep();
	dog.eat();
	
	// Rename the dog.
	petRenamer.rename(&dog, "Pluto");
	
	dog.bark();
		
	// Complete the program.
	std::cout << "Press Enter or Return to continue.";
	std::cin.get();
	return 0;
	
} // End of main().
