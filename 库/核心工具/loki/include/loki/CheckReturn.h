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
    ///  C++�����Ա�����δ�ṩ�κλ�����ǿ�ƴ����麯�����õķ���ֵ�� 
    ///  ����򵥵����ṩ��һ�ֻ��ƣ�����Ա����ͨ���û���ǿ�Ƶ��ú�����鷵��ֵ�� 
    ///  ������ʹ��������ʶ��ѡ����Է���ֵ�� ������ú����޷�ʹ�û�洢����ֵ������������������OnError���ԡ�
    ///
    ///  \par Template Parameters
    ///  CheckReturn has two template parameters, Value and OnError.
    ///  CheckReturn��������ģ�������Value��OnError��
    ///  - Value is the return type from the function.  CheckReturn stores a copy of
    ///  it rather than a reference or pointer since return value could be local to
    ///  a function.  CheckReturn works best when the return type is a built-in
    ///  primitive (bool, int, etc...) a pointer, or an enum (such as an error
    ///  condition enum).  It can work with other types that have cheap copy
    ///  operations.
    ///  - Value�Ǻ����ķ������͡� CheckReturn�洢���ĸ������������û�ָ�룬��Ϊ����ֵ�����Ǻ����ľֲ�ֵ��
    ///  ���������������û�Ԫ��bool, int�ȣ���ָ���ö�٣������������ö�٣�ʱ��CheckReturnЧ����ѡ�
    ///  �������������������۸��Ʋ���������һ��ʹ�á�
    ///  - OnError is a policy class indicating how to handle the situation when a
    ///  caller does not check or copy the returned value.  Loki provides some
    ///  policy classs and you may also write your own.  For example, you can write
    ///  a policy to create a message box when the function ignores the return value.
    ///  That would quickly tell you places where code ignores the function call.
    ///  If your write your own, you only need a templated class or struct with a
    ///  public function named "run" that accepts a reference to a const value.
    ///  - OnError��һ�������ָ࣬ʾ�ڵ����߲������Ʒ���ֵʱ��δ��������
    ///  Loki�ṩ��һЩ�����࣬��Ҳ���Ա�д�Լ��Ĳ����ࡣ
    ///  ���磬�����Ա�дһ���������Է���ֵʱ������Ϣ��Ĳ��ԡ�
    ///  ��������Ѹ�ٸ�����������Ժ������õ�λ�á�
    ///  ��������Լ��ķ�ʽ��д����ֻ��Ҫ���й���������run����ģ�����ṹ���ɣ��ù����������ܶ�constֵ�����á�
    ///
    /// @par Provided Policy Classes
    ///  - IgnoreReturnValue Deliberately ignores when the caller ignores the return value.
    ///  - IgnoreReturnValue�����÷����Է���ֵʱ��������ԡ�
    ///  - TriggerAssert Asserts in debug builds if the caller ignores the return value.
    ///  - TriggerAssert��������ߺ��Է���ֵ�����ڵ��԰汾�д������ԡ�
    ///  - FprintfStderr Prints out an error message if the caller ignores the return value.
    ///  - FprintfStderr������÷����Է���ֵ�������������Ϣ��
    ///  - ThrowTheValue Throws the ignored value as an exception.
    ///  - ThrowTheValue���������Ե�ֵ��Ϊ�쳣��
    ///  - ThrowLogicError Throws a logic_error exception to indicate a programming error.
    ///  - ����logic_error�쳣��ָʾ��̴���
    ////////////////////////////////////////////////////////////////////////////////

    template <class T>
    struct IgnoreReturnValue
    {
        static void run(const T&)
        {
            /// Do nothing at all.
            /// ʲô��������
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
        /// ת�����캯����ֵ���͸���ΪCheckReturn���͡�
        inline CheckReturn(const Value& value)
            : m_value(value), m_checked(false)
        {
        }

        /// Copy-constructor allows functions to call another function within the
        /// return statement.  The other CheckReturn's m_checked flag is set since
        /// its duty has been passed to the m_checked flag in this one.
        /// ���ƹ��캯����������return����е�����һ��������
        /// ��һ��CheckReturn��m_checked��־�����ã���Ϊ����ְ���Ѵ��ݸ��ö����е�m_checked��־��
        inline CheckReturn(const CheckReturn& that)
            : m_value(that.m_value), m_checked(false)
        {
            that.m_checked = true;
        }

        /// Destructor checks if return value was used.
        /// ������������Ƿ�ʹ���˷���ֵ��
        inline ~CheckReturn(void)
        {
            // If m_checked is false, then a function failed to check the
            // return value from a function call.
            // ���m_checkedΪfalse������û�м�麯�����õķ���ֵ��
            if (!m_checked)
                OnError<Value>::run(m_value);
        }

        /// Conversion operator changes CheckReturn back to Value type.
        /// ת���������CheckReturn���Ļ�Value���͡�
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
        /// ���ú����Ƿ��鷵��ֵ�ı�־��
        mutable bool m_checked;
    };

    // ----------------------------------------------------------------------------

}  // namespace Loki

#endif  // end file guardian
