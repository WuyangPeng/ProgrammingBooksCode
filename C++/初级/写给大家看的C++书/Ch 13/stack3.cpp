// stack3.cpp - Script 13.4

// We need the iostream file in order
// to use cout and cin.
#include <iostream>

// We need the string file
// for the string functionality.
#include <string>

template <class T, unsigned int SIZE>
class Stack {
public:
	Stack() {
		this->size = SIZE;
		data = new T[size];
		sp = 0;
	}
		
	~Stack() {
		delete[] data;
	}
	
	void push(T value) {
		data[sp++] = value;
	}
	
	T pop() {
		return data[--sp];
	}
	
private:
	unsigned int size;
	unsigned int sp;
	T* data;

};

int main() {
	Stack<int, 100> intStack;
	
	intStack.push(1);
	intStack.push(2);
	intStack.push(3);
	
	std::cout << "intStack.pop() returned " << intStack.pop() << "\n";
	std::cout << "intStack.pop() returned " << intStack.pop() << "\n";
	std::cout << "intStack.pop() returned " << intStack.pop() << "\n";

	std::cout << "Press Enter or Return to continue.";
	std::cin.get();
	return 0;
}
