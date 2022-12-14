////////////////////////////////////////////////////////////////////////////////
// The Loki Library
// Copyright (c) 2006 Richard Sposato
// Copyright (c) 2006 Peter K黰mel
// Permission to use, copy, modify, distribute and sell this software for any
//     purpose is hereby granted without fee, provided that the above copyright
//     notice appear in all copies and that both that copyright notice and this
//     permission notice appear in supporting documentation.
// The authors make no representations about the
//     suitability of this software for any purpose. It is provided "as is"
//     without express or implied warranty.
////////////////////////////////////////////////////////////////////////////////
#ifndef LOKI_CONST_POLICY_INC_
#define LOKI_CONST_POLICY_INC_

// $Id: ConstPolicy.h 769 2006-10-26 10:58:19Z syntheticpp $

namespace Loki
{
    ////////////////////////////////////////////////////////////////////////////////
    /// @note These policy classes are used in LockingPtr and SmartPtr to define
    ///  how const is propagated from the pointee.
    /// 这些策略类在LockingPtr和SmartPtr中使用，以定义如何从指针对象传播const。
    ////////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////////
    ///  \class DontPropagateConst
    ///
    ///  \ingroup ConstGroup
    ///  Don't propagate constness of pointed or referred object.
    /// 不要传播指向或引用对象的常量。
    ////////////////////////////////////////////////////////////////////////////////

    template <class T>
    struct DontPropagateConst
    {
        typedef T Type;
    };

    ////////////////////////////////////////////////////////////////////////////////
    ///  \class PropagateConst
    ///
    ///  \ingroup ConstGroup
    ///  Propagate constness of pointed or referred object.
    /// 传播指向或引用对象的常量。
    ////////////////////////////////////////////////////////////////////////////////

    template <class T>
    struct PropagateConst
    {
        typedef const T Type;
    };

// default will not break existing code
// 默认不会破坏现有代码
#ifndef LOKI_DEFAULT_CONSTNESS
    #define LOKI_DEFAULT_CONSTNESS ::Loki::DontPropagateConst
#endif

}  // end namespace Loki

#endif  // end file guardian
