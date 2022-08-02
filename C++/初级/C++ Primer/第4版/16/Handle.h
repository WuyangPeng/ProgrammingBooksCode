/*
 * This file contains code from "C++ Primer, Fourth Edition", by Stanley B.
 * Lippman, Jose Lajoie, and Barbara E. Moo, and is covered under the
 * copyright and warranty notices given in that book:
 * 
 * "Copyright (c) 2005 by Objectwrite, Inc., Jose Lajoie, and Barbara E. Moo."
 * 
 * 
 * "The authors and publisher have taken care in the preparation of this book,
 * but make no expressed or implied warranty of any kind and assume no
 * responsibility for errors or omissions. No liability is assumed for
 * incidental or consequential damages in connection with or arising out of the
 * use of the information or programs contained herein."
 * 
 * Permission is granted for this code to be used for educational purposes in
 * association with the book, given proper citation if and when posted or
 * reproduced.Any commercial use of this code requires the explicit written
 * permission of the publisher, Addison-Wesley Professional, a division of
 * Pearson Education, Inc. Send your request for permission, stating clearly
 * what code you would like to use, and in what specific way, to the following
 * address: 
 * 
 * 	Pearson Education, Inc.
 * 	Rights and Contracts Department
 * 	75 Arlington Street, Suite 300
 * 	Boston, MA 02216
 * 	Fax: (617) 848-7047
*/ 

#include <stdexcept>

template <class T> class Handle {
public:
    // unbound handle
    Handle(T *p = 0): ptr(p), use(new size_t(1)) { }

    // overloaded operators to support pointer behavior
    T& operator*();
    T* operator->();
    const T& operator*() const;
    const T* operator->() const;

    // copy control: normal pointer behavior, but last Handle deletes the object
    Handle(const Handle& h): ptr(h.ptr), use(h.use) 
                                        { ++*use; }
    Handle& operator=(const Handle&);
    ~Handle() { rem_ref(); }
private:
    T* ptr;          // shared object
    size_t *use;     // count of how many Handles point to *ptr
    void rem_ref() 
        { if (--*use == 0) { delete ptr; delete use; } }
};

template <class T> 
inline Handle<T>& Handle<T>::operator=(const Handle &rhs)
{
    ++*rhs.use;    // protect against self-assignment 
    rem_ref();     // decrement use count and delete pointers if needed
    ptr = rhs.ptr;
    use = rhs.use;
    return *this;
}

template <class T> inline T& Handle<T>::operator*() 
{ 
    if (ptr) return *ptr; 
    throw std::runtime_error
                   ("dereference of unbound Handle"); 
}
template <class T> inline T* Handle<T>::operator->() 
{ 
    if (ptr) return ptr; 
    throw std::runtime_error
                   ("access through unbound Handle");

}

template <class T> inline
const T& Handle<T>::operator*() const
{ 
    if (ptr) return *ptr; 
    throw std::runtime_error("dereference of unbound Handle");
}
template <class T> inline
const T* Handle<T>::operator->() const
{ 
    if (ptr) return ptr; 
    throw std::runtime_error("access through unbound Handle");

}
