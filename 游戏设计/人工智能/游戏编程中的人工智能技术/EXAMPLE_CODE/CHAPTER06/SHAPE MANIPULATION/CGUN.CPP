#include "CGun.h"


const int NumGunVerts = 8;
const SPoint gun[NumGunVerts] = {SPoint(2,1),
                                 SPoint(2,-1),
                                 SPoint(-2,-1),
                                 SPoint(-2,1),
                                 SPoint(-1,1),
                                 SPoint(-1,2),
                                 SPoint(1,2),
                                 SPoint(1,1)};

//--------------------------------- ctor ---------------------------------
//
//------------------------------------------------------------------------
CGun::CGun(double x,
           double y,
           double scale,
           double rot): m_dPosX(x),
                        m_dPosY(y),
                        m_dRotation(rot),
                        m_dScale(scale)
{
  //create the vertex buffer
  for (int i=0; i<NumGunVerts; ++i)
  {
    m_vecGunVB.push_back(gun[i]);
  }
}

//------------------------------ Render ----------------------------------
void CGun::Render(HDC &surface)
{
  WorldTransform();
  
  MoveToEx(surface, m_vecGunVBTrans[0].x, m_vecGunVBTrans[0].y, NULL);

  for (int vtx=0; vtx<m_vecGunVBTrans.size(); ++vtx)
  {
    LineTo(surface, m_vecGunVBTrans[vtx].x, m_vecGunVBTrans[vtx].y);
  }

  LineTo(surface, m_vecGunVBTrans[0].x, m_vecGunVBTrans[0].y);


  //now render object info
  string s = "Position(" + ftos(m_dPosX) + ", " + ftos(m_dPosY) + ")";
  TextOut(surface, 5, 0, s.c_str(), s.size());

  s = "Rotation: " + ftos(m_dRotation);
  TextOut(surface, 5, 20, s.c_str(), s.size());

  s = "Scale: " + ftos(m_dScale);
  TextOut(surface, 5, 40, s.c_str(), s.size());
}

//---------------------WorldTransform--------------------------------
//
// this function transforms a vector of vertices into world
// coordinates
//-------------------------------------------------------------------
void CGun::WorldTransform()
{
	//copy the original vertices into the buffer about to be transformed
  m_vecGunVBTrans = m_vecGunVB;
  
  //first we rotate the vertices
  for (int vtx=0; vtx<m_vecGunVBTrans.size(); ++vtx)
  {
    m_vecGunVBTrans[vtx].x = m_vecGunVB[vtx].x * cos(m_dRotation) -
                             m_vecGunVB[vtx].y * sin(m_dRotation);

     m_vecGunVBTrans[vtx].y = m_vecGunVB[vtx].x * sin(m_dRotation) +
                              m_vecGunVB[vtx].y * cos(m_dRotation);
  }

  //now scale the vertices
  for (vtx=0; vtx<m_vecGunVBTrans.size(); ++vtx)
  {
    m_vecGunVBTrans[vtx].x *= m_dScale;
    m_vecGunVBTrans[vtx].y *= m_dScale;
  }

  //and finally translate the vertices
  for (vtx=0; vtx<m_vecGunVBTrans.size(); ++vtx)
  {
    m_vecGunVBTrans[vtx].x += m_dPosX;
    m_vecGunVBTrans[vtx].y += m_dPosY;
  }
}


//----------------------------- Update -----------------------------------
//
//  Checks for user keypresses and updates the guns parameters accordingly
//------------------------------------------------------------------------
void CGun::Update()
{

	if (KEYDOWN(VK_LEFT))
	{
		m_dRotation -= MAX_ROTATION_PER_TICK;

		if (m_dRotation < -PI)
		{
			m_dRotation += 2*PI;
		}
		
	}

	if (KEYDOWN(VK_RIGHT))
	{
    m_dRotation += MAX_ROTATION_PER_TICK;

		if (m_dRotation > 2*PI)
		{
			m_dRotation -= 2*PI;
		}
  }

  if (KEYDOWN(VK_UP))
  {
    m_dScale += MAX_SCALE_PER_TICK;
  }

  if (KEYDOWN(VK_DOWN))
  {
    m_dScale -= MAX_SCALE_PER_TICK;
  }

    if (KEYDOWN('A'))
  {
    m_dPosX -= MAX_TRANSLATION_PER_TICK;

    if (m_dPosX < m_dScale)
    {
      m_dPosX = m_dScale;
    }
  }

  if (KEYDOWN('S'))
  {
    m_dPosX += MAX_TRANSLATION_PER_TICK;
    
    if (m_dPosX > WINDOW_WIDTH-m_dScale)
    {
      m_dPosX = WINDOW_WIDTH-m_dScale;
    }
  }

  if (KEYDOWN('P'))
  {
    m_dPosY -= MAX_TRANSLATION_PER_TICK;

    if (m_dPosY < m_dScale)
    {
      m_dPosY = m_dScale;
    }
  }

  if (KEYDOWN('L'))
  {
    m_dPosY += MAX_TRANSLATION_PER_TICK;

    if (m_dPosY > WINDOW_HEIGHT-m_dScale)
    {
      m_dPosY = WINDOW_HEIGHT-m_dScale;
    }
  }
}
