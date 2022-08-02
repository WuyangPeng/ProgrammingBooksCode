/// -*- tab-width: 4; c-basic-offset: 4; indent-tabs-mode: t -*-
///
/// \file   rendererfactory.h
/// \author Martin Reddy
/// \brief  A factory object to create Renderer instances.
///
/// Copyright (c) 2010, Martin Reddy. All rights reserved.
/// Distributed under the X11/MIT License. See LICENSE.txt.
/// See http://APIBook.com/ for the latest version.
///

#ifndef RENDERERFACTORY_H
#define RENDERERFACTORY_H

#include "renderer.h"
#include <string>

///
/// A factory object that creates instances of different
/// 3D renderers.
/// 创建不同3D渲染器实例的工厂对象。
/// 
class RendererFactory
{
public:
    /// Create a new instance of a named 3D renderer.
    /// type can be one of "opengl", "directx", or "mesa"
    /// 创建一个命名3D渲染器的新实例。 类型可以是"opengl", "directx"或"mesa"之一
    IRenderer* CreateRenderer(const std::string& type);
};

#endif
