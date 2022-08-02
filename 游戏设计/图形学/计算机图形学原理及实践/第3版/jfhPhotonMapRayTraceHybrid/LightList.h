#pragma once
/**
  @file LightList.h

A class for representing a list of lights with different powers,
and providing a method for emitting a photon from a random light
L with probability = power of L / total power of all lights. 

Maintains two lists: one for point lights, one for area lights. 
*/
#ifndef LightList_h
#define LightList_h

#include <G3D/G3DAll.h>
#include <GLG3D/GLG3D.h>
#include "../jfhPathTrace/AreaLight.h"
//#include "AreaLight.h"
#include "EPhoton.h"

class LightList {
private:
    int count0; // for debugging only

    Array<shared_ptr<Light>>*       m_pointLightArray;
    Array<shared_ptr<AreaLight>>*   m_areaLightArray;
    Array<float>                    m_probability;
    Power3                          m_totalPower;
    int                             m_nPointLights;
    int                             m_nAreaLights;
    Random&                         m_rnd;


    void initialize(void);

public:
    LightList(Array<shared_ptr<Light>>* pointLightArray, Array<shared_ptr<AreaLight>>*  areaLightArray, G3D::Random & rnd);
    ~LightList(void);

public:
    EPhoton emitPhoton(int);

protected:
    EPhoton pointLightEmit(shared_ptr<Light> light, int nEmitted, float prob);
    EPhoton areaLightEmit(shared_ptr<AreaLight> light, int nEmitted, float prob);

private:
    Vector3 perpVec(Vector3 v);

};

#endif

