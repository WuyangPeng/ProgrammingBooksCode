/* Code for exercise 5.8.
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

// Note: Some compilers do not like the repeated "for (int k ..."
// statement. A common trick to work around that anachronism, is to
// define the following macro:
// #define for if (0) ; else for

#include <iostream>
#include <time.h> // For clock()
#include <stddef.h> // For size_t
#include <string.h> // For memcpy()

void copy_with_pointers(char const *src, char *dst,
                        size_t n) {
   for (size_t k = 0; k!=n; ++k)
      *dst++ = *src++;
}

void copy_with_indices(char const *src, char *dst,
                       size_t n) {
   for (size_t k = 0; k!=n; ++k)
      dst[k] = src[k];
}

int main() {
   int const n_bytes = 100000;
   int const n_calls = 100;
   char *src = new char[n_bytes];
   char *dst = new char[n_bytes];

   // Reduce paging effects by accessing all bytes:
   memcpy(dst, src, n_bytes);
   clock_t start, end, reftime;

   // Test 1 (reference time)
   start = clock();
   for (int k = 0; k!=n_calls; ++k)
      memcpy(dst, src, n_bytes);
   end = clock();
   reftime = end-start;

   // Test 2 (pointers)
   start = clock();
   for (int k = 0; k!=n_calls; ++k)
      copy_with_pointers(src, dst, n_bytes);
   end = clock();
   cout << "With pointers: "
        << static_cast<double>(end-start)/reftime
        << " times slower than memcpy.\n";

   // Test 3 (indices)
   start = clock();
   for (int k = 0; k!=n_calls; ++k)
      copy_with_indices(src, dst, n_bytes);
   end = clock();
   cout << "With indices: "
        << static_cast<double>(end-start)/reftime
        << " times slower than memcpy.\n";

   delete[] src;
   delete[] dst;
   return 0;
}

