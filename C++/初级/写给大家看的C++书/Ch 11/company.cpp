// company.cpp - Script 11.2

#include <iostream>

#include <string>

// Declare a class Company.
class Company {
public:

	// Constructor:
	Company(std::string name);

	// Print some info regarding this company:
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


int main() {

	// Create a company in memory.
	Company *company = new Company("Pearson");
	
	// Print info about the company.
	company->printInfo();
	
	// Delete the company.
	delete company;
	company = NULL;
	
	// Create a publisher.
	company = new Publisher("Peachpit", 99999);
	
	// Print info about the company.
	company->printInfo();
	
	// Delete the company.
	delete company;
	company = NULL;
	
	std::cout << "Press Enter or Return to continue.";
	std::cin.get();
	return 0;
}
