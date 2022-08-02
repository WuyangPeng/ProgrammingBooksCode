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
        ContractChecker��StaticChecker����
        The ContractChecker and StaticChecker classes have two purposes:
        ContractChecker��StaticChecker���������Ŀ�ģ�
        - provide a mechanism by which programmers can determine which functions
          violate class/data invariants,
        - �ṩһ�ֻ��ƣ�����Ա����ͨ���û���ȷ����Щ����Υ����/���ݲ���ʽ��
        - and determine which exception safety a function provides.
        - ��ȷ�������ṩ���쳣��ȫ�ԡ�

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
        ContractChecker��StaticChecker������������Ϊ�����ض�������ȷ�ı��ʽ���� 
        ����ʹ��һ������������������ݾ���Ч���򷵻�true������κ�������Ч���򷵻�false�� 
        ���Ϊ��֤������������������ṩָ������ָ�롣 
        ��֤�������Զ���ʧ�ܵ��κβ���ʽ�������Ƿ���false�� 
        �����֤���Ǿ�̬��Ա����������Խ������κκ����еļ����һ��ʹ�ã������Ƕ����������ྲ̬������
        �����֤���ǷǾ�̬��Ա��������ֻ���ڷǾ�̬��Ա������ʹ������

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
        ����ǰ��David Abrahams������һ����ܣ��������������ṩ���쳣��ȫ���� 
        ���Ŀ����������������ĵ����� �κβ��ṩ��Щ����ĺ���������Ϊ����ȫ��
        ContractChecker��StaticCheckerͨ��ʹ�ò�������ȷ�������İ�ȫ���� 
        Checker�Ĳ����������ʾ�����Ƿ��ṩ��������֤�е��κ�һ����
        ����û�м��й©��ͨ�÷�������˴˺������ṩ����й©�Ļ��ƣ����û����Դ����Լ�����֤����
        StaticChecker�Ĳ�������ṩ�Բ��׳��Ͳ��䱣֤��ֱ�Ӽ�顣
        ƾ��һЩ���ɣ�����Ա����ΪStaticChecker��дһ����֤�����Լ��ǿ��֤��

        - No-throw guarantee: A function will not throw any exceptions.
        - ���׳���֤�����������׳��κ��쳣��
        - Strong guarantee: A function will not change data if an exception occurs.
          (Which I call the no-change guarantee.)
         - ǿ��֤����������쳣������������������ݡ����ҳƴ�Ϊ���䵣������
        - Basic guarantee: A function will not leak resources and data will remain
          in a valid state if an exception occurs.  (Which I call either the no-leak
          or no-break guarantee depending on context.)
        - ������֤����������й©��Դ��������������쳣�����ݽ�������Ч״̬�� 
         �����������ģ��ҽ����Ϊ����й©�����жϱ�֤������
    */

    // ----------------------------------------------------------------------------

    /** @class CheckForNoThrow

        @par Exception Safety Level:
        This exception-checking policy class for ContractChecker asserts if an
        exception exists.  Host classes can use this to show that a member function
        provides the no-throw exception safety guarantees.
        ContractChecker�Ĵ��쳣�������������Ƿ�����쳣�� 
        ���������ʹ������������Ա�����ṩ�˷��׳��쳣��ȫ��֤��

        @par Requirements For Host Class:
        This policy imposes no requirements on a host class.
        �ò��Զ�������û���κ�Ҫ��
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
        ���������쳣ʱ�����ĸ�������������ͬʱ��ContractChecker�Ĵ��쳣��������Ż���ԡ� 
        ���������ʹ�ô˲�������ʾ��Щ��Ա�����ṩ��ǿ����쳣��֤��

        @par Requirements:
        This policy requires hosts to provide both the copy-constructor and the
        equality operator, and is intended for classes with value semantics.
        �˲���Ҫ������ͬʱ�ṩ���ƹ��캯������������������ּ�����ھ���ֵ������ࡣ
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
        ContractChecker�Ĵ��쳣����������������ĸ�����ԭʼ���������Ƿ�ͬ�������Ƿ����쳣��
        ���������ʹ�ô˲�������ʾ��Щ��Ա�����ṩ�˲��׳��쳣��֤��������Զ����������ݡ�

        @par Requirements For Host Class:
        This policy requires hosts to provide both the copy-constructor and the
        equality operator, and is intended for classes with value semantics.
        �˲���Ҫ������ͬʱ�ṩ���ƹ��캯������������������ּ�����ھ���ֵ������ࡣ
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
        ContractChecker�Ĵ��쳣����������ԣ������ĸ����Ƿ�ͬ���������������Ƿ����쳣��
        ���������ʹ�ô˲�����ʾ��Щ��Ա�����Ӳ��������ݳ�Ա���Ӷ�Ĭ��������ṩǿ����쳣��ȫ����

        @par Requirements For Host Class:
        This policy requires hosts to provide both the copy-constructor and the
        equality operator, and is intended for classes with value semantics.
        �˲���Ҫ������ͬʱ�ṩ���ƹ��캯������������������ּ�����ھ���ֵ������ࡣ
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
        ����ʱ��ContractChecker�Ĵ��쳣�������಻ִ���κβ����� 
        ���������ʹ��������ʾ��Щ��Ա�����Ȳ��ṩǿ�쳣��֤Ҳ���ṩ���׳��쳣��֤��
        ���๦�ܿ����ṩ����ѱ�֤��ʲô������й©��

        @par Requirements For Host Class:
        This policy imposes no requirements on a host class.
        �ò��Զ�������û���κ�Ҫ��
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
        ����ȷ�������Ƿ�Υ���κ��಻���ԣ�����ȷ�������Ƿ�������ͻ������Լ���� 
        �ڡ�����ͬ��ơ���ʽ�У�ÿ����������ĳЩ�Ⱦ������ͺ�����������Щ�����������಻��ʽ��ͬ�� 
        ������˶Բ���ʽ�ļ���Ƿ�ʧ���Լ��κ�ǰ����������������Ƿ�ʧ�ܡ�
        ������ʾ�˺����ṩ���쳣��ȫ����

        @par Usage
        -# Implement a function that checks each class invariant.  The function must
        have the signature similar to the Validator type.  Something like:
        -# ʵ��һ�����ÿ���಻���Եĺ����� �ú������������Validator�������Ƶ�ǩ���������ǣ�
        "bool Host::IsValid( void ) const;"
        - The function should return true if everything is okay, but false if
        something is wrong.
        - ���һ���������ú���Ӧ����true��������������⣬�򷵻�false��
        - Or it could assert if anything is wrong.
        - ���������Զ����Ƿ����κδ���
        - Ideally, it should be private.
        - ��������£���Ӧ����˽�еġ�
        -# Implement similar functions to check for pre-conditions and post-conditions.
        Functions which verify pre-conditions and post-conditions do not need to
        check all class invariants, just conditions specific to certain public
        functions in the host class.
        -# ʵ�����Ƶĺ����Լ��ǰ�������ͺ��������� 
        ��֤ǰ�������ͺ��������ĺ�������Ҫ��������಻��ʽ��ֻ�����ض�����������ĳЩ�����������������ɡ�
        -# Declare some typedef's inside the class declaration like these.  Make one
        typedef for each exception policy you use.  I typedef'ed the CheckForNothing
        policy as CheckInvariants because even if a function can't provide either the
        no-throw nor the no-change policies, it should still make sure the object
        remains in a valid state.
        -# ��������������������һЩtypedef�� Ϊ��ʹ�õ�ÿ���쳣���Դ���һ��typedef�� 
        �ҽ�CheckForNothing���Զ���ΪCheckInvariants����Ϊ��ʹĳ�������Ȳ����ṩ���׳�����Ҳ�����ṩ������ԣ�����Ӧȷ���ö��󱣳���Ч״̬��
        - typedef ::Loki::ContractChecker< Host, ::Loki::CheckForNoThrow  > CheckForNoThrow;
        - typedef ::Loki::ContractChecker< Host, ::Loki::CheckForNoChange > CheckForNoChange;
        - typedef ::Loki::ContractChecker< Host, ::Loki::CheckForEquality > CheckForEquality;
        - typedef ::Loki::ContractChecker< Host, ::Loki::CheckForNothing  > CheckInvariants;
        -# Construct a checker near the top of each member function - except in the
        validator member function.  Pass the this pointer and the address of your
        validator function into the checker's constructor.  You may also pass in pointers
        to function which check pre- and post-conditions.
        -# ��ÿ����Ա����������������һ�����������֤����Ա�����г��⡣ 
        ��thisָ�����֤�����ĵ�ַ���ݵ�������Ĺ��캯���С� ��Ҳ���Դ���ָ����ǰ�������ͺ��������ĺ�����ָ�롣
        - If the function never throws, then use the CheckForNoThrow policy.
        - ��������Ӳ��׳��쳣����ʹ��CheckForNoThrow���ԡ�
        - If the function never changes any data members, then use CheckForEquality
        policy.
        - ��������Ӳ������κ����ݳ�Ա����ʹ��CheckForEquality���ԡ�
        - If the function's normal execution flow changes data, but must make sure
        data remains unchanged when any exceptions occur, then use the
        CheckForNoChange policy.
        - �������������ִ�����̸��������ݣ�������ȷ���ڷ����κ��쳣ʱ���ݱ��ֲ��䣬��ʹ��CheckForNoChange���ԡ�
        - Otherwise use the CheckInvariants policy.
        - ������ʹ��CheckInvariants���ԡ�
        -# Recompile a debug version of your program, run the program and all the unit
        tests, and look for which assertions failed.
        -# ���±������ĵ��԰汾�����г�������е�Ԫ���ԣ���������Щ����ʧ�ܡ�
    */

    template <class Host, template <class> class ExceptionPolicy>
    class ContractChecker : public ExceptionPolicy<Host>
    {
        /// Shorthand for the ExceptionPolicy class.
        /// ExceptionPolicy��ļ�д��
        typedef ExceptionPolicy<Host> Ep;

    public:
        /// Signature for the validation function.
        /// ��֤������ǩ����
        typedef bool (Host::*Validator)() const;

        /** The constructor makes sure the host is valid at the time the checker
            was created, thus insuring the host object was not corrupt from the start.
            ���캯��ȷ���ڴ��������ʱ��������Ч�ģ��Ӷ�ȷ�����������һ��ʼ��û���𻵡�
            @par host Pointer to host object.
            ָ�����������ָ�롣
            @par validator Pointer to function that checks class invariants.
            ָ�����಻���Եĺ�����ָ�롣
            @par pre Optional pointer to function that checks pre-conditions.
            ���ڼ��ǰ�������ĺ����Ŀ�ѡָ�롣
            @par post Optional pointer to function that checks post-conditions.
            ���ڼ����������ĺ����Ŀ�ѡָ�롣
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
            ������������Ƿ����κ�Host������ʧ�ܣ�Ȼ�����ExceptionPolicy��Check������ȷ�������쳣ʱ�Ĵ�������
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
            �����ȼ��ContractChecker�Ĳ�������Ȼ��Ϊ����������֤��������
            ��ȷ�������ĳ�Ա��������û���κ��಻�����������ƻ��� 
            ������Ա����������ʱ����Check����֤������Ȼ��Ч��
            �Ⲣ������ǰ�������ͺ���������֤��ָ���Ƿ�Ϊ�գ�
            ��Ϊ��������Դ���nullptrָ���Ա�ʾǰ����������������������಻��ʽ��ͬ��
        */
        inline bool Check() const
        {
            assert(0 != this);
            assert(0 != m_host);
            assert(0 != m_validator);
            // Now that this confirms the pointers to the host and validation
            // functions are not null, go ahead and validate the host object.
            // ���ڣ���ȷ����ָ��������ָ�벢����֤������Ϊ�գ����������֤��������
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
        /// ָ�����������ָ�롣
        const Host* m_host;

        /// Pointer to member function that checks Host object's invariants.
        /// ָ����Host���󲻱��Եĳ�Ա������ָ�롣
        Validator m_validator;

        /// Pointer to member function that checks Host object's pre-conditions.
        /// ָ����Host�����ǰ�������ĳ�Ա������ָ�롣
        Validator m_pre;

        /// Pointer to member function that checks Host object's post-conditions.
        /// ָ����Host����ĺ��������ĳ�Ա������ָ�롣
        Validator m_post;
    };

    // ----------------------------------------------------------------------------

    /** @class CheckStaticForNoThrow

        @par Exception Safety Level:
        This exception-checking policy class for StaticChecker asserts if an exception
        exists.  Functions can use this to show they provide the no-throw exception
        safety guarantee.
        �쳣��ȫ����
        StaticChecker�Ĵ��쳣������������Ƿ�����쳣�� ��������ʹ���������������ṩ�˲��׳��쳣�İ�ȫ��֤��
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
        ���ô˷���ʱ��StaticChecker���쳣�������಻ִ���κβ�����
        ��������ʹ�������������ǿ����ṩ���쳣��֤�� ���ຯ�������ṩ����ѱ�֤��ʲô������й©��
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
        �����麯���Ƿ��ṩ�˲��׳��쳣��ȫ�����Լ��ú����Ƿ�Υ���κβ���ʽ��
        ���������;�̬�����Ĳ������䵱ǰ�������ͺ���������

        @par Usage
        -# Implement a function that checks the invariants associated with a function,
        or with the static data for a class.  The function must
        have the signature similar to the Validator type.  Something like:
        "static bool Host::StaticIsValid( void );" or "bool IsOkay( void );"
        ʵ��һ���������ú�������뺯������ľ�̬���ݹ����Ĳ������� 
        �ú������������Validator�������Ƶ�ǩ���� 
        ����������static bool Host::StaticIsValid( void );�� ��bool IsOkay( void );��
        - The function should return true if everything is okay, but false if
        something is wrong.
        ���һ���������ú���Ӧ����true��������������⣬�򷵻�false��
        - Or it could assert if anything is wrong.
        - ���������Զ����Ƿ����κδ���
        -# If the checker is for static functions within a class, declare typedef's
        inside the class declaration like these.  Make one typedef for each policy
        you use.  I typedef'ed the CheckForNothing policy as CheckInvariants because
        even if a function can't provide the no-throw guarantee, it should still
        make sure that static data remains in a valid state.
        ���������������еľ�̬���������ڴ����������������typedef��
        Ϊ��ʹ�õ�ÿ�ֲ�������һ��typedef�� �ҽ�CheckForNothing���Զ���ΪCheckInvariants��
        ��Ϊ��ʹ�����޷��ṩ���׳���֤����ҲӦȷ����̬���ݱ�����Ч״̬��
        - typedef ::Loki::StaticChecker< ::Loki::CheckForNoThrow > CheckStaticForNoThrow;
        - typedef ::Loki::StaticChecker< ::Loki::CheckForNothing > CheckStaticInvariants;
        -# Construct a checker near the top of each member function - except in the
        validator member function.  Pass the address of your validator function into
        the checker's constructor.
        -# ��ÿ����Ա����������������һ�������������֤����Ա�����г��⡣ 
        ����֤�������ĵ�ַ���ݵ�������Ĺ��캯���С�
        - If the function never throws, then use the CheckForNoThrow policy.
        - ��������Ӳ��׳��쳣����ʹ��CheckForNoThrow���ԡ�
        - Otherwise use the CheckInvariants policy.
        - ������ʹ��CheckInvariants���ԡ�
        -# Recompile a debug version of your program, run it, and see if an assertion
        fails.
        -# ���±������ĵ��԰汾����������Ȼ��鿴�����Ƿ�ʧ�ܡ�
    */

    template <class ExceptionPolicy>
    class StaticChecker : public ExceptionPolicy
    {
        /// Shorthand for the ExceptionPolicy class.
        /// ExceptionPolicy��ļ�д��
        typedef ExceptionPolicy Ep;

    public:
        /// Signature for the validation function.
        /// ��֤������ǩ����
        typedef bool (*Validator)();

        /** The constructor makes sure the host is valid at the time the checker
            was created, thus insuring the host object was not corrupt from the start.
            ���캯��ȷ���ڴ��������ʱ��������Ч�ģ��Ӷ�ȷ�����������һ��ʼ��û���𻵡�
            @par validator Pointer to function that checks class invariants.
            ָ�����಻���Եĺ�����ָ�롣
            @par pre Optional pointer to function that checks pre-conditions.
            ���ڼ��ǰ�������ĺ����Ŀ�ѡָ�롣
            @par post Optional pointer to function that checks post-conditions.
            ���ڼ����������ĺ����Ŀ�ѡָ�롣
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
            ������������Ƿ����κ�Host������ʧ�ܣ�Ȼ�����ExceptionPolicy��Check������ȷ����δ����쳣��
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
            �����ȼ���Լ��Ĳ�������Ȼ�������֤��������ȷ�������˼�����ĺ��������ƻ��κβ�������
            �ú�������ֱ�ӵ���Check����ʱ��֤�����Ƿ���Ȼ��Ч��
            �Ⲣ������ǰ�������ͺ���������֤��ָ���Ƿ�Ϊ�գ�
            ��Ϊ��������Դ���nullptrָ���Ա�ʾǰ����������������������಻��ʽ��ͬ��
        */
        inline bool Check() const
        {
            assert(0 != this);
            assert(0 != m_validator);
            // Now that this confirms the pointers to the host and validation
            // functions are not null, go ahead and validate the host object.
            // ���ڣ���ȷ����ָ��������ָ�벢����֤���ܲ�Ϊ�գ����������֤��������
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
        /// ָ�����������󲻱��Եĳ�Ա������ָ�롣
        Validator m_validator;

        /// Pointer to member function that checks Host object's pre-conditions.
        /// ָ�������������ǰ�������ĳ�Ա������ָ�롣
        Validator m_pre;

        /// Pointer to member function that checks Host object's post-conditions.
        /// ָ������������ĺ��������ĳ�Ա������ָ�롣
        Validator m_post;
    };

    // ----------------------------------------------------------------------------

};  // end namespace Loki

#endif
