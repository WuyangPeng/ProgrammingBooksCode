#include <iostream>
#include <iterator>
using std::iterator; using std::output_iterator_tag;
using std::cout;

struct write_iter : iterator<output_iterator_tag, int>
  { // iterator that writes to cout
  struct writer
    { // proxy with assignment operator
    template <class Ty> writer& operator=(const Ty& val)
      { // write the passed value
      cout << val << ' ';
      return *this;
      }
    };
  writer operator*() const
    { // return a proxy object
    return writer();
    }
  write_iter& operator++()
    { // do nothing
    return *this;
    }
  const write_iter& operator++(int)
    { // do nothing
    return *this;
    }
  };

template <class Iter>
void setcount(Iter first, int count)
  { // write successive values to sequence
  for (int i = 0; i < count; ++i)
    *first++ = i;
  }

int main()
  { // demonstrate use of unbounded output iterator
  const int NVALS = 6;
  setcount(write_iter(), NVALS);
  return 0;
  }