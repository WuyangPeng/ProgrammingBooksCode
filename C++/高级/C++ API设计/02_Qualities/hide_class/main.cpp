/// -*- tab-width: 4; c-basic-offset: 4; indent-tabs-mode: t -*-
///
/// \file   main.cpp
/// \author Martin Reddy
/// \brief  Example of a private nested class.
///
/// Copyright (c) 2010, Martin Reddy. All rights reserved.
/// Distributed under the X11/MIT License. See LICENSE.txt.
/// See http://APIBook.com/ for the latest version.
///

#include "fireworks.h"

int main(int, char**)
{
    // create a new Fireworks object
    // 创建一个新的Fireworks对象
    apibook::Fireworks fireworks;

    // set the properties of the Fireworks particle system
    // 设置Fireworks粒子系统的属性
    fireworks.SetOrigin(50, 20);
    fireworks.SetColor(1.0, 0.0, 0.0);
    fireworks.SetSpeed(10.0);
    fireworks.SetNumberOfParticles(1000);

    // start the particle system
    // 启动粒子系统
    fireworks.Start();

    return 0;
}
