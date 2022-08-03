#include <cassert>
#include <vector>

void TestSwap()
{
    std::vector<int> vec1(100);
    std::vector<int> vec2;

    vec1.swap(vec2);

    assert(0 == vec1.size());
    assert(100 == vec2.size());
}