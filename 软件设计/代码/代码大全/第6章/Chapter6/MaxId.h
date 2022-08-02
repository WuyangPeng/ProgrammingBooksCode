#pragma once
class MaxId
{
private:
    // 这里就是私有构造函数
    MaxId()
    {
    }

public:
    // 这里是提供对实例进行访问的公有方法。
    static MaxId* GetInstance()
    {
        return m_Instance;
    }

private:
    // 这里是唯一实例。
    static MaxId* m_Instance;  
};
