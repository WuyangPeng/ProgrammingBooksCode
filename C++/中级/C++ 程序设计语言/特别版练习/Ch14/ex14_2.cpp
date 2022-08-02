/* Code for exercise 14.2.
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

#include <iostream.h>
#include <stdexcept>
#include <string>
#include <typeinfo>

typedef std::string String;

template<typename T>
struct Ptr {
   // Pointer to single object:
   Ptr(T *obj);
   // Pointer to array-element:
   Ptr(T *obj, T *array, int size);
   T& operator*() const; // Dereference
   Ptr<T>& operator++(); // Pre-increment
   Ptr<T> operator++(int); // Post-increment
   Ptr<T>& operator--(); // Pre-decrement
   Ptr<T> operator--(int); // Post-decrement
private:
   T *obj_, *array_;
   int size_;
};


template<typename T>
T& Ptr<T>::operator*() const {
   if (obj_!=0)
      return *obj_;
   else
      throw std::invalid_argument(String("Ptr error"));
}

template<typename T>
Ptr<T>& Ptr<T>::operator++() {
   if (obj_!=0 and array_!=0) {
      if (obj_<array_+(size_-1)) {
         ++obj_;
         return *this;
      } else
         throw std::out_of_range(String("Ptr error"));
   } else
      throw std::invalid_argument(String("Ptr error"));
}

template<typename T>
Ptr<T> Ptr<T>::operator++(int) {
   if (obj_!=0 and array_!=0) {
      if (obj_<array_+(size_-1))
         return Ptr<T>(obj_++, array_, size_);
      else
         throw std::out_of_range(String("Ptr error"));
   } else
      throw std::invalid_argument(String("Ptr error"));
}

template<typename T>
Ptr<T>& Ptr<T>::operator--() {
   if (obj_!=0 and array_!=0) {
      if (obj_>array_) {
         --obj_;
         return *this;
      } else
         throw std::out_of_range(String("Ptr error"));
   } else
      throw std::invalid_argument(String("Ptr error"));
}

template<typename T>
Ptr<T> Ptr<T>::operator--(int) {
   if (obj_!=0 and array_!=0) {
      if (obj_>array_)
         return Ptr<T>(obj_--, array_, size_);
      else
         throw std::out_of_range(String("Ptr error"));
   } else
      throw std::invalid_argument(String("Ptr error"));
}

template<typename T>
Ptr<T>::Ptr(T *obj): obj_(obj), array_(0), size_(0) {}

template<typename T>
Ptr<T>::Ptr(T *obj, T *array, int size):
   obj_(obj), array_(array), size_(size) {
   if (size_<0)
      throw std::invalid_argument(String("Ptr error"));
   if (obj_!=0 and array_!=0
          and not(obj_>=array_ and obj_<array_+size_))
      throw std::out_of_range(String("Ptr error"));
}

int main() {
   try {
      int i = 3;
      Ptr<int> p(&i), q(0);
      std::cout << *p << '\n';
      std::cout << *q << '\n';
   } catch (std::exception &x) {
      std::cout << x.what() << ": " << typeid(x).name() << std::endl;
   }
   try {
      static int a[] = { 11, 12, 13 };
      Ptr<int> p(&a[1], a, sizeof(a)/sizeof(a[0]));
      std::cout << *++p << '\n';
      std::cout << *++p << '\n';
      std::cout << *++p << '\n';
   } catch (std::exception &x) {
      std::cout << x.what() << ": " << typeid(x).name() << std::endl;
   }
   return 0;
}

