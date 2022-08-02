/// -*- tab-width: 4; c-basic-offset: 4; indent-tabs-mode: t -*-
///
/// \file   fireworks.h
/// \author Martin Reddy
/// \brief  An illustration of using private classes.
///
/// Copyright (c) 2010, Martin Reddy. All rights reserved.
/// Distributed under the X11/MIT License. See LICENSE.txt.
/// See http://APIBook.com/ for the latest version.
///

#ifndef FIREWORKS_H
#define FIREWORKS_H

#include <vector>

namespace apibook
{
    ///
    /// A simple fireworks particle system, used to demonstrate
    /// the use of private classes to hide implementation state.
    ///
    /// 一个简单的烟花粒子系统，用于演示使用私有类来隐藏实现状态。
    class Fireworks
    {
    public:
        Fireworks();

        /// Set the (x, y) origin of the fireworks effect
        /// 设置烟火效果的（x，y）原点
        void SetOrigin(double x, double y);
        /// Set the RGB color (0..1) for each particle
        /// 为每个粒子设置RGB颜色（0..1）
        void SetColor(float r, float g, float b);
        /// Set the gravity acting on each particle (meters/sec)
        /// 设置作用在每个粒子上的重力（米/秒）
        void SetGravity(float g);
        /// Set the speed of the particle simulation
        /// 设置粒子模拟的速度
        void SetSpeed(float s);
        /// Set the number of particles in the simulation
        /// 设置模拟中的粒子数
        void SetNumberOfParticles(int num);

        /// Start (or continue) the simulation
        /// 开始（或继续）模拟
        void Start();
        /// Stop the simulation
        /// 停止模拟
        void Stop();
        /// Advance the simulation by dt seconds
        /// 通过dt秒推进模拟
        void NextFrame(float dt);

    private:
        // FireParticle represents internal hidden state
        // (You could also forward declare this class and
        // only provide the definition in the .cpp file.)
        // FireParticle表示内部隐藏状态（您也可以前向声明此类，并且仅在.cpp文件中提供定义。）
        class FireParticle
        {
        public:
            double mX, mY;
            double mVelocityX, mVelocityY;
            double mAccelerationX, mAccelerationY;
            double mLifeTime;
        };

        double mOriginX, mOriginY;
        float mRed, mGreen, mBlue;
        float mGravity;
        float mSpeed;
        bool mIsActive;
        std::vector<FireParticle*> mParticles;
    };

}

#endif
