// books.cpp - Script 6.6

#include <iostream>

// Define the structure.
struct book {

	// Define the members.
	std::string title;
	std::string author;
	unsigned int year;
	
}; // Don't forget the semi-colon!
	
int main() {

	// Create a new variable.
	book book1;
	
	// Prompt the user for the title.
	std::cout << "Enter the book's title:\n";
	std::getline(std::cin, book1.title);

	// Prompt the user for the author.
	std::cout << "Enter the book's author:\n";
	std::getline(std::cin, book1.author);

	// Prompt the user for the publication year.
	std::cout << "Enter the book's publication year: ";
	std::cin >> book1.year;
	
	// Repeat the input.
	std::cout << "\nThe following information has been received..."
	<< "\nTitle: " << book1.title
	<< "\nAuthor: " << book1.author
	<< "\nYear: " << book1.year << "\n\n";

	// Discard any extraneous input.
	std::cin.ignore(100, '\n');
	std::cout << "Press Enter or Return to continue.\n";
	std::cin.get();
	return 0;
	
} // End of the main() function.
