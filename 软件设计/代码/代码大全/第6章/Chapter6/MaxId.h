#pragma once
class MaxId
{
private:
    // �������˽�й��캯��
    MaxId()
    {
    }

public:
    // �������ṩ��ʵ�����з��ʵĹ��з�����
    static MaxId* GetInstance()
    {
        return m_Instance;
    }

private:
    // ������Ψһʵ����
    static MaxId* m_Instance;  
};
