#ifndef CBULLET_H
#define CBULLET_H

//-----------------------------------------------------------------------
//
//  Name: CBullet.h
//
//  Author: Mat Buckland 2002
//
//	Desc: Bullet class
//
//-----------------------------------------------------------------------

#include <windows.h>
#include <vector>

#include "defines.h"
#include "utils.h"
#include "C2DMatrix.h"
#include "CParams.h"
#include "SVector2D.h"

using namespace std;



class CBullet
{
private:

    //its position in the world
    SVector2D      m_vPos;
    
    //its scale
    double         m_dScale;

    //is it active
    bool           m_bActive;

    //vertex buffer for the bullets's local coordinates
    vector<SPoint> m_vecBulletVB;

    //vertex buffer to hold the bullets's transformed vertices
    vector<SPoint> m_vecBulletVBTrans;

    //its bounding box
    RECT           m_BulletBBox;


    void WorldTransform();

public:

    CBullet();

    void Render(HDC &surface, HPEN &GreenPen);

    void Update();

    //given the X position of the gun turret this function
    //activates the bullet.
    void SwitchOn(int posX);

    //---------------------accesssor functions
    bool      Active()const{return m_bActive;}
    void      SwitchOff(){m_bActive = false;}
    SVector2D Pos()const{return m_vPos;}
    RECT      BBox()const{return m_BulletBBox;}

};


#endif
