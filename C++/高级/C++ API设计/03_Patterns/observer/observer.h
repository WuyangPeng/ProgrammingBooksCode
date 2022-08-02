/// -*- tab-width: 4; c-basic-offset: 4; indent-tabs-mode: t -*-
///
/// \file   observer.h
/// \author Martin Reddy
/// \brief  Abstract base classes to implement Observer.
///
/// Copyright (c) 2010, Martin Reddy. All rights reserved.
/// Distributed under the X11/MIT License. See LICENSE.txt.
/// See http://APIBook.com/ for the latest version.
///

#ifndef OBSERVER_H
#define OBSERVER_H

#include <map>
#include <vector>

///
/// An abstract interface for an observer class.
/// �۲�����ĳ���ӿڡ�
///
class IObserver
{
public:
    virtual ~IObserver()
    {
    }
    virtual void Update(int message) = 0;
};

///
/// An interface for a subject class.
/// ������Ľӿڡ�
///
class ISubject
{
public:
    ISubject();
    virtual ~ISubject();

    /// Add a new observer to the list of observers.
    /// �ڹ۲����б������һ���µĹ۲��ߡ�
    virtual void Subscribe(int message, IObserver* observer);
    /// Remove an existing observer from the list of observers.
    /// �ӹ۲����б���ɾ�����еĹ۲��ߡ�
    virtual void Unsubscribe(int message, IObserver* observer);
    /// Call the Update() method of all subscribed observers.
    /// ���������Ѷ��Ĺ۲��ߵ�Update()������
    virtual void Notify(int message);

private:
    typedef std::vector<IObserver*> ObserverList;
    typedef std::map<int, ObserverList> ObserverMap;
    ObserverMap mObservers;
};

#endif
