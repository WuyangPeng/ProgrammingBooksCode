#include <vector>
#include <winstl/memory/processheap_allocator.hpp>

void TestAllocatorr()
{
    std::vector<int> vec1;
    std::vector<int, winstl::processheap_allocator<int>> vec2;
}