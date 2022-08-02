/* Copyright (C) Scott Bilas, 2000. 
 * All rights reserved worldwide.
 *
 * This software is provided "as is" without express or implied
 * warranties. You may freely copy and compile this source into
 * applications you distribute provided that the copyright text
 * below is included in the resulting source code, for example:
 * "Portions Copyright (C) Scott Bilas, 2000"
 */

#include <cassert>
#include <vector>

template <typename DATA, typename HANDLE>
class HandleMgr
{
private:
    // private types 私有类型
    typedef std::vector<DATA> UserVec;
    typedef std::vector<unsigned int> MagicVec;
    typedef std::vector<unsigned int> FreeVec;

    // private data 私有数据
    UserVec m_UserData;  // data we're going to get to 我们需要获取的数据
    MagicVec m_MagicNumbers;  // corresponding magic numbers 相应的魔术数
    FreeVec m_FreeSlots;  // keeps track of free slots in the db 数据库中需要跟踪的空闲列表

public:
    // Lifetime. 生命期

    HandleMgr(void)
    {
    }

    ~HandleMgr(void)
    {
    }

    // Handle methods. 句柄方法

    // acquisition 分配
    DATA* Acquire(HANDLE& handle);
    void Release(HANDLE handle);

    // dereferencing 解引用
    DATA* Dereference(HANDLE handle);
    const DATA* Dereference(HANDLE handle) const;

    // other query 其他查询
    unsigned int GetUsedHandleCount(void) const
    {
        return (m_MagicNumbers.size() - m_FreeSlots.size());
    }

    bool HasUsedHandles(void) const
    {
        return (!!GetUsedHandleCount());
    }
};

template <typename DATA, typename HANDLE>
DATA* HandleMgr<DATA, HANDLE>::Acquire(HANDLE& handle)
{
    // if free list is empty, add a new one otherwise use first one found
    // 如果空闲列表为空，则新增一个，否则使用第一个可用表项

    unsigned int index;
    if (m_FreeSlots.empty())
    {
        index = static_cast<unsigned int>(m_MagicNumbers.size());
        handle.Init(index);
        m_UserData.push_back(DATA());
        m_MagicNumbers.push_back(handle.GetMagic());
    }
    else
    {
        index = m_FreeSlots.back();
        handle.Init(index);
        m_FreeSlots.pop_back();
        m_MagicNumbers[index] = handle.GetMagic();
    }
    return &*(m_UserData.begin() + index);
}

template <typename DATA, typename HANDLE>
void HandleMgr<DATA, HANDLE>::Release(HANDLE handle)
{
    // which one? 哪一个？
    unsigned int index = handle.GetIndex();

    // make sure it's valid 确认其有效性
    assert(index < m_UserData.size());
    assert(m_MagicNumbers[index] == handle.GetMagic());

    // ok remove it - tag as unused and add to free list
    // 可以删除了——标记其没有使用并加入空闲列表
    m_MagicNumbers[index] = 0;
    m_FreeSlots.push_back(index);
}

template <typename DATA, typename HANDLE>
inline DATA* HandleMgr<DATA, HANDLE>::Dereference(HANDLE handle)
{
    if (handle.IsNull())
        return (0);

    // check handle validity - $ this check can be removed for speed
    // if you can assume all handle references are always valid.
    // 检查句柄有效性——为提供性能可以去掉这个检查
    // 如果你假设索引句柄解引用都总是有效
    unsigned int index = handle.GetIndex();
    if ((index >= m_UserData.size()) || (m_MagicNumbers[index] != handle.GetMagic()))
    {
        // no good! invalid handle == client programming error
        // 无效句柄=客户程序错误
        assert(0);
        return (0);
    }

    return &*(m_UserData.begin() + index);
}

template <typename DATA, typename HANDLE>
inline const DATA* HandleMgr<DATA, HANDLE>::Dereference(HANDLE handle) const
{
    // this lazy cast is ok - non-const version does not modify anything
    typedef HandleMgr<DATA, HANDLE> ThisType;
    return (const_cast<ThisType*>(this)->Dereference(handle));
}
