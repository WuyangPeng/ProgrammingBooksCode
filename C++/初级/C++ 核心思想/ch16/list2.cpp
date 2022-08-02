#include <string>
#include <iostream>
#include <cassert>

using namespace std;

class List;
class Iterator;

class Node
{
public:
   /* 
      Constructs a node with a given data value.
      @param s the data to store in this node
   */
   Node(string s);
private:
   string data;
   Node* previous;
   Node* next;
friend class List;
friend class Iterator;
};

class List
{
public:
   /**
      Constructs an empty list;
   */
   List();
   /**
      Appends an element to the list.
      @param s the value to append
   */
   void push_back(string s);
   /**
      Inserts an element into the list.
      @param iter the position before which to insert
      @param s the value to append
   */
   void insert(Iterator iter, string s);
   /**
      Removes an element from the list.
      @param i the position to remove
      @return an iterator pointing to the element after the
      erased element
   */
   Iterator erase(Iterator i);
   /**
      Gets the beginning position of the list.
      @return an iterator pointing to the beginning of the list
   */
   Iterator begin();
   /**
      Gets the past-the-end position of the list.
      @return an iterator pointing past the end of the list
   */
   Iterator end();
private:
   Node* first;
   Node* last;
};

class Iterator
{
public:
   /**
      Constructs an iterator that does not point into any list.
   */
   Iterator();
   /**  
      Looks up the value at a position.
      @return the value of the node to which the iterator points
   */
   string get() const;
   /**
      Advances the iterator to the next node.
   */
   void next();
   /**
      Moves the iterator to the previous node.
   */
   void previous();
   /**
      Compares two iterators
      @param b the iterator to compare with this iterator
      @return true if this iterator and b are equal
   */
   bool equals(Iterator b) const;
private:
   Node* position;
   Node* last;
friend class List;
};

Node::Node(string s)
{  
   data = s;
   previous = NULL;
   next = NULL;
}

List::List()
{  
   first = NULL;
   last = NULL;
}

void List::push_back(string s)
{  
   Node* newnode = new Node(s);
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

void List::insert(Iterator iter, string s)
{  
   if (iter.position == NULL)
   {  
      push_back(s);
      return;
   }

   Node* after = iter.position;
   Node* before = after->previous;
   Node* newnode = new Node(s);
   newnode->previous = before;
   newnode->next = after;
   after->previous = newnode;
   if (before == NULL) /* insert at beginning */
      first = newnode;
   else
      before->next = newnode;
}

Iterator List::erase(Iterator i)
{  
   Iterator iter = i;
   assert(iter.position != NULL);
   Node* remove = iter.position;
   Node* before = remove->previous;
   Node* after = remove->next;
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

Iterator List::begin()
{  
   Iterator iter;
   iter.position = first;
   iter.last = last;
   return iter;
}

Iterator List::end()
{  
   Iterator iter;
   iter.position = NULL;
   iter.last = last;
   return iter;
}

Iterator::Iterator()
{  
   position = NULL;
   last = NULL;
}

string Iterator::get() const
{  
   assert(position != NULL);
   return position->data;
}

void Iterator::next()
{  
   assert(position != NULL);
   position = position->next;
}

void Iterator::previous()
{  
   if (position == NULL)
      position = last;
   else 
      position = position->previous;
   assert(position != NULL);
}

bool Iterator::equals(Iterator b) const
{  
   return position == b.position;
}

int main()
{  
   List staff;

   staff.push_back("Cracker, Carl");
   staff.push_back("Hacker, Harry");
   staff.push_back("Lam, Larry");
   staff.push_back("Sandman, Susan");

   /* add a value in fourth place */

   Iterator pos;
   pos = staff.begin();
   pos.next();
   pos.next();
   pos.next();

   staff.insert(pos, "Reindeer, Rudolf");

   /* remove the value in second place */

   pos = staff.begin();
   pos.next();

   staff.erase(pos);

   /* print all values */

   for (pos = staff.begin(); !pos.equals(staff.end()); pos.next())
      cout << pos.get() << "\n";

   return 0;
}

