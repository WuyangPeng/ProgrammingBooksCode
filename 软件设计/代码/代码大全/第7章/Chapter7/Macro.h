#pragma once

#include <algorithm>

// һ��������ȷչ���ĺ�
#define Cube1(a) a* a* a

// �Բ�������չ���ĺ�
#define Cube2(a) ��a��* ��a��* ��a��

// ������ȷչ���ĺ�
#define Cube3(a) ����a��* ��a��* ��a����

#define MIN_INDEX 0
#define MAX_INDEX 10

// һ���޷������ĺ��ж������ĺ�
#define LookupEntry1(key, index)        \
    index = (key - 10) / 5;             \
    index = std::min(index, MAX_INDEX); \
    index = std::max(index, MIN_INDEX);

// ������ȷ�����ĺ��ж������ĺ�
#define LookupEntry2(key, index)            \
    {                                       \
        index = (key - 10) / 5;             \
        index = std::min(index, MAX_INDEX); \
        index = std::max(index, MIN_INDEX); \
    }