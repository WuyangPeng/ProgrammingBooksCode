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

#include <stdexcept>
#include <string>

struct Char_queue {
   inline Char_queue(unsigned capacity = default_capacity);
   ~Char_queue() { delete[] queue_; }
   bool empty() const { return head_==tail_; }
   inline char dequeue();
   inline void enqueue(char);
   bool full() const { return head_==(tail_+1)%capacity_; }
   static bool const fixed_capacity = true;
private:
   static unsigned const default_capacity = 32;
   char *queue_;
   unsigned head_, tail_;
   unsigned const capacity_;
};

inline
Char_queue::Char_queue(unsigned n)
   : queue_(new char[n+1]), head_(0), tail_(0), capacity_(n+1) {
}

inline
char Char_queue::dequeue() {
   if (!empty()) {
      char c = queue_[head_];
      head_ = (head_+1)%capacity_;
      return c;
   } else
      throw std::underflow_error(std::string("queue"));
}

inline
void Char_queue::enqueue(char c) {
   if (!full()) {
      queue_[tail_] = c;
      tail_ = (tail_+1)%capacity_;
   } else
      throw std::overflow_error(std::string("queue"));
}

/* Header file would stop here. */

/* A brief test of the above implementation: */

int main() {
   Char_queue q(4);
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

