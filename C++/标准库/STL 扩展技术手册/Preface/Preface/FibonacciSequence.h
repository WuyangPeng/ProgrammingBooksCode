#pragma once

class fibonacci_sequence
{
public:
    typedef fibonacci_sequence class_type;

    class const_iterator
    {
    public:
        typedef const_iterator class_type;

        class_type& operator++();
    };
};