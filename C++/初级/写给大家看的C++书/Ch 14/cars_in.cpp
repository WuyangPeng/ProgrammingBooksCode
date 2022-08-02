// cars_in.cpp - Script 14.4

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
	std::ofstream fileOutput("cars.dat", (std::ios::app) | (std::ios::binary));
	
	// Check that the file was opened.
	if (fileOutput.is_open()) {
	
		// Create a struct of type car.
		car aCar;
		
		// Create two strings.
		std::string make, model;
	
		// Get the input.
		std::cout << "Enter the car's make, model, and year: [make model YYYY] \n(Enter 'q q 0' to quit.)\n";
		std::cin >> make >> model >> aCar.year;
		std::cin.ignore(100, '\n');
		
		// Validate and store.
		while (make != "q") {
		
			// Copy make and model to the structure.
			strncpy(aCar.make, make.c_str(), 20);
			strncpy(aCar.model, model.c_str(), 20);
	
			fileOutput.write(reinterpret_cast<char *>(&aCar), sizeof(aCar));
			std::cout << "The data has been written.\n\n";

			// Reprompt.
			std::cout << "Enter the car's make, model, and year: [make model YYYY] \n(Enter 'q q 0' to quit.)\n";
			std::cin >> make >> model >> aCar.year;
			std::cin.ignore(100, '\n');
			
		} // End of the while loop.

		// Close the stream.
		fileOutput.close();

	} else { // Couldn't open the file.
		std::cout << "The file could not be opened!\n";
		return 1; // Indicates a problem occurred.
		// Or use exceptions.
	}
	
	std::cout << "Press Enter or Return to continue.\n";
	std::cin.get();
	return 0;

} // End of the main() function.
