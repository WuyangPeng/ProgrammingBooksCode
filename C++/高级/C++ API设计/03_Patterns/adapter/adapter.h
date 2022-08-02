/// -*- tab-width: 4; c-basic-offset: 4; indent-tabs-mode: t -*-
///
/// \file   adapter.h
/// \author Martin Reddy
/// \brief  An example of the Adapter design pattern.
///
/// Copyright (c) 2010, Martin Reddy. All rights reserved.
/// Distributed under the X11/MIT License. See LICENSE.txt.
/// See http://APIBook.com/ for the latest version.
///

#ifndef ADAPTER_H
#define ADAPTER_H

// forward declaration for the object wrapped by Adapter
// ��������װ�����ǰ������
class Original;

///
/// An Adapter that wraps access to an Original object.
/// ��װ��ԭʼ����ķ�����������
///
class Adapter
{
public:
    Adapter();
    ~Adapter();

    /// Call through to Original::DoSomething()
    bool DoSomething(int value);

private:
    // prevent copying of this class because we had a pointer data member
    // ��ֹ���ƴ��࣬��Ϊ������һ��ָ�����ݳ�Ա
    Adapter(const Adapter&) = delete;
    const Adapter& operator=(const Adapter&) = delete;

    Original* mOrig;
};

#endif
