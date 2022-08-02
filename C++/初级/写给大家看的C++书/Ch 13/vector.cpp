// vector.cpp - Script 13.4

#include <iostream>

#include <string>

// We need the vector file
// for the vector functionality.
#include <vector>

int main() {

	// Create a vector of strings.
	std::vector<std::string> names;

	// Add some elements to the vector.
	names.push_back("Larry");
	names.push_back("Andi");
	
	// Iterate over every element in the vector.
	for (int i = 0; i < names.size(); i++) {
		std::cout << names[i] << "\n";
	}

	std::cout << "Press Enter or Return to continue.";
	std::cin.get();
	return 0;
}
