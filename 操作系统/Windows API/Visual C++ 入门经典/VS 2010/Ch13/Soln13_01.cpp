// Soln13_01.cpp
// Computing factorial n using parallel_for
/*
  You have to do a bit of research to complete this exercise.
  You need to use a combinable object to make this possible.
  The combinable class template defines a constructor that accept a function object
  as an argument that will be used to initialize local instances of the combinable object.
  This is is not discussed in chapter 13 and you need this capability so this is 
  the only aspect of the example that makes it more than trivial.
  I chose adjacent values for n to enable the results to be checked quite easily.
*/

#include <iostream>
#include "ppl.h"

unsigned long long factorial(int n);      // Computes factorial n

int main()
{
  int m[] = {5, 10, 15, 19, 20, 25, 49, 50};
  for(int i = 0 ; i< sizeof m/ sizeof m[0] ; ++i)
    std::cout << "Factorial " << m[i] << " = " << factorial(m[i]) << std::endl;
  return 0;
}

unsigned long long factorial(int n)
{
  Concurrency::combinable<unsigned long long> products
    = Concurrency::combinable<unsigned long long>([]()->unsigned long long{return 1LL;});
  Concurrency::parallel_for(1 , n+1,
      [&products](int i)
      {
        products.local() *= i;
      });
  return products.combine([](unsigned long long lProduct, unsigned long long rProduct)
                             { return lProduct*rProduct;  });
}
