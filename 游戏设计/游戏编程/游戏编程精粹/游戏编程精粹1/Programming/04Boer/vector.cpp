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
// Ϊ����߿ɶ��ԣ����������͵�����������
typedef vector<int> IntVector;
typedef IntVector::iterator IntVectItor;

int main()
{
    // Create a vector object of integers
    // ����һ��������������
    IntVector c;
    // Reserve room for 10 integers
    // ����10�������Ŀռ�
    c.reserve(10);

    // Fill the vector with 3 different elements
    // ��3����ͬ��Ԫ������������
    c.push_back(3);
    c.push_back(99);
    c.push_back(42);

    // Now loop and print out all the element values
    // ����ѭ�����������Ԫ��ֵ
    for (IntVectItor itor = c.begin(); itor != c.end(); ++itor)
        cout << "element value = " << (*itor) << endl;

    // Since the elements have been created, we can access or replace
    // them just like a normal array.
    // ������Ԫ�أ����ǿ�������һ���������������ʻ��滻���ǡ�
    c[0] = 12;
    c[1] = 32;
    c[2] = 999;
    for (auto i = 0u; i < c.size(); i++)
        cout << "element value = " << c[i] << endl;
}
