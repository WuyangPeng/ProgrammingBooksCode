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
// Ϊ����߿ɶ��ԣ����������͵�����������
typedef deque<int> IntDeque;
typedef IntDeque::reverse_iterator IntDequeRItor;

int main()
{
    // Create a deque container of integers
    // ����һ������˫��������
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
    // ���ѭ��������
    // ��Ҫʹ��ר�õĵ�������д��
    for (IntDequeRItor ritor = c.rbegin(); ritor != c.rend(); ++ritor)
        cout << "Value = " << (*ritor) << endl;

    // remove the first and last elements
    // ɾ����һ�������һ��Ԫ��
    c.pop_front();
    c.pop_back();

    // Accessing elements directly - if needed remember to check to see
    // the deque is not empty.  Accessing non-existant elements will
    // lead to undefined behavior; probably an access violation
    // ֱ�ӷ���Ԫ�ء��������Ҫ���鿴˫�����Ƿ�ǿ�
    // ���ʲ����ڵ�Ԫ�ؽ����²���Ԥ�Ƶ���Ϊ���ܿ��ܲ�������Υ��
    if (!c.empty())
    {
        cout << "Front = " << c.front() << endl;
        cout << "Back = " << c.back() << endl;
    }
}
