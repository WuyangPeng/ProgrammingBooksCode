#include "CBullet.h"

//the vertices that make up the bullet shape
const int NumBulletVerts = 3;

const SPoint Bullet[NumBulletVerts] = {SPoint(-1,-1),
                                       SPoint(0,1),
                                       SPoint(1,-1)};

//--------------------------------- ctor ---------------------------------
//
//------------------------------------------------------------------------
CBullet::CBullet():m_vPos(SVector2D(0, 30)),
                   m_dScale(CParams::dBulletScale),
                   m_bActive(false)
{
    
  //create the vertex buffer
  for (int i=0; i<NumBulletVerts; ++i)
  {
    m_vecBulletVB.push_back(Bullet[i]);
  }

}


//------------------------------ Render ----------------------------------
//
//------------------------------------------------------------------------
void CBullet::Render(HDC &surface, HPEN &GreenPen)
{
  WorldTransform();

  HPEN OldPen = (HPEN)SelectObject(surface, GreenPen);
  
  MoveToEx(surface, m_vecBulletVBTrans[0].x, m_vecBulletVBTrans[0].y, NULL);

  for (int vtx=0; vtx<m_vecBulletVBTrans.size(); ++vtx)
  {
    LineTo(surface, m_vecBulletVBTrans[vtx].x, m_vecBulletVBTrans[vtx].y);
  }

  LineTo(surface, m_vecBulletVBTrans[0].x, m_vecBulletVBTrans[0].y);

  SelectObject(surface, OldPen);

}


//---------------------WorldTransform--------------------------------
//
//	sets up the translation matrices for the ship and applies the
//	world transform to the ships vertex buffer
//-------------------------------------------------------------------
void CBullet::WorldTransform()
{
	//copy the original vertices into the buffer about to be transformed
  m_vecBulletVBTrans = m_vecBulletVB;
  
  //create a transformation matrix
	C2DMatrix matTransform;
	
	//scale
	matTransform.Scale(m_dScale, m_dScale);

	//and translate
	matTransform.Translate(m_vPos.x, m_vPos.y);
	
  //now transform the ships vertices
  matTransform.TransformSPoints(m_vecBulletVBTrans);

}


//------------------------------SwitchOn ---------------------------------
//
//  Given the X position of the gun turret this function activates a
//  bullet.
//------------------------------------------------------------------------
void CBullet::SwitchOn(int posX)
{
  m_vPos.x  = posX;
  m_vPos.y  = 35;
  m_bActive = true;

    //setup its bounding box
  m_BulletBBox.left  = m_vPos.x - (CParams::dBulletScale);
  m_BulletBBox.right = m_vPos.x + (CParams::dBulletScale);
  m_BulletBBox.top   = m_vPos.y + (CParams::dBulletScale);
  m_BulletBBox.bottom= m_vPos.y - (CParams::dBulletScale);
}


//----------------------------- Update -----------------------------------
//
//------------------------------------------------------------------------
void CBullet::Update()
{
  if (m_bActive)
  {
    //update the bullet's position.
    m_vPos.y += CParams::dBulletSpeed;

    //check window limits
    if (m_vPos.y > CParams::WindowHeight)
    {
      m_bActive = false;
    }

  }

  //update its bounding box
  m_BulletBBox.top    += CParams::dBulletSpeed;
  m_BulletBBox.bottom += CParams::dBulletSpeed;

}
