#ifndef VEC_H
#define VEC_H

#include <vector>

template<class T> class Vec : public std::vector<T>
{
public:
  Vec() : std::vector<T>() {}
  Vec(int s) : std::vector<T>(s) {}
  
  T& operator[](int i)
    {
    if (i < (int)size())
      {
      return at(i);
      }
    else
      {
      std::cout << "You have tried to use element " << i << " of a Vec which has only "
      << size() << " elements." << std::endl;
      throw;
      }
    }
    
  const T& operator[](int i) const
      {
      if (i < (int)size())
        {
        return at(i);
        }
      else
        {
        std::cout << "You have tried to use element " << i << " of a Vec which has only "
        << size() << " elements." << std::endl;
        throw;
        }
    }
};
    
#endif