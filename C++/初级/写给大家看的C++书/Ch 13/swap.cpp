// swap.cpp - Script 13.1

#include <iostream>

#include <string>

// Create the function template.
// Function swaps the values 
// of two variables.
template <class T>
void swap(T &a, T &b) {
    T tmp = a;
    a = b;
    b = tmp;
}

int main() {

    // Swap integers.
    int i1 = 100;
    int i2 = 200;
    std::cout << "before swap: i1 == " << i1 << ", i2 == " << i2 << "\n";
    swap(i1,i2);
    std::cout << "after swap: i1 == " << i1 << ", i2 == " << i2 << "\n";
    
    // Swap strings.
    std::string s1 = "Larry";
    std::string s2 = "Andi";
    std::cout << "before swap: s1 == " << s1 << ", s2 == " << s2 << "\n";
    swap(s1,s2);
    std::cout << "after swap: s1 == " << s1 << ", s2 == " << s2 << "\n";
    
	std::cout << "Press Enter or Return to continue.";
	std::cin.get();
	return 0;
}
