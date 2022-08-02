/* Copyright (C) James Boer, 2000. 
 * All rights reserved worldwide.
 *
 * This software is provided "as is" without express or implied
 * warranties. You may freely copy and compile this source into
 * applications you distribute provided that the copyright text
 * below is included in the resulting source code, for example:
 * "Portions Copyright (C) James Boer, 2000"
 */
//=============================================================================
//
// 	ResourceManager.h - memory management resource manager
//
// 	Author:	 James Boer
//
//=============================================================================

#ifndef __RESOURCEMANAGER_H
#define __RESOURCEMANAGER_H

// disable warnings about extra chars in debug builds for templates
#pragma warning(disable : 4786)
// Disable warning messages about needs to have dll-interface to be used by clients
#pragma warning(disable : 4251)

#include <ctime>
#include <map>
#include <stack>

#ifndef UINT
    #define UINT unsigned int
#endif

// A resource handle is define as an unsigned integer
#define RHANDLE UINT

// All bits filled defines an invalid resource handle
#define INVALID_RHANDLE 0xFFFFFFFF

#define IS_INVALID_RHANDLE(_rh) ((_rh == INVALID_RHANDLE) ? true : false)

#define IS_VALID_RHANDLE(_rh) ((_rh == INVALID_RHANDLE) ? false : true)

class BaseResource
{
public:
    enum PriorityType
    {
        RES_LOW_PRIORITY = 0,
        RES_MED_PRIORITY,
        RES_HIGH_PRIORITY
    };

    BaseResource()
    {
        Clear();
    }

    virtual ~BaseResource()
    {
        Destroy();
    }

    // Clears the class data
    // 清除类数据
    virtual void Clear();

    // Create and destroy functions.  Note that the Create() function of the
    // derived class does not have to exactly match the base class.  No assumptions
    // are made regarding parameters.
    // 完成构造和析构功能的函数
    // 注意继承类的Create()函数不必完全匹配基类
    // 不应该作这样的关于参数的假设
    virtual bool Create()
    {
        return false;
    }

    virtual void Destroy()
    {
    }

    // Dispose and recreate must be able to discard and then completely recreate
    // the data contained in the class with no additional parameters
    // 释放并重建必须可放弃，并且支持不使用附加参数来重建类包含的数据
    virtual bool Recreate() = 0;
    virtual void Dispose() = 0;

    // GetSize() must return the size of the data inside the class, and IsDisposed()
    // let's the manager know if the data exists.
    // GetSize()必须返回类中的数据大小，IsDisposed()使管理者能知道数据是否存在
    virtual size_t GetSize() = 0;
    virtual bool IsDisposed() = 0;

    // These functions set the parameters by which the sorting operator determines
    // in what order resources are discarded
    // 这些函数设置参数决定哪些类型的资源将被丢弃
    inline void SetPriority(PriorityType priority)
    {
        m_Priority = priority;
    }
    inline PriorityType GetPriority()
    {
        return m_Priority;
    }

    inline void SetReferenceCount(UINT nCount)
    {
        m_nRefCount = nCount;
    }
    inline UINT GetReferenceCount()
    {
        return m_nRefCount;
    }
    inline bool IsLocked()
    {
        return (m_nRefCount > 0) ? true : false;
    }

    inline void SetLastAccess(time_t LastAccess)
    {
        m_LastAccess = LastAccess;
    }
    inline time_t GetLastAccess()
    {
        return m_LastAccess;
    }

    // The less-than operator defines how resources get sorted for discarding.
    // 小于操作符定义资源如何在丢弃时排序
    virtual bool operator<(BaseResource& container);

protected:
    PriorityType m_Priority;
    UINT m_nRefCount;
    time_t m_LastAccess;
};

// This class allows an STL object to compare the objects instead of
// comparing the value of the objects' pointers.
template <class T>
class ptr_less
{
public:
    inline bool operator()(T left, T right)
    {
        return ((*left) < (*right));
    }
};

// This class allows an STL object to compare the objects instead of
// comparing the value of the objects' pointers.
template <class T>
class ptr_greater
{
public:
    inline bool operator()(T left, T right)
    {
        return !((*left) < (*right));
    }
};

typedef std::map<RHANDLE, BaseResource*> ResMap;
typedef ResMap::iterator ResMapItor;
typedef ResMap::value_type ResMapPair;

class ResManager
{
public:
    ResManager()
    {
        Clear();
    }

    virtual ~ResManager()
    {
        Destroy();
    }

    void Clear();

    bool Create(UINT nMaxSize);
    void Destroy();

    // --------------------------------------------------------------------------
    // Memory management routines

    bool SetMaximumMemory(size_t nMem);
    size_t GetMaximumMemory()
    {
        return m_nMaximumMemory;
    }

    // --------------------------------------------------------------------------
    // Resource map iteration
    // 资源映射表迭代

    // Access functions for cycling through each item.  Giving direct
    // access to the map or iterator causes a stack pointer fault if you access
    // the map across a dll boundary, but it's safe through the wrappers.
    // 循环访问每个子项的函数
    // 跨越DLL边界直接访问映射表或迭代子将导致一个栈指针错误
    // 但通过这个包装来访问将是安全的
    inline void GotoBegin()
    {
        m_CurrentResource = m_ResourceMap.begin();
    }

    inline BaseResource* GetCurrentResource()
    {
        return (*m_CurrentResource).second;
    }

    inline bool GotoNext()
    {
        m_CurrentResource++;
        return IsValid();
    }

    inline bool IsValid()
    {
        return (m_CurrentResource != m_ResourceMap.end()) ? true : false;
    }

    // -----------------------------------------------------------------------
    // General resource access
    // 一般资源访问

    // Allows the resource manager to pre-reserve an amount of memory so
    // an inserted resource does not exceed the maximum allowed memory
    // 允许资源管理器在不超过最大允许内存的情况下预先保留一些内存
    // 以便在以后插入资源时可以直接使用
    bool ReserveMemory(size_t nMem);

    // If you pass in the address of a resource handle, the Resource Manager
    // will provide a unique handle for you.
    // 如果你提供资源句柄变量的地址，资源管理器将提供给你惟一句柄
    bool InsertResource(RHANDLE* rhUniqueID, BaseResource* pResource);
    bool InsertResource(RHANDLE rhUniqueID, BaseResource* pResource);

    // Removes an object completely from the manager.
    // 从管理器中完全删除一个对象
    bool RemoveResource(BaseResource* pResource);
    bool RemoveResource(RHANDLE rhUniqueID);

    // Destroys an object and deallocates it's memory
    // 析构一个对象并释放其内存
    bool DestroyResource(BaseResource* pResource);
    bool DestroyResource(RHANDLE rhUniqueID);

    // Using GetResource tells the manager that you are about to access the
    // object.  If the resource has been disposed, it will be recreated
    // before it has been returned.
    // 使用GetResource函数告诉管理器你希望访问对象
    // 如果资源已经被释放，它将在被返回之前重建
    BaseResource* GetResource(RHANDLE rhUniqueID);

    // Locking the resource ensures that the resource does not get managed by
    // the Resource Manager.  You can use this to ensure that a surface does not
    // get swapped out, for instance.  The resource contains a reference count
    // to ensure that numerous locks can be safely made.
    // 锁定资源以确保资源不会被资源管理器管理
    // 你可以使用这个函数来确保一个资源的实例不被交换出内存
    // 资源包括一个引用计数器来确保能安全的保存锁的数量
    BaseResource* Lock(RHANDLE rhUniqueID);

    // Unlocking the object let's the resource manager know that you no longer
    // need exclusive access.  When all locks have been released (the reference
    // count is 0), the object is considered safe for management again and can
    // be swapped out at the manager's discretion.  The object can be referenced
    // either by handle or by the object's pointer.
    // 解锁一个对象使资源管理器知道你不再需要一个排他性访问
    // 当所有的锁都被释放（引用计数为0），
    // 对象将被认为可以被安全管理并可以被交互出内存
    // 对象可以通过句柄或对象指针被引用 
    int Unlock(RHANDLE rhUniqueID);
    int Unlock(BaseResource* pResource);

    // Retrieve the stored handle based on a pointer to the resource.  Note that
    // it's assumed that there are no duplicate pointers, as it will return the
    // first match found.
    // 基于资源指针获取存储句柄
    // 注意这里假设没有重复指针，并将返回第一个匹配资源
    RHANDLE FindResourceHandle(BaseResource* pResource);

protected:
    // Internal functions
    // 内部函数
    inline void AddMemory(size_t nMem)
    {
        m_nCurrentUsedMemory += nMem;
    }

    inline void RemoveMemory(size_t nMem)
    {
        m_nCurrentUsedMemory -= nMem;
    }

    UINT GetNextResHandle()
    {
        return --m_rhNextResHandle;
    }

    // This must be called when you wish the manager to check for discardable
    // resources.  Resources will only be swapped out if the maximum allowable
    // limit has been reached, and it will discard them from lowest to highest
    // priority, determined by the resource class's < operator.  Function will
    // fail if requested memory cannot be freed.
    // 当你希望管理器检查已释放资源时需要调用此函数
    // 资源只有在达到最大可分配限制后才会被交互出去。
    // 并且将按照优先级从低到高丢弃资源，
    // 优先级由类的<运算符决定，
    // 如果请求内存不能被释放则函数将失败
    bool CheckForOverallocation();

protected:
    RHANDLE m_rhNextResHandle;
    size_t m_nCurrentUsedMemory;
    size_t m_nMaximumMemory;
    bool m_bResourceReserved;
    ResMapItor m_CurrentResource;
    ResMap m_ResourceMap;
};

#endif  // __RESOURCEMANAGER_H