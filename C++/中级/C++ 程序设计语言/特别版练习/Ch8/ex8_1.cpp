/* Code for exercise 8.1.
 | 
 | "C++ Solutions--Companion to The C++ Programming Language, Third Edition"
 | by David Vandevoorde; Addison-Wesley 1998; ISBN 0-201-30965-3.
 |
 | Permission to use, copy, modify, distribute and sell this software
 | and its documentation for any purpose is hereby granted without fee.
 | The author makes no representations about the suitability of this
 | software for any purpose.  It is provided "as is" without express or
 | implied warranty.
 `----------------------------------------------------------------------*/

#include <assert.h>
#include <iostream>
#include <string>
#include <algorithm> // for std::swap

namespace StringList {
   using std::string;

   struct Node {
      string string_;
      Node *prev_;
      Node *next_;
   } head_node, tail_node;

   typedef Node *Cursor;

   void init() {
      head_node.prev_ = tail_node.next_ = 0;
      head_node.next_ = &tail_node;
      tail_node.prev_ = &head_node;
   }

   inline Cursor next(Cursor c) {
      assert(c);
      return c->next_;
   }

   inline Cursor prev(Cursor c) {
      assert(c);
      return c->prev_;
   }

   inline Cursor head() {
      return &head_node;
   }

   inline Cursor tail() {
      return &tail_node;
   }

   string extract(Cursor c) {
      assert(c!=head() and c!=tail());
      string s = c->string_;
      c->prev_->next_ = c->next_;
      c->next_->prev_ = c->prev_;
      delete c;
      return s;
   }

   Cursor insert_after(Cursor c, string s) {
      assert(c!=tail());
      Node *n = new Node;
      n->string_ = s;
      n->prev_ = c; n->next_ = c->next_;
      c->next_ = n; n->next_->prev_ = n;
      return n;
   }

   Cursor insert_before(Cursor c, string s) {
      assert(c!=head());
      Node *n = new Node;
      n->string_ = s;
      n->prev_ = c->prev_; n->next_ = c;
      c->prev_ = n; n->prev_->next_ = n;
      return n;
   }

   void reverse() {
      // First exchange the prev_ and next_ pointers
      // inside each internal node:
      for (Cursor c = next(head()); c!=tail(); c = c->prev_)
         std::swap(c->prev_, c->next_);
      // Then exchange the head and tail positions:
      tail()->prev_->prev_ = head();
      head()->next_->next_ = tail();
      std::swap(head()->next_, tail()->prev_);
   }

   namespace { // unnamed namespace
      void quicksort(Cursor left, Cursor right) {
         // The input partition is described by cursors
         // pointing to nodes just outside its boundaries:
         Cursor p = left->next_; // The pivot
         Cursor l = left->next_, r = right->prev_;
         // Zero- or one-element lists are trivially sorted:
         if (left==right || l==right || l==r)
            return;
         // Partition the list into elements smaller and
         // larger than the pivot value:
         while (true) {
            while (l!=r && l->string_<p->string_)
               l = next(l);
            while (l!=r && p->string_<=r->string_)
               r = prev(r);
            if (l==r)
               break;
            std::swap(l->string_, r->string_);
         }
         // Establising the boundaries of both partitions
         // is more delicate when dealing with doubly linked
         // than the version for arrays:
         if (l->string_<p->string_) {
            if (r->next_!=right)
               l = next(l);
         } else {
            if (left->next_!=r)
               r = prev(r);
         }
         // Recursively partition these partitions:
         quicksort(left, l);
         quicksort(r, right);
      }
   } // End unnamed namespace

   void sort() {
      if (head()->next_!=tail()
      and head()->next_->next_!=tail())
         quicksort(head(), tail());
   }
} // End namespace StringList

void print_stringlist() {
	StringList::Cursor p = StringList::head();
   while ((p = StringList::next(p))!=StringList::tail())
      std::cout << p->string_ << endl;
}


int main() {
   StringList::init();
   StringList::insert_before(StringList::tail(), string("Cobol"));
   StringList::insert_before(StringList::tail(), string("Fortran"));
   StringList::insert_before(StringList::tail(), string("Lisp"));
   StringList::insert_before(StringList::tail(), string("Algol 68"));
   StringList::insert_before(StringList::tail(), string("Basic"));
   StringList::insert_before(StringList::tail(), string("Pascal"));
   StringList::insert_before(StringList::tail(), string("C"));
   StringList::insert_before(StringList::tail(), string("Ada"));
   StringList::insert_before(StringList::tail(), string("Modula-2"));
   StringList::insert_before(StringList::tail(), string("C++"));
   std::cout << ">>> Original list of strings: \n";
   print_stringlist();
   std::cout << "\n>>> Reversed list of strings: \n";
   StringList::reverse();
   print_stringlist();
   std::cout << "\n>>> Sorted list of strings: \n";
   StringList::sort();
   print_stringlist();
   std::cout << "\n>>> Done.\n";
   return 0;
}


