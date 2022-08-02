// sizeof_void.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

template <typename T>
struct is_void
{
    enum { value = 0 };
};

template <>
struct is_void<void>
{
    enum { value = 1 };
};

char const *truth(int i)
{
    return (0 == i) ? "false" : "true";
}

template <typename T>
struct size_of
{
    enum { value = sizeof(T) };
};

template <>
struct size_of<void>
{
    enum { value = 0 };
};



int _tmain(int argc, _TCHAR* argv[])
{
    printf("int:   %s\n", truth(is_void<int>::value));
    printf("void:  %s\n", truth(is_void<void>::value));
    printf("void*: %s\n", truth(is_void<void*>::value));

    printf("sizeof(int):   %u\n", size_of<int>::value);
    printf("sizeof(void):  %u\n", size_of<void>::value);
    printf("sizeof(void*): %u\n", size_of<void*>::value);

    return 0;
}

