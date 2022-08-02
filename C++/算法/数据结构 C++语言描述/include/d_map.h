#ifndef MINIMAP_CLASS
#define MINIMAP_CLASS

#include "d_pair.h"		// miniPair class
#include "d_stree.h"		// stree class

// implements a map containing key/value pairs.
// a map does not contain multiple copies of the same item.
// types T and Key must have a default constructor
template <typename Key, typename T>
class miniMap
{
	public:

		typedef stree<miniPair<const Key,T> >::iterator iterator;
		typedef stree<miniPair<const Key,T> >::const_iterator const_iterator;
			// miniMap iterators are simply stree iterators. an iterator cannot
			// change the key in a tree node, since the key attribute
			// of a miniPair object in the tree is const

		typedef miniPair<const Key, T> value_type;
			// for programmer convenience

		miniMap();
			// default constructor. create an empty map

		miniMap(value_type *first, value_type *last);
			// build a map whose key/value pairs are determined by pointer
			// values [first, last)

		bool empty() const;
			// is the map empty?

		int size() const;
			// return the number of elements in the map

		iterator find (const Key& key);
			// search for item in the map with the given key
			// and return an iterator pointing at it, or end()
			// if it is not found

		const_iterator find (const Key& key) const;
			// constant version of find()

		T& operator[] (const Key& key);
			// if no value is associated with key, create a new
			// map entry with the default value T() and return a
			// reference to the default value; otherwise,
			// return a reference to the value already associated
			// with the key

		int count(const Key& key) const;
			// returns 1 if an element with the key is in the map
			// and 0 otherwise

		miniPair<iterator,bool> insert(const value_type& kvpair);
			// if the map does not contain a key/value pair whose
			// key matches that of kvpair, insert a coy of kvpair
			// and return a miniPair object whose first element is an
			// iterator positioned at the new key/value pair and whose second
			// element is true. if the map already contains a key/value
			// pair whose key matches that of kvpair, return a miniPair
			// object whose first element is an iterator positioned at the
			// existing key/value pair and whose second element is false

		int erase(const Key& key);
			// erase the key/value pair with the specified key
			// from the map and return the number
			// of items erased (1 or 0)

		void erase(iterator pos);
			// erase the map key/value pair pointed by to pos

		void erase(iterator first, iterator last);
			// erase the key/value pairs in the range [first, last)

		iterator begin();
			// return an iterator pointing at the first member
			// in the map
		const_iterator begin() const;
			// constant version of begin()

		iterator end();
			// return an iterator pointing just past the last
			// member in the map
		const_iterator end() const;
			// constant version of end()

	private:
		// miniMap implemented using an stree of key-value pairs
		stree<miniPair<const Key,T> > t;
};

template <typename Key, typename T>
miniMap<Key,T>::miniMap()
{}

template <typename Key, typename T>
miniMap<Key,T>::miniMap(value_type *first, value_type *last):
		t(first, last)
{}

template <typename Key, typename T>
bool miniMap<Key,T>::empty() const
{
	return t.empty();
}

template <typename Key, typename T>
int miniMap<Key,T>::size() const
{
	return t.size();
}

template <typename Key, typename T>
miniMap<Key,T>::iterator miniMap<Key,T>::find (const Key& key)
{
	// pass a miniPair to stree find() that contains key as its
	// first member and T() as its second
	return t.find(value_type(key, T()));
}

template <typename Key, typename T>
miniMap<Key,T>::const_iterator miniMap<Key,T>::find (const Key& key) const
{
	// pass a miniPair to stree find() that contains key as its
	// first member and T() as its second
	return t.find(value_type(key, T()));
}

template <typename Key, typename T>
T& miniMap<Key,T>::operator[] (const Key& key)
{
	// build a miniPair object consisting of key
	// and the default value T()
	value_type tmp(key, T());
	// will point to a pair in the map
	iterator iter;

	// try to insert tmp into the map. the iterator
	// component of the pair returned by t.insert()
	// points at either the newly created key/value
	// pair or a pair already in the map. return a
	// reference to the value in the pair
	iter = t.insert(tmp).first;

	return (*iter).second;
}

template <typename Key, typename T>
int miniMap<Key,T>::count(const Key& key) const
{
	// pass a miniPair to stree count() that contains key as its
	// first member and T() as its second
	return t.count(value_type(key, T()));
}

template <typename Key, typename T>
miniPair<miniMap<Key,T>::iterator,bool>
miniMap<Key,T>::insert(const miniMap<Key,T>::value_type& kvpair)
{
	// t.insert() returns a pair<iterator,bool> object, not a
	// miniPair<iterator,bool> object
	pair<iterator, bool> p = t.insert(kvpair);

	// build and return a miniPair<iterator,bool> object
	return miniPair<iterator, bool>(p.first, p.second);
}

template <typename Key, typename T>
int miniMap<Key,T>::erase(const Key& key)
{
	// pass a miniPair to stree erase() that contains key as its
	// first member and T() as its second
	return t.erase(value_type(key, T()));
}

template <typename Key, typename T>
void miniMap<Key,T>::erase(iterator pos)
{
	t.erase(pos);
}

template <typename Key, typename T>
void miniMap<Key,T>::erase(iterator first, iterator last)
{
	t.erase(first,last);
}

template <typename Key, typename T>
miniMap<Key,T>::iterator miniMap<Key,T>::begin()
{
	return t.begin();
}

template <typename Key, typename T>
miniMap<Key,T>::iterator miniMap<Key,T>::end()
{
	return t.end();
}

template <typename Key, typename T>
miniMap<Key,T>::const_iterator miniMap<Key,T>::begin() const
{
	return t.begin();
}

template <typename Key, typename T>
miniMap<Key,T>::const_iterator miniMap<Key,T>::end() const
{
	return t.end();
}

#endif	// MINIMAP_CLASS
