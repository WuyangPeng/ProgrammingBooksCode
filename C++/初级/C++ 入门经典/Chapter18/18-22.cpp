#include <iostream>
#include <array>

using std::cout;
using std::endl;
using std::array;

int main()
{
	// The array is allocated to hold six integers.
	// The first three are set to 10, 20, and 30 while
	// the remainder are set to 0.
	array<int,6> a = {10, 20, 30};

	cout << "The size of the array: " << a.size() << endl;
	cout << "The element at index 1: " << a[1] << endl;
	cout << "Setting a[4] to 100" << endl;
	a[4] = 100;
	cout << "Outputting all elements of the array: " << endl;
	for (int element : a)
		cout << " " << element << endl;
}
