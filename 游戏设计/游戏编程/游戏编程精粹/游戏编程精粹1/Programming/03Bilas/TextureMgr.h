#pragma once

class TextureMgr
{
    static TextureMgr* ms_Singleton;

public:
    TextureMgr(void)
    {
        ms_Singleton = this;
        /*...*/
    }

    ~TextureMgr(void)
    {
        ms_Singleton = 0;
        /*...*/
    }

    // ...

    TextureMgr& GetSingleton(void)
    {
        return { *ms_Singleton };
    }
};