#include <algorithm>
#include <cstdlib>
#include <vector>

void TestAlgorithm()
{
    std::vector<int> v1;
    std::vector<int> v2(v1.size());
    using Abs = int (*)(int);
    Abs abs = ::abs;
    std::transform(v1.begin(), v1.end(), v2.begin(), abs);
}