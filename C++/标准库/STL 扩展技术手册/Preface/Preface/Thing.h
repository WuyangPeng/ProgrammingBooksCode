#pragma once

template <typename iterator>
struct thing
{
    typedef iterator iterator;  // �������
};

template <typename I>
struct thing
{
    typedef I iterator;
};

template <typename Iterator>
struct thing
{
    typedef Iterator iterator;
};