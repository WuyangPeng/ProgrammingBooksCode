////////////////////////////////////////////////////////////////////////////////
// The Loki Library
// Copyright (c) 2007 by Rich Sposato
// Permission to use, copy, modify, distribute and sell this software for any
//     purpose is hereby granted without fee, provided that the above copyright
//     notice appear in all copies and that both that copyright notice and this
//     permission notice appear in supporting documentation.
// The author makes no representations about the
//     suitability of this software for any purpose. It is provided "as is"
//     without express or implied warranty.
////////////////////////////////////////////////////////////////////////////////

#ifndef LOKI_CHECK_RETURN_INC_
#define LOKI_CHECK_RETURN_INC_

// $Id$

#include <assert.h>
#include <stdio.h>
#include <stdexcept>

namespace Loki
{
    // ----------------------------------------------------------------------------

    ////////////////////////////////////////////////////////////////////////////////
    ///  \class CheckReturn
    ///
    ///  \par Purpose
    ///  C++ provides no mechanism within the language itself to force code to
    ///  check the return value from a function call.  This simple class provides
    ///  a mechanism by which programmers can force calling functions to check the
    ///  return value.  Or at least make them consciously choose to disregard the
    ///  return value.  If the calling function fails to use or store the return
    ///  value, the destructor calls the OnError policy.
    ///  C++在语言本身内未提供任何机制来强制代码检查函数调用的返回值。 
    ///  这个简单的类提供了一种机制，程序员可以通过该机制强制调用函数检查返回值。 
    ///  或至少使他们有意识地选择忽略返回值。 如果调用函数无法使用或存储返回值，则析构函数将调用OnError策略。
    ///
    ///  \par Template Parameters
    ///  CheckReturn has two template parameters, Value and OnError.
    ///  CheckReturn具有两个模板参数，Value和OnError。
    ///  - Value is the return type from the function.  CheckReturn stores a copy of
    ///  it rather than a reference or pointer since return value could be local to
    ///  a function.  CheckReturn works best when the return type is a built-in
    ///  primitive (bool, int, etc...) a pointer, or an enum (such as an error
    ///  condition enum).  It can work with other types that have cheap copy
    ///  operations.
    ///  - Value是函数的返回类型。 CheckReturn存储它的副本而不是引用或指针，因为返回值可能是函数的局部值。
    ///  当返回类型是内置基元（bool, int等），指针或枚举（例如错误条件枚举）时，CheckReturn效果最佳。
    ///  它可以与其他具有廉价复制操作的类型一起使用。
    ///  - OnError is a policy class indicating how to handle the situation when a
    ///  caller does not check or copy the returned value.  Loki provides some
    ///  policy classs and you may also write your own.  For example, you can write
    ///  a policy to create a message box when the function ignores the return value.
    ///  That would quickly tell you places where code ignores the function call.
    ///  If your write your own, you only need a templated class or struct with a
    ///  public function named "run" that accepts a reference to a const value.
    ///  - OnError是一个策略类，指示在调用者不检查或复制返回值时如何处理情况。
    ///  Loki提供了一些策略类，您也可以编写自己的策略类。
    ///  例如，您可以编写一个函数忽略返回值时创建消息框的策略。
    ///  这样可以迅速告诉您代码忽略函数调用的位置。
    ///  如果您用自己的方式编写，则只需要带有公共函数“run”的模板类或结构即可，该公共函数接受对const值的引用。
    ///
    /// @par Provided Policy Classes
    ///  - IgnoreReturnValue Deliberately ignores when the caller ignores the return value.
    ///  - IgnoreReturnValue当调用方忽略返回值时，故意忽略。
    ///  - TriggerAssert Asserts in debug builds if the caller ignores the return value.
    ///  - TriggerAssert如果调用者忽略返回值，则在调试版本中触发断言。
    ///  - FprintfStderr Prints out an error message if the caller ignores the return value.
    ///  - FprintfStderr如果调用方忽略返回值，则输出错误消息。
    ///  - ThrowTheValue Throws the ignored value as an exception.
    ///  - ThrowTheValue引发被忽略的值作为异常。
    ///  - ThrowLogicError Throws a logic_error exception to indicate a programming error.
    ///  - 引发logic_error异常以指示编程错误。
    ////////////////////////////////////////////////////////////////////////////////

    template <class T>
    struct IgnoreReturnValue
    {
        static void run(const T&)
        {
            /// Do nothing at all.
            /// 什么都不做。
        }
    };

    template <class T>
    struct ThrowTheValue
    {
        static void run(const T& value)
        {
            throw value;
        }
    };

    template <class T>
    struct ThrowLogicError
    {
        static void run(const T&)
        {
            throw ::std::logic_error("CheckReturn: return value was not checked.\n");
        }
    };

    template <class T>
    struct TriggerAssert
    {
        static void run(const T&)
        {
            assert(0);
        }
    };

    template <class T>
    struct FprintfStderr
    {
        static void run(const T&)
        {
            fprintf(stderr, "CheckReturn: return value was not checked.\n");
        }
    };

    template <class Value, template <class> class OnError = TriggerAssert>
    class CheckReturn
    {
    public:
        /// Conversion constructor changes Value type to CheckReturn type.
        /// 转换构造函数将值类型更改为CheckReturn类型。
        inline CheckReturn(const Value& value)
            : m_value(value), m_checked(false)
        {
        }

        /// Copy-constructor allows functions to call another function within the
        /// return statement.  The other CheckReturn's m_checked flag is set since
        /// its duty has been passed to the m_checked flag in this one.
        /// 复制构造函数允许函数在return语句中调用另一个函数。
        /// 另一个CheckReturn的m_checked标志已设置，因为它的职责已传递给该对象中的m_checked标志。
        inline CheckReturn(const CheckReturn& that)
            : m_value(that.m_value), m_checked(false)
        {
            that.m_checked = true;
        }

        /// Destructor checks if return value was used.
        /// 析构函数检查是否使用了返回值。
        inline ~CheckReturn(void)
        {
            // If m_checked is false, then a function failed to check the
            // return value from a function call.
            // 如果m_checked为false，则函数没有检查函数调用的返回值。
            if (!m_checked)
                OnError<Value>::run(m_value);
        }

        /// Conversion operator changes CheckReturn back to Value type.
        /// 转换运算符将CheckReturn更改回Value类型。
        inline operator Value(void)
        {
            m_checked = true;
            return m_value;
        }

    private:
        /// Default constructor not implemented.
        CheckReturn(void) = delete;

        /// Copy-assignment operator not implemented.
        CheckReturn& operator=(const CheckReturn& that) = delete;

        /// Copy of returned value.
        /// Copy of returned value.
        Value m_value;

        /// Flag for whether calling function checked return value yet.
        /// 调用函数是否检查返回值的标志。
        mutable bool m_checked;
    };

    // ----------------------------------------------------------------------------

}  // namespace Loki

#endif  // end file guardian
