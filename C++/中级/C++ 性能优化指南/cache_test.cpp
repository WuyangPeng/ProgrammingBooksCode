# include <iostream>
# include <memory>
# include "stopwatch03.h"

template<typename T> void cache_test1(T* p, unsigned limit, unsigned step = 1, unsigned reps = 1) {
    for (unsigned k = 0; k < reps; ++k)
        for (unsigned i = 0, j = 0; j < limit; i = (i + step) % limit, ++j)
            p[i] = (T)i;
}

template<typename T> T cache_test2(T* p, unsigned limit, unsigned step = 1, unsigned reps = 1) {
    T sum = 0;
    for (unsigned k = 0; k < reps; ++k)
        for (unsigned i = 0, j = 0; j < limit; i = (i + step) % limit, ++j)
            sum += p[i];
    return sum;
}


int test_cache(int test_no) {
    bool rc = true;

    switch(test_no) {
    default:return -1;
    case 0: return 5;
    case 1: break;  //  add validation tests
    case 2: {
        break;
        }
    case 3: {
        break;
        }
    case 4: {
        typedef unsigned long long T;
        size_t memsize = (1<<28) / sizeof(T);
        unsigned step = 1025;
        unsigned reps = 10;
        std::cout << "T == unsigned long long" << std::endl;
        std::unique_ptr<T> p;
        try {
            p.reset(new T[memsize]);
        }
        catch (std::exception&)
        {
            std::cout << "Could not allocate a block of 10,000,000 bytes" << std::endl;
            rc = false;
            break;
        }
        T sum = 0;
        for (unsigned limit = memsize, iterations = reps; limit > 65536; limit >>= 1/*, iterations <<= 1*/) {
            std::cout << "cache_test2(" << limit << ", " << step << ", "<< iterations << ")";

            Stopwatch sw(" = ");
            sum += cache_test2<T>(p.get(), limit, step, iterations);
        }
        std::cout << sum << std::endl;
        break;
    }
    case 5: {
        typedef unsigned char T;
        size_t memsize = (1<<28) / sizeof(T);
        unsigned step = 1025;
        unsigned reps = 10;
        std::cout << "T == unsigned char" << std::endl;
        std::unique_ptr<T> p;
        try {
            p.reset(new T[memsize]);
        }
        catch (std::exception&)
        {
            std::cout << "Could not allocate a block of 10,000,000 bytes" << std::endl;
            rc = false;
            break;
        }
        T sum = 0;
        for (unsigned limit = memsize, iterations = reps; limit > 65536; limit >>= 1/*, iterations <<= 1*/) {
            std::cout << "cache_test2(" << limit << ", " << step << ", "<< iterations << ")";

            Stopwatch sw(" = ");
            sum += cache_test2<T>(p.get(), limit, step, iterations);
        }
        std::cout << sum << std::endl;
        break;
    }
    }
    return rc ? 1 : 0;
}
