#if !defined (AUTOVECTOR_H)
#define AUTOVECTOR_H
// Bartosz Milewski (c) 2000
#include <memory>
#include <cassert>

template<class T>
class const_auto_iterator: public
	std::iterator<std::forward_iterator_tag, T const *>
{
public:
	const_auto_iterator () : _pp (0) {}
	const_auto_iterator (std::auto_ptr<T> const * p) : _pp (p) {}
	bool operator != (const_auto_iterator<T> const & it) const 
		{ return it._pp != _pp; }
	bool operator == (const_auto_iterator<T> const & it) const 
		{ return it._pp == _pp; }
	const_auto_iterator operator++ (int) { return _pp++; }
	const_auto_iterator operator++ () { return ++_pp; }
	T const * operator * () { return _pp->get (); }
	T const * operator-> () { return _pp->get (); }
private:
	std::auto_ptr<T> const * _pp;
};

template <class T> 
class auto_vector
{
public:
	typedef std::size_t size_t;
	typedef const_auto_iterator<T> const_iterator;
public:
	explicit auto_vector (size_t capacity = 0)
		: _capacity (0), _end (0), _arr (0)
	{
		if (capacity != 0)
		{
			_arr = new std::auto_ptr<T> [capacity];
			_capacity = capacity;
		}
	}
	~auto_vector () { delete []_arr; }
	size_t size () const { return _end; }
	T const * operator [] (size_t i) const
	{
		return _arr [i].get (); 
	}
	T * operator [] (size_t i) 
	{
		return _arr [i].get (); 
	}
	void assign (size_t i, std::auto_ptr<T> & p)
	{
		assert (i < _end);
		_arr [i] = p;
	}
	void assign_direct (size_t i, T * p)
	{
		assert (i < _end);
		_arr [i].reset (ptr);
	}
	void push_back (std::auto_ptr<T> & p)
	{
		assert (_end <= _capacity);
		if (_end == _capacity)
			grow (_end + 1);
		_arr [_end] = p;
		_end++;
	}
	std::auto_ptr<T> pop_back ()
	{
		assert (_end != 0);
		return _arr [--_end];
	}
	const_iterator begin () const { return _arr; }
	const_iterator end () const { return _arr + _end; }
private:
	void grow (size_t reqCapacity);

	std::auto_ptr<T>  * _arr;
	size_t				_capacity;
	size_t				_end;
};

template <class T>
void auto_vector<T>::grow (size_t reqCapacity)
{
	size_t newCapacity = 2 * _capacity;
	if (reqCapacity > newCapacity)
		newCapacity = reqCapacity;
	// allocate new array
	std::auto_ptr<T> * arrNew = new std::auto_ptr<T> [newCapacity];
	// transfer all entries
	for (size_t i = 0; i < _end; ++i)
		arrNew [i] = _arr [i];
	_capacity = newCapacity;
	// free old memory
	delete []_arr;
	// substitute new array for old array
	_arr = arrNew;
}
#endif
