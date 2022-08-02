// random.cpp - Script 14.6

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
	
		// Need to determine how many items
		// are in the file.
		unsigned long start, end;
		
		// Get the initial position.
		start = fileInput.tellg();
		
		// Move to the end and get that position.
		fileInput.seekg(0, std::ios::end);
		end = fileInput.tellg();
		
		// Calculate the number of items.
		// end position - start position = total bytes
		// divide this by the size of a single structure
		unsigned short num = (end - start)/(sizeof(car));
		
		// Get a random number from the user.
		unsigned short input;
		do {
			std::cout << "Enter a random number between 0 and "
			<< (num - 1) << ": ";
			std::cin >> input;
			std::cin.ignore(100, '\n');
		} while (input >= num); // input must be smaller than num
	
		// Print a header.
		std::cout << "The randomly selected car is: ";
		
		// Move the pointer to the choosen location.
		fileInput.seekg((sizeof(car) * input));
		
		// Read in the item.
		car aCar;
		fileInput.read(reinterpret_cast<char *>(&aCar), sizeof(aCar) );
		
		// Print the selected item.
		std::cout << aCar.year
		<< " " << aCar.make
		<< " " << aCar.model << "\n";
			
		// Close the stream.
		fileInput.close();

	} else { // Couldn't open the file.
		std::cout << "The file could not be opened!\n";
		return 1; // Indicates a problem occurred.
		// Or use exceptions.
	}
	
	std::cin.ignore(100, '\n');
	std::cout << "Press Enter or Return to continue.\n";
	std::cin.get();
	return 0;

} // End of the main() function.
