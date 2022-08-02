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
    /// һ���򵥵��̻�����ϵͳ��������ʾʹ��˽����������ʵ��״̬��
    class Fireworks
    {
    public:
        Fireworks();

        /// Set the (x, y) origin of the fireworks effect
        /// �����̻�Ч���ģ�x��y��ԭ��
        void SetOrigin(double x, double y);
        /// Set the RGB color (0..1) for each particle
        /// Ϊÿ����������RGB��ɫ��0..1��
        void SetColor(float r, float g, float b);
        /// Set the gravity acting on each particle (meters/sec)
        /// ����������ÿ�������ϵ���������/�룩
        void SetGravity(float g);
        /// Set the speed of the particle simulation
        /// ��������ģ����ٶ�
        void SetSpeed(float s);
        /// Set the number of particles in the simulation
        /// ����ģ���е�������
        void SetNumberOfParticles(int num);

        /// Start (or continue) the simulation
        /// ��ʼ���������ģ��
        void Start();
        /// Stop the simulation
        /// ֹͣģ��
        void Stop();
        /// Advance the simulation by dt seconds
        /// ͨ��dt���ƽ�ģ��
        void NextFrame(float dt);

    private:
        // FireParticle represents internal hidden state
        // (You could also forward declare this class and
        // only provide the definition in the .cpp file.)
        // FireParticle��ʾ�ڲ�����״̬����Ҳ����ǰ���������࣬���ҽ���.cpp�ļ����ṩ���塣��
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
