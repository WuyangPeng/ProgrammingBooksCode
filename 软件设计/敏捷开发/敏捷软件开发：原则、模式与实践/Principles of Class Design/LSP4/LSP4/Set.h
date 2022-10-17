#pragma once

template <class T>
class Set
{
public:
    virtual void Add(const T&) = 0;
    virtual void Delete(const T&) = 0;
    virtual bool IsMember(const T&) const = 0;
};

template <class T>
void PrintSet(const Set<T>& s)
{
    for (Iterator<T> i(s); i; i++)
    {
        std::cout << (*i) << std::endl;
    }
}
