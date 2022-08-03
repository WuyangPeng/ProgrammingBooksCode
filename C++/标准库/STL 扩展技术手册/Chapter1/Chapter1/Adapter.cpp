#include <algorithm>
#include <iostream>
#include <iterator>
#include <list>
#include <sstream>
#include <vector>

void TestFrontInserter()
{
    std::vector<int> vec;
    // Code that inserts elements into vec

    std::list<int> lst;
    std::copy(vec.begin(), vec.end(), std::front_inserter(lst));
}

void TestIterator()
{
    std::vector<int> values;
    std::stringstream sstm;

    std::copy(std::istream_iterator<int>(std::cin),  // Read in values
              std::istream_iterator<int>(),
              std::back_inserter(values));

    std::sort(values.begin(), values.end());  // Sort values
    std::copy(values.begin(), values.end(),
              std::ostream_iterator<int>(sstm, ""));  // Write out
}