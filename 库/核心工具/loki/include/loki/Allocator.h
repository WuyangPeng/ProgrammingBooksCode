////////////////////////////////////////////////////////////////////////////////
// The Loki Library
// Copyright (c) 2008 by Rich Sposato
//
// Permission to use, copy, modify, distribute and sell this software for any
//     purpose is hereby granted without fee, provided that the above copyright
//     notice appear in all copies and that both that copyright notice and this
//     permission notice appear in supporting documentation.
// The author makes no representations about the
//     suitability of this software for any purpose. It is provided "as is"
//     without express or implied warranty.
////////////////////////////////////////////////////////////////////////////////

#ifndef LOKI_ALLOCATOR_HPP_INCLUDED
#define LOKI_ALLOCATOR_HPP_INCLUDED

// $Id: Allocator.h 896 2008-08-08 22:20:05Z syntheticpp $

// Requires project to be compiled with loki/src/SmallObj.cpp and loki/src/Singleton.cpp

#include <loki/SmallObj.h>

namespace Loki
{
    //-----------------------------------------------------------------------------

    /** @class LokiAllocator
        Adapts Loki's Small-Object Allocator for STL container classes.
        This class provides all the functionality required for STL allocators, but
        uses Loki's Small-Object Allocator to perform actual memory operations.
        Implementation comes from a post in Loki forums (by Rasmus Ekman?).
        使Loki的Small-Object Allocator适配STL容器类。 
        此类提供STL分配器所需的所有功能，但使用Loki的小型对象分配器执行实际的内存操作。
        实施来自Loki论坛上的帖子（Rasmus Ekman？）。
    */
    template <typename Type, typename AllocT = Loki::AllocatorSingleton<>>
    class LokiAllocator
    {
    public:
        typedef ::std::size_t size_type;
        typedef ::std::ptrdiff_t difference_type;
        typedef Type* pointer;
        typedef const Type* const_pointer;
        typedef Type& reference;
        typedef const Type& const_reference;
        typedef Type value_type;

        /// Default constructor does nothing.
        inline LokiAllocator() noexcept
        {
        }

        /// Copy constructor does nothing.
        inline LokiAllocator(const LokiAllocator&) noexcept
        {
        }

        /// Type converting allocator constructor does nothing.
        template <typename Type1>
        inline LokiAllocator(const LokiAllocator<Type1>&) noexcept
        {
        }

        /// Destructor does nothing.
        inline ~LokiAllocator() noexcept
        {
        }

        /// Convert an allocator<Type> to an allocator <Type1>.
        /// 将分配器<Type>转换为分配器<Type1>。
        template <typename Type1>
        struct rebind
        {
            typedef LokiAllocator<Type1> other;
        };

        /// Return address of reference to mutable element.
        /// 引用可变元素的返回地址。
        pointer address(reference elem) const
        {
            return &elem;
        }

        /// Return address of reference to const element.
        /// 引用const元素的返回地址。
        const_pointer address(const_reference elem) const
        {
            return &elem;
        }

        /** Allocate an array of count elements.  Warning!  The true parameter in
            the call to Allocate means this function can throw exceptions.  This is
            better than not throwing, and returning a null pointer in case the caller
            assumes the return value is not null.
            分配元素数组。 警告！调用Allocate中的true参数表示此函数可以引发异常。
            这总比不抛出异常好，并且在调用者认为返回值不为null的情况下返回null指针。
            @param count # of elements in array.
            数组中元素的数量。
            @param hint Place where caller thinks allocation should occur.
            提示调用者认为应该进行分配的地方。
            @return Pointer to block of memory.
            指向内存块的指针。
        */
        pointer allocate(size_type count, [[maybe_unused]] const void* hint = 0)
        {
            void* p = AllocT::Instance().Allocate(count * sizeof(Type), true);
            return reinterpret_cast<pointer>(p);
        }

        /// Ask allocator to release memory at pointer with size bytes.
        /// 要求分配器在具有size字节的指针处释放内存。
        void deallocate(pointer p, size_type size)
        {
            AllocT::Instance().Deallocate(p, size * sizeof(Type));
        }

        /// Calculate max # of elements allocator can handle.
        /// 计算分配器可以处理的最大元素数。
        size_type max_size() const noexcept
        {
            // A good optimizer will see these calculations always produce the same
            // value and optimize this function away completely.
            // 一个好的优化器将看到这些计算总是产生相同的值，并且完全消除了此函数。
            const size_type max_bytes = size_type(-1);
            const size_type bytes = max_bytes / sizeof(Type);
            return bytes;
        }

        /// Construct an element at the pointer.
        /// 在指针处构造一个元素。
        void construct(pointer p, const Type& value)
        {
            // A call to global placement new forces a call to copy constructor.
            // 对全局放置new的调用将强制对复制构造函数的调用。
            ::new (p) Type(value);
        }

        /// Destruct the object at pointer.
        /// 销毁指针指向的对象。
        void destroy([[maybe_unused]] pointer p)
        {
            p->~Type();
        }
    };

    //-----------------------------------------------------------------------------

    /** All equality operators return true since LokiAllocator is basically a
        monostate design pattern, so all instances of it are identical.
        由于LokiAllocator基本上是单态设计模式，因此所有相等运算符均返回true，因此其所有实例都是相同的。
    */
    template <typename Type>
    inline bool operator==(const LokiAllocator<Type>&, const LokiAllocator<Type>&)
    {
        return true;
    }

    /** All inequality operators return false since LokiAllocator is basically a
        monostate design pattern, so all instances of it are identical.
        由于LokiAllocator本质上是单态设计模式，因此所有不等式运算符均返回false，因此所有实例均相同。
    */
    template <typename Type>
    inline bool operator!=(const LokiAllocator<Type>&, const LokiAllocator<Type>&)
    {
        return false;
    }

    //-----------------------------------------------------------------------------

}  // namespace Loki

#endif  // LOKI_ALLOCATOR_INCLUDED
