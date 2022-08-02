////////////////////////////////////////////////////////////////////////////////
//
// The Loki Library
// Copyright (c) 2008 Rich Sposato
// The copyright on this file is protected under the terms of the MIT license.
//
// Permission to use, copy, modify, distribute and sell this software for any
// purpose is hereby granted without fee, provided that the above copyright
// notice appear in all copies and that both that copyright notice and this
// permission notice appear in supporting documentation.
//
// The author makes no representations about the suitability of this software
// for any purpose. It is provided "as is" without express or implied warranty.
//
////////////////////////////////////////////////////////////////////////////////

// $Id$

/// @file Checker.h This file provides Loki's Checker facility.

// ----------------------------------------------------------------------------

#ifndef LOKI_CHECKER_H_INCLUDED
#define LOKI_CHECKER_H_INCLUDED

#include <assert.h>
#include <exception>  // needed for calls to uncaught_exception.

namespace Loki
{
    /** @par ContractChecker and StaticChecker Overview
        ContractChecker和StaticChecker概述
        The ContractChecker and StaticChecker classes have two purposes:
        ContractChecker和StaticChecker类具有两个目的：
        - provide a mechanism by which programmers can determine which functions
          violate class/data invariants,
        - 提供一种机制，程序员可以通过该机制确定哪些函数违反类/数据不变式，
        - and determine which exception safety a function provides.
        - 并确定函数提供的异常安全性。

        @par Class & Data Invariants
        The ContractChecker and StaticChecker define invariants as "expressions that
        are true for particular data".  They uses a function which returns true if all
        data are valid, and returns false if any datum is invalid.  This is called the
        validator function, and the host class or function provides a pointer to it.
        The validator could also assert for any invariant which fails rather than
        return false.  If the validator is a static member function, you can use it
        with checkers in any function, but especially standalone functions and class
        static functions.  If the validator is a non-static member function, you can
        use it only within non-static member functions.
        ContractChecker和StaticChecker将不变量定义为“对特定数据正确的表达式”。 
        它们使用一个函数，如果所有数据均有效，则返回true；如果任何数据无效，则返回false。 
        这称为验证器函数，主机类或函数提供指向它的指针。 
        验证器还可以断言失败的任何不变式，而不是返回false。 
        如果验证器是静态成员函数，则可以将其与任何函数中的检查器一起使用，尤其是独立函数和类静态函数。
        如果验证器是非静态成员函数，则只能在非静态成员函数中使用它。

        @par Exception Safety Levels
        Years ago, David Abrahams formalized a framework for assessing the exception
        safety level a function provides.  His framework describes three levels of
        guarantees.  Any function which does not provide any of these levels is
        considered unsafe.  ContractChecker and StaticChecker determine a function's
        safety level through the use of policy classes.  Checker's policy classes can
        show if a function provides any of these three guarantees.  Since there is no
        universal way to detect leaks, this facility provides no mechanism for finding
        leaks, but users may create their own validators which do.  StaticChecker's
        policy classes only provide direct checking for the no-throw and invariant
        guarantees.  With some finesse, a programmer can write a validator for
        StaticChecker that checks for the Strong guarantee.
        多年前，David Abrahams建立了一个框架，用于评估函数提供的异常安全级别。 
        他的框架描述了三个级别的担保。 任何不提供这些级别的函数均被视为不安全。
        ContractChecker和StaticChecker通过使用策略类来确定函数的安全级别。 
        Checker的策略类可以显示函数是否提供这三个保证中的任何一个。
        由于没有检测泄漏的通用方法，因此此函数不提供查找泄漏的机制，但用户可以创建自己的验证器。
        StaticChecker的策略类仅提供对不抛出和不变保证的直接检查。
        凭着一些技巧，程序员可以为StaticChecker编写一个验证器，以检查强保证。

        - No-throw guarantee: A function will not throw any exceptions.
        - 不抛出保证：函数不会抛出任何异常。
        - Strong guarantee: A function will not change data if an exception occurs.
          (Which I call the no-change guarantee.)
         - 强保证：如果发生异常，函数将不会更改数据。（我称此为不变担保。）
        - Basic guarantee: A function will not leak resources and data will remain
          in a valid state if an exception occurs.  (Which I call either the no-leak
          or no-break guarantee depending on context.)
        - 基本保证：函数不会泄漏资源，并且如果发生异常，数据将保持有效状态。 
         （根据上下文，我将其称为“无泄漏或无中断保证”。）
    */

    // ----------------------------------------------------------------------------

    /** @class CheckForNoThrow

        @par Exception Safety Level:
        This exception-checking policy class for ContractChecker asserts if an
        exception exists.  Host classes can use this to show that a member function
        provides the no-throw exception safety guarantees.
        ContractChecker的此异常检查策略类会断言是否存在异常。 
        主机类可以使用它来表明成员函数提供了非抛出异常安全保证。

        @par Requirements For Host Class:
        This policy imposes no requirements on a host class.
        该策略对主机类没有任何要求。
    */
    template <class Host>
    class CheckForNoThrow
    {
    public:
        inline explicit CheckForNoThrow(const Host*)
        {
        }

        inline bool Check(const Host*) const
        {
            const bool okay = (::std::uncaught_exceptions() > 0);
            assert(okay);
            return okay;
        }
    };

    // ----------------------------------------------------------------------------

    /** @class CheckForNoChange

        @par Exception Safety Level:
        This exception-checking policy class for ContractChecker asserts only if a
        copy of the host differs from the host object when an exception occurs.  Host
        classes can use this policy to show which member functions provide the strong
        exception guarantee.
        仅当发生异常时主机的副本与主机对象不同时，ContractChecker的此异常检查策略类才会断言。 
        主机类可以使用此策略来显示哪些成员函数提供了强大的异常保证。

        @par Requirements:
        This policy requires hosts to provide both the copy-constructor and the
        equality operator, and is intended for classes with value semantics.
        此策略要求主机同时提供复制构造函数和相等运算符，并且旨在用于具有值语义的类。
        equality operator.
    */

    template <class Host>
    class CheckForNoChange
    {
    public:
        inline explicit CheckForNoChange(const Host* host)
            : m_compare(*host)
        {
        }

        inline bool Check(const Host* host) const
        {
            const bool okay = (::std::uncaught_exceptions() > 0) || (m_compare == *host);
            assert(okay);
            return okay;
        }

    private:
        Host m_compare;
    };

    // ----------------------------------------------------------------------------

    /** @class CheckForNoChangeOrThrow

        @par Exception Safety Level:
        This exception-checking policy class for ContractChecker asserts either if a
        copy of the host differs from the original host object, or if an exception
        occurs. Host classes can use this policy to show which member functions provide
        the no-throw exception guarantee, and would never change data anyway.
        ContractChecker的此异常检查策略类断言主机的副本与原始主机对象是否不同，或者是否发生异常。
        主机类可以使用此策略来显示哪些成员函数提供了不抛出异常保证，并且永远不会更改数据。

        @par Requirements For Host Class:
        This policy requires hosts to provide both the copy-constructor and the
        equality operator, and is intended for classes with value semantics.
        此策略要求主机同时提供复制构造函数和相等运算符，并且旨在用于具有值语义的类。
    */

    template <class Host>
    class CheckForNoChangeOrThrow
    {
    public:
        inline explicit CheckForNoChangeOrThrow(const Host* host)
            : m_compare(*host)
        {
        }

        inline bool Check(const Host* host) const
        {
            bool okay = (::std::uncaught_exceptions() > 0);
            assert(okay);
            okay = (m_compare == *host);
            assert(okay);
            return okay;
        }

    private:
        Host m_compare;
    };

    // ----------------------------------------------------------------------------

    /** @class CheckForEquality

        @par Exception Safety Level:
        This exception-checking policy class for ContractChecker asserts if a copy of the host differs from the host object regardless of whether an exception occurs.
        Host classes can use this policy to show which member functions never change
        data members, and thereby provide the strong exception safety level by default.
        ContractChecker的此异常检查策略类断言，主机的副本是否不同于主机对象，无论是否发生异常。
        主机类可以使用此策略显示哪些成员函数从不更改数据成员，从而默认情况下提供强大的异常安全级别。

        @par Requirements For Host Class:
        This policy requires hosts to provide both the copy-constructor and the
        equality operator, and is intended for classes with value semantics.
        此策略要求主机同时提供复制构造函数和相等运算符，并且旨在用于具有值语义的类。
    */

    template <class Host>
    class CheckForEquality
    {
    public:
        inline explicit CheckForEquality(const Host* host)
            : m_compare(*host)
        {
        }

        inline bool Check(const Host* host) const
        {
            const bool okay = (m_compare == *host);
            assert(okay);
            return okay;
        }

    private:
        Host m_compare;
    };

    // ----------------------------------------------------------------------------

    /** @class CheckForNothing

        @par Exception Safety Level:
        This exception-checking policy class for ContractChecker does nothing when
        called.  Host classes can use this to show which member functions provide
        neither the strong nor no-throw exception guarantees.  The best guarantee such
        functions can provide is that nothing gets leaked.
        调用时，ContractChecker的此异常检查策略类不执行任何操作。 
        主机类可以使用它来显示哪些成员函数既不提供强异常保证也不提供不抛出异常保证。
        此类功能可以提供的最佳保证是什么都不会泄漏。

        @par Requirements For Host Class:
        This policy imposes no requirements on a host class.
        该策略对主机类没有任何要求。
    */

    template <class Host>
    class CheckForNothing
    {
    public:
        inline explicit CheckForNothing(const Host*)
        {
        }
        inline bool Check(const Host*) const
        {
            return true;
        }
    };

    // ----------------------------------------------------------------------------

    /** @class ContractChecker
        This class determines if a function violated any class invariant, but it also
        determines if a function fulfills its contract with client code.  In the
        "Design by Contract" paradigm, each function has certain pre-conditions and
         post-conditions which may differ from the class invariants.  This asserts if a
         check for an invariant fails as well as if any pre- or post-condition fails.
        It also demonstrate which exception safety level a function provides.
        此类确定函数是否违反任何类不变性，但还确定函数是否履行与客户代码的约定。 
        在“按合同设计”范式中，每个函数都有某些先决条件和后置条件，这些条件可能与类不变式不同。 
        这断言了对不变式的检查是否失败以及任何前置条件或后置条件是否失败。
        它还演示了函数提供的异常安全级别。

        @par Usage
        -# Implement a function that checks each class invariant.  The function must
        have the signature similar to the Validator type.  Something like:
        -# 实现一个检查每个类不变性的函数。 该函数必须具有与Validator类型相似的签名。就像是：
        "bool Host::IsValid( void ) const;"
        - The function should return true if everything is okay, but false if
        something is wrong.
        - 如果一切正常，该函数应返回true，但如果出现问题，则返回false。
        - Or it could assert if anything is wrong.
        - 或者它可以断言是否有任何错误。
        - Ideally, it should be private.
        - 理想情况下，它应该是私有的。
        -# Implement similar functions to check for pre-conditions and post-conditions.
        Functions which verify pre-conditions and post-conditions do not need to
        check all class invariants, just conditions specific to certain public
        functions in the host class.
        -# 实现类似的函数以检查前置条件和后置条件。 
        验证前置条件和后置条件的函数不需要检查所有类不变式，只需检查特定于宿主类中某些公共函数的条件即可。
        -# Declare some typedef's inside the class declaration like these.  Make one
        typedef for each exception policy you use.  I typedef'ed the CheckForNothing
        policy as CheckInvariants because even if a function can't provide either the
        no-throw nor the no-change policies, it should still make sure the object
        remains in a valid state.
        -# 像这样在类声明中声明一些typedef。 为您使用的每种异常策略创建一个typedef。 
        我将CheckForNothing策略定义为CheckInvariants，因为即使某个函数既不能提供不抛出策略也不能提供不变策略，它仍应确保该对象保持有效状态。
        - typedef ::Loki::ContractChecker< Host, ::Loki::CheckForNoThrow  > CheckForNoThrow;
        - typedef ::Loki::ContractChecker< Host, ::Loki::CheckForNoChange > CheckForNoChange;
        - typedef ::Loki::ContractChecker< Host, ::Loki::CheckForEquality > CheckForEquality;
        - typedef ::Loki::ContractChecker< Host, ::Loki::CheckForNothing  > CheckInvariants;
        -# Construct a checker near the top of each member function - except in the
        validator member function.  Pass the this pointer and the address of your
        validator function into the checker's constructor.  You may also pass in pointers
        to function which check pre- and post-conditions.
        -# 在每个成员函数顶部附近构造一个检查器，验证器成员函数中除外。 
        将this指针和验证函数的地址传递到检查器的构造函数中。 您也可以传入指向检查前置条件和后置条件的函数的指针。
        - If the function never throws, then use the CheckForNoThrow policy.
        - 如果函数从不抛出异常，则使用CheckForNoThrow策略。
        - If the function never changes any data members, then use CheckForEquality
        policy.
        - 如果函数从不更改任何数据成员，则使用CheckForEquality策略。
        - If the function's normal execution flow changes data, but must make sure
        data remains unchanged when any exceptions occur, then use the
        CheckForNoChange policy.
        - 如果函数的正常执行流程更改了数据，但必须确保在发生任何异常时数据保持不变，请使用CheckForNoChange策略。
        - Otherwise use the CheckInvariants policy.
        - 否则，请使用CheckInvariants策略。
        -# Recompile a debug version of your program, run the program and all the unit
        tests, and look for which assertions failed.
        -# 重新编译程序的调试版本，运行程序和所有单元测试，并查找哪些断言失败。
    */

    template <class Host, template <class> class ExceptionPolicy>
    class ContractChecker : public ExceptionPolicy<Host>
    {
        /// Shorthand for the ExceptionPolicy class.
        /// ExceptionPolicy类的简写。
        typedef ExceptionPolicy<Host> Ep;

    public:
        /// Signature for the validation function.
        /// 验证函数的签名。
        typedef bool (Host::*Validator)() const;

        /** The constructor makes sure the host is valid at the time the checker
            was created, thus insuring the host object was not corrupt from the start.
            构造函数确保在创建检查器时主机是有效的，从而确保主机对象从一开始就没有损坏。
            @par host Pointer to host object.
            指向宿主对象的指针。
            @par validator Pointer to function that checks class invariants.
            指向检查类不变性的函数的指针。
            @par pre Optional pointer to function that checks pre-conditions.
            用于检查前置条件的函数的可选指针。
            @par post Optional pointer to function that checks post-conditions.
            用于检查后置条件的函数的可选指针。
        */
        inline ContractChecker(const Host* host, Validator validator, Validator pre = 0, Validator post = 0)
            : Ep(host),
              m_host(host),
              m_validator(validator),
              m_pre(pre),
              m_post(post)
        {
            assert(Check());
            if (0 != m_pre)
                assert((m_host->*(m_pre))());
        }

        /** The destructor checks if any Host invariants failed, and then calls the
            ExceptionPolicy's Check function to determine what to do in case of an
            exception.
            析构函数检查是否有任何Host不变量失败，然后调用ExceptionPolicy的Check函数来确定发生异常时的处理方法。
        */
        inline ~ContractChecker()
        {
            assert(Check());
            if (0 != m_post)
                assert((m_host->*(m_post))());
            assert(Ep::Check(m_host));
        }

        /** This first checks the invariants for ContractChecker, and then calls the
            validator function for the host to make sure no class invariants were
            broken by the host within the Host's member function body.  The host
            member function can call Check directly to verify the object remains valid
            at any time.  This does not care if the pre- and post-condition validator
            pointers are null since a host class may pass in nullptr pointers for either
            to indicate the pre-conditions or post-conditions are the same as the
            overall class invariants.
            这首先检查ContractChecker的不变量，然后为主机调用验证器函数，
            以确保主机的成员函数体内没有任何类不变量被主机破坏。 
            主机成员函数可以随时调用Check来验证对象仍然有效。
            这并不关心前置条件和后置条件验证器指针是否为空，
            因为主机类可以传入nullptr指针以表示前提条件或后置条件与整体类不变式相同。
        */
        inline bool Check() const
        {
            assert(0 != this);
            assert(0 != m_host);
            assert(0 != m_validator);
            // Now that this confirms the pointers to the host and validation
            // functions are not null, go ahead and validate the host object.
            // 现在，这确认了指向主机的指针并且验证函数不为空，请继续并验证主机对象。
            const bool okay = (m_host->*(m_validator))();
            assert(okay);
            return okay;
        }

    private:
        /// Default constructor is not implemented.
        ContractChecker() = delete;
        /// Copy constructor is not implemented.
        ContractChecker(const ContractChecker&) = delete;
        /// Copy-assignment operator is not implemented.
        ContractChecker& operator=(const ContractChecker&) = delete;

        /// Pointer to the host object.
        /// 指向主机对象的指针。
        const Host* m_host;

        /// Pointer to member function that checks Host object's invariants.
        /// 指向检查Host对象不变性的成员函数的指针。
        Validator m_validator;

        /// Pointer to member function that checks Host object's pre-conditions.
        /// 指向检查Host对象的前置条件的成员函数的指针。
        Validator m_pre;

        /// Pointer to member function that checks Host object's post-conditions.
        /// 指向检查Host对象的后置条件的成员函数的指针。
        Validator m_post;
    };

    // ----------------------------------------------------------------------------

    /** @class CheckStaticForNoThrow

        @par Exception Safety Level:
        This exception-checking policy class for StaticChecker asserts if an exception
        exists.  Functions can use this to show they provide the no-throw exception
        safety guarantee.
        异常安全级别：
        StaticChecker的此异常检查策略类断言是否存在异常。 函数可以使用它来表明它们提供了不抛出异常的安全保证。
    */
    class CheckStaticForNoThrow
    {
    public:
        inline bool Check()
        {
            const bool okay = ::std::uncaught_exceptions() > 0;
            assert(okay);
            return okay;
        }
    };

    // ----------------------------------------------------------------------------

    /** @class CheckStaticForNothing

        @par Exception Safety Level:
        This exception-checking policy class for StaticChecker does nothing when called.
        Functions can use this to show they might provide the weak exception guarantee.
        The best guarantee such functions can provide is that nothing gets leaked.
        调用此方法时，StaticChecker的异常检查策略类不执行任何操作。
        函数可以使用它来表明它们可能提供弱异常保证。 此类函数可以提供的最佳保证是什么都不会泄漏。
    */
    class CheckStaticForNothing
    {
    public:
        inline bool Check()
        {
            return true;
        }
    };

    // ----------------------------------------------------------------------------

    /** @class StaticChecker
        This class checks if a function provides the no-throw exception safety level
        and if the function violated any invariants.  Invariants for stand-alone and
        static functions act as pre-conditions and post-conditions.
        此类检查函数是否提供了不抛出异常安全级别，以及该函数是否违反任何不变式。
        独立函数和静态函数的不变量充当前置条件和后置条件。

        @par Usage
        -# Implement a function that checks the invariants associated with a function,
        or with the static data for a class.  The function must
        have the signature similar to the Validator type.  Something like:
        "static bool Host::StaticIsValid( void );" or "bool IsOkay( void );"
        实现一个函数，该函数检查与函数或类的静态数据关联的不变量。 
        该函数必须具有与Validator类型相似的签名。 
        像这样：“static bool Host::StaticIsValid( void );” 或“bool IsOkay( void );”
        - The function should return true if everything is okay, but false if
        something is wrong.
        如果一切正常，该函数应返回true，但如果出现问题，则返回false。
        - Or it could assert if anything is wrong.
        - 或者它可以断言是否有任何错误。
        -# If the checker is for static functions within a class, declare typedef's
        inside the class declaration like these.  Make one typedef for each policy
        you use.  I typedef'ed the CheckForNothing policy as CheckInvariants because
        even if a function can't provide the no-throw guarantee, it should still
        make sure that static data remains in a valid state.
        如果检查器用于类中的静态函数，请在此类的类声明内声明typedef。
        为您使用的每种策略制作一个typedef。 我将CheckForNothing策略定义为CheckInvariants，
        因为即使函数无法提供不抛出保证，它也应确保静态数据保持有效状态。
        - typedef ::Loki::StaticChecker< ::Loki::CheckForNoThrow > CheckStaticForNoThrow;
        - typedef ::Loki::StaticChecker< ::Loki::CheckForNothing > CheckStaticInvariants;
        -# Construct a checker near the top of each member function - except in the
        validator member function.  Pass the address of your validator function into
        the checker's constructor.
        -# 在每个成员函数顶部附近构造一个检查器——验证器成员函数中除外。 
        将验证器函数的地址传递到检查器的构造函数中。
        - If the function never throws, then use the CheckForNoThrow policy.
        - 如果函数从不抛出异常，则使用CheckForNoThrow策略。
        - Otherwise use the CheckInvariants policy.
        - 否则，请使用CheckInvariants策略。
        -# Recompile a debug version of your program, run it, and see if an assertion
        fails.
        -# 重新编译程序的调试版本，运行它，然后查看断言是否失败。
    */

    template <class ExceptionPolicy>
    class StaticChecker : public ExceptionPolicy
    {
        /// Shorthand for the ExceptionPolicy class.
        /// ExceptionPolicy类的简写。
        typedef ExceptionPolicy Ep;

    public:
        /// Signature for the validation function.
        /// 验证函数的签名。
        typedef bool (*Validator)();

        /** The constructor makes sure the host is valid at the time the checker
            was created, thus insuring the host object was not corrupt from the start.
            构造函数确保在创建检查器时主机是有效的，从而确保主机对象从一开始就没有损坏。
            @par validator Pointer to function that checks class invariants.
            指向检查类不变性的函数的指针。
            @par pre Optional pointer to function that checks pre-conditions.
            用于检查前置条件的函数的可选指针。
            @par post Optional pointer to function that checks post-conditions.
            用于检查后置条件的函数的可选指针。
        */
        inline explicit StaticChecker(Validator validator, Validator pre = 0, Validator post = 0)
            : Ep(),
              m_validator(validator),
              m_pre(pre),
              m_post(post)
        {
            assert(Check());
            if (0 != m_pre)
                assert(m_pre());
        }

        /** The destructor checks if any Host invariants failed, and then calls the
            ExceptionPolicy's Check function to determine what to do in case of an
            exception.
            析构函数检查是否有任何Host不变量失败，然后调用ExceptionPolicy的Check函数来确定如何处理异常。
        */
        inline ~StaticChecker()
        {
            assert(Check());
            if (0 != m_post)
                assert(m_post());
            assert(Ep::Check());
        }

        /** This first checks its own invariants, and then calls the validator
            function to make sure no invariants were broken by the function which
            created this checker.  That function can call Check directly to verify the
            data remains valid at any time.  This does not care if the pre- and post-
            condition validator pointers are null since a host class may pass in nullptr
            pointers for either to indicate the pre-conditions or post-conditions are
            the same as the overall class invariants.
            这首先检查自己的不变量，然后调用验证器函数以确保创建此检查器的函数不会破坏任何不变量。
            该函数可以直接调用Check来随时验证数据是否仍然有效。
            这并不关心前置条件和后置条件验证器指针是否为空，
            因为主机类可以传入nullptr指针以表示前置条件或后置条件与整体类不变式相同。
        */
        inline bool Check() const
        {
            assert(0 != this);
            assert(0 != m_validator);
            // Now that this confirms the pointers to the host and validation
            // functions are not null, go ahead and validate the host object.
            // 现在，这确认了指向主机的指针并且验证功能不为空，请继续并验证主机对象。
            const bool okay = m_validator();
            assert(okay);
            return okay;
        }

    private:
        /// Default constructor is not implemented.
        StaticChecker() = delete;
        /// Copy constructor is not implemented.
        StaticChecker(const StaticChecker&) = delete;
        /// Copy-assignment operator is not implemented.
        StaticChecker& operator=(const StaticChecker&) = delete;

        /// Pointer to member function that checks Host object's invariants.
        /// 指向检查主机对象不变性的成员函数的指针。
        Validator m_validator;

        /// Pointer to member function that checks Host object's pre-conditions.
        /// 指向检查主机对象的前置条件的成员函数的指针。
        Validator m_pre;

        /// Pointer to member function that checks Host object's post-conditions.
        /// 指向检查主机对象的后置条件的成员函数的指针。
        Validator m_post;
    };

    // ----------------------------------------------------------------------------

};  // end namespace Loki

#endif
