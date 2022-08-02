#ifndef PTRLIST_H
#define PTRLIST_H

#include <list>

template <class T> class PtrList;
template <> class PtrList<void> {
  public:
	void append( void *elem )
		{ impl_.push_back( elem ); }
    // . . . 
  private:
	std::list<void *> impl_;
};
template <class T>
class PtrList : private PtrList<void> {
  public:
    PtrList()
    	{}
    ~PtrList()
    	{}
    void append( T *newElem );
    // . . . 
};

template <typename T>
inline void
PtrList<T>::append( T *newElem )
	{ PtrList<void>::append( newElem ); }

#endif
