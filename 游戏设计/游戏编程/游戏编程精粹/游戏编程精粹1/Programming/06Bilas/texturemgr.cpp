/* Copyright (C) Scott Bilas, 2000. 
 * All rights reserved worldwide.
 *
 * This software is provided "as is" without express or implied
 * warranties. You may freely copy and compile this source into
 * applications you distribute provided that the copyright text
 * below is included in the resulting source code, for example:
 * "Portions Copyright (C) Scott Bilas, 2000"
 */

#include <ddraw.h>
#include <cassert>
#include <map>
#include <string>
#include <vector>

#include "handle.h"
#include "handlemgr.h"

// ... [ platform-specific surface handle type here ]
// ... [ 平台相关的句柄类型 ]
typedef LPDIRECTDRAWSURFACE7 OsHandle;

struct tagTexture
{
};

typedef Handle<tagTexture> HTexture;

class TextureMgr
{
    // Texture object data and db.
    // 材质对象数据

    struct Texture
    {
        typedef std::vector<OsHandle> HandleVec;

        std::string m_Name;  // for reconstruction 重构造时使用
        unsigned int m_Width;  // mip 0 width 宽度
        unsigned int m_Height;  // mip 1 width 高度
        HandleVec m_Handles;  // handles to mip surfaces surfaces句柄

        OsHandle GetOsHandle(unsigned int mip) const
        {
            assert(mip < m_Handles.size());
            return (m_Handles[mip]);
        }

        bool Load(const std::string& name);
        void Unload(void);
    };

    typedef HandleMgr<Texture, HTexture> HTextureMgr;

    // Index by name into db.
    // 数据库以名字为索引

    // case-insensitive string comparison predicate
    // 大小写不敏感的字符串比较谓词
    struct istring_less
    {
        bool operator()(const std::string& l, const std::string& r) const
        {
            return (::_stricmp(l.c_str(), r.c_str()) < 0);
        }
    };

    typedef std::map<std::string, HTexture, istring_less> NameIndex;
    typedef std::pair<NameIndex::iterator, bool> NameIndexInsertRc;

    // Private data.
    // 私有数据

    HTextureMgr m_Textures;
    NameIndex m_NameIndex;

public:
    // Lifetime.
    // 生命期

    TextureMgr(void)
    { /* ... */
    }

    ~TextureMgr(void);

    // Texture management.
    // 材质管理

    HTexture GetTexture(const char* name);
    void DeleteTexture(HTexture htex);

    // Texture query.
    // 材质查询

    const std::string& GetName(HTexture htex) const
    {
        return (m_Textures.Dereference(htex)->m_Name);
    }
    int GetWidth(HTexture htex) const
    {
        return (m_Textures.Dereference(htex)->m_Width);
    }
    int GetHeight(HTexture htex) const
    {
        return (m_Textures.Dereference(htex)->m_Height);
    }
    OsHandle GetTexture(HTexture htex, unsigned int mip = 0) const
    {
        return (m_Textures.Dereference(htex)->GetOsHandle(mip));
    }
};

TextureMgr ::~TextureMgr(void)
{
    // release all our remaining textures before we go
    // 在析构前释放索引剩余材质
    NameIndex::iterator i, begin = m_NameIndex.begin(), end = m_NameIndex.end();
    for (i = begin; i != end; ++i)
    {
        m_Textures.Dereference(i->second)->Unload();
    }
}

HTexture TextureMgr ::GetTexture(const char* name)
{
    // insert/find
    // 插入和查找
    NameIndexInsertRc rc =
        m_NameIndex.insert(std::make_pair(name, HTexture()));
    if (rc.second)
    {
        // this is a new insertion
        // 这个一个新的插入操作
        Texture* tex = m_Textures.Acquire(rc.first->second);
        if (!tex->Load(rc.first->first))
        {
            DeleteTexture(rc.first->second);
            rc.first->second = HTexture();
        }
    }
    return (rc.first->second);
}

void TextureMgr ::DeleteTexture(HTexture htex)
{
    Texture* tex = m_Textures.Dereference(htex);
    if (tex != 0)
    {
        // delete from index
        // 使用索引删除
        m_NameIndex.erase(m_NameIndex.find(tex->m_Name));

        // delete from db
        // 从数据库删除
        tex->Unload();
        m_Textures.Release(htex);
    }
}

bool TextureMgr::Texture ::Load(const std::string& name)
{
    m_Name = name;
    // ... [ load texture from file system, return false on failure ]
    // ... [ 从文件系统载入材质，失败时返回false ]
    return (true /* or false on error */); // 错误时返回false
}

void TextureMgr::Texture ::Unload(void)
{
    m_Name.erase();
    // ... [ free up mip surfaces ]
    m_Handles.clear();
}
