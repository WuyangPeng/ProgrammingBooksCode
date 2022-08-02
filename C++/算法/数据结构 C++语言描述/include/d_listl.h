#ifndef LIST_FUNCTIONS
#define LIST_FUNCTIONS

#include <list>

using namespace std;

// insert item into an ordered list
template <typename T>
void insertOrder(list<T>& orderedList, const T& item);

// remove all duplicate values the list
template <typename T>
void removeDuplicates(list<T>& aList);

template <typename T>
void splice(list<T>& dest, typename list<T>::iterator pos,
				const list<T>& source);

// *** function implementations ***

template <typename T>
void insertOrder(list<T>& orderedList, const T& item)
{
   // curr starts at first list element, stop marks end
   list<T>::iterator curr = orderedList.begin(),
                     stop = orderedList.end();

   // find the insertion point, which may be at end of list
   while ((curr != stop) && (*curr < item))
      curr++;

   // do the insertion using insert()
   orderedList.insert(curr, item);
}

template <typename T>
void removeDuplicates(list<T>& aList)
{
	// current data value
   T currValue;
   // the two list iterators we use
   list<T>::iterator curr, p;
    
   // start at the front of the list
   curr = aList.begin();
    
   // cycle through the list
   while(curr != aList.end())
   {	
		// record the current list data value
      currValue = *curr;

      // set p one element to the right of curr
      p = curr;
      p++;

      // move forward until end of list, removing
      // all occurrences of currValue
      while(p != aList.end())
         if (*p == currValue)
				// erase current element and advance p to next
 				aList.erase(p++);
         else
            p++;		// move to the next list element
      // duplicates of currValue removed. move to the next
      // data value and repeat the process
      curr++;
   }
}

template <typename T>
void splice(list<T>& dest, typename list<T>::iterator pos,
				const list<T>& source)
{
	list<T>::const_iterator sourceIter;

	sourceIter = source.begin();

	// insert each element of source before the
	// position pos
	while (sourceIter!= source.end())
	{
		dest.insert(pos, *sourceIter);
		sourceIter++;
	}
}


#endif	// LIST_FUNCTIONS
