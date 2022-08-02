#ifndef CGUN_H
#define CGUN_H
//-----------------------------------------------------------------------
//
//  Name: CGun.h
//
//  Author: Mat Buckland 2002
//
//	Desc: Class to show how to create and manipulate a simple shape using
//        matrix transformations
//
//-----------------------------------------------------------------------
#include <vector>
#include <windows.h>

#include "defines.h"
#include "utils.h"
#include "C2DMatrix.h"

using namespace std;



//------------------------------------------------------------------------
//
// 
//------------------------------------------------------------------------
class CGun
{
public:

    //its position in the world
    double         m_dPosX,
                   m_dPosY;

    //its rotation
    double         m_dRotation;

    //its scale
    double         m_dScale;

    //vertex buffer for the gun's local coordinates
    vector<SPoint> m_vecGunVB;

    //vertex buffer to hold the gun's transformed vertices
    vector<SPoint> m_vecGunVBTrans;

    CGun(double x,
           double y,
           double scale,
           double rot);

    void WorldTransform();
    void Render(HDC &surface);
    void Update();
};

#endif