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

        assert(src != 0);  // 检查src向量必须不为空（NULL）
        assert(dst != 0);  // 检查dst向量必须不为空（NULL）

        length = sqrt((src->x * src->x) + (src->y * src->y) + (src->z * src->z));

        assert(length != 0);  // 检查长度不能为零（避免被零除异常）

        dst->x = src->x / length;
        dst->y = src->y / length;
        dst->z = src->z / length;
    }
}
