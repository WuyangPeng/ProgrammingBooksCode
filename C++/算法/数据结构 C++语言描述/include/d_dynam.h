#ifndef DYNAMIC_CLASS
#define DYNAMIC_CLASS

#include <iostream>

using namespace std;

template <typename T>
class dynamicClass
{
	public:
		// constructors
		dynamicClass(const T& m1, const T& m2);
		dynamicClass(const dynamicClass<T>& obj);
        
		// destructor
		~dynamicClass();

		// assignment operator
		dynamicClass<T>& operator= (const dynamicClass<T>& rhs);

	private:
		// data of type T and a pointer to data of type T
		T member1;
		T *member2;
};

// constructor with arguments to initialize the data members.
// use constructor initialization list to give member1 the
// value m1
template <typename T>
dynamicClass<T>::dynamicClass(const T& m1, const T& m2):
	member1(m1)
{
	// allocate dynamic memory. initialize it with value m2
	member2 = new T(m2);
	cout << "Constructor: " << member1 << '/'
		  << *member2 << endl;
}


// copy constructor. initialize new object to have the
// same data as obj. use constructor initialization
// list to give member1 the value obj.member1
template <typename T>
dynamicClass<T>::dynamicClass(const dynamicClass<T>& obj):
	member1(obj.member1)
{
	// allocate dynamic memory and initialize it with
	// value *obj.member2.
	member2 = new T(*obj.member2); 
	cout << "Copy Constructor:  " << member1
		  << '/' << *member2 << endl;
}

// destructor. deallocates the dynamic memory allocated
// by the constructor
template <typename T>
dynamicClass<T>::~dynamicClass()
{
	cout << "Destructor: " << member1 << '/'
		  << *member2 << endl;
	delete member2;                 
}

// overloaded assignment operator. returns a reference to 
// current object
template <typename T>
dynamicClass<T>& dynamicClass<T>::operator=
               (const dynamicClass<T>& rhs)
{
	// copy static data member from rhs to the current object
	member1 = rhs.member1;
	// contents of dynamic memory must be same as that of rhs
	*member2 = *rhs.member2;        
	cout << "Assignment Operator: "<< member1 << '/'
		  << *member2 << endl;

	return *this;                   
}

#endif  // DYNAMIC_CLASS
