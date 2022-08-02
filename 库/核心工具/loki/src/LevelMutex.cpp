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

/// @file LevelMutex.cpp Contains functions needed by LevelMutex class.

// ----------------------------------------------------------------------------

#if (!defined(__CYGWIN__) || (defined(__CYGWIN__) && __GNUC__ > 3)) && !defined(__APPLE__)

    #include <loki/LevelMutex.h>

    #include <algorithm>
    #include <cerrno>

using namespace ::std;

LOKI_THREAD_LOCAL volatile ::Loki::LevelMutexInfo* ::Loki::LevelMutexInfo::s_currentMutex = nullptr;

unsigned int ::Loki::MutexSleepWaits::sleepTime = 1;

/// Anonymous namespace hides some functions which are implementation details.
namespace
{
    // ----------------------------------------------------------------------------

    /** Determines if the mutex at specific iterator location is unique within the
container of mutexes.  It only checks mutexes at later locations in the
container instead of the entire container partly for efficiency sake.  (Any
prior duplications would have gotten caught during earlier calls to this
function.)  This should not throw exceptions.  It requires O(m) operations
where m is the number of elements in the container after the iterator.
 @param mutexes Container to check.
 @param cit Location of mutex used for comparing.
 @return True for uniqueness, false if a duplicate exists.
 */
    bool IsUniqueMutex(const ::Loki::LevelMutexInfo::MutexContainer& mutexes,
                       ::Loki::LevelMutexInfo::LevelMutexContainerCIter cit)
    {
        assert(mutexes.end() != cit);

        const ::Loki::LevelMutexInfo::LevelMutexContainerCIter end = mutexes.end();
        const volatile ::Loki::LevelMutexInfo* mutex = *cit;
        for (++cit; cit != end; ++cit)
        {
            const volatile ::Loki::LevelMutexInfo* check = *cit;
            if (check == mutex)
                return false;
        }
        return true;
    }

    // ----------------------------------------------------------------------------

    /** Returns pointer to first mutex it finds in the container.  This should not
 throw, and takes O(1) most of the time.  At worse, it takes O(m) operations
 where m is the size of the container.
 @param mutexes Container of mutexes.
 @return Pointer to first mutex it finds, or nullptr if container is empty or
  each element is a nullptr.
 */
    const volatile ::Loki::LevelMutexInfo* GetFirstMutex(
        const ::Loki::LevelMutexInfo::MutexContainer& mutexes)
    {
        if (mutexes.size() == 0)
            return nullptr;
        ::Loki::LevelMutexInfo::LevelMutexContainerCIter it(mutexes.begin());
        const volatile ::Loki::LevelMutexInfo* mutex = *it;
        if (nullptr != mutex)
            return mutex;

        const ::Loki::LevelMutexInfo::LevelMutexContainerCIter end(mutexes.end());
        while (it != end)
        {
            mutex = *it;
            if (nullptr != mutex)
                return mutex;
            ++it;
        }

        return nullptr;
    }

    // ----------------------------------------------------------------------------

    /** Gets the level number associated with the first mutex found in a container.
 Usually takes O(1) operations, but take up to O(m) where m is the size of the
 container.
 @return Level number of first mutex in container, or UnlockedLevel if no
  mutexes were found in the container.
 */
    unsigned int GetLevel(const ::Loki::LevelMutexInfo::MutexContainer& mutexes)
    {
        const volatile ::Loki::LevelMutexInfo* mutex = GetFirstMutex(mutexes);
        return (nullptr == mutex) ? ::Loki::LevelMutexInfo::UnlockedLevel : mutex->GetLevel();
    }

    // ----------------------------------------------------------------------------

}  // end anonymous namespace

namespace Loki
{
    // ----------------------------------------------------------------------------

    unsigned int GetCurrentThreadsLevel()
    {
        const volatile LevelMutexInfo* mutex = LevelMutexInfo::GetCurrentMutex();
        return (nullptr == mutex) ? LevelMutexInfo::UnlockedLevel : mutex->GetLevel();
    }

    // ----------------------------------------------------------------------------

    unsigned int CountMutexesInCurrentThread()
    {
        const volatile LevelMutexInfo* mutex = LevelMutexInfo::GetCurrentMutex();
        unsigned int count = 0;
        while (nullptr != mutex)
        {
            count++;
            mutex = mutex->GetPrevious();
        }
        return count;
    }

    // ----------------------------------------------------------------------------

    unsigned int CountLocksInCurrentThread()
    {
        const volatile LevelMutexInfo* mutex = LevelMutexInfo::GetCurrentMutex();
        unsigned int count = 0;
        while (nullptr != mutex)
        {
            count += mutex->GetLockCount();
            mutex = mutex->GetPrevious();
        }
        return count;
    }

    // ----------------------------------------------------------------------------

    unsigned int CountMutexesAtCurrentLevel()
    {
        const volatile LevelMutexInfo* mutex = LevelMutexInfo::GetCurrentMutex();
        if (nullptr == mutex)
            return 0;
        unsigned int count = 0;
        unsigned int level = mutex->GetLevel();
        while (nullptr != mutex)
        {
            if (level != mutex->GetLevel())
                break;
            mutex = mutex->GetPrevious();
            count++;
        }
        return count;
    }

    // ----------------------------------------------------------------------------

    MutexErrors DoMutexesMatchContainer(const LevelMutexInfo::MutexContainer& mutexes)
    {
        const auto count = mutexes.size();
        if (0 == count)
            return MutexErrors::EmptyContainer;
        unsigned int currentLevel = GetCurrentThreadsLevel();
        const LevelMutexInfo::LevelMutexContainerCIter endSpot = mutexes.end();

        for (LevelMutexInfo::LevelMutexContainerCIter cit = mutexes.begin();
             cit != endSpot;
             ++cit)
        {
            const volatile LevelMutexInfo* mutex = *cit;
            if (nullptr == mutex)
                return MutexErrors::NullMutexPointer;
            if (currentLevel != mutex->GetLevel())
            {
                return (LevelMutexInfo::UnlockedLevel == currentLevel) ?
                           MutexErrors::NotRecentLock :
                           MutexErrors::WrongLevel;
            }
            if (!mutex->IsRecentLock(count))
                return MutexErrors::NotRecentLock;
            if (!IsUniqueMutex(mutexes, cit))
                return MutexErrors::DuplicateMutex;
        }

        if (count != CountMutexesAtCurrentLevel())
            return MutexErrors::LevelTooHigh;

        return MutexErrors::Success;
    }

    // ----------------------------------------------------------------------------

    LevelMutexInfo::MutexUndoer::MutexUndoer(MutexContainer& mutexes)
        : m_mutexes(mutexes),
          m_here(mutexes.end())
    {
        assert(this != nullptr);
    }

    // ----------------------------------------------------------------------------

    LevelMutexInfo::MutexUndoer::~MutexUndoer()
    {
        assert(this != nullptr);
        try
        {
            if (m_here == m_mutexes.end())
                return;
            LevelMutexContainerRIter rend(m_mutexes.rend());
            LevelMutexContainerRIter rit(m_here);
            --rit;
            for (; rit != rend; ++rit)
            {
                volatile ::Loki::LevelMutexInfo* mutex = *rit;
                assert(nullptr != mutex);
                mutex->UnlockThis();
            }
        }
        catch (...)
        {
        }
    }

    // ----------------------------------------------------------------------------

    void LevelMutexInfo::MutexUndoer::SetPlace(LevelMutexContainerIter& here)
    {
        assert(this != nullptr);
        m_here = here;
    }

    // ----------------------------------------------------------------------------

    void LevelMutexInfo::MutexUndoer::Cancel()
    {
        assert(this != nullptr);
        m_here = m_mutexes.end();
    }

    // ----------------------------------------------------------------------------

    const volatile LevelMutexInfo* LevelMutexInfo::GetCurrentMutex()
    {
        assert(IsValidList());
        return s_currentMutex;
    }

    // ----------------------------------------------------------------------------

    bool LevelMutexInfo::IsValidList()
    {
        const volatile LevelMutexInfo* mutex1 = s_currentMutex;
        const volatile LevelMutexInfo* mutex2 = s_currentMutex;
        if (nullptr == mutex1)
            return true;

        while (nullptr != mutex2)
        {
            if (nullptr == mutex2)
                break;
            mutex2 = mutex2->m_previous;
            if (mutex1 == mutex2)
                return false;
            if (nullptr == mutex2)
                break;
            mutex2 = mutex2->m_previous;
            if (mutex1 == mutex2)
                return false;
            if (nullptr == mutex2)
                break;
            mutex1 = mutex1->m_previous;
            if (nullptr == mutex1)
                break;
        }

        mutex1 = s_currentMutex;
        unsigned int level = mutex1->m_level;
        while (nullptr != mutex1)
        {
            if (level > mutex1->m_level)
                return false;
            level = mutex1->m_level;
            mutex1 = mutex1->m_previous;
        }

        return true;
    }

    // ----------------------------------------------------------------------------

    MutexErrors LevelMutexInfo::MultiLock(MutexContainer& mutexes)
    {
        assert(IsValidList());

        const auto count = mutexes.size();
        if (count == 0)
            return MutexErrors::EmptyContainer;

        LevelMutexContainerIter it(mutexes.begin());
        volatile LevelMutexInfo* mutex = *it;
        if (nullptr == mutex)
            return MutexErrors::NullMutexPointer;
        // Since the pointer to the first mutex is not NULL, save it so we use it
        // to call the derived class and check for errors.
        // 由于指向第一个互斥锁的指针不是NULL，请保存它，以便我们使用它来调用派生类并检查错误。
        const volatile LevelMutexInfo* const first = mutex;
        if (!IsUniqueMutex(mutexes, it))
            return MutexErrors::DuplicateMutex;
        const unsigned int checkLevel = mutex->GetLevel();
        const unsigned int currentLevel = GetCurrentThreadsLevel();
        if (currentLevel < checkLevel)
        {
            return first->DoErrorCheck(MutexErrors::LevelTooHigh);
        }

        const LevelMutexContainerIter end(mutexes.end());
        if (currentLevel == checkLevel)
        {
            MutexErrors result = DoMutexesMatchContainer(mutexes);
            if (MutexErrors::Success != result)
            {
                if (LevelMutexInfo::UnlockedLevel == currentLevel)
                {
                    return first->DoErrorCheck(result);
                }
                return first->DoErrorCheck(MutexErrors::LevelTooHigh);
            }
            for (it = mutexes.begin(); it != end; ++it)
            {
                mutex = *it;
                mutex->IncrementCount();
            }
            return MutexErrors::Success;
        }
        assert(!mutex->IsRecentLock(count));

        if (1 < count)
        {
            for (++it; it != end; ++it)
            {
                mutex = *it;
                if (nullptr == mutex)
                    return first->DoErrorCheck(MutexErrors::NullMutexPointer);
                const unsigned int level = mutex->GetLevel();
                if (checkLevel != level)
                    return first->DoErrorCheck(MutexErrors::WrongLevel);
                if (!IsUniqueMutex(mutexes, it))
                    return first->DoErrorCheck(MutexErrors::DuplicateMutex);
                assert(!mutex->IsRecentLock(count));
            }

            it = mutexes.begin();
            ::std::sort(it, end);
        }

        MutexUndoer undoer(mutexes);
        for (; it != end; ++it)
        {
            mutex = *it;
            const MutexErrors result = mutex->LockThis();
            if (MutexErrors::Success != result)
                return first->DoErrorCheck(result);
            undoer.SetPlace(it);
        }
        undoer.Cancel();

        return MutexErrors::Success;
    }

    // ----------------------------------------------------------------------------

    MutexErrors LevelMutexInfo::MultiLock(MutexContainer& mutexes, unsigned int milliSeconds)
    {
        assert(IsValidList());

        if (0 == milliSeconds)
            return MultiLock(mutexes);
        const auto count = mutexes.size();
        if (0 == count)
            return MutexErrors::EmptyContainer;

        LevelMutexContainerIter it(mutexes.begin());
        volatile LevelMutexInfo* mutex = *it;
        if (nullptr == mutex)
            return MutexErrors::NullMutexPointer;
        // Since the pointer to the first mutex is not NULL, save it so we use it
        // to call the derived class and check for errors.
        // 由于指向第一个互斥锁的指针不是NULL，请保存它，以便我们使用它来调用派生类并检查错误。
        const volatile LevelMutexInfo* const first = mutex;
        if (!IsUniqueMutex(mutexes, it))
            return first->DoErrorCheck(MutexErrors::DuplicateMutex);
        const unsigned int checkLevel = mutex->GetLevel();
        const unsigned int currentLevel = GetCurrentThreadsLevel();
        if (currentLevel < checkLevel)
        {
            return first->DoErrorCheck(MutexErrors::LevelTooHigh);
        }

        const LevelMutexContainerIter end(mutexes.end());
        if (currentLevel == checkLevel)
        {
            MutexErrors result = DoMutexesMatchContainer(mutexes);
            if (MutexErrors::Success != result)
            {
                if (LevelMutexInfo::UnlockedLevel == currentLevel)
                {
                    return first->DoErrorCheck(result);
                }
                return first->DoErrorCheck(MutexErrors::LevelTooHigh);
            }
            for (it = mutexes.begin(); it != end; ++it)
            {
                mutex = *it;
                mutex->IncrementCount();
            }
            return MutexErrors::Success;
        }
        assert(!mutex->IsRecentLock(count));

        if (1 < count)
        {
            for (++it; it != end; ++it)
            {
                mutex = *it;
                if (nullptr == mutex)
                    return first->DoErrorCheck(MutexErrors::NullMutexPointer);
                const unsigned int level = mutex->GetLevel();
                if (checkLevel != level)
                    return first->DoErrorCheck(MutexErrors::WrongLevel);
                if (!IsUniqueMutex(mutexes, it))
                    return first->DoErrorCheck(MutexErrors::DuplicateMutex);
                assert(!mutex->IsRecentLock(count));
            }

            it = mutexes.begin();
            ::std::sort(it, end);
        }

        MutexUndoer undoer(mutexes);
        for (; it != end; ++it)
        {
            mutex = *it;
            const MutexErrors result = mutex->LockThis(milliSeconds);
            if (MutexErrors::Success != result)
                return first->DoErrorCheck(result);
            undoer.SetPlace(it);
        }
        undoer.Cancel();

        return MutexErrors::Success;
    }

    // ----------------------------------------------------------------------------

    MutexErrors LevelMutexInfo::MultiUnlock(MutexContainer& mutexes)
    {
        assert(IsValidList());

        MutexErrors result = DoMutexesMatchContainer(mutexes);
        if (result != MutexErrors::Success)
        {
            const volatile LevelMutexInfo* const mutex = GetFirstMutex(mutexes);
            if (nullptr != mutex)
                return mutex->DoErrorCheck(result);
            throw MutexException("Unable to unlock mutexes in container.",
                                 LevelMutexInfo::UnlockedLevel, result);
        }

        const auto count = mutexes.size();
        if (1 < count)
        {
            ::std::sort(mutexes.begin(), mutexes.end());
        }

        bool failed = false;
        LevelMutexContainerRIter rit(mutexes.rbegin());
        const LevelMutexContainerRIter rend(mutexes.rend());
        for (; rit != rend; ++rit)
        {
            try
            {
                volatile LevelMutexInfo* mutex = *rit;
                result = mutex->UnlockThis();
                if (MutexErrors::Success != result)
                    failed = true;
            }
            catch (...)
            {
                failed = true;
                // If one fails to unlock, keep trying to unlock the others.
                // So don't just exit the for loop.  This keeps going instead
                // of trying to relock the mutex and exit since it is not
                // safe to leave some locked, but not others.
                // 如果其中一个无法解锁，请继续尝试解锁其他。 因此，不要仅仅退出for循环。
                // 这样就可以继续进行，而不是尝试重新锁定互斥锁并退出，因为将某些锁锁定是不安全的。
            }
        }

        return (failed) ? MutexErrors::MultiUnlockFailed : MutexErrors::Success;
    }

    // ----------------------------------------------------------------------------

    LevelMutexInfo::LevelMutexInfo(unsigned int level)
        : m_level(level),
          m_count(0),
          m_previous(nullptr)
    {
        assert(IsValid());
    }

    // ----------------------------------------------------------------------------

    LevelMutexInfo::~LevelMutexInfo()
    {
        assert(IsValid());
        assert(0 == m_count);
        assert(nullptr == m_previous);
    }

    // ----------------------------------------------------------------------------

    bool LevelMutexInfo::IsValid() const volatile
    {
        assert(nullptr != this);
        assert(LevelMutexInfo::UnlockedLevel != m_level);
        assert(m_previous != this);
        assert((nullptr == m_previous) || (0 < m_count));
        assert(IsValidList());
        return true;
    }

    // ----------------------------------------------------------------------------

    void LevelMutexInfo::IncrementCount() volatile
    {
        assert(IsValid());
        assert(0 < m_count);
        ++m_count;
    }

    // ----------------------------------------------------------------------------

    void LevelMutexInfo::DecrementCount() volatile
    {
        assert(IsValid());
        assert(0 < m_count);
        --m_count;
    }

    // ----------------------------------------------------------------------------

    bool LevelMutexInfo::IsLockedByCurrentThread() const volatile
    {
        assert(IsValid());
        LOKI_MUTEX_DEBUG_CODE(Checker checker(this); (void)checker;)

        if (!IsLocked())
            return false;
        const volatile LevelMutexInfo* mutex = s_currentMutex;
        while (nullptr != mutex)
        {
            if (this == mutex)
                return true;
            mutex = mutex->m_previous;
        }
        return false;
    }

    // ----------------------------------------------------------------------------

    bool LevelMutexInfo::IsRecentLock() const volatile
    {
        assert(IsValid());
        LOKI_MUTEX_DEBUG_CODE(Checker checker(this); (void)checker;)

        if (0 == m_count)
            return false;
        const volatile LevelMutexInfo* mutex = s_currentMutex;
        while (nullptr != mutex)
        {
            assert(m_level <= mutex->m_level);
            if (this == mutex)
                return true;
            if (m_level != mutex->m_level)
                return false;
            mutex = mutex->m_previous;
        }
        return false;
    }

    // ----------------------------------------------------------------------------

    bool LevelMutexInfo::IsRecentLock(size_t count) const volatile
    {
        assert(IsValid());
        LOKI_MUTEX_DEBUG_CODE(Checker checker(this); (void)checker;)

        if (0 == count)
            return false;
        const volatile LevelMutexInfo* mutex = s_currentMutex;
        for (; count > 0; count--)
        {
            if (nullptr == mutex)
                return false;
            if (this == mutex)
                return true;
            mutex = mutex->m_previous;
        }
        return false;
    }

    // ----------------------------------------------------------------------------

    bool LevelMutexInfo::IsLockedByAnotherThread() const volatile
    {
        assert(IsValid());
        LOKI_MUTEX_DEBUG_CODE(Checker checker(this); (void)checker;)

        if (!IsLocked())
            return false;
        if (IsLockedByCurrentThread())
            return false;
        if (!IsLocked())
            return false;
        return true;
    }

    // ----------------------------------------------------------------------------

    void LevelMutexInfo::PostLock() volatile
    {
        assert(IsValid());
        assert(0 == m_count);
        assert(nullptr == m_previous);
        assert(this != s_currentMutex);
        assert(!IsLockedByCurrentThread());
        LOKI_MUTEX_DEBUG_CODE(Checker checker(this); (void)checker;)

        m_count = 1;
        m_previous = s_currentMutex;
        s_currentMutex = this;
    }

    // ----------------------------------------------------------------------------

    void LevelMutexInfo::PreUnlock() volatile
    {
        assert(IsValid());
        assert(1 == m_count);
        assert(nullptr != s_currentMutex);
        assert(this == s_currentMutex);
        assert(IsLockedByCurrentThread());
        LOKI_MUTEX_DEBUG_CODE(Checker checker(this); (void)checker;)

        s_currentMutex = m_previous;
        m_previous = nullptr;
        m_count = 0;
    }

    // ----------------------------------------------------------------------------

    MutexErrors LevelMutexInfo::PreLockCheck(bool forTryLock) volatile
    {
        assert(IsValid());
        LOKI_MUTEX_DEBUG_CODE(Checker checker(this); (void)checker;)

        const unsigned int currentLevel = GetCurrentThreadsLevel();
        if (currentLevel < LevelMutexInfo::GetLevel())
            return MutexErrors::LevelTooHigh;
        const bool lockedByThisThread = IsLockedByCurrentThread();
        if (!lockedByThisThread && forTryLock && IsLocked())
            return MutexErrors::AlreadyLocked;
        if (currentLevel == LevelMutexInfo::GetLevel())
        {
            // If this mutex has the same level as the current level,
            // and was locked by the current thread, then assume it
            // was locked with the MultiLock function.  Which means it
            // is safe to relock this.  If this checked if it equals
            // s_currentMutex that would defeat re-entrancy for all
            // multi-locked mutexes.
            if (lockedByThisThread)
            {
                m_count++;
                return MutexErrors::Success;
            }
            else
            {
                return MutexErrors::LevelTooHigh;
            }
        }

        return MutexErrors::NoProblem;
    }

    // ----------------------------------------------------------------------------

    MutexErrors LevelMutexInfo::PreUnlockCheck() volatile
    {
        assert(IsValid());
        LOKI_MUTEX_DEBUG_CODE(Checker checker(this); (void)checker;)

        if (0 == m_count)
            return MutexErrors::WasntLocked;
        const unsigned int currentLevel = GetCurrentThreadsLevel();
        if (currentLevel > m_level)
            return MutexErrors::LevelTooLow;
        if (currentLevel < m_level)
            return MutexErrors::LevelTooHigh;
        const bool lockedByThisThread = IsLockedByCurrentThread();
        if (!lockedByThisThread)
            return MutexErrors::NotLockedByThread;
        if (1 < m_count)
        {
            m_count--;
            return MutexErrors::Success;
        }

        return MutexErrors::NoProblem;
    }

    // ----------------------------------------------------------------------------

    MutexErrors ThrowOnAnyMutexError::CheckError(MutexErrors error,
                                                 unsigned int level)
    {
        if ((error != MutexErrors::Success) && (error != MutexErrors::NoProblem))
        {
            throw MutexException("Error occurred using mutex.", level, error);
        }
        return error;
    }

    // ----------------------------------------------------------------------------

    MutexErrors ThrowOnBadDesignMutexError::CheckError(MutexErrors error,
                                                       unsigned int level)
    {
        if ((error == MutexErrors::LevelTooHigh) && (error == MutexErrors::LevelTooLow))
        {
            throw MutexException("Error occurred using mutex.", level, error);
        }
        return error;
    }

    // ----------------------------------------------------------------------------

    void MutexSleepWaits::Wait()
    {
    #if defined(_MSC_VER)
        ::SleepEx(sleepTime, true);
    #else
        ::sleep(sleepTime);
    #endif
    }

    // ----------------------------------------------------------------------------

    SpinLevelMutex::SpinLevelMutex(unsigned int level)
        : m_mutex(),
          m_level(level)
    {
    #if defined(_MSC_VER)
        ::InitializeCriticalSection(&m_mutex);
    #else
        const int result = ::pthread_mutex_init(&m_mutex, 0);
        switch (result)
        {
        case 0:
            return;
        case EBUSY:
            throw MutexException("pthread mutex already initialized!",
                                 level, MutexErrors::AlreadyInitialized);
        default:
        case EINVAL:
            throw MutexException("pthread mutex has an invalid attribute!",
                                 level, MutexErrors::InvalidAttribute);
        case EFAULT:
            throw MutexException("pthread mutex has an invalid address!",
                                 level, MutexErrors::InvalidAddress);
        }
    #endif
    }

    // ----------------------------------------------------------------------------

    SpinLevelMutex::~SpinLevelMutex()
    {
        try
        {
    #if defined(_MSC_VER)
            ::DeleteCriticalSection(&m_mutex);
    #else
            ::pthread_mutex_destroy(&m_mutex);
    #endif
        }
        catch (...)
        {
            // Not much we can do after catching an exception inside a destructor!
        }
    }

    // ----------------------------------------------------------------------------

    MutexErrors SpinLevelMutex::Lock() volatile
    {
        // Have to cast away volatile since Windows CriticalSection class does not
        // use volatile qualifier.
        SpinLevelMutex* pThis = const_cast<SpinLevelMutex*>(this);
    #if defined(_MSC_VER)
        ::EnterCriticalSection(&pThis->m_mutex);
    #else
        const int result = ::pthread_mutex_lock(&pThis->m_mutex);
        switch (result)
        {
        case 0:
            break;
        default:
        case EINVAL:
            throw MutexException("pthread mutex not initialized properly!",
                                 GetLevel(), MutexErrors::NotInitialized);
        case EFAULT:
            throw MutexException("pthread mutex is not valid!",
                                 GetLevel(), MutexErrors::InvalidAddress);
        case EDEADLK:
            throw MutexException("locking this pthread mutex may cause a deadlock!",
                                 GetLevel(), MutexErrors::MayDeadlock);
        }
    #endif
        return MutexErrors::Success;
    }

    // ----------------------------------------------------------------------------

    MutexErrors SpinLevelMutex::TryLock() volatile
    {
        // Have to cast away volatile since Windows CriticalSection class does not
        // use volatile qualifier.
        SpinLevelMutex* pThis = const_cast<SpinLevelMutex*>(this);
    #if defined(_MSC_VER)
        const bool locked = (0 != ::TryEnterCriticalSection(&pThis->m_mutex));
        return (locked) ? MutexErrors::Success : MutexErrors::TryFailed;
    #else
        const int result = ::pthread_mutex_trylock(&pThis->m_mutex);
        switch (result)
        {
        case 0:
            return MutexErrors::Success;
        default:
        case EBUSY:
            break;
        case EAGAIN:
            throw MutexException("pthread mutex reached recursion limit!",
                                 GetLevel(), MutexErrors::TooMuchRecursion);
        }
        return MutexErrors::TryFailed;
    #endif
    }

    // ----------------------------------------------------------------------------

    MutexErrors SpinLevelMutex::Unlock() volatile
    {
        // Have to cast away volatile since Windows CriticalSection class does not
        // use volatile qualifier.
        SpinLevelMutex* pThis = const_cast<SpinLevelMutex*>(this);
    #if defined(_MSC_VER)
        ::LeaveCriticalSection(&pThis->m_mutex);
    #else
        const int result = ::pthread_mutex_unlock(&pThis->m_mutex);
        if (EPERM == result)
            throw MutexException("current thread did not lock this pthread mutex!",
                                 GetLevel(), MutexErrors::NotLockedByThread);
    #endif
        return MutexErrors::Success;
    }

    // ----------------------------------------------------------------------------

    #if defined(_MSC_VER)

    SleepLevelMutex::SleepLevelMutex(unsigned int level)
        : SpinLevelMutex(level),
          m_sleepTime(1),
          m_wakable(true)
    {
    }

        // ----------------------------------------------------------------------------

    #else

    SleepLevelMutex::SleepLevelMutex(unsigned int level, unsigned int sleepTime)
        : SpinLevelMutex(level),
          m_sleepTime(sleepTime / 1000)
    {
        if (0 == m_sleepTime)
            m_sleepTime = 1;  // Can't have a resolution less than 1 second.
    }

    #endif

    // ----------------------------------------------------------------------------

    SleepLevelMutex::~SleepLevelMutex()
    {
    }

    // ----------------------------------------------------------------------------

    MutexErrors SleepLevelMutex::Lock() volatile
    {
        bool locked = false;
        while (!locked)
        {
            locked = (MutexErrors::Success == TryLock());
            if (locked)
                break;
    #if defined(_MSC_VER)
            ::SleepEx(m_sleepTime, m_wakable);
    #else
            ::sleep(m_sleepTime);
    #endif
        }
        return MutexErrors::Success;
    }

    // ----------------------------------------------------------------------------

    MutexException::MutexException(const char* message,
                                   unsigned int level, MutexErrors reason)
        : m_message(message),
          m_level(level),
          m_reason(reason)
    {
    }

    // ----------------------------------------------------------------------------

    MutexException::MutexException(const MutexException& that) noexcept
        : ::std::exception(that),
          m_message(that.m_message),
          m_level(that.m_level),
          m_reason(that.m_reason)
    {
    }

    // ----------------------------------------------------------------------------

    MutexException& MutexException::operator=(const MutexException& that) noexcept
    {
        m_message = that.m_message;
        m_level = that.m_level;
        m_reason = that.m_reason;
        return *this;
    }

    // ----------------------------------------------------------------------------

    MutexException::~MutexException() noexcept
    {
    }

    // ----------------------------------------------------------------------------

    const char* MutexException::what() const noexcept
    {
        return m_message;
    }

    // ----------------------------------------------------------------------------

    MutexLocker::MutexLocker(volatile LevelMutexInfo& mutex, bool lock)
        : m_locked(false),
          m_mutex(mutex)
    {
        assert(nullptr != this);
        if (!lock)
            return;
        const MutexErrors result = mutex.Lock();
        m_locked = (MutexErrors::Success == result);
        if (!m_locked)
            throw MutexException("Unable to lock mutex.", mutex.GetLevel(), result);
    }

    // ----------------------------------------------------------------------------

    MutexLocker::MutexLocker(volatile LevelMutexInfo& mutex, unsigned int milliSeconds,
                             bool lock)
        : m_locked(false),
          m_mutex(mutex)
    {
        assert(nullptr != this);
        if (!lock)
            return;
        const MutexErrors result = mutex.Lock(milliSeconds);
        m_locked = (MutexErrors::Success == result);
        if (!m_locked)
            throw MutexException("Unable to lock mutex.", mutex.GetLevel(), result);
    }

    // ----------------------------------------------------------------------------

    MutexLocker::~MutexLocker()
    {
        assert(nullptr != this);
        if (!m_locked)
            return;
        try
        {
            m_mutex.Unlock();
        }
        catch (...)
        {
            // Not much we can do when catching an exception inside a destructor.
        }
    }

    // ----------------------------------------------------------------------------

    bool MutexLocker::Lock()
    {
        assert(nullptr != this);
        if (m_locked)
            return true;
        const MutexErrors result = m_mutex.Lock();
        if (MutexErrors::Success != result)
            return false;
        m_locked = true;
        return true;
    }

    // ----------------------------------------------------------------------------

    bool MutexLocker::Unlock()
    {
        assert(nullptr != this);
        if (!m_locked)
            return true;
        const MutexErrors result = m_mutex.Unlock();
        if (MutexErrors::Success != result)
            return false;
        m_locked = false;
        return true;
    }

    // ----------------------------------------------------------------------------

    MultiMutexLocker::MultiMutexLocker(LevelMutexInfo::MutexContainer& mutexes,
                                       bool lock)
        : m_locked(false),
          m_mutexes(mutexes)
    {
        assert(nullptr != this);
        if (!lock)
            return;
        const MutexErrors result = LevelMutexInfo::MultiLock(mutexes);
        m_locked = (MutexErrors::Success == result);
        if (!m_locked)
            throw MutexException("Unable to lock multiple mutexes.",
                                 GetLevel(mutexes), result);
    }

    // ----------------------------------------------------------------------------

    MultiMutexLocker::MultiMutexLocker(LevelMutexInfo::MutexContainer& mutexes,
                                       unsigned int milliSeconds, bool lock)
        : m_locked(false),
          m_mutexes(mutexes)
    {
        assert(nullptr != this);
        if (!lock)
            return;
        const MutexErrors result = LevelMutexInfo::MultiLock(mutexes, milliSeconds);
        m_locked = (MutexErrors::Success == result);
        if (!m_locked)
            throw MutexException("Unable to lock multiple mutexes.",
                                 GetLevel(mutexes), result);
    }

    // ----------------------------------------------------------------------------

    MultiMutexLocker::~MultiMutexLocker()
    {
        assert(nullptr != this);
        if (!m_locked)
            return;
        try
        {
            LevelMutexInfo::MultiUnlock(m_mutexes);
        }
        catch (...)
        {
            // Not much we can do when catching an exception inside a destructor.
        }
    }

    // ----------------------------------------------------------------------------

    bool MultiMutexLocker::Lock()
    {
        assert(nullptr != this);
        if (m_locked)
            return true;
        const MutexErrors result = LevelMutexInfo::MultiLock(m_mutexes);
        if (MutexErrors::Success != result)
            return false;
        m_locked = true;
        return true;
    }

    // ----------------------------------------------------------------------------

    bool MultiMutexLocker::Unlock()
    {
        assert(nullptr != this);
        if (!m_locked)
            return true;
        const MutexErrors result = LevelMutexInfo::MultiUnlock(m_mutexes);
        if (MutexErrors::Success != result)
            return false;
        m_locked = false;
        return true;
    }

    // ----------------------------------------------------------------------------

}  // end namespace Loki

#endif
