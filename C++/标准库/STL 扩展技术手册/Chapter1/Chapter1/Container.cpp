#include <cassert>
#include <deque>
#include <string>
#include <vector>

extern "C" void sort_ints(int* p, size_t n);

void TestVector()
{
    std::vector<int> v = { 1, 2, 3 };
    assert(!v.empty());
    sort_ints(&v[0], v.size());
}

void TestDeque()
{
    std::deque<int> d = { 1, 2, 3 };
    assert(!d.empty());
    sort_ints(&d[0], d.size());  // This is a crash waiting to happen
}

void TestString()
{
    std::string s1("abc");
    char s2[4];
    assert(!s1.empty());
    ::strcpy_s(&s2[0], s1.size(), &s1[0]);  // Bad day... eventually
}