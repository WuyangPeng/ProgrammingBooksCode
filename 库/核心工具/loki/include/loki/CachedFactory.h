////////////////////////////////////////////////////////////////////////////////
// The Loki Library
// Copyright (c) 2006 by Guillaume Chatelet
//
// Code covered by the MIT License
//
// Permission to use, copy, modify, distribute and sell this software for any
// purpose is hereby granted without fee, provided that the above copyright
// notice appear in all copies and that both that copyright notice and this
// permission notice appear in supporting documentation.
//
// The authors make no representations about the suitability of this software
// for any purpose. It is provided "as is" without express or implied warranty.
//
// This code DOES NOT accompany the book:
// Alexandrescu, Andrei. "Modern C++ Design: Generic Programming and Design
//     Patterns Applied". Copyright (c) 2001. Addison-Wesley.
//
////////////////////////////////////////////////////////////////////////////////
#ifndef LOKI_CACHEDFACTORY_INC_
#define LOKI_CACHEDFACTORY_INC_

// $Id: CachedFactory.h 950 2009-01-26 19:45:54Z syntheticpp $

#include <loki/Key.h>
#include <algorithm>
#include <cassert>
#include <functional>
#include <iostream>
#include <iterator>
#include <map>
#include <vector>

#ifdef DO_EXTRA_LOKI_TESTS
    #define D(x) x
#else
    #define D(x) ;
#endif

#if defined(_MSC_VER) || defined(__CYGWIN__)
    #include <time.h>
#endif

/**
 * \defgroup	FactoriesGroup Factories
 * \defgroup	CachedFactoryGroup Cached Factory
 * \ingroup		FactoriesGroup
 * \brief		CachedFactory provides an extension of a Factory with caching
 * support.
 * CachedFactory提供了带有缓存的工厂扩展。
 * 
 * Once used objects are returned to the CachedFactory that manages its
 * destruction.
 * If your code uses lots of "long to construct/destruct objects" using the
 * CachedFactory will surely speedup the execution.
 * 一旦使用过的对象返回到CachedFactory，管理其销毁。
 * 如果您的代码大量使用“长时间构造/销毁对象”，使用CachedFactory则肯定会加快执行速度。
 */
namespace Loki
{
    /**
     * \defgroup	EncapsulationPolicyCachedFactoryGroup	Encapsulation policies
     * \ingroup	CachedFactoryGroup
     * \brief	Defines how the object is returned to the client
     * 定义如何将对象返回给客户端
    */
    /**
	 * \class	SimplePointer
	 * \ingroup	EncapsulationPolicyCachedFactoryGroup
	 * \brief	No encaspulation : returns the pointer
	 * 
	 * This implementation does not make any encapsulation.
	 * It simply returns the object's pointer.
     * 此实现不进行任何封装。 它只是返回对象的指针。
	 */
    template <class AbstractProduct>
    class SimplePointer
    {
    protected:
        typedef AbstractProduct* ProductReturn;

        ProductReturn encapsulate(AbstractProduct* pProduct)
        {
            return pProduct;
        }

        AbstractProduct* release(ProductReturn& pProduct)
        {
            AbstractProduct* pPointer(pProduct);
            pProduct = nullptr;
            return pPointer;
        }

        const char* name()
        {
            return "pointer";
        }
    };

    /**
    * \defgroup	CreationPolicyCachedFactoryGroup		Creation policies
    * \ingroup		CachedFactoryGroup
    * \brief		Defines a way to limit the creation operation.
    * 定义一种限制创建操作的方法。
    * 
    * For instance one may want to be alerted (Exception) when
    * - Cache has created a more than X object within the last x seconds
    * - Cache creation rate has increased dramatically
    * 例如，可能在以下情况下收到警报（异常）：
    * ——缓存在过去的x秒内创建了多个X对象
    * ——缓存的创建速度急剧提高
    * .
    * which may result from bad caching strategy, or critical overload
    * 这可能是由于不良的缓存策略或严重的过载造成的
    */
    /**
	 * \class	NeverCreate
	 * \ingroup	CreationPolicyCachedFactoryGroup
	 * \brief	Never allows creation. Testing purposes only.
	 * 
	 * Using this policy will throw an exception.
     * 使用此策略将引发异常。
	 */
    class NeverCreate
    {
    protected:
        struct Exception : public std::exception
        {
            const char* what() const noexcept
            {
                return "NeverFetch Policy : No Fetching allowed";
            }
        };

        bool canCreate()
        {
            throw Exception();
        }

        void onCreate()
        {
        }

        void onDestroy()
        {
        }

        const char* name()
        {
            return "never";
        }
    };

    /**
      * \class		AlwaysCreate
      * \ingroup	CreationPolicyCachedFactoryGroup
      * \brief		Always allows creation.
      * 
      * Doesn't limit the creation in any way
      * 不以任何方式限制创建
      */
    class AlwaysCreate
    {
    protected:
        bool canCreate()
        {
            return true;
        }

        void onCreate()
        {
        }

        void onDestroy()
        {
        }

        const char* name()
        {
            return "always";
        }
    };

    /**
     * \class	RateLimitedCreation
     * \ingroup	CreationPolicyCachedFactoryGroup
     * \brief	Limit in rate.
     * 速率限制。
     * 
     * This implementation will prevent from Creating more than maxCreation objects
     * within byTime ms by throwing an exception.
     * Could be usefull to detect prevent loads (http connection for instance).
     * Use the setRate method to set the rate parameters.
     * default is 10 objects in a second.
     * 此实现将通过抛出异常来防止在byTime ms内创建多个maxCreation对象。
     * 可能对检测阻止负载（例如http连接）有用。
     * 使用setRate方法设置速率参数。
     * 默认为每秒10个对象。
     */
    // !! CAUTION !!
    // The std::clock() function is not quite precise
    // under linux this policy might not work.
    // TODO : get a better implementation (platform dependant)
    // 在Linux下，std::clock()函数不太精确，此策略可能无法正常工作。
    // TODO：获得更好的实现（取决于平台）
    class RateLimitedCreation
    {
    private:
        typedef std::vector<clock_t> Vector;
        Vector m_vTimes;
        unsigned m_MaxCreation;
        clock_t timeValidity;
        clock_t lastUpdate;

        void cleanVector()
        {
            using namespace std;
            clock_t currentTime = clock();
            D(cout << "currentTime = " << currentTime << endl;)
            D(cout << "currentTime - lastUpdate = " << currentTime - lastUpdate << endl;)
            if (currentTime - lastUpdate > timeValidity)
            {
                m_vTimes.clear();
                D(cout << " is less than time validity " << timeValidity;)
                D(cout << " so clearing vector" << endl;)
            }
            else
            {
                D(cout << "Cleaning time less than " << currentTime - timeValidity << endl;)
                D(displayVector();)
                auto difference = currentTime - timeValidity;
                Vector::iterator newEnd = remove_if(m_vTimes.begin(), m_vTimes.end(), [difference](const auto& value) {
                    return value < difference;
                });

                // this rearrangement might be costly, consider optimization
                // by calling cleanVector in less used onCreate function
                // ... although it may not be correct
                // 这种重排可能代价很高，请考虑通过在较少使用的onCreate函数中调用cleanVector来进行优化
                // ... 虽然可能不正确
                m_vTimes.erase(newEnd, m_vTimes.end());
                D(displayVector();)
            }
            lastUpdate = currentTime;
        }

#ifdef DO_EXTRA_LOKI_TESTS
        void displayVector()
        {
            std::cout << "Vector : ";
            copy(m_vTimes.begin(), m_vTimes.end(), std::ostream_iterator<clock_t>(std::cout, " "));
            std::cout << std::endl;
        }
#endif

    protected:
        RateLimitedCreation()
            : m_MaxCreation(10), timeValidity(CLOCKS_PER_SEC), lastUpdate(clock())
        {
        }

        struct Exception : public std::exception
        {
            const char* what() const noexcept
            {
                return "RateLimitedCreation Policy : Exceeded the authorized creation rate";
            }
        };

        bool canCreate()
        {
            cleanVector();
            if (m_vTimes.size() > m_MaxCreation)
                throw Exception();
            else
                return true;
        }

        void onCreate()
        {
            m_vTimes.push_back(clock());
        }

        void onDestroy()
        {
        }

        const char* name()
        {
            return "rate limited";
        }

    public:
        // set the creation rate
        // No more than maxCreation within byTime milliseconds
        // 设置创建速度
        // 在byTime毫秒内不超过maxCreation
        void setRate(unsigned maxCreation, unsigned byTime)
        {
            assert(byTime > 0);
            this->m_MaxCreation = maxCreation;
            this->timeValidity = static_cast<clock_t>(byTime * CLOCKS_PER_SEC / 1000);
            D(std::cout << "Setting no more than " << maxCreation << " creation within " << this->timeValidity << " ms" << std::endl;)
        }
    };

    /**
     * \class	AmountLimitedCreation
     * \ingroup	CreationPolicyCachedFactoryGroup
     * \brief	Limit by number of objects
     * 受对象数限制
     * 
     * This implementation will prevent from Creating more than maxCreation objects
     * within byTime ms by calling eviction policy.
     * Use the setRate method to set the rate parameters.
     * default is 10 objects.
     * 此实现将通过调用驱逐策略来防止在byTime ms内创建多个maxCreation对象。
     * 使用setRate方法设置速率参数。
     * 默认为10个对象
     */
    class AmountLimitedCreation
    {
    private:
        unsigned m_MaxCreation;
        unsigned created;

    protected:
        AmountLimitedCreation()
            : m_MaxCreation(10), created(0)
        {
        }

        bool canCreate()
        {
            return !(created >= m_MaxCreation);
        }

        void onCreate()
        {
            ++created;
        }

        void onDestroy()
        {
            --created;
        }
        const char* name()
        {
            return "amount limited";
        }

    public:
        // set the creation max amount
        // 设置创建的最大数量
        void setMaxCreation(unsigned maxCreation)
        {
            assert(maxCreation > 0);
            this->m_MaxCreation = maxCreation;
            D(std::cout << "Setting no more than " << maxCreation << " creation" << std::endl;)
        }
    };

    /**
        * \defgroup	EvictionPolicyCachedFactoryGroup		Eviction policies
        * \ingroup	CachedFactoryGroup
        * \brief	Gathers informations about the stored objects and choose a
        * candidate for eviction.
        * 收集有关存储对象的信息，然后选择驱逐对象。
    */

    class EvictionException : public std::exception
    {
    public:
        const char* what() const noexcept
        {
            return "Eviction Policy : trying to make room but no objects are available";
        }
    };

    // The following class is intented to provide helpers to sort
    // the container that will hold an eviction score
    // 下面的类旨在提供帮助者，对装有驱逐分数的容器进行排序。
    template <
        typename ST,  // Score type
        typename DT  // Data type
        >
    class EvictionHelper
    {
    protected:
        typedef typename std::map<DT, ST> HitMap;
        typedef typename HitMap::iterator HitMapItr;

    private:
        typedef std::pair<ST, DT> SwappedPair;
        typedef std::multimap<ST, DT> SwappedHitMap;
        typedef typename SwappedHitMap::iterator SwappedHitMapItr;

    protected:
        HitMap m_mHitCount;

        // This function sorts the map according to the score
        // and returns the lower bound of the sorted container
        // 此函数根据得分对map进行排序，并返回已排序容器的下限
        DT& getLowerBound()
        {
            assert(!m_mHitCount.empty());
            // inserting the swapped pair into a multimap
            // 将交换对插入multimap
            SwappedHitMap copyMap;
            for (HitMapItr itr = m_mHitCount.begin(); itr != m_mHitCount.end(); ++itr)
                copyMap.insert(SwappedPair((*itr).second, (*itr).first));
            if ((*copyMap.rbegin()).first == 0)  // the higher score is 0 ...
                throw EvictionException();  // there is no key evict
            return (*copyMap.begin()).second;
        }
    };

    /**
	 * \class	EvictLRU
	 * \ingroup	EvictionPolicyCachedFactoryGroup
	 * \brief	Evicts least accessed objects first.
	 * 
	 * Implementation of the Least recent used algorithm as
	 * described in http://en.wikipedia.org/wiki/Page_replacement_algorithms .
     * 如 http://en.wikipedia.org/wiki/Page_replacement_algorithms 中所述的最近最少使用算法的实现。
	 * 
	 * WARNING : If an object is heavily fetched
	 * (more than ULONG_MAX = UINT_MAX = 4294967295U)
	 * it could unfortunately be removed from the cache.
     * 警告：如果大量提取对象（超过ULONG_MAX = UINT_MAX = 4294967295U），则可能会将其从缓存中删除。
	 */
    template <
        typename DT,  // Data Type (AbstractProduct*)
        typename ST = unsigned  // default data type to use as Score Type
        >
    class EvictLRU : public EvictionHelper<ST, DT>
    {
    private:
        typedef EvictionHelper<ST, DT> EH;

    protected:
        virtual ~EvictLRU()
        {
        }

        // OnStore initialize the counter for the new key
        // If the key already exists, the counter is reseted
        // OnStore初始化新密钥的计数器，如果密钥已经存在，则重置计数器
        void onCreate(const DT& key)
        {
            EH::m_mHitCount[key] = 0;
        }

        void onFetch(const DT&)
        {
        }

        // onRelease increments the hit counter associated with the object
        // onRelease增加与对象关联的命中计数器
        void onRelease(const DT& key)
        {
            ++(EH::m_mHitCount[key]);
        }

        void onDestroy(const DT& key)
        {
            EH::m_mHitCount.erase(key);
        }

        // this function is implemented in Cache and redirected
        // to the Storage Policy
        // 此函数在Cache中实现，并重定向到存储策略
        virtual void remove(DT const key) = 0;

        // LRU Eviction policy
        // LRU驱逐策略
        void evict()
        {
            remove(EH::getLowerBound());
        }

        const char* name()
        {
            return "LRU";
        }
    };

    /**
	 * \class	EvictAging
	 * \ingroup	EvictionPolicyCachedFactoryGroup
	 * \brief	LRU aware of the time span of use
	 * 
	 * Implementation of the Aging algorithm as
	 * described in http://en.wikipedia.org/wiki/Page_replacement_algorithms .
     * 如 http://en.wikipedia.org/wiki/Page_replacement_algorithms 中所述的时效算法的实现。
	 * 
	 * This method is much more costly than evict LRU so
	 * if you need extreme performance consider switching to EvictLRU
     * 此方法比驱逐LRU的成本高得多，因此，如果您需要出色的性能，请考虑切换到Evict LRU。
	 */
    template <
        typename DT,  // Data Type (AbstractProduct*)
        typename ST = unsigned  // default data type to use as Score Type
        >
    class EvictAging : public EvictionHelper<ST, DT>
    {
    private:
        EvictAging(const EvictAging&) = delete;
        EvictAging& operator=(const EvictAging&) = delete;
        typedef EvictionHelper<ST, DT> EH;
        typedef typename EH::HitMap HitMap;
        typedef typename EH::HitMapItr HitMapItr;

        // update the counter
        // 更新计数器
        template <class T>
        struct updateCounter
        {
            updateCounter(const DT& key)
                : key_(key)
            {
            }

            void operator()(T x)
            {
                x.second = (x.first == key_ ? (x.second >> 1) | (1 << ((sizeof(ST) - 1) * 8)) : x.second >> 1);
                D(std::cout << x.second << std::endl;)
            }

            const DT& key_;
            updateCounter(const updateCounter& rhs)
                : key_(rhs.key_)
            {
            }

        private:
            updateCounter& operator=(const updateCounter& rhs) = delete;
        };

    protected:
        EvictAging()
        {
        }
        virtual ~EvictAging()
        {
        }

        // OnStore initialize the counter for the new key
        // If the key already exists, the counter is reseted
        // OnStore初始化新密钥的计数器。如果密钥已经存在，则重置计数器。
        void onCreate(const DT& key)
        {
            EH::m_mHitCount[key] = 0;
        }

        void onFetch(const DT&)
        {
        }

        // onRelease increments the hit counter associated with the object
        // Updating every counters by iterating over the map
        // If the key is the key of the fetched object :
        //  the counter is shifted to the right and it's MSB is set to 1
        // else
        //  the counter is shifted to the left
        //  onRelease增加与对象关联的命中计数器，通过遍历map来更新每个计数器
        //  如果键是获取的对象的键：
        //  计数器向右移动，并且MSB设置为1，
        //  否则
        //  计数器向左移动。
        void onRelease(const DT& key)
        {
            std::for_each(EH::m_mHitCount.begin(), EH::m_mHitCount.end(), updateCounter<typename HitMap::value_type>(key));
        }

        void onDestroy(const DT& key)
        {
            EH::m_mHitCount.erase(key);
        }

        // this function is implemented in Cache and redirected
        // to the Storage Policy
        // 此函数在缓存中实现，并重定向到存储策略
        virtual void remove(DT const key) = 0;

        // LRU with Aging Eviction policy
        // 具有时效驱逐政策的LRU
        void evict()
        {
            remove(EH::getLowerBound());
        }
        const char* name()
        {
            return "LRU with aging";
        }
    };

    /**
	 * \class	EvictRandom
	 * \ingroup	EvictionPolicyCachedFactoryGroup
	 * \brief	Evicts a random object
	 * 
	 * Implementation of the Random algorithm as
	 * described in http://en.wikipedia.org/wiki/Page_replacement_algorithms .
     * 如 http://en.wikipedia.org/wiki/Page_replacement_algorithms 中所述的随机算法的实现。
	 */
    template <
        typename DT,  // Data Type (AbstractProduct*)
        typename ST = void  // Score Type not used by this policy
        >
    class EvictRandom
    {
    private:
        std::vector<DT> m_vKeys;
        typedef typename std::vector<DT>::size_type size_type;
        typedef typename std::vector<DT>::iterator iterator;

    protected:
        virtual ~EvictRandom()
        {
        }

        void onCreate(const DT&)
        {
        }

        void onFetch(const DT&)
        {
        }

        void onRelease(const DT& key)
        {
            m_vKeys.push_back(key);
        }

        void onDestroy(const DT& key)
        {
            using namespace std;
            m_vKeys.erase(remove_if(m_vKeys.begin(), m_vKeys.end(), [key](const auto& value) {
                              return value == key;
                          }),
                          m_vKeys.end());
        }

        // Implemented in Cache and redirected to the Storage Policy
        // 在缓存中实现并重定向到存储策略
        virtual void remove(DT const key) = 0;

        // Random Eviction policy
        // 随机驱逐政策
        void evict()
        {
            if (m_vKeys.empty())
                throw EvictionException();
            size_type random = static_cast<size_type>((m_vKeys.size() * rand()) / (static_cast<size_type>(RAND_MAX) + 1));
            remove(*(m_vKeys.begin() + random));
        }
        const char* name()
        {
            return "random";
        }
    };

    /**
    * \defgroup	StatisticPolicyCachedFactoryGroup		Statistic policies
    * \ingroup	CachedFactoryGroup
    * \brief	Gathers information about the cache.
    * 
    * For debugging purpose this policy proposes to gather informations
    * about the cache. This could be useful to determine whether the cache is
    * mandatory or if the policies are well suited to the application.
    * 为了调试目的，该策略建议收集有关缓存的信息。 
    * 这对于确定缓存是强制性的还是策略是否非常适合应用程序可能很有用。
    */
    /**
	 * \class	NoStatisticPolicy
	 * \ingroup	StatisticPolicyCachedFactoryGroup
	 * \brief	Do nothing
	 *
	 * Should be used in release code for better performances  
     * 应该在发布代码中使用以获得更好的性能
	 */
    class NoStatisticPolicy
    {
    protected:
        void onDebug()
        {
        }
        void onFetch()
        {
        }
        void onRelease()
        {
        }
        void onCreate()
        {
        }
        void onDestroy()
        {
        }
        const char* name()
        {
            return "no";
        }
    };

    /**
	 * \class	SimpleStatisticPolicy
	 * \ingroup	StatisticPolicyCachedFactoryGroup
	 * \brief	Simple statistics
	 *
	 * Provides the following informations about the cache :
     * 提供有关缓存的以下信息：
	 * 		- Created objects
	 * 		- Fetched objects
	 * 		- Destroyed objects
	 * 		- Cache hit
	 * 		- Cache miss
	 * 		- Currently allocated
	 * 		- Currently out
	 * 		- Cache overall efficiency
	 */
    class SimpleStatisticPolicy
    {
    private:
        unsigned allocated, created, hit, out, fetched;

    protected:
        SimpleStatisticPolicy()
            : allocated(0), created(0), hit(0), out(0), fetched(0)
        {
        }

        void onDebug()
        {
            using namespace std;
            cout << "############################" << endl;
            cout << "## About this cache " << this << endl;
            cout << "## + Created objects     : " << created << endl;
            cout << "## + Fetched objects     : " << fetched << endl;
            cout << "## + Destroyed objects   : " << created - allocated << endl;
            cout << "## + Cache hit           : " << hit << endl;
            cout << "## + Cache miss          : " << fetched - hit << endl;
            cout << "## + Currently allocated : " << allocated << endl;
            cout << "## + Currently out       : " << out << endl;
            cout << "############################" << endl;
            if (fetched != 0)
            {
                cout << "## Overall efficiency " << 100 * double(hit) / fetched << "%" << endl;
                cout << "############################" << endl;
            }
            cout << endl;
        }

        void onFetch()
        {
            ++fetched;
            ++out;
            ++hit;
        }
        void onRelease()
        {
            --out;
        }
        void onCreate()
        {
            ++created;
            ++allocated;
            --hit;
        }
        void onDestroy()
        {
            --allocated;
        }

        const char* name()
        {
            return "simple";
        }

    public:
        unsigned getCreated()
        {
            return created;
        }
        unsigned getFetched()
        {
            return fetched;
        }
        unsigned getHit()
        {
            return hit;
        }
        unsigned getMissed()
        {
            return fetched - hit;
        }
        unsigned getAllocated()
        {
            return allocated;
        }
        unsigned getOut()
        {
            return out;
        }
        unsigned getDestroyed()
        {
            return created - allocated;
        }
    };

    ///////////////////////////////////////////////////////////////////////////
    // Cache Factory definition
    // 缓存工厂定义
    ///////////////////////////////////////////////////////////////////////////
    class CacheException : public std::exception
    {
    public:
        const char* what() const throw()
        {
            return "Internal Cache Error";
        }
    };

    /**
	 * \class		CachedFactory
	 * \ingroup		CachedFactoryGroup
	 * \brief		Factory with caching support
	 * 
     * This class acts as a Factory (it creates objects)
     * but also keeps the already created objects to prevent
     * long constructions time.
     * 该类充当Factory（它创建对象），但也保留已创建的对象，以防止较长的构造时间。
	 * 
	 * Note this implementation do not retain ownership.
     * 请注意，此实现不保留所有权
	 */
    template <class AbstractProduct,
              typename IdentifierType,
              typename CreatorParmTList = NullType,
              template <class> class EncapsulationPolicy = SimplePointer,
              class CreationPolicy = AlwaysCreate,
              template <typename, typename> class EvictionPolicy = EvictRandom,
              class StatisticPolicy = NoStatisticPolicy,
              template <typename, class> class FactoryErrorPolicy = DefaultFactoryError,
              class ObjVector = std::vector<AbstractProduct*>>
    class CachedFactory : protected EncapsulationPolicy<AbstractProduct>,
                          public CreationPolicy,
                          public StatisticPolicy,
                          EvictionPolicy<AbstractProduct*, unsigned>
    {
    private:
        typedef Factory<AbstractProduct, IdentifierType, CreatorParmTList, FactoryErrorPolicy> MyFactory;
        typedef FactoryImpl<AbstractProduct, IdentifierType, CreatorParmTList> Impl;
        typedef Functor<AbstractProduct*, CreatorParmTList> ProductCreator;
        typedef EncapsulationPolicy<AbstractProduct> NP;
        typedef CreationPolicy CP;
        typedef StatisticPolicy SP;
        typedef EvictionPolicy<AbstractProduct*, unsigned> EP;

        typedef typename Impl::Parm1 Parm1;
        typedef typename Impl::Parm2 Parm2;
        typedef typename Impl::Parm3 Parm3;
        typedef typename Impl::Parm4 Parm4;
        typedef typename Impl::Parm5 Parm5;
        typedef typename Impl::Parm6 Parm6;
        typedef typename Impl::Parm7 Parm7;
        typedef typename Impl::Parm8 Parm8;
        typedef typename Impl::Parm9 Parm9;
        typedef typename Impl::Parm10 Parm10;
        typedef typename Impl::Parm11 Parm11;
        typedef typename Impl::Parm12 Parm12;
        typedef typename Impl::Parm13 Parm13;
        typedef typename Impl::Parm14 Parm14;
        typedef typename Impl::Parm15 Parm15;

    public:
        typedef typename NP::ProductReturn ProductReturn;

    private:
        typedef Key<Impl, IdentifierType> MyKey;
        typedef std::map<MyKey, ObjVector> KeyToObjVectorMap;
        typedef std::map<AbstractProduct*, MyKey> FetchedObjToKeyMap;

        MyFactory factory;
        KeyToObjVectorMap fromKeyToObjVector;
        FetchedObjToKeyMap providedObjects;
        unsigned outObjects;

        ObjVector& getContainerFromKey(MyKey key)
        {
            return fromKeyToObjVector[key];
        }

        AbstractProduct* const getPointerToObjectInContainer(ObjVector& entry)
        {
            if (entry.empty())  // No object available（没有可用的物件）
            {  // the object will be created in the calling function.
                // It has to be created in the calling function because of
                // the variable number of parameters for CreateObject(...) method
                // 该对象将在调用函数中创建。 由于CreateObject(...) 方法的参数数量可变，因此必须在调用函数中创建它
                return nullptr;
            }
            else
            {  // returning the found object
                // 返回找到的对象
                AbstractProduct* pObject(entry.back());
                assert(pObject != nullptr);
                entry.pop_back();
                return pObject;
            }
        }

        bool shouldCreateObject(AbstractProduct* const pProduct)
        {
            if (pProduct != nullptr)  // object already exists（对象已经存在）
                return false;
            if (CP::canCreate() == false)  // Are we allowed to Create ?（我们可以创建吗？）
                EP::evict();  // calling Eviction Policy to clean up（调用驱逐政策进行清理）
            return true;
        }

        void ReleaseObjectFromContainer(ObjVector& entry, AbstractProduct* const object)
        {
            entry.push_back(object);
        }

        void onFetch(AbstractProduct* const pProduct)
        {
            SP::onFetch();
            EP::onFetch(pProduct);
            ++outObjects;
        }

        void onRelease(AbstractProduct* const pProduct)
        {
            SP::onRelease();
            EP::onRelease(pProduct);
            --outObjects;
        }

        void onCreate(AbstractProduct* const pProduct)
        {
            CP::onCreate();
            SP::onCreate();
            EP::onCreate(pProduct);
        }

        void onDestroy(AbstractProduct* const pProduct)
        {
            CP::onDestroy();
            SP::onDestroy();
            EP::onDestroy(pProduct);
        }

        // delete the object
        template <class T>
        struct deleteObject
        {
            void operator()(T x)
            {
                delete x;
            }
        };

        // delete the objects in the vector
        template <class T>
        struct deleteVectorObjects
        {
            void operator()(T x)
            {
                ObjVector& vec(x.second);
                std::for_each(vec.begin(), vec.end(), deleteObject<typename ObjVector::value_type>());
            }
        };

        // delete the keys of the map
        template <class T>
        struct deleteMapKeys
        {
            void operator()(T x)
            {
                delete x.first;
            }
        };

    protected:
        virtual void remove(AbstractProduct* const pProduct)
        {
            typename FetchedObjToKeyMap::iterator fetchedItr = providedObjects.find(pProduct);
            if (fetchedItr != providedObjects.end())  // object is unreleased.（对象未发布）
                throw CacheException();
            bool productRemoved = false;
            typename KeyToObjVectorMap::iterator objVectorItr;
            typename ObjVector::iterator objItr;
            for (objVectorItr = fromKeyToObjVector.begin(); objVectorItr != fromKeyToObjVector.end(); ++objVectorItr)
            {
                ObjVector& v((*objVectorItr).second);
                objItr = remove_if(v.begin(), v.end(), [pProduct](const auto& value) {
                    return value == pProduct;
                });

                if (objItr != v.end())  // we found the vector containing pProduct and removed it（我们找到了包含pProduct的载体并将其删除）
                {
                    onDestroy(pProduct);  // warning policies we are about to destroy an object（警告政策，我们将要摧毁一个物体）
                    v.erase(objItr, v.end());  // real removing
                    productRemoved = true;
                    break;
                }
            }
            if (productRemoved == false)
                throw CacheException();  // the product is not in the cache ?!（产品不在缓存中？！）
            delete pProduct;  // deleting it
        }

    public:
        CachedFactory()
            : factory(), fromKeyToObjVector(), providedObjects(), outObjects(0)
        {
        }

        ~CachedFactory()
        {
            using namespace std;
            // debug information
            SP::onDebug();
            // cleaning the Cache
            for_each(fromKeyToObjVector.begin(), fromKeyToObjVector.end(), deleteVectorObjects<typename KeyToObjVectorMap::value_type>());
            if (!providedObjects.empty())
            {
                // The factory is responsible for the creation and destruction of objects.
                // If objects are out during the destruction of the Factory : deleting anyway.
                // This might not be a good idea. But throwing an exception in a destructor is
                // considered as a bad pratice and asserting might be too much.
                // What to do ? Leaking memory or corrupting in use pointers ? hmm...
                // 工厂负责创建和销毁对象。
                // 如果在销毁工厂期间有物体掉出来：仍要删除。 这可能不是一个好主意。
                // 但是在析构函数中抛出异常被认为是一种糟糕的做法，断言可能太多了。
                // 该怎么办 ？ 内存泄漏或使用指针损坏？ 嗯...
                D(cout << "====>>  Cache destructor : deleting " << providedObjects.size() << " in use objects  <<====" << endl
                       << endl;)
                for_each(providedObjects.begin(), providedObjects.end(),
                         deleteMapKeys<typename FetchedObjToKeyMap::value_type>());
            }
        }

        ///////////////////////////////////
        // Acts as the proxy pattern and //
        // forwards factory methods      //
        // 充当代理模式并转发工厂方法    //
        ///////////////////////////////////

        bool Register(const IdentifierType& id, ProductCreator creator)
        {
            return factory.Register(id, creator);
        }

        template <class PtrObj, typename CreaFn>
        bool Register(const IdentifierType& id, const PtrObj& p, CreaFn fn)
        {
            return factory.Register(id, p, fn);
        }

        bool Unregister(const IdentifierType& id)
        {
            return factory.Unregister(id);
        }

        /// Return the registered ID in this Factory
        /// 返回该工厂的注册ID
        std::vector<IdentifierType>& RegisteredIds()
        {
            return factory.RegisteredIds();
        }

        ProductReturn CreateObject(const IdentifierType& id)
        {
            MyKey key(id);
            AbstractProduct* pProduct(getPointerToObjectInContainer(getContainerFromKey(key)));
            if (shouldCreateObject(pProduct))
            {
                pProduct = factory.CreateObject(key.id);
                onCreate(pProduct);
            }
            onFetch(pProduct);
            providedObjects[pProduct] = key;
            return NP::encapsulate(pProduct);
        }

        ProductReturn CreateObject(const IdentifierType& id, Parm1 p1)
        {
            MyKey key(id, p1);
            AbstractProduct* pProduct(getPointerToObjectInContainer(getContainerFromKey(key)));
            if (shouldCreateObject(pProduct))
            {
                pProduct = factory.CreateObject(key.id, key.p1);
                onCreate(pProduct);
            }
            onFetch(pProduct);
            providedObjects[pProduct] = key;
            return NP::encapsulate(pProduct);
        }

        ProductReturn CreateObject(const IdentifierType& id, Parm1 p1, Parm2 p2)
        {
            MyKey key(id, p1, p2);
            AbstractProduct* pProduct(getPointerToObjectInContainer(getContainerFromKey(key)));
            if (shouldCreateObject(pProduct))
            {
                pProduct = factory.CreateObject(key.id, key.p1, key.p2);
                onCreate(pProduct);
            }
            onFetch(pProduct);
            providedObjects[pProduct] = key;
            return NP::encapsulate(pProduct);
        }

        ProductReturn CreateObject(const IdentifierType& id, Parm1 p1, Parm2 p2, Parm3 p3)
        {
            MyKey key(id, p1, p2, p3);
            AbstractProduct* pProduct(getPointerToObjectInContainer(getContainerFromKey(key)));
            if (shouldCreateObject(pProduct))
            {
                pProduct = factory.CreateObject(key.id, key.p1, key.p2, key.p3);
                onCreate(pProduct);
            }
            onFetch(pProduct);
            providedObjects[pProduct] = key;
            return NP::encapsulate(pProduct);
        }

        ProductReturn CreateObject(const IdentifierType& id, Parm1 p1, Parm2 p2, Parm3 p3, Parm4 p4)
        {
            MyKey key(id, p1, p2, p3, p4);
            AbstractProduct* pProduct(getPointerToObjectInContainer(getContainerFromKey(key)));
            if (shouldCreateObject(pProduct))
            {
                pProduct = factory.CreateObject(key.id, key.p1, key.p2, key.p3, key.p4);
                onCreate(pProduct);
            }
            onFetch(pProduct);
            providedObjects[pProduct] = key;
            return NP::encapsulate(pProduct);
        }

        ProductReturn CreateObject(const IdentifierType& id, Parm1 p1, Parm2 p2, Parm3 p3, Parm4 p4, Parm5 p5)
        {
            MyKey key(id, p1, p2, p3, p4, p5);
            AbstractProduct* pProduct(getPointerToObjectInContainer(getContainerFromKey(key)));
            if (shouldCreateObject(pProduct))
            {
                pProduct = factory.CreateObject(key.id, key.p1, key.p2, key.p3, key.p4, key.p5);
                onCreate(pProduct);
            }
            onFetch(pProduct);
            providedObjects[pProduct] = key;
            return NP::encapsulate(pProduct);
        }

        ProductReturn CreateObject(const IdentifierType& id, Parm1 p1, Parm2 p2, Parm3 p3, Parm4 p4, Parm5 p5, Parm6 p6)
        {
            MyKey key(id, p1, p2, p3, p4, p5, p6);
            AbstractProduct* pProduct(getPointerToObjectInContainer(getContainerFromKey(key)));
            if (shouldCreateObject(pProduct))
            {
                pProduct = factory.CreateObject(key.id, key.p1, key.p2, key.p3, key.p4, key.p5, key.p6);
                onCreate(pProduct);
            }
            onFetch(pProduct);
            providedObjects[pProduct] = key;
            return NP::encapsulate(pProduct);
        }

        ProductReturn CreateObject(const IdentifierType& id, Parm1 p1, Parm2 p2, Parm3 p3, Parm4 p4, Parm5 p5, Parm6 p6, Parm7 p7)
        {
            MyKey key(id, p1, p2, p3, p4, p5, p6, p7);
            AbstractProduct* pProduct(getPointerToObjectInContainer(getContainerFromKey(key)));
            if (shouldCreateObject(pProduct))
            {
                pProduct = factory.CreateObject(key.id, key.p1, key.p2, key.p3, key.p4, key.p5, key.p6, key.p7);
                onCreate(pProduct);
            }
            onFetch(pProduct);
            providedObjects[pProduct] = key;
            return NP::encapsulate(pProduct);
        }

        ProductReturn CreateObject(const IdentifierType& id, Parm1 p1, Parm2 p2, Parm3 p3, Parm4 p4, Parm5 p5, Parm6 p6, Parm7 p7, Parm8 p8)
        {
            MyKey key(id, p1, p2, p3, p4, p5, p6, p7, p8);
            AbstractProduct* pProduct(getPointerToObjectInContainer(getContainerFromKey(key)));
            if (shouldCreateObject(pProduct))
            {
                pProduct = factory.CreateObject(key.id, key.p1, key.p2, key.p3, key.p4, key.p5, key.p6, key.p7, key.p8);
                onCreate(pProduct);
            }
            onFetch(pProduct);
            providedObjects[pProduct] = key;
            return NP::encapsulate(pProduct);
        }

        ProductReturn CreateObject(const IdentifierType& id, Parm1 p1, Parm2 p2, Parm3 p3, Parm4 p4, Parm5 p5, Parm6 p6, Parm7 p7, Parm8 p8, Parm9 p9)
        {
            MyKey key(id, p1, p2, p3, p4, p5, p6, p7, p8, p9);
            AbstractProduct* pProduct(getPointerToObjectInContainer(getContainerFromKey(key)));
            if (shouldCreateObject(pProduct))
            {
                pProduct = factory.CreateObject(key.id, key.p1, key.p2, key.p3, key.p4, key.p5, key.p6, key.p7, key.p8, key.p9);
                onCreate(pProduct);
            }
            onFetch(pProduct);
            providedObjects[pProduct] = key;
            return NP::encapsulate(pProduct);
        }

        ProductReturn CreateObject(const IdentifierType& id, Parm1 p1, Parm2 p2, Parm3 p3, Parm4 p4, Parm5 p5, Parm6 p6, Parm7 p7, Parm8 p8, Parm9 p9, Parm10 p10)
        {
            MyKey key(id, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10);
            AbstractProduct* pProduct(getPointerToObjectInContainer(getContainerFromKey(key)));
            if (shouldCreateObject(pProduct))
            {
                pProduct = factory.CreateObject(key.id, key.p1, key.p2, key.p3, key.p4, key.p5, key.p6, key.p7, key.p8, key.p9, key.p10);
                onCreate(pProduct);
            }
            onFetch(pProduct);
            providedObjects[pProduct] = key;
            return NP::encapsulate(pProduct);
        }

        ProductReturn CreateObject(const IdentifierType& id, Parm1 p1, Parm2 p2, Parm3 p3, Parm4 p4, Parm5 p5,
                                   Parm6 p6, Parm7 p7, Parm8 p8, Parm9 p9, Parm10 p10, Parm11 p11)
        {
            MyKey key(id, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11);
            AbstractProduct* pProduct(getPointerToObjectInContainer(getContainerFromKey(key)));
            if (shouldCreateObject(pProduct))
            {
                pProduct = factory.CreateObject(key.id, key.p1, key.p2, key.p3, key.p4, key.p5, key.p6, key.p7, key.p8, key.p9, key.p10, key.p11);
                onCreate(pProduct);
            }
            onFetch(pProduct);
            providedObjects[pProduct] = key;
            return NP::encapsulate(pProduct);
        }

        ProductReturn CreateObject(const IdentifierType& id, Parm1 p1, Parm2 p2, Parm3 p3, Parm4 p4, Parm5 p5,
                                   Parm6 p6, Parm7 p7, Parm8 p8, Parm9 p9, Parm10 p10, Parm11 p11, Parm12 p12)
        {
            MyKey key(id, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12);
            AbstractProduct* pProduct(getPointerToObjectInContainer(getContainerFromKey(key)));
            if (shouldCreateObject(pProduct))
            {
                pProduct = factory.CreateObject(key.id, key.p1, key.p2, key.p3, key.p4, key.p5, key.p6, key.p7, key.p8, key.p9, key.p10, key.p11, key.p12);
                onCreate(pProduct);
            }
            onFetch(pProduct);
            providedObjects[pProduct] = key;
            return NP::encapsulate(pProduct);
        }

        ProductReturn CreateObject(const IdentifierType& id, Parm1 p1, Parm2 p2, Parm3 p3, Parm4 p4, Parm5 p5, Parm6 p6, Parm7 p7, Parm8 p8, Parm9 p9, Parm10 p10, Parm11 p11, Parm12 p12, Parm13 p13)
        {
            MyKey key(id, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13);
            AbstractProduct* pProduct(getPointerToObjectInContainer(getContainerFromKey(key)));
            if (shouldCreateObject(pProduct))
            {
                pProduct = factory.CreateObject(key.id, key.p1, key.p2, key.p3, key.p4, key.p5, key.p6, key.p7, key.p8, key.p9, key.p10, key.p11, key.p12, key.p13);
                onCreate(pProduct);
            }
            onFetch(pProduct);
            providedObjects[pProduct] = key;
            return NP::encapsulate(pProduct);
        }

        ProductReturn CreateObject(const IdentifierType& id, Parm1 p1, Parm2 p2, Parm3 p3, Parm4 p4, Parm5 p5, Parm6 p6, Parm7 p7, Parm8 p8, Parm9 p9, Parm10 p10, Parm11 p11, Parm12 p12, Parm13 p13, Parm14 p14)
        {
            MyKey key(id, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14);
            AbstractProduct* pProduct(getPointerToObjectInContainer(getContainerFromKey(key)));
            if (shouldCreateObject(pProduct))
            {
                pProduct = factory.CreateObject(key.id, key.p1, key.p2, key.p3, key.p4, key.p5, key.p6, key.p7, key.p8, key.p9, key.p10, key.p11, key.p12, key.p13, key.p14);
                onCreate(pProduct);
            }
            onFetch(pProduct);
            providedObjects[pProduct] = key;
            return NP::encapsulate(pProduct);
        }

        ProductReturn CreateObject(const IdentifierType& id, Parm1 p1, Parm2 p2, Parm3 p3, Parm4 p4, Parm5 p5, Parm6 p6, Parm7 p7, Parm8 p8, Parm9 p9, Parm10 p10, Parm11 p11, Parm12 p12, Parm13 p13, Parm14 p14, Parm15 p15)
        {
            MyKey key(id, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15);
            AbstractProduct* pProduct(getPointerToObjectInContainer(getContainerFromKey(key)));
            if (shouldCreateObject(pProduct))
            {
                pProduct = factory.CreateObject(key.id, key.p1, key.p2, key.p3, key.p4, key.p5, key.p6, key.p7, key.p8, key.p9, key.p10, key.p11, key.p12, key.p13, key.p14, key.p15);
                onCreate(pProduct);
            }
            onFetch(pProduct);
            providedObjects[pProduct] = key;
            return NP::encapsulate(pProduct);
        }

        /// Use this function to release the object
        /// 使用此函数释放对象
        /**
		 * if execution brakes in this function then you tried
		 * to release an object that wasn't provided by this Cache
		 * ... which is bad :-)
         * 如果执行在此函数中起作用，则您尝试释放该Cache尚未提供的对象...这很糟糕:-)
		 */
        void ReleaseObject(ProductReturn& object)
        {
            AbstractProduct* pProduct(NP::release(object));
            typename FetchedObjToKeyMap::iterator itr = providedObjects.find(pProduct);
            if (itr == providedObjects.end())
                throw CacheException();
            onRelease(pProduct);
            ReleaseObjectFromContainer(getContainerFromKey((*itr).second), pProduct);
            providedObjects.erase(itr);
        }

        /// display the cache configuration
        /// 显示缓存配置
        void displayCacheType()
        {
            using namespace std;
            cout << "############################" << endl;
            cout << "## Cache configuration" << endl;
            cout << "## + Encapsulation " << NP::name() << endl;
            cout << "## + Creating      " << CP::name() << endl;
            cout << "## + Eviction      " << EP::name() << endl;
            cout << "## + Statistics    " << SP::name() << endl;
            cout << "############################" << endl;
        }
    };
}  // namespace Loki

#endif  // end file guardian
