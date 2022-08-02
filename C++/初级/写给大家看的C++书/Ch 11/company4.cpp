// company4.cpp - Script 11.7

#include <iostream>

#include <string>

// Declare a class Company.
class Company {
public:
	Company(std::string name);
	virtual void printInfo();
	
protected:
	std::string name;
};

// Declare a class Publisher.
// Publisher inherits from Company.
class Publisher : public Company {
public:
	Publisher(std::string name, int booksPublished);	
	virtual void printInfo();
	virtual int getNumberOfPublishedBooks();
	
private:
	int booksPublished;
};

// Implement the methods.
Company::Company(std::string name) {
	this->name = name;
}

void Company::printInfo() {
	std::cout << "This is a company called '" << name << "'.\n";
}

Publisher::Publisher(std::string name, int booksPublished) : Company(name) {
	this->booksPublished = booksPublished;
}

void Publisher::printInfo() {
	std::cout << "This is a publisher called '" << name << "' that has published " << booksPublished << " books.\n";
}

int Publisher::getNumberOfPublishedBooks() {
	return booksPublished;
}

// Function prototype:
// Function returns a pointer of type Company.
Company *createCompany(std::string name, int booksPublished = -1);


int main() {

	// Create a company in memory
	// by calling the createCompany() function.
	Company *company = createCompany("Peachpit", 99999);
	
	// Cast the pointer to a pointer to Publisher.
	Publisher *publisher = dynamic_cast<Publisher*>(company);
	
	// Check if the cast was successful.
	if (publisher != NULL) {
		// Print the number of books.
		std::cout << "This publisher has published " << publisher->getNumberOfPublishedBooks() << " books.\n";
	} else { // Not successful
		std::cout << "company does not point to a Publisher!\n";
	}
			
	// Perform cleanup.
	delete company;
	company = NULL;
	
	std::cout << "Press Enter or Return to continue.";
	std::cin.get();
	return 0;
}

// Function definition.
Company *createCompany(std::string name, int booksPublished /* = -1 */) {

	// Use the number of booksPublished
	// to determine if this should be a
	// Company or a Publisher.
	if (booksPublished < 0) {
		return new Company(name);
	}else {
		return new Publisher(name, booksPublished);
	}

}
