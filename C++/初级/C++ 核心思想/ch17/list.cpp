#include <string>
#include <iostream>
#include <cassert>

using namespace std;

/* forward declarations */
template<typename T> class List;
template<typename T> class Iterator;

/**
   A class to hold the nodes of the linked list.
*/
template<typename T>
class Node
{
public:
   /**
      Constructs a node for a given data value.
      @param s the data to store in this node
   */
   Node(T s);
private:
   T data;
   Node<T>* previous;
   Node<T>* next;
friend class List<T>;
friend class Iterator<T>;
};
   
/**
   An iterator denotes a position in the list or
   past the end of the list.
*/
template<typename T>
class Iterator
{
public:
   /**
      Constructs an iterator that is not attached to any list.
   */
   Iterator();
   /** 
       Looks up the value at a position.
       @return the value of the Node to which the iterator 
       points
   */
   T operator*() const;
   /**
      Advances the iterator to the next position.
   */
   void operator++(int dummy);
   /**
      Moves the iterator to the previous position.
   */
   void operator--(int dummy);
   /**
      Compares two iterators.
      @param b the iterator to compare with this iterator
      @return true if this iterator and b are equal
   */
   bool operator==(Iterator<T> b) const;
   /**
      Compares two iterators.
      @param b the iterator to compare with this iterator
      @return true if this iterator and b are not equal
   */
   bool operator!=(Iterator<T> b) const;
private:
   Node<T>* position;
   Node<T>* last;
friend class List<T>;
};

/**
   A linked list of values of a given type.
   @param T the type of the list values
*/
template<typename T>
class List
{
public:
   /**
      Constructs an empty list.
   */
   List();
   /**
      Constructs a list as a copy of another list.
      @param b the list to copy
   */
   List(const List<T>& b);
   /**
      Deletes all nodes of this list.
   */
   ~List();
   /**
      Assigns another list to this list.
      @param b the list to assign
      @return a reference to this list
   */
   List<T>& operator=(const List<T>& b);

   /**
      Appends an element to the list.
      @param s the value to append
   */
   void push_back(T s);
   /**
      Inserts an element into the list.
      @param iter the position before which to insert
      @param s the value to append
   */
   void insert(Iterator<T> iter, T s);
   /**
      Removes an element from the list.
      @param i the position to remove
      @return an iterator pointing to the element after the
      erased element
   */
   Iterator<T> erase(Iterator<T> i);
   /**
      Gets the beginning position of the list.
      @return an iterator pointing to the beginning of the list
   */
   Iterator<T> begin();
   /**
      Gets the past-the-end position of the list.
      @return an iterator pointing past the end of the list
   */
   Iterator<T> end();

private:
   /**
      Copies another list to this list.
      @param b the list to copy
   */
   void copy(const List<T>& b);
   /**
      Deletes all nodes of this list.
   */
   void free();
   
   Node<T>* first;
   Node<T>* last;
};

template<typename T>
List<T>::List()
{  
   first = NULL;
   last = NULL;
}

template<typename T>
List<T>::~List()
{  
   free();
}

template<typename T>
List<T>::List(const List<T>& b)
{  
   first = NULL;
   last = NULL;
   copy(b);
}

template<typename T>
List<T>& List<T>::operator=(const List<T>& b)
{  
   if (this != &b)
   {
      free();
      copy(b);
   }
   return *this;
}


template<typename T>
void List<T>::push_back(T s)
{  
   Node<T>* newnode = new Node<T>(s);
   if (last == NULL) /* list is empty */
   {  
      first = newnode;
      last = newnode;
   }
   else
   {  
      newnode->previous = last;
      last->next = newnode;
      last = newnode;
   }
}

template<typename T>
void List<T>::insert(Iterator<T> iter, T s)
{  
   if (iter.position == NULL)
   {  
      push_back(s);
      return;
   }

   Node<T>* after = iter.position;
   Node<T>* before = after->previous;
   Node<T>* newnode = new Node<T>(s);
   newnode->previous = before;
   newnode->next = after;
   after->previous = newnode;
   if (before == NULL) /* insert at beginning */
      first = newnode;
   else
      before->next = newnode;
}

template<typename T>
Iterator<T> List<T>::erase(Iterator<T> i)
{  
   Iterator<T> iter = i;
   assert(iter.position != NULL);
   Node<T>* remove = iter.position;
   Node<T>* before = remove->previous;
   Node<T>* after = remove->next;
   if (remove == first)
      first = after;
   else
      before->next = after;
   if (remove == last)
      last = before;
   else
      after->previous = before;
   iter.position = after;
   delete remove;
   return iter;
}

template<typename T>
Iterator<T> List<T>::begin()
{  
   Iterator<T> iter;
   iter.position = first;
   iter.last = last;
   return iter;
}

template<typename T>
Iterator<T> List<T>::end()
{  
   Iterator<T> iter;
   iter.position = NULL;
   iter.last = last;
   return iter;
}

template<typename T>
Iterator<T>::Iterator()
{  
   position = NULL;
   last = NULL;
}

template<typename T>
T Iterator<T>::operator*() const
{  
   assert(position != NULL);
   return position->data;
}

template<typename T>
void Iterator<T>::operator++(int dummy)
{  
   assert(position != NULL);
   position = position->next;
}

template<typename T>
void Iterator<T>::operator--(int dummy)
{  
   if (position == NULL)
      position = last;
   else 
      position = position->previous;
   assert(position != NULL);
}

template<typename T>
bool Iterator<T>::operator==(Iterator<T> b) const
{  
   return position == b.position;
}

template<typename T>
bool Iterator<T>::operator!=(Iterator<T> b) const
{  
   return position != b.position;
}

template<typename T>
Node<T>::Node(T s)
{  
   data = s;
   previous = NULL;
   next = NULL;
}

template<typename T>
void List<T>::copy(const List<T>& b)
{
   for (Iterator<T> p = b.begin(); p != b.end(); p++)
      push_back(*p);
}

template<typename T>
void List<T>::free()
{
   while (begin() != end())
      erase(begin());
}

int main()
{  
   List<string> staff;

   staff.push_back("Cracker, Carl");
   staff.push_back("Hacker, Harry");
   staff.push_back("Lam, Larry");
   staff.push_back("Sandman, Susan");

   /* add a value in fourth place */

   Iterator<string> pos;
   pos = staff.begin();
   pos++;
   pos++;
   pos++;

   staff.insert(pos, "Reindeer, Rudolf");

   /* remove the value in second place */

   pos = staff.begin();
   pos++;

   staff.erase(pos);

   /* print all values */

   for (pos = staff.begin(); pos != staff.end(); pos++)
      cout << *pos << "\n";

   return 0;
}
