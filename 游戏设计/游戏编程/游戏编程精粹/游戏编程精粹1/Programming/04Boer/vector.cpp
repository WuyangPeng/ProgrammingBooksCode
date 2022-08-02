/* Copyright (C) James Boer, 2000. 
 * All rights reserved worldwide.
 *
 * This software is provided "as is" without express or implied
 * warranties. You may freely copy and compile this source into
 * applications you distribute provided that the copyright text
 * below is included in the resulting source code, for example:
 * "Portions Copyright (C) James Boer, 2000"
 */

#include <iostream>
#include <vector>

using namespace std;

// Typedef the container and iterator names for better readability
// 为了提高可读性，定义容器和迭代器的名字
typedef vector<int> IntVector;
typedef IntVector::iterator IntVectItor;

int main()
{
    // Create a vector object of integers
    // 创建一个整数向量对象
    IntVector c;
    // Reserve room for 10 integers
    // 保留10个整数的空间
    c.reserve(10);

    // Fill the vector with 3 different elements
    // 将3个不同的元素填入向量中
    c.push_back(3);
    c.push_back(99);
    c.push_back(42);

    // Now loop and print out all the element values
    // 现在循环并打出所有元素值
    for (IntVectItor itor = c.begin(); itor != c.end(); ++itor)
        cout << "element value = " << (*itor) << endl;

    // Since the elements have been created, we can access or replace
    // them just like a normal array.
    // 创建了元素，我们可以向在一般数组中那样访问或替换它们。
    c[0] = 12;
    c[1] = 32;
    c[2] = 999;
    for (auto i = 0u; i < c.size(); i++)
        cout << "element value = " << c[i] << endl;
}
