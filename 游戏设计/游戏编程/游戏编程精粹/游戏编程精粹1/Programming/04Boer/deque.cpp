/* Copyright (C) James Boer, 2000. 
 * All rights reserved worldwide.
 *
 * This software is provided "as is" without express or implied
 * warranties. You may freely copy and compile this source into
 * applications you distribute provided that the copyright text
 * below is included in the resulting source code, for example:
 * "Portions Copyright (C) James Boer, 2000"
 */

#include <deque>
#include <iostream>

using namespace std;

// Typedef the container and iterator names for better readability
// 为了提高可读性，定义容器和迭代器的名字
typedef deque<int> IntDeque;
typedef IntDeque::reverse_iterator IntDequeRItor;

int main()
{
    // Create a deque container of integers
    // 创建一个整数双队列容器
    IntDeque c;

    // Fill the deque with 3 different elements
    c.push_front(3);
    c.push_front(2);
    c.push_front(1);
    c.push_back(3);
    c.push_back(2);
    c.push_back(1);

    // Cycle BACKWARD through the list - special iterators and notation
    // is necessary to do this.
    // 向后循环该链表
    // 需要使用专用的迭代器和写法
    for (IntDequeRItor ritor = c.rbegin(); ritor != c.rend(); ++ritor)
        cout << "Value = " << (*ritor) << endl;

    // remove the first and last elements
    // 删除第一个和最后一个元素
    c.pop_front();
    c.pop_back();

    // Accessing elements directly - if needed remember to check to see
    // the deque is not empty.  Accessing non-existant elements will
    // lead to undefined behavior; probably an access violation
    // 直接访问元素——如果需要，查看双队列是否非空
    // 访问不存在的元素将导致不可预计的行为，很可能产生访问违例
    if (!c.empty())
    {
        cout << "Front = " << c.front() << endl;
        cout << "Back = " << c.back() << endl;
    }
}
