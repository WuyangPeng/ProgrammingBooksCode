/// -*- tab-width: 4; c-basic-offset: 4; indent-tabs-mode: t -*-
///
/// \file   rendererfactory.cpp
/// \author Martin Reddy
/// \brief  A factory object to create IRenderer instances.
///
/// Copyright (c) 2010, Martin Reddy. All rights reserved.
/// Distributed under the X11/MIT License. See LICENSE.txt.
/// See http://APIBook.com/ for the latest version.
///

#include "rendererfactory.h"
#include <iostream>

// instantiate the static variable in RendererFactory
// 在RendererFactory中实例化静态变量
RendererFactory::CallbackMap RendererFactory::mRenderers;

void RendererFactory::RegisterRenderer(const std::string& type, CreateCallback cb)
{
    mRenderers[type] = cb;
}

void RendererFactory::UnregisterRenderer(const std::string& type)
{
    mRenderers.erase(type);
}

IRenderer* RendererFactory::CreateRenderer(const std::string& type)
{
    CallbackMap::iterator it = mRenderers.find(type);
    if (it != mRenderers.end())
    {
        // call the creation callback to construct this derived type
        // 调用创建回调以构造此派生类型
        return (it->second)();
    }

    return nullptr;
}
