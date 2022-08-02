#pragma once

#include <Windows.h>
#include <cassert>
#include <cmath>

class Vec
{
public:
    float x;
    float y;
    float z;
};

namespace Assert
{
    inline void VectorNormalize(Vec* src, Vec* dst)
    {
        float length;

        assert(src != 0);  // ���src�������벻Ϊ�գ�NULL��
        assert(dst != 0);  // ���dst�������벻Ϊ�գ�NULL��

        length = sqrt((src->x * src->x) + (src->y * src->y) + (src->z * src->z));

        assert(length != 0);  // ��鳤�Ȳ���Ϊ�㣨���ⱻ����쳣��

        dst->x = src->x / length;
        dst->y = src->y / length;
        dst->z = src->z / length;
    }
}
