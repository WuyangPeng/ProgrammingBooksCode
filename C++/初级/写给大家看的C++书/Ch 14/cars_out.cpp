// cars_out.cpp - Script 14.5

#include <iostream>
#include <string>

// We need the fstream file in order
// to work with files.
#include <fstream>

// Define the structure.
struct car {

	char make[20];
	char model[20];
	unsigned short year;
	
}; // Don't forget the semi-colon!

int main() {

	// Define a file object.
	std::ifstream fileInput("cars.dat", std::ios::binary);
	
	// Check that the file was opened.
	if (fileInput.is_open()) {
	
		// Create a struct of type car.
		car aCar;
	
		// Print a header.
		std::cout << "The following cars are listed in the database:\nMake\tModel\tYear\n";
	
		// Validate and store.
		while (fileInput.read(reinterpret_cast<char *>(&aCar), sizeof(aCar) )) {		

			std::cout << aCar.make
			<< "\t" << aCar.model
			<< "\t" << aCar.year << "\n";
			
		} // End of the while loop.

		// Close the stream.
		fileInput.close();

	} else { // Couldn't open the file.
		std::cout << "The file could not be opened!\n";
		return 1; // Indicates a problem occurred.
		// Or use exceptions.
	}
	
	std::cout << "Press Enter or Return to continue.\n";
	std::cin.get();
	return 0;

} // End of the main() function.
