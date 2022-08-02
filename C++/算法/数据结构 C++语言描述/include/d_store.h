#ifndef STORE_CLASS
#define STORE_CLASS

#include <iostream>

using namespace std;

template <typename T>
class store
{
	public:
		store(const T& item = T());   	// constructor

		// access and update functions
		T getValue() const;              // return value
		void setValue(const T& item); 	// update value

		// overloaded operator << as a friend
		friend ostream& operator<< (ostream& ostr, const store<T>& obj)
		{
			ostr << "Value = " << obj.value;
			return ostr;
		}
	private:
		// data stored by the object
		T value;
};

// use an initialization list to assign value
template <typename T>
store<T>::store(const T& item): value(item)
{}

// return the current value
template <typename T>
T store<T>::getValue() const
{
	return value;
}

//   assign the argument as the new data member value
template <typename T>
void store<T>::setValue(const T& item)
{
	value = item;
}

#endif	// STORE_CLASS
