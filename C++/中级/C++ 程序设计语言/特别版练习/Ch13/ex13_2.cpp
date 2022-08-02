/* Code for exercise 13.2.
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
#include <new>


struct Link {
   Link(Link *next = 0): next_(next) {}
private:
   friend class LinkList;
   friend class Cursor;
   Link *next_;
};

struct Cursor {
   // Pre- and post-increment:
   Cursor& operator++() { p_ = p_->next_; return *this; }
   Cursor operator++(int) 
      { Cursor old(*this); p_ = p_->next_; return old; }
private:
   friend class LinkList;
   friend bool operator==(Cursor const&, Cursor const&);
   friend bool operator!=(Cursor const&, Cursor const&);
   Cursor(Link *p): p_(p) {}
   Link *p_;
};


bool operator==(Cursor const &a, Cursor const &b) {
   return a.p_==b.p_;
}

bool operator!=(Cursor const &a, Cursor const &b) {
   return a.p_!=b.p_;
}

struct LinkList {
   LinkList(): head_(&head_) {}
   ~LinkList() { assert(is_empty()); }

   // Element access functions:
   Link& operator[](Cursor const &p)
      { return *p.p_->next_; }
   Link const& operator[](Cursor const &p) const 
      { return *p.p_->next_; }

   // Element insertion/extraction:
   void insert(Cursor p, Link *link) {
      assert(p.p_->next_ and link and (link->next_==0));
      link->next_ = p.p_->next_;
      p.p_->next_ = link;
   }

   Link* extract(Cursor p) {
      Link *link = p.p_->next_;
      assert(link and link!=&head_);
      p.p_->next_ = link->next_;
      link->next_ = 0;
      return link;
   }

   // Iteration functions:
   Cursor first() const { return Cursor(const_cast<Link*>(&head_)); }
   bool is_last(Cursor const &p) const { return p.p_->next_==&head_; }
   bool is_empty() const { return head_.next_==&head_; }
private:
   Link head_;
};


template<typename T>
struct aligner {
   union {
      long double long_double_;
      long long_;
      void (*simple_function_ptr_)();
   };
};


template<typename T>
struct TLink: Link {
   T& value() { return *(T*)(raw_mem_); }
   T const& value() const { return *(T const*)(raw_mem_); }
   union {
      unsigned char raw_mem_[sizeof(T)];
      aligner<T> dummy_;
   };
};


template<typename T>
struct TLinkList: private LinkList {

   // Element access functions:
   T& operator[](Cursor const &p) {
      LinkList &base = (LinkList&)*this;
      return static_cast<TLink<T>&>(base[p]).value();
   }

   T const& operator[](Cursor const &p) const {
      LinkList const &base = (LinkList const&)*this;
      return static_cast<TLink<T> const&>(base[p]).value();
   }

   // Element insertion/extraction:
   void insert(Cursor p, TLink<T> *link) { LinkList::insert(p, link); }
   TLink<T>* extract(Cursor p)
      { return static_cast<TLink<T>*>(LinkList::extract(p)); }

   // Iteration functions:
   Cursor first() const { return LinkList::first(); }
   bool is_last(Cursor const &p) const { return LinkList::is_last(p); }
   bool is_empty() const { return LinkList::is_empty(); }
};


struct X {
   X(int i): i_(i) {} // No default constructor!
   void report() const { std::cout << i_; }
private:
   int const i_;
};

TLink<X>* create_XLink(int i) {
   TLink<X> *p = new TLink<X>;
   new(p->raw_mem_) X(i);
   return p;
}

void destroy_XLink(TLink<X> *p) {
   delete p;
}

template<typename T>
void reverse(TLinkList<T> &list) {
   for (Cursor p = ++list.first(); !list.is_last(p);)
      list.insert(list.first(), list.extract(p));
};

void report(TLinkList<X> const &list) {
   Cursor p = list.first();
   if (!list.is_last(p))
      list[p].report();
   for (; !list.is_last(++p);) {
      std::cout << ", ";
      list[p].report();
   }
   std::cout << '\n';
}

typedef TLink<X> XLink;

int main() {
   TLinkList<X> list;
   Cursor end = list.first();
   int i;
   std::cout << "Enter integers (zero indicates last entry):\n";
   while ((std::cin >> i) and (i!=0)) {
      TLink<X> *p = create_XLink(i);
      list.insert(end, p);
      ++end;
   };
   std::cout << "Original list: ";
   report(list);
   reverse(list);
   std::cout << "Reversed list: ";
   report(list);
   for (Cursor p = list.first(); not list.is_last(p);)
      destroy_XLink(list.extract(p));
}

