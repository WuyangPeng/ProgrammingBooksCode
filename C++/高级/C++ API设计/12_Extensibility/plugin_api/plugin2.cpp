/// -*- tab-width: 4; c-basic-offset: 4; indent-tabs-mode: t -*-
///
/// \file   plugin2.h
/// \author Martin Reddy
/// \brief  An example plugin built against the plugin API.
///
/// Copyright (c) 2010, Martin Reddy. All rights reserved.
/// Distributed under the X11/MIT License. See LICENSE.txt.
/// See http://APIBook.com/ for the latest version.
///

#include "pluginapi.h"
#include <iostream>

class DirectXRenderer : public IRenderer
{
public:
    bool LoadScene([[maybe_unused]] const char* filename)
    {
        return true;
    }
    void SetViewportSize([[maybe_unused]] int w, [[maybe_unused]] int h)
    {
    }
    void SetCameraPos([[maybe_unused]] double x, [[maybe_unused]] double y, [[maybe_unused]] double z)
    {
    }
    void SetLookAt([[maybe_unused]] double x, [[maybe_unused]] double y, [[maybe_unused]] double z)
    {
    }
    void Render()
    {
        std::cout << "DirectX Render" << std::endl;
    }
};

PLUGIN_FUNC IRenderer* CreateRenderer()
{
    return new DirectXRenderer;
}

PLUGIN_FUNC void DestroyRenderer(IRenderer* r)
{
    delete r;
}

PLUGIN_DISPLAY_NAME("DirectX Renderer");

PLUGIN_INIT()
{
    // register our new renderer
    std::cout << "PLUGIN_INIT" << std::endl;
    RegisterRenderer("directx", CreateRenderer, DestroyRenderer);
    return 0;
}
