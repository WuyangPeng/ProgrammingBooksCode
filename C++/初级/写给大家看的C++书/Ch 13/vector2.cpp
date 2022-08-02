// vector2.cpp - Script 13.5

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
	
	// Ask the vector to give us an iterator.
	std::vector<std::string>::iterator iter = names.begin();
	
	// Iterate over all the elements.
	while (iter != names.end()) {
		std::cout << *iter << "\n";
		++iter;
	}

	std::cout << "Press Enter or Return to continue.";
	std::cin.get();
	return 0;
}
