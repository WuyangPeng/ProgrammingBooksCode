/* Copyright (C) James Boer, 2000. 
 * All rights reserved worldwide.
 *
 * This software is provided "as is" without express or implied
 * warranties. You may freely copy and compile this source into
 * applications you distribute provided that the copyright text
 * below is included in the resulting source code, for example:
 * "Portions Copyright (C) James Boer, 2000"
 */

#pragma warning(disable : 4786)
#include <algorithm>
#include <iostream>
#include <map>
#include <string>

using namespace std;

// This function object allows us to compare map containers
// 这个函数对象允许我们比较映射表容器
template <class F, class S>
class value_equals
{
private:
    S second;

public:
    value_equals(const S& s)
        : second(s)
    {
    }
    bool operator()(pair<const F, S> elem)
    {
        return elem.second == second;
    }
};

// Typedef the container and iterator names for better readability
// 为获得更好可读性而进行的容器和迭代子的类型定义
typedef map<int, string> isMap;
typedef isMap::value_type isValType;
typedef isMap::iterator isMapItor;

int main()
{
    isMap c;

    // Insert key / value pairs
    // 插入键/值对
    c.insert(isValType(100, "One Hundred"));
    c.insert(isValType(3, "Three"));
    c.insert(isValType(150, "One Hundred Fifty"));
    c.insert(isValType(99, "Ninety Nine"));

    // display all the keys and values
    // 显示所有键和值
    for (isMapItor itor = c.begin(); itor != c.end(); ++itor)
        cout << "Key = " << (*itor).first << ", Value = " << (*itor).second << endl;

    // You can also access the map like an associative array
    // 你也可以通过关联数组方式访问映射表
    cout << "Key 3 displays value " << c[3].c_str() << endl;

    // Or insert like this as well
    // 或者以关联数组方式插入键/值对
    c[123] = "One Hundred Twenty Three";

    // Find and remove a specific element based on the key
    // 基于键找一并删除一个特定值
    isMapItor pos = c.find(123);
    if (pos != c.end())
        // erasing an element invalidates any iterators pointing to it.  Calling
        // pos++ now would result in undefined behavior.
        // 删除一个元素将使指向它的所有迭代器无效
        // 现在调用pos++，结果将是未定义行为
        c.erase(pos);

    // Find and remove an element based on the value
    // 基于值找到并删除元素
    pos = find_if(c.begin(), c.end(), value_equals<int, string>("Ninety Nine"));
    if (pos != c.end())
        c.erase(pos);

    // If you must remove elements while iterating through the list...
    // 如果你需要在遍历列表时删除元素……
    for (isMapItor itr = c.begin(); itr != c.end();)
    {
        if (itr->second == "Three")
            c.erase(itr++);
        else
            ++itr;
    }
}
