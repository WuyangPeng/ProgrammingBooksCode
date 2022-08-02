#pragma once

#include <algorithm>

// 一个不能正确展开的宏
#define Cube1(a) a* a* a

// 仍不能正常展开的宏
#define Cube2(a) （a）* （a）* （a）

// 可以正确展开的宏
#define Cube3(a) （（a）* （a）* （a））

#define MIN_INDEX 0
#define MAX_INDEX 10

// 一个无法工作的含有多条语句的宏
#define LookupEntry1(key, index)        \
    index = (key - 10) / 5;             \
    index = std::min(index, MAX_INDEX); \
    index = std::max(index, MIN_INDEX);

// 可以正确工作的含有多条语句的宏
#define LookupEntry2(key, index)            \
    {                                       \
        index = (key - 10) / 5;             \
        index = std::min(index, MAX_INDEX); \
        index = std::max(index, MIN_INDEX); \
    }