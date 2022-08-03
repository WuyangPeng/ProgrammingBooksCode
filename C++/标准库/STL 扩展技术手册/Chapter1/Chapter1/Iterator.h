#pragma once

class V
{
};

class II
{
public:
    II& operator++()
    {
        return *this;
    }

    II operator++(int)
    {
        return *this;
    }

    V operator*()
    {
        return V{};
    }
};

class OI
{
public:
    OI& operator++()
    {
        return *this;
    }

    OI operator++(int)
    {
        return *this;
    }

    V& operator*()
    {
        return v;
    }

private:
    V v{};
};

class FI
{
public:
    FI& operator++()
    {
        return *this;
    }

    FI operator++(int)
    {
        return *this;
    }

    V operator*()
    {
        return V{};
    }
};

class BI
{
public:
    BI& operator++()
    {
        return *this;
    }

    BI operator++(int)
    {
        return *this;
    }

    BI& operator--()
    {
        return *this;
    }

    BI operator--(int)
    {
        return *this;
    }
};

class RI
{
public:
    RI& operator++()
    {
        return *this;
    }

    RI operator++(int)
    {
        return *this;
    }

    RI& operator--()
    {
        return *this;
    }

    RI operator--(int)
    {
        return *this;
    }

    V& operator*()
    {
        return v;
    }

    V& operator[](int)
    {
        return v;
    }

private:
    V v{};
};

template <typename T>
class some_iterator
{
public:
    T* operator->()
    {
        return &t;
    }

private:
    T t{};
};

class D2
{
public:
    void release()
    {
    }
};

class D1
{
public:
    void release()
    {
    }

    D2* operator->()
    {
        return &t;
    }

    D2& operator*()
    {
        return t;
    }

private:
    D2 t{};
};

class I
{
public:
    D1* operator->()
    {
        return &t;
    }

    D1& operator*()
    {
        return t;
    }

private:
    D1 t{};
};

class C
{
public:
    I begin()
    {
        return I();
    }
};

bool operator==(const II&, const II&)
{
    return true;
}

bool operator!=(const II&, const II&)
{
    return false;
}

bool operator==(const V&, const V&)
{
    return true;
}

int operator-(const II&, const II&)
{
    return 0;
}

bool operator==(const OI&, const OI&)
{
    return true;
}

bool operator!=(const OI&, const OI&)
{
    return false;
}

bool operator==(const FI&, const FI&)
{
    return true;
}

bool operator!=(const FI&, const FI&)
{
    return false;
}

int operator-(const FI&, const FI&)
{
    return 0;
}

bool operator==(const BI&, const BI&)
{
    return true;
}

bool operator!=(const BI&, const BI&)
{
    return false;
}

bool operator==(const RI&, const RI&)
{
    return true;
}

bool operator!=(const RI&, const RI&)
{
    return false;
}

RI operator+(const RI& lhs, int)
{
    return lhs;
}

RI operator-(const RI& lhs, int)
{
    return lhs;
}

template <typename T>
bool operator==(const some_iterator<T>&, const some_iterator<T>&)
{
    return true;
}
template <typename T>
bool operator!=(const some_iterator<T>&, const some_iterator<T>&)
{
    return false;
}