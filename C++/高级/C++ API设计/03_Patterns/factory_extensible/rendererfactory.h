/// -*- tab-width: 4; c-basic-offset: 4; indent-tabs-mode: t -*-
///
/// \file   rendererfactory.h
/// \author Martin Reddy
/// \brief  A factory object to create IRenderer instances.
///
/// Copyright (c) 2010, Martin Reddy. All rights reserved.
/// Distributed under the X11/MIT License. See LICENSE.txt.
/// See http://APIBook.com/ for the latest version.
///

#ifndef RENDERERFACTORY_H
#define RENDERERFACTORY_H

#include "renderer.h"
#include <map>
#include <string>

///
/// A factory object that creates instances of different
/// 3D renderers. New renderers can be dynamically added
/// and removed from the factory object.
/// 创建不同3D渲染器实例的工厂对象。 可以动态添加新渲染器并将其从工厂对象中删除。
///
class RendererFactory
{
public:
    /// The type for the callback that creates an IRenderer instance
    /// 创建IRenderer实例的回调的类型
    typedef IRenderer* (*CreateCallback)();

    /// Add a new 3D renderer to the system
    /// 将新的3D渲染器添加到系统
    static void RegisterRenderer(const std::string& type, CreateCallback cb);

    /// Remove an existing 3D renderer from the system
    /// 从系统中删除现有的3D渲染器
    static void UnregisterRenderer(const std::string& type);

    /// Create an instance of a named 3D renderer
    /// 创建命名3D渲染器的实例
    static IRenderer* CreateRenderer(const std::string& type);

private:
    typedef std::map<std::string, CreateCallback> CallbackMap;
    static CallbackMap mRenderers;
};

#endif
