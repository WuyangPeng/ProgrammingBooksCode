#ifndef RAWSTORAGE_H
#define RAWSTORAGE_H

#include <iterator>
#include <memory>

template <class Out, class T>
class raw_storage_iterator
    : public std::iterator<std::output_iterator_tag,void,void,void,void> {
  public:
    raw_storage_iterator& operator =( const T& element );
    explicit raw_storage_iterator( Out cur )
    	: cur_(cur) {}
    raw_storage_iterator& operator *()
    	{ return *this; }
    raw_storage_iterator& operator ++()
    	{ ++cur_; return *this; }
    raw_storage_iterator operator ++( int ) {
    	raw_storage_iterator tmp( *this );
    	++*this;
    	return tmp;
    }

  protected:
    Out cur_;
};

template <class Out, class T>
raw_storage_iterator<Out, T> &
raw_storage_iterator<Out,T>::operator =( const T &val ) {
    T *elem = &*cur_; // get a ptr to element
    new ( elem ) T(val); // placement and copy constructor
    return *this;
}

#endif
