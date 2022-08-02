// stack2.cpp - Script 13.3

#include <iostream>

// We need the string file
// for the string functionality.
#include <string>

// Create a class template.
template <class T>
class Stack {
public:

	// Constructor:
	Stack(unsigned int size = 100) {
		this->size = size;
		data = new T[size];
		sp = 0;
	}
		
	// Destructor:
	~Stack() {
		delete[] data;
	}

	// Methods:	
	void push(T value) {
		data[sp++] = value;
	}
	
	T pop() {
		return data[--sp];
	}
	
private:
	unsigned int size;
	unsigned int sp;
	T *data;
};

int main() {

	// Create a new stack.
	Stack<float> intStack(100);
	
	// Add some items.
	intStack.push(3.14);
	intStack.push(2.7841);
	intStack.push(56.0);
	
	// Retrieve some items.
	std::cout << "intStack.pop() returned " << intStack.pop() << "\n";
	std::cout << "intStack.pop() returned " << intStack.pop() << "\n";
	std::cout << "intStack.pop() returned " << intStack.pop() << "\n";

	std::cout << "Press Enter or Return to continue.";
	std::cin.get();
	return 0;
}
