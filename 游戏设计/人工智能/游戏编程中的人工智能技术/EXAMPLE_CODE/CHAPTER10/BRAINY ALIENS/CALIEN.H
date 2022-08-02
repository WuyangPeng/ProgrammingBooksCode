#ifndef CALIEN_H
#define CALIEN_H
//-----------------------------------------------------------------------
//
//  Name: CAlien.h
//
//  Author: Mat Buckland 2002
//
//	Desc: class to define a space invader type alien. The alien has a 
//        neural net for a brain which controls its movement.
//
//-----------------------------------------------------------------------

#include <vector>
#include <windows.h>

#include "defines.h"
#include "utils.h"
#include "C2DMatrix.h"
#include "CBullet.h"
#include "CNeuralNet.h"
#include "CParams.h"

#include "SVector2D.h"

using namespace std;



//------------------------------------------------------------------------
//
// class to define an alien 
//------------------------------------------------------------------------

//enumerated type to define thew actions the alien can perform each
//frame
enum action_type{thrust_left,
                 thrust_right,
                 thrust_up,
                 drift};

class CAlien
{

private:

    CNeuralNet      m_ItsBrain;

    //its position in the world
    SVector2D       m_vPos;

    SVector2D       m_vVelocity;
    
    //its scale
    double          m_dScale;

    //its mass
    double          m_dMass;   

    //its age (= its fitness)
    int             m_iAge;

    //its bounding box(for collision detection)
    RECT            m_AlienBBox;

    //vertex buffer for the alien's local coordinates
    vector<SPoint>  m_vecAlienVB;

    //vertex buffer to hold the alien's transformed vertices
    vector<SPoint>  m_vecAlienVBTrans;

    //when set to true a warning is displayed informing of
    //an input size mismatch to the neural net.
    bool            m_bWarning;


    void         WorldTransform();

    //checks for collision with any active bullets. Returns true if
    //a collision is detected
    bool         CheckForCollision(vector<CBullet> &bullets)const;

    //updates the alien's neural network and returns its next action
    action_type  GetActionFromNetwork(const vector<CBullet> &bullets,
                                      const SVector2D       &GunPos);
    

    //overload '<' used for sorting
	  friend bool operator<(const CAlien& lhs, const CAlien& rhs)
	  {
		  return (lhs.m_iAge > rhs.m_iAge);
	  }


public:
     
    CAlien();

    void Render(HDC &surface, HPEN &GreenPen, HPEN &RedPen);
    
    //queries the alien's brain and updates it position accordingly
    bool Update(vector<CBullet> &bullets, const SVector2D &GunPos);

    //resets any relevant member variables ready for a new run
    void Reset();

    //this mutates the connection weights in the alien's neural net
    void Mutate();

    //-------------------------------------accessor methods
    SVector2D Pos()const{return m_vPos;}
    double    Fitness()const{return m_iAge;}
};


#endif