#ifndef ORDEREDLIST_CLASS
#define ORDEREDLIST_CLASS

#include <list>

using namespace std;

template <typename T>
class orderedList: public list<T>
{
   public:
     	// constructor. implemented with inline code
      orderedList(): list<T>() 
		{}

		orderedList(T *first, T *last);
			// constructor. build an ordered list whose data comes from the
			// pointer range [first, last)

      void insert(const T& item);
			// insert item into the ordered list
   private:
      // disallow automatic access to insert functions in base class
      void push_front(const T& item);
      void push_back(const T& item);
      void insert(list<T>::iterator& pos, const T& item);
};


template <typename T>
orderedList<T>::orderedList(T *first, T *last)
{
	T *curr = first;

	// use insert() to create the ordered list
	while (curr != last)
		insert(*curr++);
}

template <typename T>
void orderedList<T>::insert(const T& item)
{
   // curr starts at first list element, stop marks end. the begin()
   // and end() functions belong to the base class
   list<T>::iterator curr = begin(), stop = end();

   // find the insertion point, which may be at end of list
   while ((curr != stop) && (*curr < item))
      curr++;

   // do the insertion using base class insert() function
   list<T>::insert(curr, item);
}

#endif   // ORDEREDLIST_CLASS
