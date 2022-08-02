////////////////////////////////////////////////////////////////////////////////
//
// LevelMutex facility for the Loki Library
// Copyright (c) 2008 Richard Sposato
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

/// @file LevelMutex.h Defines classes and functions for LevelMutex facility.
/// 定义LevelMutex工具的类和函数。

#ifndef LOKI_LEVEL_MUTEX_H_INCLUDED
#define LOKI_LEVEL_MUTEX_H_INCLUDED

// ----------------------------------------------------------------------------

#include <assert.h>
#include <time.h>
#include <vector>

#if defined(_MSC_VER)
    #include <Windows.h>
#else
    #include <pthread.h>
#endif

#if !defined(_WIN32) && !defined(_WIN64)
    #include <unistd.h>  // declares sleep under Linux（在Linux下声明sleep）
#endif

/** @par thread_local Keyword
    The mutexes require compilers to provide thread local storage - meaning each
    thread gets its own copy of the data.  The next version of C++ will have a
    new keyword, thread_local for that purpose.  Some existing compilers already
    provide thread local storage using different syntax, so these lines use
    thread_local to mimic that syntax.  If your compiler provides thread local
    storage but using different syntax besides "thread_local", you may want to
    modify these lines.  If your compiler does not support thread local storage,
    you can't use LevelMutex.
    互斥锁要求编译器提供线程本地存储——意味着每个线程都有自己的数据副本。 
    为此，C++的下一版本将具有新的关键字thread_local。 
    一些现有的编译器已经使用不同的语法提供了线程本地存储，因此这些行使用thread_local来模仿该语法。
    如果您的编译器提供了线程本地存储，但除了“thread_local”之外还使用其他语法，则可能需要修改这些行。 
    如果您的编译器不支持线程本地存储，则不能使用LevelMutex。
 */
#ifndef LOKI_THREAD_LOCAL

    #if defined(_MSC_VER)
        #if (_MSC_VER >= 1900)
            #define LOKI_THREAD_LOCAL thread_local
        #elif (_MSC_VER >= 1300)
            #define LOKI_THREAD_LOCAL __declspec(thread)
        #else
            #error "Only Visual Studio versions 7.0 and after supported."
        #endif

    #elif (__GNUC__)
        #define LOKI_THREAD_LOCAL __thread

    #else
        #warning "Check if your compiler provides thread local storage."
        #define LOKI_THREAD_LOCAL thread_local
    #endif
#endif

#if defined(DEBUG) || defined(_DEBUG)
    #define LOKI_MUTEX_DEBUG_CODE(x) x
#else
    #define LOKI_MUTEX_DEBUG_CODE(x)
#endif

namespace Loki
{
    // ----------------------------------------------------------------------------

    /// @enum Type Possible error conditions detected by LevelMutex functions.
    /// LevelMutex函数检测到可能的错误情况。
    enum class MutexErrors
    {
        Success = 0,  ///< Operation occurred correctly.（操作正确）
        NoProblem,  ///< Pre-lock and pre-unlock checks passed.（通过了预锁定和预解锁检查）
        WrongLevel,  ///< All mutexes in container must have same level.（容器中的所有互斥锁必须具有相同的级别）
        LevelTooLow,  ///< Trying to unlock a mutex lower than current level.（尝试解锁低于当前级别的互斥锁）
        LevelTooHigh,  ///< Trying to lock a mutex higher than current level.（试图锁定高于当前级别的互斥锁）
        TryFailed,  ///< TryLock call failed to lock mutex.（TryLock调用无法锁定互斥锁）
        NullMutexPointer,  ///< Container has a NULL pointer in it.（容器中有一个NULL指针）
        DuplicateMutex,  ///< Container must have unique pointers - no duplicates.（容器必须具有唯一的指针——不能重复）
        EmptyContainer,  ///< Container must have at least 1 pointer in it.（容器中必须至少包含1个指针）
        AlreadyLocked,  ///< TryLock call failed because mutex already locked.（TryLock调用失败，因为互斥锁已锁定）
        WasntLocked,  ///< Unlock failed because mutex was not even locked.（解锁失败，因为没有锁定互斥锁）
        NotRecentLock,  ///< Mutex in container was not recently locked by this thread.（容器中的互斥锁最近未被该线程锁定）
        NotLockedByThread,  ///< Can't unlock a mutex not locked by this thread.（无法解锁未被此线程锁定的互斥锁）
        MultiUnlockFailed,  ///< MultiUnlock can't unlock at least 1 mutex in container.（MultiUnlock无法解锁容器中的至少1个互斥锁）
        TimedOut,  ///< Wait time elapsed without locking mutex.（等待时间已过，没有锁定互斥锁）
        TooMuchRecursion,  ///< Tried to relock a PThread mutex which is not re-entrant.（试图重新锁定不是可重入的PThread互斥锁）
        NotInitialized,  ///< Tried to lock a PThread mutex which did not get setup.（试图锁定未设置的PThread互斥锁）
        AlreadyInitialized,  ///< PThread mutex initialized before ctor called.（在构造函数调用之前初始化了PThread互斥锁）
        InvalidAttribute,  ///< PThread mutex improperly initialized.（PThread互斥体初始化不正确）
        InvalidAddress,  ///< Bad pointer used to initialize a PThread mutex.（用于初始化PThread互斥锁的错误指针）
        ExceptionThrown,  ///< Exception caught in mutex operation.（互斥操作中捕获到异常）
        MayDeadlock,  ///< Locking this mutex may cause a deadlock.（锁定此互斥锁可能会导致死锁）
        OtherError  ///< Unknown error occurred.（发生未知错误）
    };

    // ----------------------------------------------------------------------------

    /** @class LevelMutexInfo
        This monolithic base class stores common info for a template class used to
        control mutexes.  The template class, LevelMutex, is policy-based class.
        这个庞大的基类存储用于控制互斥量的模板类的公共信息。 模板类LevelMutex是基于策略的类。

        @par Implementation
        Each thread has a list of mutexes it locked.  When a mutex first gets locked, it
        gets added to the head of the list.  If locked again, LevelMutex merely increments
        a count.  When unlocked, the count gets decremented until it reaches zero, and
        then it gets removed from the list.  Each mutex has a pointer to the mutex most
        recently locked by the current thread.  The current level of a thread is always
        the level of the most recently locked mutex, or UnlockedLevel if the thread does
        not have any mutexes locked now.  A mutex is considered "recently" locked if it is at
        the head of the list, or the same level as the current mutex and also locked by the
        current thread.
        每个线程都有一个锁定的互斥锁列表。 互斥锁首次锁定时，它将被添加到列表的开头。 
        如果再次锁定，LevelMutex只会增加一个计数。 解锁后，计数递减直到达到零，然后从列表中将其删除。 
        每个互斥锁都有一个指向当前线程最近锁定的互斥锁的指针。 
        线程的当前级别始终是最近锁定的互斥锁的级别，如果该线程现在没有任何互斥锁，则为UnlockedLevel。
        如果互斥锁位于列表的开头，或者与当前互斥锁处于同一级别，并且也被当前线程锁定，则认为该互斥锁已“最近”锁定。

        @par Class Invariants
        This class maintains invariants for each LevelMutexInfo so that no function
        calls corrupt a mutex.  Each function makes a call to IsValid at the start so
        that LevelMutex knows it acts on valid internal data.  Many functions call
        IsValid again when they return to insure the function did not leave any data in
        an invalid state.  The exit call to IsValid occurs through a tiny helper class
        called Checker to insure all data remain valid even when exceptions occur.
        Another helper class, MutexUndoer, unlocks mutexes in a container if an
        exception occurs during calls to MultiLock.
        此类为每个LevelMutexInfo维护不变式，因此没有任何函数调用会破坏互斥量。 
        每个函数在开始时都会调用IsValid，以便LevelMutex知道它对有效的内部数据起作用。 
        许多函数返回时会再次调用IsValid，以确保该函数不会使任何数据保持无效状态。
        对IsValid的退出调用通过一个名为Checker的微型帮助程序类进行，以确保即使发生异常，所有数据仍然有效。 
        如果在调用MultiLock期间发生异常，则另一个帮助程序类MutexUndoer会解锁容器中的互斥锁。

        @par Error Results
        Many functions return an enum value to indicate an error status.  Many enum values
        indicate errors detected within LevelMutex, but some indicate errors found in policy
        classes, SpinLevelMutex and SleepLevelMutex.
        许多函数返回一个枚举值来指示错误状态。 许多枚举值指示在LevelMutex中检测到错误，
        但有些指示在策略类SpinLevelMutex和SleepLevelMutex中发现错误。
    */

    class LevelMutexInfo
    {
    public:
        /** Level for thread that has not locked any mutex. Maximum possible level
            for a mutex is UnlockedLevel-1;  No mutex may have a level of UnlockedLevel.
            尚未锁定任何互斥锁的线程的级别。 互斥锁的最大可能级别为UnlockedLevel - 1。
            任何互斥锁都不能具有UnlockedLevel级别。
        */
        static constexpr unsigned int UnlockedLevel = 0xFFFFFFFF;

        /// Container for locking multiple mutexes at once.
        /// 一次锁定多个互斥锁的容器。
        typedef ::std::vector<volatile LevelMutexInfo*> MutexContainer;
        typedef MutexContainer::iterator LevelMutexContainerIter;
        typedef MutexContainer::const_iterator LevelMutexContainerCIter;
        typedef MutexContainer::reverse_iterator LevelMutexContainerRIter;
        typedef MutexContainer::const_reverse_iterator LevelMutexContainerCRIter;

        /** Locks several mutexes at once.  Requires O(m + n*n) actions where m is the
            number of mutexes currently locked by the thread and n is the number of mutexes
            in the container. This provides strong exception safety. If an exception occurs,
            any mutexes that were locked during this call will get unlocked.
            一次锁定多个互斥锁。 需要 O(m + n * n)个操作，其中m是线程当前锁定的互斥锁的数量，n是容器中互斥锁的数量。
            这提供了强大的异常安全性。 如果发生异常，则在此调用期间锁定的任何互斥锁都将被解锁。
            @param mutexes Container of pointers to mutexes.  Container must have at
            least 1 mutex, all mutexes must have the same level, no NULL pointers, and all
            mutexes must not exceed the thread's current level.  This sorts the container
            by address order.
            指向互斥锁的指针的容器。 容器必须至少具有1个互斥锁，所有互斥锁必须具有相同的级别，
            没有NULL指针，并且所有互斥锁都不得超过线程的当前级别。 这按地址顺序对容器进行排序。
            @return Enum value indicating success or error.
            表示成功或错误的枚举值。
        */
        static MutexErrors MultiLock(MutexContainer& mutexes);

        /** Locks several mutexes at once.  Requires O(m + n*n + n*t) actions where m is
            the number of mutexes currently locked by the thread, n is the number of mutexes
            in the container, and t is the wait time for each mutex. This provides strong
            exception safety.  If an exception occurs, any mutexes that were locked during
            this call will ge unlocked.
            一次锁定多个互斥锁。 需要O(m + n*n + n*t)个操作，其中m是线程当前锁定的互斥锁的数量，n是容器中互斥锁的数量，t是每个互斥锁的等待时间。
            这提供了强大的异常安全性。 如果发生异常，则在此调用期间锁定的所有互斥锁都将被解锁。
            @param mutexes Container of pointers to mutexes.  Container must have at
            least 1 mutex, all mutexes must have the same level, no NULL pointers, and all
            mutexes must not exceed the thread's current level.  This sorts the container
            by address order.
            指向互斥锁的指针的容器。 容器必须至少具有1个互斥锁，所有互斥锁必须具有相同的级别，
            没有NULL指针，并且所有互斥锁都不得超过线程的当前级别。 这按地址顺序对容器进行排序。
            @param milliSeconds Amount of time to wait for each mutex.
            milliSeconds 等待每个互斥锁的时间。
            @return Enum value indicating success or error.
            表示成功或错误的枚举值。
        */
        static MutexErrors MultiLock(MutexContainer& mutexes, unsigned int milliSeconds);

        /** Unlocks several mutexes at once.  Requires O(m) actions where m is the number of
            mutexes in the container. This provides strong exception safety. If an exception
            occurs when unlocking one mutex, other mutexes in the container get unlocked anyway.
            一次解锁多个互斥锁。 需要O(m)操作，其中m是容器中的互斥量。 
            这提供了强大的异常安全性。 如果解锁一个互斥锁时发生异常，则容器中的其他互斥锁仍将被解锁。
            @param mutexes Container of pointers to mutexes.  Container must have at least 1
            mutex, all mutexes must have the same level, no NULL pointers, and all mutexes must
            be locked by the current thread.  This sorts the container dby address order.
            指向互斥锁的指针的容器。容器必须至少具有1个互斥锁，所有互斥锁必须具有相同的级别，
            没有NULL指针，并且所有互斥锁必须由当前线程锁定。 这按地址顺序对容器进行排序。
            @return Enum value indicating success or error.
            表示成功或错误的枚举值。
        */
        static MutexErrors MultiUnlock(MutexContainer& mutexes);

        /** Gives pointer to most recently locked mutex, or NULL if nothing locked.
            The pointer is for a const mutex so the mutex can't be modified inappropriately.
            The pointer is for a volatile mutex so callers can call volatile member
            functions to get info about the mutex.
            提供指向最近锁定的互斥锁的指针；如果没有锁定，则为NULL。
            指针用于const互斥锁，因此不能修改互斥锁。 
            该指针用于volatile互斥锁，因此调用者可以调用volatile成员函数来获取有关互斥锁的信息。
        */
        static const volatile LevelMutexInfo* GetCurrentMutex();

        /// Returns the level of this mutex.
        /// 返回此互斥锁的级别。
        inline unsigned int GetLevel() const volatile
        {
            return m_level;
        }

        /// Returns true if this mutex was locked at least once.
        /// 如果此互斥锁至少被锁定一次，则返回true。
        inline bool IsLocked() const volatile
        {
            return (0 < m_count);
        }

        /// Returns count of how many times this mutex got locked.
        /// 返回此互斥体被锁定多少次的计数。
        inline unsigned int GetLockCount() const volatile
        {
            return m_count;
        }

        /// Returns pointer to mutex previously locked by the thread which locked this.
        /// 返回指向先前由此线程锁定的互斥锁的指针。
        inline const volatile LevelMutexInfo* GetPrevious() const volatile
        {
            return m_previous;
        }

        /** Tries to lock mutex, and returns immediately if mutex already locked by
            another thread.  It will return immediately with a value of AlreadyLocked
            if the mutex was locked by a different thread.  It may throw an exception
            or assert when errors occur if the ErrorPolicy class implements that behavior.
            尝试锁定互斥锁，如果互斥锁已被另一个线程锁定，则立即返回。
            如果互斥锁被另一个线程锁定，它将立即返回AlreadyLocked值。
            如果ErrorPolicy类实现了该行为，则在发生错误时它可能会引发异常或断言。
            @return An error condition if any occurred, else Success.
            错误情况（如果发生），否则为成功。
        */
        virtual MutexErrors TryLock() volatile = 0;

        /** Blocking call will attempt to lock mutex and wait until it can lock.
            This may throw an exception if the lock failed or an error occurred - if
            that is what the error policy specifies.          
            阻塞调用者将尝试锁定互斥锁并等待直到可以锁定为止。
            如果锁定失败或发生错误，这可能会引发异常——如果那是错误策略指定的内容。
            @return An error condition if any occurred, else Success.
            错误情况（如果发生），否则为成功。
        */
        virtual MutexErrors Lock() volatile = 0;

        /** Attempts to lock mutex, but only waits for a limited amount of time
            before it gives up.  Will return quickly if an error occurs before any
            attempt to lock.  This may throw an exception if the lock failed or an
            error occurred - if that is what the error policy specifies.
            尝试锁定互斥锁，但是在放弃互斥锁之前仅等待有限的时间。 
            如果在尝试任何锁定之前发生错误，将快速返回。 
            如果锁定失败或发生错误，这可能会引发异常——如果那是错误策略指定的内容。
            @param milliSeconds How long to wait.
            milliSeconds 等待多长时间。
            @return An error condition if any occurred, else Success.
            错误情况（如果发生），否则为成功。
        */
        virtual MutexErrors Lock(unsigned int milliSeconds) volatile = 0;

        /** Unlocks the mutex, or returns an error condition.  This may throw an
            exception if the lock failed or an error occurred - if that is what the
            error policy specifies.
            解锁互斥锁，或返回错误条件。如果锁定失败或发生错误，这可能会引发异常——如果那是错误策略指定的内容。
            @return An error condition if any occurred, else Success.
            错误情况（如果发生），否则为成功。
        */
        virtual MutexErrors Unlock() volatile = 0;

        /** Returns true if this mutex was locked by current thread, and level is the same
            as the current thread's level.  Which means this was the most recently locked
            mutex, or it was locked along with several others of the same level recently.
            如果此互斥锁已被当前线程锁定，并且级别与当前线程的级别相同，则返回true。
            这意味着这是最近锁定的互斥锁，或者它与其他同一级别的互斥锁一起被锁定。
        */
        bool IsRecentLock() const volatile;

        /** Returns true if this mutex was locked within the last count mutexes.
            如果此互斥锁被锁定在最后一个计数互斥锁内，则返回true。
            @param count How many recent mutexes to look through to find this mutex.
            count 查找多少个最近的互斥锁以查找此互斥锁。
        */
        bool IsRecentLock(size_t count) const volatile;

        /// Returns true if this was locked by current thread.
        /// 如果当前线程已将其锁定，则返回true。
        bool IsLockedByCurrentThread() const volatile;

        /// Returns true if this was locked by another thread.
        /// 如果已被另一个线程锁定，则返回true。
        bool IsLockedByAnotherThread() const volatile;

    protected:
        /** @class Checker Performs validity check on mutex to insure no class invariants
            were violated inside any member function.  This class only gets used in debug
            builds, and any instance of it gets optimized away in release builds.  A checker
            is created inside many of member functions so that it's destructor gets called
            when the function exits.  It determines if any class invariants were violated
            during the function call.
            Checker对互斥量执行有效性检查，以确保在任何成员函数内都没有违反类不变式。 
            此类仅在调试版本中使用，并且其任何实例在发行版本中都经过优化。
            在许多成员函数内部创建一个检查器，以便在函数退出时调用其析构函数。
            它确定在函数调用期间是否违反了任何类不变式。
        */
        class Checker
        {
        public:
            inline explicit Checker(const volatile LevelMutexInfo* mutex)
                : m_mutex(mutex)
            {
            }

            inline ~Checker()
            {
                m_mutex->IsValid();
            }

        private:
            Checker() = delete;
            Checker(const Checker&) = delete;
            Checker& operator=(const Checker&) = delete;
            const volatile LevelMutexInfo* m_mutex;
        };

        /** @class MutexUndoer
            Undoes actions by MultiLock if an exception occurs.  It keeps track of
            which mutexes in a container got locked, and if an exception occurs, then
            the destructor unlocks them.  If MultiLock succeeds, then it cancels the
            undoer so nothing gets unlocked inadvertently.
            如果发生异常，则通过MultiLock撤消操作。 它跟踪容器中哪些互斥锁被锁定，并且如果发生异常，则析构函数将其解锁。 
            如果MultiLock成功，则它将取消撤消操作，因此不会无意中解锁任何内容。
        */
        class MutexUndoer
        {
        public:
            explicit MutexUndoer(MutexContainer& mutexes);
            ~MutexUndoer();
            void SetPlace(LevelMutexContainerIter& here);
            void Cancel();

        private:
            MutexUndoer() = delete;
            MutexUndoer(const MutexUndoer&) = delete;
            MutexUndoer& operator=(const MutexUndoer&) = delete;

            MutexContainer& m_mutexes;
            LevelMutexContainerIter m_here;
        };

        /** Returns true if linked-list of locked mutexes in this thread is valid.
            Which means the list has no loops, and each previous mutex on the list has a
            higher or same level as the current mutex.  Called by IsValid.
            如果此线程中的锁定互斥锁的链接列表有效，则返回true。
            这意味着列表没有循环，并且列表上的每个先前互斥锁都具有与当前互斥锁更高或相同的级别。 由IsValid调用。
        */
        static bool IsValidList();

        /** This is the only available constructor, and it forces any derived class to set
            a level for each mutex.
            这是唯一可用的构造函数，它会强制任何派生类为每个互斥体设置一个级别。
        */
        explicit LevelMutexInfo(unsigned int level);

        /// The destructor only gets called by the derived class.
        /// 析构函数仅由派生类调用。
        virtual ~LevelMutexInfo();

        MutexErrors PreLockCheck(bool forTryLock) volatile;

        MutexErrors PreUnlockCheck() volatile;

        /** This gets called after each call to DoLock and DoTryLock to make sure the data
            members in this object get set correctly.
            每次调用DoLock和DoTryLock后都会调用此方法，以确保正确设置此对象中的数据成员。
        */
        void PostLock() volatile;

        /// Gets called just before an attempt to unlock a mutex.
        /// 在尝试解锁互斥锁之前被调用。
        void PreUnlock() volatile;

        /// Called to relock a mutex already locked by the current thread.
        /// 调用以重新锁定当前线程已锁定的互斥锁。
        void IncrementCount() volatile;

        /// Called to unlock a mutex locked multiple times by the current thread.
        /// 被调用以解锁当前线程多次锁定的互斥锁。
        void DecrementCount() volatile;

        /** Returns true if no class invariant broken, otherwise asserts.  This function
            only gets called in debug builds.
            如果没有类不变式返回，则返回true，否则断言。 仅在调试版本中调用此函数。
        */
        bool IsValid() const volatile;

    private:
        /// Copy constructor is not implemented.
        /// 复制构造函数未实现。
        LevelMutexInfo(const LevelMutexInfo&) = delete;
        /// Copy-assignment operator is not implemented.
        /// 未实现赋值运算符。
        LevelMutexInfo& operator=(const LevelMutexInfo&) = delete;

        /** Called only by MultiLock & MultiUnlock to pass a result through an
            error checking policy.
            仅由MultiLock和MultiUnlock调用以通过错误检查策略传递结果。
            @param result What error condition to check.
            result 检查什么错误条件。
            @return Result or assertion or an exception - depending on error policy.
            Result 或断言或异常——取决于错误策略。
        */
        virtual MutexErrors DoErrorCheck(MutexErrors result) const volatile = 0;

        /// Called only by MultiLock to Lock each particular mutex within a container.
        /// 仅由MultiLock调用以锁定容器中的每个特定互斥量。
        virtual MutexErrors LockThis() volatile = 0;

        /** Called only by MultiLock to lock each particular mutex within a container.
            仅由MultiLock调用以锁定容器中的每个特定互斥量。
            @param milliSeconds How much time to wait before giving up on locking a mutex.
            milliSeconds 放弃锁定互斥锁之前要等待多少时间。
        */
        virtual MutexErrors LockThis(unsigned int milliSeconds) volatile = 0;

        /// Called only by MultiUnlock to unlock each particular mutex within a container.
        /// 仅由MultiUnlock调用以解锁容器中的每个特定互斥量。
        virtual MutexErrors UnlockThis() volatile = 0;

        /// Pointer to singly-linked list of mutexes locked by the current thread.
        /// 指向当前线程锁定的互斥锁的单链接列表的指针。
        static LOKI_THREAD_LOCAL volatile LevelMutexInfo* s_currentMutex;

        /// Level of this mutex.
        /// 此互斥锁的级别。
        const unsigned int m_level;

        /// How many times this mutex got locked.
        /// 此互斥锁被锁定了多少次。
        unsigned int m_count;

        /// Pointer to mutex locked before this one.
        /// 指向互斥锁的指针在此之前已锁定。
        volatile LevelMutexInfo* m_previous;
    };

    // ----------------------------------------------------------------------------

    /** @class ThrowOnAnyMutexError
        Implements the ErrorPolicy for LevelMutex and throws an exception for any
        error condition.  Only allows MutexErrors::Success and MutexErrors::NoProblem
        to get through.  Useful for release builds.
        为LevelMutex实现ErrorPolicy，并为任何错误情况引发异常。
        仅允许MutexErrors::Success和MutexErrors::NoProblem通过。 对于发行版本很有用。
    */
    class ThrowOnAnyMutexError
    {
    public:
        static MutexErrors CheckError(MutexErrors error, unsigned int level);
    };

    // ----------------------------------------------------------------------------

    /** @class ThrowOnBadDesignMutexError
        Implements the ErrorPolicy for LevelMutex and throws an exception if the error
        indicates the programmer did not levelize the calls to mutexes.  Otherwise
        returns the error result.  Useful for release builds.
        为LevelMutex实现ErrorPolicy并在错误指示程序员未对互斥量的调用进行分级的情况下引发异常。
        否则返回错误结果。 对于发行版本很有用。
    */
    class ThrowOnBadDesignMutexError
    {
    public:
        static MutexErrors CheckError(MutexErrors error, unsigned int level);
    };

    // ----------------------------------------------------------------------------

    /** @class AssertAnyMutexError
        Implements the ErrorPolicy for LevelMutex and asserts for any error condition.
        Only allows MutexErrors::Success and MutexErrors::NoProblem to get through.
        Useful for testing mutexes in debug builds.
        为LevelMutex实现ErrorPolicy并针对任何错误情况进行断言。
        仅允许MutexErrors::Success和MutexErrors::NoProblem通过。 
        对于在调试版本中测试互斥锁很有用。
    */
    class AssertAnyMutexError
    {
    public:
        static inline MutexErrors CheckError(MutexErrors error, [[maybe_unused]] unsigned int level)
        {
            assert((error == MutexErrors::Success) || (error == MutexErrors::NoProblem));
            return error;
        }
    };

    // ----------------------------------------------------------------------------

    /** @class AssertBadDesignMutexError
        Implements the ErrorPolicy for LevelMutex and asserts if the error
        indicates the programmer did not levelize the calls to mutexes.  Otherwise
        returns the error result.  Useful for testing mutexes in debug builds.
        为LevelMutex实现ErrorPolicy，并在错误指示程序员未对互斥锁的调用进行分级时断言。
        否则返回错误结果。 对于在调试版本中测试互斥锁很有用。
    */
    class AssertBadDesignMutexError
    {
    public:
        static inline MutexErrors CheckError(MutexErrors error, [[maybe_unused]] unsigned int level)
        {
            assert((error != MutexErrors::LevelTooHigh) && (error != MutexErrors::LevelTooLow));
            return error;
        }
    };

    // ----------------------------------------------------------------------------

    /** @class JustReturnMutexError
        Implements the ErrorPolicy for LevelMutex and does nothing no matter how bad
        the error condition.  Only recommended use is for automated unit-testing of
        mutex policies.
        为LevelMutex实现ErrorPolicy，并且无论错误情况有多严重，都不会执行任何操作。
        仅建议将其用于互斥策略的自动单元测试。
    */
    class JustReturnMutexError
    {
    public:
        static inline MutexErrors CheckError(MutexErrors error, [[maybe_unused]] unsigned int level)
        {
            return error;
        }
    };

    // ----------------------------------------------------------------------------

    /** @class NoMutexWait
        Implements the WaitPolicy for LevelMutex.  Does nothing at all so it turns
        all wait loops into spin loops.  Useful for low-level mutexes.
        为LevelMutex实现WaitPolicy。 什么也不做，因此将所有等待循环变成旋转循环。 对于低级互斥有用。
    */
    class NoMutexWait
    {
    public:
        static inline void Wait()
        {
        }
    };

    // ----------------------------------------------------------------------------

    /** @class MutexSleepWaits
        Implements the WaitPolicy for LevelMutex.  Sleeps for a moment so thread won't
        consume idle CPU cycles.  Useful for high-level mutexes.
        为LevelMutex实现WaitPolicy。 休眠一会儿，这样线程就不会消耗空闲的CPU周期。 对于高级互斥锁很有用。
    */
    class MutexSleepWaits
    {
    public:
        static void Wait();
        static unsigned int sleepTime;
    };

    // ----------------------------------------------------------------------------

    /** @class SpinLevelMutex
        Implements a spin-loop to wait for the mutex to unlock.  Since this class makes
        the thread wait in a tight spin-loop, it can cause the thread to remain busy
        while waiting and thus consume CPU cycles.  For that reason, this mutex is best
        used only for very low-level resources - especially resources which do not
        require much CPU time to exercise.  Rule of thumb: Use this only if all actions
        on the resource consume a very small number of CPU cycles.  Otherwise, use the
        SleepLevelMutex instead.
        实现一个自旋循环，以等待互斥体解锁。 
        由于此类使线程在紧密的自旋循环中等待，因此它可能导致线程在等待时保持繁忙，从而消耗CPU周期。
        因此，此互斥锁最好仅用于非常低级的资源，尤其是不需要大量CPU时间来执行的资源。 
        经验法则：仅在资源上的所有操作消耗很少的CPU周期时才使用此方法。 否则，请改用SleepLevelMutex。
    */
    class SpinLevelMutex
    {
    public:
        /// Constructs a spin-level mutex.
        explicit SpinLevelMutex(unsigned int level);

        /// Destructs the mutex.
        virtual ~SpinLevelMutex();

        virtual MutexErrors Lock() volatile;

        virtual MutexErrors TryLock() volatile;

        virtual MutexErrors Unlock() volatile;

        inline unsigned int GetLevel() const volatile
        {
            return m_level;
        }

    private:
        /// Copy constructor is not implemented.
        SpinLevelMutex(const SpinLevelMutex&) = delete;
        /// Copy-assignment operator is not implemented.
        SpinLevelMutex& operator=(const SpinLevelMutex&) = delete;

#if defined(_MSC_VER)
    #if (_MSC_VER >= 1300)
        /// The actual mutex.
        /// 实际的互斥量。
        CRITICAL_SECTION m_mutex;
    #else
        #error "Only Visual Studio versions 7.0 and after supported."
    #endif

#elif (__GNUC__)
        /// The actual mutex.
        pthread_mutex_t m_mutex;

#else
    #error "Check if any mutex libraries are compatible with your compiler."
#endif

        /// Keep a copy of the mutex level around for error reporting.
        /// 保留互斥量级别的副本以进行错误报告。
        const unsigned int m_level;

    };  // end class SpinLevelMutex

    // ----------------------------------------------------------------------------

    /** @class SleepLevelMutex
        Implements a sleeping loop to wait for the mutex to unlock.
        实现一个睡眠循环以等待互斥锁解锁。

        @par Purpose
        Since this class puts the thread to sleep for short intervals, you can use this 
        class for most of your mutexes. Especially for locking any high level resources
        where any one operation on the resouce consumes many CPU cycles.  The purpose of
        this mutex is to reduce the number of CPU cycles spent in idle loops.  All
        SleepLevelMutex's should have higher levels than all your SpinLevelMutex's.
        由于此类使线程短暂睡眠，因此您可以将此类用于大多数互斥锁。 
        特别是用于锁定任何高级资源，其中资源上的任何一项操作都会消耗很多CPU周期。
        该互斥量的目的是减少空闲循环中花费的CPU周期数。 所有SleepLevelMutex的级别都应高于所有SpinLevelMutex的级别。

        @par Dependence on SpinLevelMutex
        This utilizes SpinLevelMutex so it does not have to re-implement the DoTryLock
        and DoUnlock functions the same way.  All it really needs is a DoLock function
        and the amount of time it should sleep if an attempt to lock a function fails.
        这利用了SpinLevelMutex，因此不必以相同的方式重新实现DoTryLock和DoUnlock函数。 
        它真正需要的只是一个DoLock函数以及在尝试锁定一个函数失败时应该休眠的时间。
    */
    class SleepLevelMutex : public SpinLevelMutex
    {
    public:
        /** Constructs a levelized mutex that puts threads to sleep while they wait
            for another thread to unlock the mutex.
            构造一个分层的互斥锁，使线程在等待另一个线程解锁互斥锁时进入睡眠状态。
            @param level Level of this mutex.
            此互斥锁的级别。
        */
        explicit SleepLevelMutex(unsigned int level);

        SleepLevelMutex(unsigned int level, unsigned int sleepTime);

        /// Destructs the mutex.
        virtual ~SleepLevelMutex();

        inline unsigned int GetSleepTime() const volatile
        {
            return m_sleepTime;
        }

        inline void SetSleepTime(unsigned int sleepTime) volatile
        {
            if (0 != sleepTime)
                m_sleepTime = sleepTime;
        }

#if defined(_MSC_VER)
        inline bool GetWakable() const volatile
        {
            return m_wakable;
        }
        inline void SetWakable(bool wakable) volatile
        {
            m_wakable = wakable;
        }
#endif

        /** Attempts to lock a mutex, and if it fails, then sleeps for a while
            before attempting again.
            尝试锁定互斥锁，如果互斥锁失败，则会休眠一段时间，然后再次尝试。
        */
        virtual MutexErrors Lock() volatile;

    private:
        /// Default constructor is not implemented.
        SleepLevelMutex() = delete;
        /// Copy constructor is not implemented.
        SleepLevelMutex(const SleepLevelMutex&) = delete;
        /// Copy-assignment operator is not implemented.
        SleepLevelMutex& operator=(const SleepLevelMutex&) = delete;

#if defined(_MSC_VER)
    #if (_MSC_VER >= 1300)
        /// True if operating system may wake thread to respond to events.
        /// 如果操作系统可能唤醒线程以响应事件，则为true。
        bool m_wakable;
    #else
        #error "Only Visual Studio versions 7.0 and after supported."
    #endif
#endif

        /// How many milli-seconds to sleep before trying to lock mutex again.
        /// 尝试再次锁定互斥锁之前要休眠多少毫秒。
        unsigned int m_sleepTime;

    };  // end class SleepLevelMutex

    // ----------------------------------------------------------------------------

    /** @class LevelMutex
        Levelized mutex class prevents deadlocks by requiring programs to lock mutexes in
        the same order, and unlock them in reverse order.  This is accomplished by forcing
        each mutex to have a level and forcing code to lock mutexes with higher levels
        before locking mutexes at lower levels.  If you want to lock several mutexes, they
        must be locked in decreasing order by level, or if they are all of the same level,
        then locked by LevelMutex::MultiLock.
        级别化的互斥锁类通过要求程序以相同顺序锁定互斥锁并以相反顺序将其解锁来防止死锁。 
        这是通过强制每个互斥锁具有一个级别并强制代码在将互斥锁锁定在较低级别之前锁定具有较高级别的互斥锁来实现的。 
        如果要锁定多个互斥锁，则必须按级别降序对其进行锁定，或者如果它们都处于同一级别，
        则必须通过LevelMutex::MultiLock锁定。

        @par Features
        - Immune: Very unlikely to deadlock since all mutexes are locked in the same
                  order and unlocked in reverse order.
          免疫：由于所有互斥锁均以相同顺序锁定并以相反顺序解锁，因此极不可能发生死锁。
        - Scalable: Can handle any number of mutexes.
          可扩展：可以处理任意数量的互斥锁。
        - Efficient: Many operations occur in constant time, and most operations require
                     no more than O(m) steps.
          高效的：许多操作是在恒定时间内进行的，并且大多数操作只需要O(m)个步骤即可。
        - Exception safe: All operations provide strong safety or don't throw.
          异常安全：所有操作均提供强大的安全性或不抛出异常。
        - Extendable: Can work with existing mutexes through policy-based design.
          可扩展：可以通过基于策略的设计与现有互斥锁一起使用。
        - Easily Extended: Derived classes only need to implement 5 functions and a mutex
                           to get all the features of this class.
          轻松扩展：派生类仅需要实现5个函数和一个互斥体即可获得该类的所有功能。
        - Re-Entrant: Allows for re-entrancy even if mutexes in policy classes don't.
          重新进入：即使策略类中没有互斥，也允许重新进入。
        - Cost-Free: No resource allocations occur in LevelMutex - although user-defined
                     policy classes may allocate resources.
          无成本：尽管用户定义的策略类可以分配资源，但LevelMutex中不会发生资源分配。
        - Compact: Each LevelMutex object is small.
          紧凑：每个LevelMutex对象都很小。
        - Portable: As long as your compiler and libraries can meet the requirements.
          可移植性：只要您的编译器和库可以满足要求。
        - Robust: Maintains data integrity even if exceptions occur in policy classes.
          健壮：即使策略类中发生异常，也可以保持数据完整性。
        - Affording: Several functions provide information about a mutex which allows
                     client code to easily choose correct actions.
          负担：几个函数提供有关互斥量的信息，该互斥量使客户端代码可以轻松选择正确的操作。

        @par Requirements
        - Your compiler must allow for thread-specific data.
          您的编译器必须允许线程特定的数据。       
        - You must have a threading or mutex library.
          您必须具有线程库或互斥库。

        @par Policy-Based Design
        This class hosts 3 policies and a default level.  The policy-based design allows
        users to write their own policies to extend the behaviors of LevelMutex.  The
        paragraphs below say how to design a class for each policy.
        - MutexPolicy The mutex policy class.
        - defaultLevel A level for existing client code that calls a default constructor.
        - ErrorPolicy How the mutex should handle error conditions.
        - WaitPolicy Whether a thread should wait, and how long in some internal loops.

        @par MutexPolicy
        A policy class that wraps a low-level mutex. Loki provides two policy classes
        for the actual mutex (SpinLevelMutex and SleepLevelMutex), both of which wrap
        either pthreads or the Windows CRITICAL_SECTION. If you want to use a mutex
        mechanism besides one of those, then all you have to do is provide a class
        which wraps the mutex and implements these functions.
            explicit SpinLevelMutex( unsigned int level );
            virtual ~SpinLevelMutex( void );
            virtual MutexErrors Lock( void ) volatile;
            virtual MutexErrors TryLock( void ) volatile;
            virtual MutexErrors Unlock( void ) volatile;
        Indeed, since the base class does most of the work, and provides all the interace
        and functionality to client classes, a derived class has very few requirements.
        It only needs to implement a single constructor, the destructor, some virtual
        functions, and whatever data members it requires.  You don't actually need to
        declare those functions as virtual if the policy class is not a base or child
        class.  In the parlance of design patterns, LevelMutex is a Template, and the
        MutexPolicy is a Strategy.

        @par DefaultLevel
        The template class requires a default level to use inside the default constructor.
        Some existing code calls instantiates mutexes with a default constructor, so the
        mutex must know what level to use there.  Please do not use zero or UnlockedLevel
        as the default level.

        @par ErrorPolicy
        This policy specifies how to handle error conditions.  The mutexes can return
        errors, assert, or throw exceptions.  I recommend that debug code use asserts,
        release code use exceptions, and unit-testing code just return errors.  The
        error policy class only needs to implement one function:
            static MutexErrors CheckError( MutexErrors error, unsigned int level );

        @par WaitPolicy
        This states whether the mutex should wait within some tight internal loops,
        how the waiting is done, and for how long.  A wait policy class could sleep,
        do nothing, check if other objects need attention, or check if the program
        received events or notices from the operating system.  It only needs to
        implement one function:
            static void Wait( void );

        @par Per-Function Usage
        If you implement a function with a static local mutex, then you have to insure
        the function is not called from a lower level via call-backs, virtual functions in
        interface classes.  If the function does get called from a lower level, you are
        setting up a potential deadlock.  LevelMutex will detect that by checking the
        current level and the local mutex's level, so it will refuse to lock the local mutex.

        @par Per-Object Usage
        If you use a mutex as a data member of an object to protect that object, then I
        recommend specifying which functions are volatile and which are not, and then only
        use the mutex within the volatile functions.  You may also want to provide accessor
        functions so that client code can lock and unlock the mutex either to allow for
        calling multiple operations without having to lock and unlock before and after each
        operation, or so they can lock it along with several other objects at the same
        level.

        @par Per-Class Usage
        If you make a static data member within a class, you can use that to lock any
        resources shared by those objects, or to require threads to act on only one object
        at a time.  You may also want to provide static accessor functions so that client
        code can lock several other resources at the same level.
    */

    template <class MutexPolicy,
              unsigned int DefaultLevel,
              class ErrorPolicy = ::Loki::ThrowOnBadDesignMutexError,
              class WaitPolicy = ::Loki::NoMutexWait>
    class LevelMutex : public LevelMutexInfo
    {
    public:
        typedef ErrorPolicy EP;
        typedef WaitPolicy WP;
        typedef MutexPolicy MP;

        /** This constructor allows callers to replace the default level with another
            value.  It also acts as the default constructor for existing code which uses
            default construction for mutexes.  This is the only time the DefaultLevel
            template parameter gets used.
        */
        explicit LevelMutex(unsigned int level = DefaultLevel)
            : LevelMutexInfo(level),
              m_mutex(level)
        {
            assert(IsValid());
        }

        /// The destructor.
        ~LevelMutex()
        {
            assert(IsValid());
        }

        /** These functions allow callers to access the mutex in case they need to
            modify specific values in the MutexPolicy (e.g. - sleep time, functors to
            call as tasks, etc...)  There is one function for every combination of
            const and volatile qualifiers so callers get a reference to a MutexPolicy
            with the proper qualifiers.
        */
        inline const volatile MutexPolicy& GetMutexPolicy() const volatile
        {
            return m_mutex;
        }
        inline volatile MutexPolicy& GetMutexPolicy() volatile
        {
            return m_mutex;
        }
        inline const MutexPolicy& GetMutexPolicy() const
        {
            return m_mutex;
        }
        inline MutexPolicy& GetMutexPolicy()
        {
            return m_mutex;
        }

        virtual MutexErrors TryLock() volatile
        {
            assert(IsValid());
            LOKI_MUTEX_DEBUG_CODE(Checker checker(this); (void)checker;)

            MutexErrors result = LevelMutexInfo::PreLockCheck(true);
            if (MutexErrors::Success == result)
                return MutexErrors::Success;
            else if (MutexErrors::AlreadyLocked == result)
                return result;
            else if (MutexErrors::NoProblem != result)
                return EP::CheckError(result, GetLevel());

            assert(0 == LevelMutexInfo::GetLockCount());
            result = m_mutex.TryLock();
            if (MutexErrors::Success != result)
                return EP::CheckError(result, GetLevel());
            LevelMutexInfo::PostLock();

            return MutexErrors::Success;
        }

        virtual MutexErrors Lock() volatile
        {
            assert(IsValid());
            LOKI_MUTEX_DEBUG_CODE(Checker checker(this); (void)checker;)

            MutexErrors result = LevelMutexInfo::PreLockCheck(false);
            if (MutexErrors::Success == result)
                return MutexErrors::Success;
            else if (MutexErrors::NoProblem != result)
                return EP::CheckError(result, GetLevel());

            assert(!LevelMutexInfo::IsLockedByCurrentThread());
            result = m_mutex.Lock();
            if (MutexErrors::Success != result)
                return EP::CheckError(result, GetLevel());
            PostLock();

            return MutexErrors::Success;
        }

        virtual MutexErrors Lock(unsigned int milliSeconds) volatile
        {
            assert(IsValid());
            LOKI_MUTEX_DEBUG_CODE(Checker checker(this); (void)checker;)

            MutexErrors result = LevelMutexInfo::PreLockCheck(false);
            if (MutexErrors::Success == result)
                return MutexErrors::Success;
            else if (MutexErrors::NoProblem != result)
                return EP::CheckError(result, GetLevel());

            assert(!LevelMutexInfo::IsLockedByCurrentThread());
            clock_t timeOut = clock() + milliSeconds;
            while (clock() < timeOut)
            {
                WP::Wait();
                result = m_mutex.TryLock();
                switch (result)
                {
                case MutexErrors::Success:
                {
                    PostLock();
                    return MutexErrors::Success;
                }
                case MutexErrors::AlreadyLocked:
                    return MutexErrors::AlreadyLocked;
                case MutexErrors::TryFailed:
                    break;
                default:
                    return EP::CheckError(result, GetLevel());
                }
            }

            return MutexErrors::TimedOut;
        }

        virtual MutexErrors Unlock() volatile
        {
            assert(IsValid());
            LOKI_MUTEX_DEBUG_CODE(Checker checker(this); (void)checker;)

            MutexErrors result = LevelMutexInfo::PreUnlockCheck();
            if (MutexErrors::Success == result)
                return MutexErrors::Success;
            else if (MutexErrors::NoProblem != result)
                return EP::CheckError(result, GetLevel());

            LevelMutexInfo::PreUnlock();
            result = MutexErrors::OtherError;
            try
            {
                result = m_mutex.Unlock();
                if (MutexErrors::Success != result)
                    PostLock();
            }
            catch (...)
            {
                PostLock();
                result = MutexErrors::ExceptionThrown;
            }

            return result;
        }

    private:
        /// Copy constructor is not implemented since mutexes don't get copied.
        LevelMutex(const LevelMutex&) = delete;
        /// Copy-assignment operator is not implemented since mutexes don't get copied.
        LevelMutex& operator=(const LevelMutex&) = delete;

        virtual MutexErrors DoErrorCheck(MutexErrors result) const volatile
        {
            return EP::CheckError(result, GetLevel());
        }

        /** Called only by MultiLock to lock each particular mutex within a container.
            This does not do pre-lock error checking since MultiLock does that.  Since
            this skips the error checking, that means that callers of LevelMutex should
            not call this function directly, and so this will not be publicly available.
            @return Error status indicating success or reason for failure.
        */
        virtual MutexErrors LockThis() volatile
        {
            assert(IsValid());
            LOKI_MUTEX_DEBUG_CODE(Checker checker(this); (void)checker;)
            assert(this != LevelMutexInfo::GetCurrentMutex());

            const MutexErrors result = m_mutex.Lock();
            if (MutexErrors::Success != result)
                return result;
            PostLock();

            return MutexErrors::Success;
        }

        /** Called only by MultiLock to lock each particular mutex within a container.
            This does not do pre-lock error checking since MultiLock does that.  Since
            this skips the error checking, callers of LevelMutex should not call this
            function directly, and so this will not be publicly available.
            @param milliSeconds How much time to wait before giving up on locking a mutex.
            @return Error status indicating success or reason for failure.
        */
        virtual MutexErrors LockThis(unsigned int milliSeconds) volatile
        {
            assert(IsValid());
            LOKI_MUTEX_DEBUG_CODE(Checker checker(this); (void)checker;)

            clock_t timeOut = clock() + milliSeconds;
            while (clock() < timeOut)
            {
                WP::Wait();
                const bool locked = (MutexErrors::Success == m_mutex.TryLock());
                if (locked)
                {
                    PostLock();
                    return MutexErrors::Success;
                }
            }

            return MutexErrors::TimedOut;
        }

        /** Called only by MultiUnlock to unlock each mutex within a container.
            This does not do pre-unlock error checking since MultiLock does that.  Since
            this skips the error checking, callers of LevelMutex should not call this
            function directly, and so this will not be publicly available.
            @return Error status indicating success or reason for failure.
        */
        virtual MutexErrors UnlockThis() volatile
        {
            assert(IsValid());
            assert(NULL != LevelMutexInfo::GetCurrentMutex());
            LOKI_MUTEX_DEBUG_CODE(Checker checker(this); (void)checker;)

            if (1 < LevelMutexInfo::GetLockCount())
            {
                LevelMutexInfo::DecrementCount();
                return MutexErrors::Success;
            }

            LevelMutexInfo::PreUnlock();
            MutexErrors result = m_mutex.Unlock();

            return result;
        }

        /// An instance of an unleveled mutex wrapped to match LevelMutex's needs.
        MutexPolicy m_mutex;

    };  // end class LevelMutex

    // ----------------------------------------------------------------------------

    /** Returns level of most recently locked mutex by this thread, or UnlockedLevel
        if no mutexes are locked.  Runs in constant time, and never throws exceptions.
    */
    unsigned int GetCurrentThreadsLevel();

    /** Returns count of how mutexes the current thread locked.  Requires O(m)
        actions where m is the number of mutexes in the thread.  Never throws exceptions.
    */
    unsigned int CountMutexesInCurrentThread();

    /** Returns count of how mutexes the current thread locked.  The lock count
        exceeds the number of mutexes locked by current thread if any mutex got locked
        more than once.  Requires O(m) actions where m is the number of mutexes in the
        thread.  Never throws exceptions.
    */
    unsigned int CountLocksInCurrentThread();

    /** Returns count of mutexes locked by current thread which have the same level
        as GetCurrentThreadsLevel.  Requires O(m) actions where m is the number of
        mutexes in the thread at current level.  Never throws exceptions.
    */
    unsigned int CountMutexesAtCurrentLevel();

    /** Determines if container of mutexes matches the recently locked mutexes.
        If they do match, it returns success, otherwise an error condition.
    */
    MutexErrors DoMutexesMatchContainer(const LevelMutexInfo::MutexContainer& mutexes);

    // ----------------------------------------------------------------------------

    /** @class MutexException
        Exception class used to throw error statuses about LevelMutex's up to code that
        can respond to mutex problems.  This class exists because it conveys more info
        about the error condition than just ::std::exception.
    */
    class MutexException : public ::std::exception
    {
    public:
        /** Constructs an exception which stores information about a mutex and the
            reason an attempt to use a mutex failed.
        */
        MutexException(const char* message, unsigned int level, MutexErrors reason);

        /// Copy constructor performs a member-by-member copy of an exception.
        MutexException(const MutexException& that) noexcept;

        /// Copy-assignment operator performs a member-by-member copy of an exception.
        MutexException& operator=(const MutexException& that) noexcept;

        /// Destroys the exception.
        virtual ~MutexException() noexcept;

        /// Returns a simple message about which operation failed.
        virtual const char* what() const noexcept;

        /// Returns level of mutex(es) used when problem occurred.
        unsigned int GetLevel() const
        {
            return m_level;
        }

        /// Returns an error status for why operation failed.
        MutexErrors GetReason() const
        {
            return m_reason;
        }

    private:
        /// Default constructor is not implemented.
        MutexException() noexcept = delete;

        /// Simple message about operation that failed.
        const char* m_message;
        /// Level of mutex(es) used when problem occurred.
        unsigned int m_level;
        /// Error status for why operation failed.
        MutexErrors m_reason;

    };  // end class MutexException

    // ----------------------------------------------------------------------------

    /** @class MutexLocker
        You can place an instance of this as a local variable inside a function to lock
        a single mutex.  It will lock the mutex if no error occurs, or throw if one
        does happen.  When the function ends, the destructor will determine if it needs
        to unlock the mutex.  This RAII technique insures the mutex gets unlocked even
        when exceptions occur.
    */
    class MutexLocker
    {
    public:
        /** Creates an object to lock an unlock a mutex for a function.  This
            will throw if an attempt to lock the mutex fails.
            @param mutex Reference to the mutex.
            @param lock True if function wants to lock the mutex as this gets
            constructed.
        */
        explicit MutexLocker(volatile LevelMutexInfo& mutex, bool lock = true);

        /** Creates an object to lock an unlock a mutex for a function.  This waits
            a specified amount of time for another thread to unlock the mutex if it is
            locked.  This will throw if an attempt to lock the mutex fails.
            @param mutex Reference to the mutex.
            @param milliSeconds Amount of time to wait for another thread to unlock
            the mutex.
            @param lock True if function wants to lock the mutex as this gets
            constructed.
        */
        MutexLocker(volatile LevelMutexInfo& mutex, unsigned int milliSeconds, bool lock = true);

        /// Destructs the locker, and determines if it needs to unlock the mutex.
        ~MutexLocker();

        /** You can call this to lock (or relock) a mutex.  In theory, you can lock
            and unlock a mutex several times within a function in order to give other
            threads access to a resource while this function does not need it.
            @return True if mutex is locked by this, else false if not locked.
        */
        bool Lock();

        /** You can call this to unlock a mutex before the destructor does it.
            By unlocking the mutexes before returning, the function can do other
            operations without making other threads wait too long.
            @return True if unlocked by this, else false if not unlocked by this.
            (Which is not the same as whether the mutex itself is locked or not by
            another thread.)
        */
        bool Unlock();

        /// Returns true if the mutex is locked by this object.
        inline bool IsLocked() const
        {
            return m_locked;
        }

        /// Provides access to mutex controlled by this.
        const volatile LevelMutexInfo& GetMutex() const
        {
            return m_mutex;
        }

    private:
        /// Default constructor is not implemented.
        MutexLocker() = delete;
        /// Copy constructor is not implemented.
        MutexLocker(const MutexLocker&) = delete;
        /// Copy-assignment operator is not implemented.
        MutexLocker& operator=(const MutexLocker&) = delete;

        /// True if mutex got locked.
        bool m_locked;

        /// Reference to mutex.
        volatile LevelMutexInfo& m_mutex;
    };

    // ----------------------------------------------------------------------------

    /** @class MultiMutexLocker
        You can place an instance of this as a local variable inside a function to lock
        a collection of mutexes.  It locks them if no error occurs, or throws an
        exception if one does happen.  When the function ends, the destructor determines
        if it needs to unlock the mutexes.  This RAII technique insures the mutexes get
        unlocked even when exceptions occur.  You will also have to construct a
        MutexContainer as a local object within the same function.
    */
    class MultiMutexLocker
    {
    public:
        /** Creates an object to lock and unlock a collection of mutexes for a function.
            This will throw if an attempt to lock any mutex fails. If an exception occurs,
            it unlocks mutexes it previously locked.
            @param mutex Reference to a collection of mutexes.
            @param lock True if function wants to lock the mutex as this gets
            constructed.
        */
        explicit MultiMutexLocker(LevelMutexInfo::MutexContainer& mutexes,
                                  bool lock = true);

        /** Creates an object to lock and unlock a collection of mutexes for a function.
            This waits a specified amount of time for other threads to unlock each mutex
            that is locked.  This will throw if an attempt to lock any mutex fails. If an
            exception occurs, it unlocks mutexes it previously locked.
            @param mutexes Reference to a collection of mutexes.
            @param milliSeconds Amount of time to wait for another thread to unlock
            the mutex.
            @param lock True if function wants to lock the mutexes as this gets
            constructed.
        */
        MultiMutexLocker(LevelMutexInfo::MutexContainer& mutexes,
                         unsigned int milliSeconds, bool lock = true);

        /// Destructs the locker, and determines if it needs to unlock the mutexes.
        ~MultiMutexLocker();

        /** You can call this to lock (or relock) the mutexes.  In theory, you can lock
            and unlock mutexes several times within a function in order to give other
            threads access to resources while this function does not need them.
            @return True if mutex is locked by this, else false if not locked.
        */
        bool Lock();

        /** You can call this to unlock the mutexes before the destructor does it.
            By unlocking the mutexes before returning, the function can do other
            operations without making other threads wait too long.
            @return True if unlocked by this, else false if not unlocked by this.
            (Which is not the same as whether the mutex itself is locked or not by
            another thread.)
        */
        bool Unlock();

        /// Returns true if the mutexes are locked by this object.
        inline bool IsLocked() const
        {
            return m_locked;
        }

        /// Provides access to the collection of mutexes controlled by this.
        const LevelMutexInfo::MutexContainer& GetMutexes() const
        {
            return m_mutexes;
        }

    private:
        /// Default constructor is not implemented.
        MultiMutexLocker() = delete;
        /// Copy constructor is not implemented.
        MultiMutexLocker(const MultiMutexLocker&) = delete;
        /// Copy-assignment operator is not implemented.
        MultiMutexLocker& operator=(const MultiMutexLocker&) = delete;

        /// True if mutexes got locked.
        bool m_locked;

        /// Reference to external container of mutexes;
        LevelMutexInfo::MutexContainer& m_mutexes;
    };

    // ----------------------------------------------------------------------------

}  // end namespace Loki

#endif  // end file guardian
