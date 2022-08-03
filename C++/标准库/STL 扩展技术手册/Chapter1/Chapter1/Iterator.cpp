#include "Iterator.h"

#include <cassert>
#include <vector>

void TestInput()
{
    II ii;

    II ii2(ii);

    II ii3;

    ii3 = ii2;

    ++ii2;  // Preincrement, or
    ii3++;  // Postincrement

    if (ii == ii2)
    {
    }

    if (ii3 != ii)
    {
    }

    II end;  // Obtain the endpoint iterator value
    if (end != ii)
    {
        V v1 = *ii;  // Dereference ii to yield type convertible to V
    }

    II ii5 = ii;
    if (end != ii)
    {
        assert(*ii5 == *ii);
    }

    II ii6 = ii;
    assert(ii == ii6);  // Valid
    ++ii;
    ++ii6;
    assert(ii == ii6);  // Not valid!

    II ii1;

    II ii7 = ii1;
    II ii8 = ii1;
    [[maybe_unused]] int n1 = std::distance(ii7, end);  // Iterate range[ii7 , end)
    [[maybe_unused]] int n2 = std::distance(ii8, end);  // ii8 already == end
    [[maybe_unused]] int n3 = std::distance(ii1, end);  // ii1 already == end

    assert(0 == n2);
    assert(0 == n3);
}

void TestOutput()
{
    OI oi;  // Obtain start of writable range
    OI end;  // Obtain endpoint iterator value

    for (; end != oi; ++oi)
    {
        *oi = V();  // Assigns result of V() to *oi
    }
}

void TestForward()
{
    FI fi1;
    FI fi2 = fi1;
    FI fi3 = fi1;
    FI end;
    [[maybe_unused]] int n1 = std::distance(fi1, end);  // Iterate range [fi1, end)
    [[maybe_unused]] int n2 = std::distance(fi2, end);  // Iterate range [fi2, end)
    [[maybe_unused]] int n3 = std::distance(fi3, end);  // Iterate range [fi3, end)

    assert(n1 == n2);
    assert(n1 == n3);
}

void TestBidirectional()
{
    BI bi;
    BI end;
    BI begin;
    for (bi = begin; bi != end; ++bi)  // Forwards
    {
    }

    // At this point bi == end.Now we traverse the range backwards.
    for (;; --bi)
    {
        if (bi == begin)
        {
            break;
        }
    }
}

void TestRandom()
{
    RI ri;
    RI ri2 = ri + 1;
    RI ri3 = ri - -1;
    assert(ri2 == ri3);
    V v1 = ri[1];
    V v2 = *ri2;
    assert(v1 == v2);

    RI p;
    // 以下关系对指针成立，对随机访问迭代器却不一定成立。
    assert(&*(p + 1) == &*p + 1);
}

struct X
{
    int x;
};

void TestMember()
{
    some_iterator<X> si;
    some_iterator<X> si2;
    some_iterator<X> end;

    if (end != si && end != si2)
    {
        si->x = si2->x;
    }
}

void TestC0()
{
    C cont;
    I it = cont.begin();
    it->release();  // 这里调用的是D1的release
}

void TestC1()
{
    C cont;
    I it = cont.begin();
    // it->->release();  // 不支持这样的语句
}

void TestC2()
{
    C cont;
    I it = cont.begin();
    (*it)->release();  // 这里调用的是D2的release
}