/* Code for exercise 10.12.
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

#include <iostream>
#include <typeinfo>

/* The following can go in a header file */

struct Char_queue {
   Char_queue(unsigned capacity = 0): in_(&out_cell_)
      { out_cell_.next_ = 0; }
   ~Char_queue();
   bool empty() const { return in_==&out_cell_; }
   char dequeue();
   void enqueue(char);
   bool full() const { return false; }
   static bool const fixed_capacity = false;
private:
   struct Cell {
      Cell *next_;
      char c_;
   };
   Cell out_cell_;
   Cell *in_;
};

/* Header file would stop here. */


/* Now the implementation file */

#include <stdexcept>
#include <string>
#include <new>

Char_queue::~Char_queue() {
   // Delete all elements in the queue:
   for (Cell *p = out_cell_.next_; p;) {
         Cell *victim = p;
         p = p->next_;
      delete victim;
   }
}

char Char_queue::dequeue() {
   if (!empty()) {
      Cell *victim = out_cell_.next_;
      if (victim==in_) { in_ = &out_cell_; }
      char c = victim->c_;
      out_cell_.next_ = victim->next_;
      delete victim;
      return c;
   } else
      throw std::underflow_error(std::string("queue"));
}

void Char_queue::enqueue(char c) {
   // the 'std::nothrow' prevents the bad_alloc exception:
   in_->next_ = new(std::nothrow) Cell;
   if (!in_->next_)
      throw std::overflow_error(std::string("queue"));
   in_ = in_->next_;
   in_->next_ = 0;
   in_->c_ = c;
}


/* A brief test of the above implementation: */

int main() {
   Char_queue q;
   while (1) {
      if (q.empty()) { std::cout << "Queue is empty.\n"; }
      else if (q.full()) { std::cout << "Queue is full.\n"; }
      char cmd, ch;
      std::cin >> cmd;
      try {
         switch (cmd) {
         case 'e': case 'E':
            std::cin >> ch;
            q.enqueue(ch);
            break;
         case 'd': case 'D':
            std::cout << "Dequeued " << q.dequeue() << '\n';
            break;
         case 'q': case 'Q':
            std::cout << "Quitting!\n";
            return 0;
         default:
            std::cerr << "Invalid command!\n";
         }
      } catch (std::exception &x) {
         std::cerr << "Caught exception " << typeid(x).name()
                   << " (" << x.what() << ")\n";
      }
   }
   return 0;
}

