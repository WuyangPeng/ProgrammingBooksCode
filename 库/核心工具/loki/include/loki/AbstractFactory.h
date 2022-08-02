////////////////////////////////////////////////////////////////////////////////
// The Loki Library
// Copyright (c) 2001 by Andrei Alexandrescu
// This code accompanies the book:
// Alexandrescu, Andrei. "Modern C++ Design: Generic Programming and Design
//     Patterns Applied". Copyright (c) 2001. Addison-Wesley.
// Permission to use, copy, modify, distribute and sell this software for any
//     purpose is hereby granted without fee, provided that the above copyright
//     notice appear in all copies and that both that copyright notice and this
//     permission notice appear in supporting documentation.
// The author or Addison-Wesley Longman make no representations about the
//     suitability of this software for any purpose. It is provided "as is"
//     without express or implied warranty.
////////////////////////////////////////////////////////////////////////////////
#ifndef LOKI_ABSTRACTFACTORY_INC_
#define LOKI_ABSTRACTFACTORY_INC_

// $Id: AbstractFactory.h 771 2006-10-27 18:05:03Z clitte_bbt $

#include "HierarchyGenerators.h"
#include "Sequence.h"
#include "TypeManip.h"
#include "Typelist.h"

#include <cassert>

/**
 * \defgroup	FactoriesGroup Factories
 * \defgroup	AbstractFactoryGroup Abstract Factory
 * \ingroup		FactoriesGroup
 * \brief		Implements an abstract object factory.
 */

/**
 * \class		AbstractFactory
 * \ingroup		AbstractFactoryGroup
 * \brief		Implements an abstract object factory.
 * 实现抽象对象工厂。
 */

namespace Loki
{
    ////////////////////////////////////////////////////////////////////////////////
    // class template AbstractFactoryUnit
    // The building block of an Abstract Factory
    // 抽象工厂的组成部分
    ////////////////////////////////////////////////////////////////////////////////

    template <class T>
    class AbstractFactoryUnit
    {
    public:
        virtual T* DoCreate(Type2Type<T>) = 0;
        virtual ~AbstractFactoryUnit()
        {
        }
    };

    ////////////////////////////////////////////////////////////////////////////////
    // class template AbstractFactory
    // Defines an Abstract Factory interface starting from a typelist
    // 从类型列表开始定义一个Abstract Factory接口
    ////////////////////////////////////////////////////////////////////////////////

    template <class TList, template <class> class Unit = AbstractFactoryUnit>
    class AbstractFactory : public GenScatterHierarchy<TList, Unit>
    {
    public:
        typedef TList ProductList;

        template <class T>
        T* Create()
        {
            Unit<T>& unit = *this;
            return unit.DoCreate(Type2Type<T>());
        }
    };

    ////////////////////////////////////////////////////////////////////////////////
    // class template OpNewFactoryUnit
    // Creates an object by invoking the new operator
    // 通过调用new运算符来创建对象
    ////////////////////////////////////////////////////////////////////////////////

    template <class ConcreteProduct, class Base>
    class OpNewFactoryUnit : public Base
    {
        typedef typename Base::ProductList BaseProductList;

    protected:
        typedef typename BaseProductList::Tail ProductList;

    public:
        typedef typename BaseProductList::Head AbstractProduct;
        ConcreteProduct* DoCreate(Type2Type<AbstractProduct>)
        {
            return new ConcreteProduct;
        }
    };

    ////////////////////////////////////////////////////////////////////////////////
    // class template PrototypeFactoryUnit
    // Creates an object by cloning a prototype
    // 通过克隆原型创建对象
    // There is a difference between the implementation herein and the one described
    //     in the book: GetPrototype and SetPrototype use the helper friend
    //     functions DoGetPrototype and DoSetPrototype. The friend functions avoid
    //     name hiding issues. Plus, GetPrototype takes a reference to pointer
    //     instead of returning the pointer by value.
    // 代码中的实现与书中描述的实现之间有区别：
    // GetPrototype和SetPrototype使用帮助者友元函数DoGetPrototype和DoSetPrototype。
    // 友元函数避免了名称隐藏问题。 另外，GetPrototype采用对指针的引用，而不是按值返回指针。
    ////////////////////////////////////////////////////////////////////////////////

    template <class ConcreteProduct, class Base>
    class PrototypeFactoryUnit : public Base
    {
        typedef typename Base::ProductList BaseProductList;

    protected:
        typedef typename BaseProductList::Tail ProductList;

    public:
        typedef typename BaseProductList::Head AbstractProduct;

        PrototypeFactoryUnit(AbstractProduct* p = 0)
            : pPrototype_(p)
        {
        }

        template <class CP, class Base1>
        friend void DoGetPrototype(const PrototypeFactoryUnit<CP, Base1>& me, typename Base1::ProductList::Head*& pPrototype);

        template <class CP, class Base1>
        friend void DoSetPrototype(PrototypeFactoryUnit<CP, Base1>& me, typename Base1::ProductList::Head* pObj);

        template <class U>
        void GetPrototype(U*& p)
        {
            return DoGetPrototype(*this, p);
        }

        template <class U>
        void SetPrototype(U* pObj)
        {
            DoSetPrototype(*this, pObj);
        }

        AbstractProduct* DoCreate(Type2Type<AbstractProduct>)
        {
            assert(pPrototype_);
            return pPrototype_->Clone();
        }

    private:
        AbstractProduct* pPrototype_;
    };

    template <class CP, class Base>
    inline void DoGetPrototype(const PrototypeFactoryUnit<CP, Base>& me, typename Base::ProductList::Head*& pPrototype)
    {
        pPrototype = me.pPrototype_;
    }

    template <class CP, class Base>
    inline void DoSetPrototype(PrototypeFactoryUnit<CP, Base>& me, typename Base::ProductList::Head* pObj)
    {
        me.pPrototype_ = pObj;
    }

    ////////////////////////////////////////////////////////////////////////////////
    // class template ConcreteFactory
    // Implements an AbstractFactory interface
    // 实现一个AbstractFactory接口
    ////////////////////////////////////////////////////////////////////////////////

    template <class AbstractFact,
              template <class, class> class Creator = OpNewFactoryUnit,
              class TList = typename AbstractFact::ProductList>
    class ConcreteFactory : public GenLinearHierarchy<typename TL::Reverse<TList>::Result, Creator, AbstractFact>
    {
    public:
        typedef typename AbstractFact::ProductList ProductList;
        typedef TList ConcreteProductList;
    };

}  // namespace Loki

#endif  // end file guardian
