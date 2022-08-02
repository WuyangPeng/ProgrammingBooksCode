#ifndef SPUTIL_H
#define SPUTIL_H

#include <ostream>
#include <iostream>
#include <memory>

struct resource
  { // simple struct to demonstrate resource handling
  resource(int i0 = 0) : i(i0) {}
  int i;
  };

template <class Elem, class Tr>
std::basic_ostream<Elem, Tr>& operator<<(
  std::basic_ostream<Elem, Tr>& str,
  const resource& res)
  { // insert resource contents into stream
  return str << res.i;
  }

class d_res : public resource
  { // simple derived class
public:
  d_res(int i0) : resource(i0) {}
  };

static void show_rc(unsigned long count)
  { // show a reference count
  std::cout << " reference count: "
       << count << '\n';
  }

template <class Sp>
void show_refs(const std::tr1::shared_ptr<Sp>& sp)
  { // show reference count for shared_ptr objects
  show_rc(sp.use_count());
  }

template <class Sp>
void show_refs(const std::tr1::weak_ptr<Sp>& wp)
  { // show reference count for weak_ptr objects
  show_rc(wp.use_count());
  }

template <class Sp>
void show_refs(const Sp&)
  { // show reference count for other types (do nothing)
  }

template <class Sp>
void do_show(const Sp& sp)
  { // show contents of smart pointer
  std::cout << " pointer: "
      << (void*)sp.get() << '\n';
  if (sp.get())
    std::cout << " value: " << *sp << '\n';
  }

template <class Sp>
void show(const char *title, const Sp& sp)
  { // show title and contents of smart pointer
  std::cout << title << '\n';
  show_refs(sp);
  do_show(sp);
  }

template <class Ty>
void show(const char *title,
  const std::tr1::weak_ptr<Ty>& wp)
  { // show title and contents of weak_ptr object
  std::cout << title << '\n';
  if (wp.expired())
    std::cout << " expired\n";
  else
    {   // show reference count before creating
        // temporary shared_ptr object
    show_rc(wp.use_count());
    do_show(wp.lock());
    }
  }

struct instrumented
  { // struct to report construction and destruction
  instrumented()
    { std::cout << " constructing instrumented\n"; }
  instrumented(const instrumented&)
    { std::cout << " copy constructing instrumented\n"; }
  instrumented& operator=(const instrumented&)
    { std::cout << " copying instrumented\n"; }
  ~instrumented()
    { std::cout << " destroying instrumented\n"; }
  };

#endif  // SPUTIL_H
