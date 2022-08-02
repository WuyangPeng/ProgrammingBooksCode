////////////////////////////////////////////////////////////////////////////////
//
// Part of LevelMutex test program for The Loki Library
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


// ----------------------------------------------------------------------------

#include "Thing.hpp"

#include <assert.h>
#include <algorithm>
#include <functional>

#include <SafeFormat.h>
#include <LockingPtr.h>

using namespace ::Loki;


// ----------------------------------------------------------------------------

typedef ::Loki::LockingPtr< Thing, volatile SleepMutex > SingleThingLocker;

typedef ::Loki::LockingPtr< const Thing, volatile SleepMutex > ConstSingleThingLocker;

typedef ::Loki::LockingPtr< LevelThing, volatile SleepMutex > LevelThingLocker;

typedef ::Loki::LockingPtr< const LevelThing, volatile SleepMutex > ConstLevelThingLocker;

typedef ::Loki::LockingPtr< SomeThing, volatile SleepMutex > SomeThingLocker;

typedef ::Loki::LockingPtr< const SomeThing, volatile SleepMutex > ConstSomeThingLocker;

volatile Thing * Thing::s_thing = nullptr;

Thing::ThingPool Thing::s_pool;

LevelThing::LevelThingPool LevelThing::s_pool;

TestResults * TestResults::s_instance = nullptr;

MultiLevelPool::MultiThingPool MultiLevelPool::s_pool;


// ----------------------------------------------------------------------------

ExceptionTossingMutex::ExceptionTossingMutex( unsigned int level ) :
#if defined( _MSC_VER )
    SleepLevelMutex( level ),
#else
    SleepLevelMutex( level ),
#endif
    m_policy( ExceptionTossingMutex::Never )
{
    assert( nullptr != this );
#if defined( _MSC_VER )
    SetSleepTime( 5 );
    SetWakable( false );
#else
    SetSleepTime( 1 );
#endif
}

// ----------------------------------------------------------------------------

ExceptionTossingMutex::~ExceptionTossingMutex( void )
{
    assert( nullptr != this );
}

// ----------------------------------------------------------------------------

MutexErrors ExceptionTossingMutex::Lock( void ) volatile
{
    if ( m_policy != ExceptionTossingMutex::Never )
    {
        bool toss = ( m_policy == ExceptionTossingMutex::Always );
        if ( !toss )
        {
            const unsigned int number = ( ::rand() % 16 );
            toss = ( 0 == number );
        }
        if ( toss )
        {
            throw MutexException( "Just a test exception from DoLock.",
                GetLevel(), ::Loki::MutexErrors::OtherError );
        }
    }
    return SleepLevelMutex::Lock();
}

// ----------------------------------------------------------------------------

MutexErrors ExceptionTossingMutex::TryLock( void ) volatile
{
    if ( m_policy != ExceptionTossingMutex::Never )
    {
        bool toss = ( m_policy == ExceptionTossingMutex::Always );
        if ( !toss )
        {
            const unsigned int number = ( ::rand() % 16 );
            toss = ( 0 == number );
        }
        if ( toss )
        {
            throw MutexException( "Just a test exception from DoLock.",
                GetLevel(), ::Loki::MutexErrors::OtherError );
        }
    }
    return SleepLevelMutex::TryLock();
}

// ----------------------------------------------------------------------------

MutexErrors ExceptionTossingMutex::Unlock( void ) volatile
{
    if ( m_policy != ExceptionTossingMutex::Never )
    {
        bool toss = ( m_policy == ExceptionTossingMutex::Always );
        if ( !toss )
        {
            const unsigned int number = ( ::rand() % 16 );
            toss = ( 0 == number );
        }
        if ( toss )
        {
            throw MutexException( "Just a test exception from DoLock.",
                GetLevel(), ::Loki::MutexErrors::OtherError );
        }
    }
    return SleepLevelMutex::Unlock();
}

// ----------------------------------------------------------------------------

bool TestResults::Create( unsigned int threadCount )
{
    if ( nullptr != s_instance )
        return true;
    s_instance = new TestResults( threadCount );
    return ( nullptr != s_instance );
}

// ----------------------------------------------------------------------------

void TestResults::Destroy( void )
{
    delete s_instance;
    s_instance = nullptr;
}

// ----------------------------------------------------------------------------

TestResults::TestResults( unsigned int threadCount ) :
    m_results()
{
    assert( nullptr != this );
    Reset( threadCount );
}

// ----------------------------------------------------------------------------

TestResults::~TestResults( void )
{
    assert( nullptr != this );
    assert( this == s_instance );
}

// ----------------------------------------------------------------------------

void TestResults::Reset( unsigned int threadCount )
{
    assert( nullptr != this );
    TestResult result;
    result.m_total = 0;
    result.m_fails = 0;
    m_results.clear();
    m_results.resize( threadCount, result );
}

// ----------------------------------------------------------------------------

void TestResults::SetResult(size_t threadIndex, unsigned int total,
    unsigned int fails )
{
    assert( nullptr != this );
    assert( this == s_instance );

    if ( threadIndex <= m_results.size() )
    {
        m_results[ threadIndex ].m_total = total;
        m_results[ threadIndex ].m_fails = fails;
    }
}

// ----------------------------------------------------------------------------

void TestResults::OutputResults( void )
{
    assert( nullptr != this );
    assert( this == s_instance );

    bool passed = true;
    const auto count = m_results.size();
    for ( unsigned int ii = 0; ii < count; ++ii )
    {
        Printf( "Thread: %d \t total: %d \t fails: %d\n" )( ii )
            ( m_results[ ii ].m_total )
            ( m_results[ ii ].m_fails );
        if ( m_results[ ii ].m_fails != 0 )
            passed = false;
        m_results[ ii ].m_total = 0;
        m_results[ ii ].m_fails = 0;
    }
    const char * message = ( passed ) ? "Passed!" : "FAILED!";
    Printf( "Value Test Result: %s\n" )( message );
}

// ----------------------------------------------------------------------------

TestResults::TestResult::TestResult( void ) :
    m_total( 0 ),
    m_fails( 0 )
{
    assert( nullptr != this );
}

// ----------------------------------------------------------------------------

TestResults::TestResult::TestResult( const TestResult & that ) :
    m_total( that.m_total ),
    m_fails( that.m_fails )
{
    assert( nullptr != this );
}

// ----------------------------------------------------------------------------

TestResults::TestResult::~TestResult( void )
{
    assert( nullptr != this );
}

// ----------------------------------------------------------------------------

void GoToSleep( unsigned int milliSeconds )
{
#if defined( _MSC_VER )
    ::SleepEx( milliSeconds, true );
#elif ( __GNUC__ )
    unsigned int seconds = milliSeconds / 1000;
    if ( 0 == seconds )
        seconds = 1;
    ::_sleep( seconds );
#else
    #error "Find out if your compiler supports a sleep command and add it here."
#endif
}

// ----------------------------------------------------------------------------

void Thing::Init( unsigned int value )
{
    if ( nullptr != s_thing )
        return;
    s_thing = new Thing( value );
}

// ----------------------------------------------------------------------------

void Thing::Destroy( void )
{
    if ( nullptr == s_thing )
        return;
    delete s_thing;
    s_thing = nullptr;
}

// ----------------------------------------------------------------------------

volatile Thing * Thing::GetFromPool( unsigned int index )
{
    if ( s_pool.size() <= index )
        return nullptr;
    volatile Thing * thing = s_pool[ index ];
    return thing;
}

// ----------------------------------------------------------------------------

size_t Thing::GetPoolSize(void)
{
    return s_pool.size();
}

// ----------------------------------------------------------------------------

bool Thing::MakePool( unsigned int count )
{
    if ( ( 0 == count ) || ( 100 < count ) )
        return false;

    DestroyPool();
    s_pool.reserve( count );
    for ( unsigned int ii = 0; ii < count; ++ii )
    {
        volatile Thing * thing = new Thing( ii );
        s_pool.push_back( thing );
    }

    return true;
}

// ----------------------------------------------------------------------------

void Thing::DestroyPool( void )
{
    const auto count = s_pool.size();
    for ( unsigned int ii = 0; ii < count; ++ii )
    {
        volatile Thing * thing = s_pool[ ii ];
        delete thing;
    }
    s_pool.clear();
}

// ----------------------------------------------------------------------------

Thing::Thing( unsigned int value ) :
    m_mutex( 10 ),
    m_value( value )
{
    assert( nullptr != this );
#if defined( _MSC_VER )
    m_mutex.GetMutexPolicy().SetSleepTime( 5 );
    m_mutex.GetMutexPolicy().SetWakable( false );
#else
    m_mutex.GetMutexPolicy().SetSleepTime( 1 );
#endif
}

// ----------------------------------------------------------------------------

Thing::~Thing( void )
{
    assert( nullptr != this );
}

// ----------------------------------------------------------------------------

void Thing::Print(size_t value, unsigned int index, unsigned int startSize) const volatile
{
    assert( nullptr != this );
    volatile SleepMutex & mutex = const_cast< volatile SleepMutex & >( m_mutex );
    ConstSingleThingLocker pSafeThis( *this, mutex );
    pSafeThis->Print( value, index, startSize );
}

// ----------------------------------------------------------------------------

void Thing::Print(size_t value, unsigned int index, unsigned int startSize) const
{
    assert( nullptr != this );
    switch ( startSize )
    {
        default:
        case 16: ::GoToSleep( 3 ); Printf("%d: %d: ----------------\n")( value )( index );
        case 15: ::GoToSleep( 3 ); Printf("%d: %d: ---------------\n")( value )( index );
        case 14: ::GoToSleep( 3 ); Printf("%d: %d: --------------\n")( value )( index );
        case 13: ::GoToSleep( 3 ); Printf("%d: %d: -------------\n")( value )( index );
        case 12: ::GoToSleep( 3 ); Printf("%d: %d: ------------\n")( value )( index );
        case 11: ::GoToSleep( 3 ); Printf("%d: %d: -----------\n")( value )( index );
        case 10: ::GoToSleep( 3 ); Printf("%d: %d: ----------\n")( value )( index );
        case  9: ::GoToSleep( 3 ); Printf("%d: %d: ---------\n")( value )( index );
        case  8: ::GoToSleep( 3 ); Printf("%d: %d: --------\n")( value )( index );
        case  7: ::GoToSleep( 3 ); Printf("%d: %d: -------\n")( value )( index );
        case  6: ::GoToSleep( 3 ); Printf("%d: %d: ------\n")( value )( index );
        case  5: ::GoToSleep( 3 ); Printf("%d: %d: -----\n")( value )( index );
        case  4: ::GoToSleep( 3 ); Printf("%d: %d: ----\n")( value )( index );
        case  3: ::GoToSleep( 3 ); Printf("%d: %d: ---\n")( value )( index );
        case  2: ::GoToSleep( 3 ); Printf("%d: %d: --\n")( value )( index );
        case  1: ::GoToSleep( 3 ); Printf("%d: %d: -\n")( value )( index );
        case  0: ::GoToSleep( 3 ); Printf("%d: %d: \n")( value )( index );
    }
}

// ----------------------------------------------------------------------------

void Thing::SetValue(size_t value) volatile
{
    assert( nullptr != this );
    SingleThingLocker pSafeThis( *this, m_mutex );
    pSafeThis->m_value = value;
}

// ----------------------------------------------------------------------------

volatile LevelThing * LevelThing::GetFromPool( unsigned int index )
{
    if ( s_pool.size() <= index )
        return nullptr;
    volatile LevelThing * thing = s_pool[ index ];
    return thing;
}

// ----------------------------------------------------------------------------

bool LevelThing::MakePool( unsigned int count )
{
    s_pool.clear();
    s_pool.reserve( count );
    for ( unsigned int ii = 0; ii < count; ++ii )
    {
        volatile LevelThing * thing = new LevelThing( ii * 10, ii );
        s_pool.push_back( thing );
    }
    return true;
}

// ----------------------------------------------------------------------------

void LevelThing::DestroyPool( void )
{
    const auto count = s_pool.size();
    for ( unsigned int ii = 0; ii < count; ++ii )
    {
        volatile LevelThing * thing = s_pool[ ii ];
        delete thing;
    }
    s_pool.clear();
}

// ----------------------------------------------------------------------------

LevelThing::LevelThing( unsigned int level, unsigned int place ) :
    m_mutex( level ),
    m_place( place ),
    m_value( 0 )
{
    assert( nullptr != this );
#if defined( _MSC_VER )
    m_mutex.GetMutexPolicy().SetSleepTime( 5 );
    m_mutex.GetMutexPolicy().SetWakable( false );
#else
    m_mutex.GetMutexPolicy().SetSleepTime( 1 );
#endif
}

// ----------------------------------------------------------------------------

LevelThing::~LevelThing( void )
{
    assert( nullptr != this );
}

// ----------------------------------------------------------------------------

LevelThing::Unlocker LevelThing::LockHierarchy( void ) volatile
{
    assert( nullptr != this );
    for ( signed ii = m_place; 0 <= ii; --ii )
    {
        volatile LevelThing * thing = s_pool[ ii ];
        assert( nullptr != thing );
        const MutexErrors result = thing->m_mutex.Lock();
        if ( MutexErrors::Success != result )
            break;
    }

    Unlocker unlocker( this );
    return unlocker;
}

// ----------------------------------------------------------------------------

void LevelThing::UnlockHierarchy( void ) volatile
{
    assert( nullptr != this );
    try
    {
        for ( unsigned ii = 0; ii <= m_place; ++ii )
        {
            volatile LevelThing * thing = s_pool[ ii ];
            assert( nullptr != thing );
            thing->m_mutex.Unlock();
        }
    }
    catch ( ... )
    {
    }
}

// ----------------------------------------------------------------------------

void LevelThing::SetValue(size_t value) volatile
{
    assert( nullptr != this );
    MutexLocker locker( m_mutex, !m_mutex.IsLockedByCurrentThread() );
    (void)locker;
    m_value = value;
    if ( 0 == m_place )
        return;

    volatile LevelThing * thing = s_pool[ m_place - 1 ];
    assert( nullptr != thing );
    thing->SetValue( value );
}

// ----------------------------------------------------------------------------

void LevelThing::SetValue(size_t  value)
{
    assert( nullptr != this );
    m_value = value;
    if ( 0 == m_place )
        return;

    LevelThing * thing = const_cast< LevelThing * >( s_pool[ m_place - 1 ] );
    assert( nullptr != thing );
    thing->SetValue( value );
}

// ----------------------------------------------------------------------------

bool LevelThing::DoValuesMatch(size_t value) const volatile
{
    assert( nullptr != this );
    {
        MutexLocker locker( m_mutex, !m_mutex.IsLockedByCurrentThread() );
        (void)locker;
        if ( m_value != value )
            return false;
    }
    if ( 0 == m_place )
        return true;

    const volatile LevelThing * thing = s_pool[ m_place - 1 ];
    assert( nullptr != thing );
    return thing->DoValuesMatch( value );
}

// ----------------------------------------------------------------------------

bool LevelThing::DoValuesMatch(size_t value) const
{
    assert( nullptr != this );
    if ( m_value != value )
        return false;
    if ( 0 == m_place )
        return true;

    const LevelThing * thing = const_cast< LevelThing * >( s_pool[ m_place - 1 ] );
    assert( nullptr != thing );
    return thing->DoValuesMatch( value );
}

// ----------------------------------------------------------------------------

SomeThing::SomeThing( unsigned int level, unsigned int place ) :
    m_mutex( level ),
    m_place( place ),
    m_level( level ),
    m_value( 0 )
{
    assert( nullptr != this );
#if defined( _MSC_VER )
    m_mutex.GetMutexPolicy().SetSleepTime( 5 );
    m_mutex.GetMutexPolicy().SetWakable( false );
#else
    m_mutex.GetMutexPolicy().SetSleepTime( 1 );
#endif
}

// ----------------------------------------------------------------------------

SomeThing::~SomeThing( void )
{
    assert( nullptr != this );
}

// ----------------------------------------------------------------------------

void SomeThing::SetValue(size_t value) volatile
{
    assert( nullptr != this );
    SomeThingLocker pSafeThis( *this, m_mutex );
    pSafeThis->m_value = value;
}

// ----------------------------------------------------------------------------

void SomeThing::SetValue(size_t value)
{
    assert( nullptr != this );
    m_value = value;
}

// ----------------------------------------------------------------------------

ManyThingsPool::ManyThingsPool( unsigned int level, unsigned int count ) :
    m_pool()
{
    assert( nullptr != this );
    m_pool.reserve( count );
    for ( unsigned int ii = 0; ii < count; ++ii )
    {
        volatile SomeThing * thing = new SomeThing( level, ii );
        m_pool.push_back( thing );
    }
}

// ----------------------------------------------------------------------------

ManyThingsPool::~ManyThingsPool( void )
{
    assert( nullptr != this );
    const auto count = m_pool.size();
    for ( unsigned int ii = 0; ii < count; ++ii )
    {
        volatile SomeThing * thing = m_pool[ ii ];
        delete thing;
    }
    m_pool.clear();
}

// ----------------------------------------------------------------------------

size_t ManyThingsPool::GetCount( void ) const
{
    assert( nullptr != this );
    const auto count = m_pool.size();
    return count;
}

// ----------------------------------------------------------------------------

volatile SomeThing * ManyThingsPool::GetFromPool( unsigned int index )
{
    assert( nullptr != this );
    ManyThingsPool * pThis = const_cast< ManyThingsPool * >( this );
    if ( pThis->m_pool.size() <= index )
        return nullptr;
    volatile SomeThing * thing = pThis->m_pool[ index ];
    assert( nullptr != thing );
    return thing;
}

// ----------------------------------------------------------------------------

void MultiLevelPool::MakePool( unsigned int count, unsigned int thingCount )
{
    s_pool.clear();
    s_pool.reserve( count );
    unsigned int level = 100;
    for ( unsigned int ii = 0; ii < count; ++ii )
    {
        const unsigned int newCount = ( ::rand() % thingCount ) + 4;
        ManyThingsPool * pool = new ManyThingsPool( ii + level, newCount );
        s_pool.push_back( pool );
    }
}

// ----------------------------------------------------------------------------

void MultiLevelPool::DestroyPool( void )
{
    const auto count = s_pool.size();
    for ( unsigned int ii = 0; ii < count; ++ii )
    {
        ManyThingsPool * pool = s_pool[ ii ];
        delete pool;
    }
    s_pool.clear();
}

// ----------------------------------------------------------------------------

size_t MultiLevelPool::GetCount(void)
{
    const auto count = s_pool.size();
    return count;
}

// ----------------------------------------------------------------------------

ManyThingsPool * MultiLevelPool::GetFromPool( unsigned int index )
{
    if ( s_pool.size() <= index )
        return nullptr;
    ManyThingsPool * pool = s_pool[ index ];
    assert( nullptr != pool );
    return pool;
}

// ----------------------------------------------------------------------------

void CheckForMatchingValues( unsigned int & failCount, unsigned int & testCount,
                            size_t value, const SomeThingPool& pool)
{
    const auto count = pool.size();
    for ( unsigned int ii = 0; ii < count; ++ii )
    {
        SomeThing * thing = const_cast< SomeThing * >( pool[ ii ] );
        assert( nullptr != thing );
        testCount++;
        if ( value != thing->GetValue() )
            failCount++;
    }
}

// ----------------------------------------------------------------------------

void CheckForMatchingValues( unsigned int & failCount, unsigned int & testCount,
                            size_t value, const SomeThingPool& pool, bool locked)
{
    if ( !locked )
    {
        CheckForMatchingValues( failCount, testCount, value, pool );
        return;
    }

    const auto count = pool.size();
    for ( unsigned int ii = 0; ii < count; ++ii )
    {
        volatile SomeThing * thing = pool[ ii ];
        assert( nullptr != thing );
        assert( thing->GetMutex().IsLockedByCurrentThread() );
        testCount++;
        if ( value != thing->GetValue() )
            failCount++;
    }
}

// ----------------------------------------------------------------------------

void MakePool( SomeThingPool & target )
{
    SomeThingPool temp;
    bool useThis = false;
    size_t count2 = 0;
    unsigned int r = 0;
    bool first = true;
    const size_t count1 = MultiLevelPool::GetCount();

    for ( unsigned int index1 = 0; index1 < count1; ++index1 )
    {
        r = ( ::rand() % 4 );
        useThis = ( 0 == index1 ) || ( r != 0 );
        if ( !useThis )
            continue;

        ManyThingsPool * pool = MultiLevelPool::GetFromPool( index1 );
        assert( nullptr != pool );
        count2 = pool->GetCount();
        first = true;

        for ( unsigned int index2 = 0; index2 < count2; ++index2 )
        {
            r = ( ::rand() % 4 );
            useThis = ( 0 == index1 ) || ( r != 0 );
            if ( !useThis )
                continue;
            volatile SomeThing * thing = pool->GetFromPool( index2 );
            assert( nullptr != thing );
            temp.push_back( thing );

            if ( first )
            {
                // The containers at most levels will have multiple mutexes,
                // but some levels will have just a single mutex.
                r = ( ::rand() % 4 );
                if ( r != 0 )
                    break;
            }
            first = false;
        }
    }

    temp.swap( target );
}

// ----------------------------------------------------------------------------

/// @struct SomeThingComparator Binary-functor for comparing 2 SomeThing's.
struct SomeThingComparator // : std::binary_function< volatile SomeThing *, volatile SomeThing *, bool >
{
    using first_argument_type = volatile SomeThing *;
    using second_argument_type = volatile SomeThing *;
    using result_type = bool;

    /// Returns true if left string < right string.
	inline bool operator ()( volatile SomeThing * lhs, volatile SomeThing * rhs ) const
    {
        return ( lhs->GetLevel() < rhs->GetLevel() );
    }
};

// ----------------------------------------------------------------------------

void SortByLevel( SomeThingPool & pool )
{
    const auto count = pool.size();
    assert( 0 != count );
    SomeThingComparator comparator;
    ::std::sort( pool.begin(), pool.end(), comparator );
}

// ----------------------------------------------------------------------------

void LockThese( SomeThingPool & pool )
{

    const auto count = pool.size();
    assert( 0 != count );
    SortByLevel( pool );

    volatile SomeThing * thing = pool[ count - 1 ];
    assert( nullptr != thing );
    unsigned int level = thing->GetLevel();
    LevelMutexInfo::MutexContainer mutexes;
    MutexErrors result = MutexErrors::Success;
    signed int ii = static_cast<int>(count - 1);

    for ( ; 0 <= ii; --ii )
    {
        thing = pool[ ii ];
        assert( nullptr != thing );
        if ( level != thing->GetLevel() )
        {
            assert( mutexes.size() != 0 );
            result = LevelMutexInfo::MultiLock( mutexes );
            assert( result == MutexErrors::Success );
            mutexes.clear();
            level = thing->GetLevel();
        }
        mutexes.push_back( &thing->GetMutex() );
    }

    assert( mutexes.size() != 0 );
    result = LevelMutexInfo::MultiLock( mutexes );
    assert( result == MutexErrors::Success );

    for ( ii = static_cast<int>(count - 1); 0 <= ii; --ii )
    {
        thing = pool[ ii ];
        assert( nullptr != thing );
        assert( thing->GetMutex().IsLockedByCurrentThread() );
    }
}

// ----------------------------------------------------------------------------

void UnlockThese( SomeThingPool & pool )
{

    const auto count = pool.size();
    assert( 0 != count );
    SortByLevel( pool );

    volatile SomeThing * thing = pool[ 0 ];
    assert( nullptr != thing );
    unsigned int level = thing->GetLevel();
    LevelMutexInfo::MutexContainer mutexes;
    MutexErrors result = MutexErrors::Success;
    unsigned int ii = 0;

    for ( ii = 0; ii < count; ++ii )
    {
        thing = pool[ ii ];
        assert( nullptr != thing );
        if ( level != thing->GetLevel() )
        {
            assert( mutexes.size() != 0 );
            result = LevelMutexInfo::MultiUnlock( mutexes );
            assert( result == MutexErrors::Success );
            mutexes.clear();
            level = thing->GetLevel();
        }
        mutexes.push_back( &thing->GetMutex() );
    }

    assert( mutexes.size() != 0 );
    result = LevelMutexInfo::MultiUnlock( mutexes );
    assert( result == MutexErrors::Success );

    for ( ii = 0; ii < count; ++ii )
    {
        thing = pool[ ii ];
        assert( nullptr != thing );
        assert( !thing->GetMutex().IsLockedByCurrentThread() );
    }
}

// ----------------------------------------------------------------------------

unsigned int CountLockedByThisThread( const SomeThingPool & pool )
{
    const auto count = pool.size();
    unsigned int locked = 0;

    for ( unsigned int ii = 0; ii < count; ++ii )
    {
        const volatile SomeThing * thing = pool[ ii ];
        assert( nullptr != thing );
        if ( thing->GetMutex().IsLockedByCurrentThread() )
            locked++;
    }

    return locked;
}

// ----------------------------------------------------------------------------
