/* Code for exercise 17.6.
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
#include <stack>
#include <stdexcept>
#include <string>
#include <typeinfo>
#include <vector>

template<typename T, typename C = std::vector<T> >
struct Queue {
   typedef typename C::value_type value_type;
   typedef typename C::size_type size_type;
   typedef C container_type;
   explicit Queue(C const &contents = C())
      : outstack_(contents) {}
   bool empty() const
      { return instack_.empty() && outstack_.empty(); }
   size_type size() const
      { return instack_.size()+outstack_.size(); }
   value_type& front()
      { transfer(); return outstack_.top(); }
   value_type const& front() const
      { transfer(); return outstack_.top(); }
   value_type& back()
      { untransfer(); return instack_.top(); }
   value_type const& back() const
      { untransfer(); return instack_.top(); }
   void push(value_type const& x) { instack_.push(x); }
   void pop() { transfer(); outstack_.pop(); }
private:
   void transfer() {
      if (outstack_.empty())
         while (!instack_.empty()) {
            outstack_.push(instack_.top());
            instack_.pop();
         }
   }
   void untransfer() {
      assert(cerr << "WARNING: Queue::untransfer()'ed.\n");
      if (instack_.empty())
         while (!outstack_.empty()) {
            instack_.push(outstack_.top());
            outstack_.pop();
         }
   }
   std::stack<T, C> instack_, outstack_;
};


int main() {
   Queue<char> q;
   while (1) {
      if (q.empty()) { std::cout << "Queue is empty.\n"; }
      else { std::cout << "Queue has " << q.size() << " elements.\n"; }
      char cmd, ch;
      std::cin >> cmd;
      try {
         switch (cmd) {
         case 'e': case 'E':
            std::cin >> ch;
            q.push(ch);
            break;
         case 'd': case 'D':
            if (q.empty()) {
               throw std::underflow_error(std::string("Queue"));
            }
            std::cout << "Dequeued " << q.front() << '\n';
            q.pop();
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

