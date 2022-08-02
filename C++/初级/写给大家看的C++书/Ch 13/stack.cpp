// stack.cpp - Script 13.2

#include <iostream>

#include <string>

// Create a class template.
template <class T>
class Stack {
public:
	// Constructor:
	Stack(unsigned int size = 100);
	
	// Destructor:
	~Stack();
	
	// Methods:
	void push(T value);
	T pop();
	
private:
	unsigned int size;
	unsigned int sp;
	T *data;

};

// Implement the constructor.
template <class T>
Stack<T>::Stack(unsigned int size /* = 100 */) {
	this->size = size;
	data = new T[size];
	sp = 0;
}

// Implement the destructor.		
template <class T>
Stack<T>::~Stack() {
	delete[] data;
}
	
// Implement the methods.
template <class T>
void Stack<T>::push(T value) {
	data[sp++] = value;
}
	
template <class T>
T Stack<T>::pop() {
	return data[--sp];
}


int main() {

	// Create a new stack.
	Stack<int> intStack(100);
	
	// Add some items.
	intStack.push(1);
	intStack.push(2);
	intStack.push(3);
	
	// Retrieve some items.
	std::cout << "intStack.pop() returned " << intStack.pop() << "\n";
	std::cout << "intStack.pop() returned " << intStack.pop() << "\n";
	std::cout << "intStack.pop() returned " << intStack.pop() << "\n";

	std::cout << "Press Enter or Return to continue.";
	std::cin.get();
	return 0;
}
