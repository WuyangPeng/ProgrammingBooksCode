/* Code for exercise 25.5.
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

struct Filter {
   struct Retry {
      virtual char const* message() { return 0; }
   };
   virtual ~Filter() {}
   virtual void start() {}
   virtual int read() = 0;
   virtual void write() {}
   virtual void compute() {}
   virtual int result() = 0;
   virtual int retry(Retry &m) {
      std::cerr << m.message() << '\n';
      return 2;
   }
};

int main_loop(Filter *p) {
   for (;;) {
      try {
         p->start();
         while (p->read()) {
            p->compute();
            p->write();
         }
         return p->result();
      }
      catch(Filter::Retry &m) {
         if (int i = p->retry(m))
            return i;
      }
      catch (...) {
         std::cerr << "Fatal filter error.\n";
         return 1;
      }
   }
}

struct UniqueWords: Filter {
   UniqueWords(std::istream &in, std::ostream &out)
      : in_(in), out_(out), n_eliminated_(0) {}
   virtual int read()
      { in_ >> next_word_; return in_.good(); }
   virtual void compute() {
      if (last_word_==next_word_) {
         next_word_ = ""; // Kill next word
         ++n_eliminated_;
      } else
         last_word_ = next_word_;
   }
   virtual void write() { out_ << next_word_ << '\n'; }
   virtual int result() { return n_eliminated_; }
private:
   std::istream &in_;
   std::ostream &out_;
   std::string last_word_, next_word_;
   int n_eliminated_;
};

int main() {
   UniqueWords uniq(std::cin, std::cout);
   main_loop(&uniq);
   std::cerr << "Eliminated " << uniq.result() << " duplicates.\n";
   return 0;
}

