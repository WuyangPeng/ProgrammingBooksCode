/* Copyright (C) James Boer, 2000. 
 * All rights reserved worldwide.
 *
 * This software is provided "as is" without express or implied
 * warranties. You may freely copy and compile this source into
 * applications you distribute provided that the copyright text
 * below is included in the resulting source code, for example:
 * "Portions Copyright (C) James Boer, 2000"
 */

#include <cassert>
#include <iostream>

using std::cout;
using std::endl;

class SingletonBase
{
public:
    SingletonBase()
    {
        cout << "SingletonBase created!" << endl;
    }

    virtual ~SingletonBase()
    {
        cout << "SingletonBase destroyed!" << endl;
    }

    virtual void Access()
    {
        cout << "SingletonBase accessed!" << endl;
    }

    static SingletonBase* GetObj()
    {
        return m_pObj;
    }

    static void SetObj(SingletonBase* pObj)
    {
        m_pObj = pObj;
    }

protected:
    static SingletonBase* m_pObj;
};

SingletonBase* SingletonBase::m_pObj;

inline SingletonBase* Base()
{
    assert(SingletonBase::GetObj());
    return SingletonBase::GetObj();
}

// Create a derived singleton-type class
// 创建一个派生的singleton类型类
class SingletonDerived : public SingletonBase
{
public:
    SingletonDerived()
    {
        cout << "SingletonDerived created!" << endl;
    }

    virtual ~SingletonDerived()
    {
        cout << "SingletonDerived destroyed" << endl;
    }

    virtual void Access()
    {
        cout << "SingletonDerived accessed!" << endl;
    }

protected:
};

inline SingletonDerived* Derived()
{
    assert(SingletonDerived::GetObj());
    return (SingletonDerived*)SingletonDerived::GetObj();
}

void Test()
{
    // Using the code...
    // The complex singleton requires more work to use, but is
    // more flexible.  It also allows more control over object
    // creation, which is sometimes desirable.
    // 使用代码……
    // 复杂的singleton的使用需要做更多工作，而这个更加灵活
    // 它还允许对对象创建进行更多的控制，这有时候非常有用
    SingletonDerived::SetObj(new SingletonDerived);

    // Notice that the functionality has been overridden by the new
    // class, even though accessing it through the original method.
    // 注意这个方法的功能被新类重载了
    // 即使通过原有方法访问也是如此
    Base()->Access();
    Derived()->Access();

    // This variation on a singleton unfortunately requires both
    // explicit creation and deletion.
    // 很不幸，singleton上的这个变量要求显示地创建和销毁
    delete SingletonDerived::GetObj();
}
