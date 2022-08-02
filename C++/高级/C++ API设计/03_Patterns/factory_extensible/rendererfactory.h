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
/// ������ͬ3D��Ⱦ��ʵ���Ĺ������� ���Զ�̬�������Ⱦ��������ӹ���������ɾ����
///
class RendererFactory
{
public:
    /// The type for the callback that creates an IRenderer instance
    /// ����IRendererʵ���Ļص�������
    typedef IRenderer* (*CreateCallback)();

    /// Add a new 3D renderer to the system
    /// ���µ�3D��Ⱦ����ӵ�ϵͳ
    static void RegisterRenderer(const std::string& type, CreateCallback cb);

    /// Remove an existing 3D renderer from the system
    /// ��ϵͳ��ɾ�����е�3D��Ⱦ��
    static void UnregisterRenderer(const std::string& type);

    /// Create an instance of a named 3D renderer
    /// ��������3D��Ⱦ����ʵ��
    static IRenderer* CreateRenderer(const std::string& type);

private:
    typedef std::map<std::string, CreateCallback> CallbackMap;
    static CallbackMap mRenderers;
};

#endif
