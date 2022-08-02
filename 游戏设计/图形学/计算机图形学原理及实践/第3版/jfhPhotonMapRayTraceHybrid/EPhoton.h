#pragma once
/**
  @file EPhoton.h

 A class to represent a photon emitted from a light source. The photon has a "power"
 and a propagation ray. 
 */
#ifndef EPhoton_h
#define EPhoton_h

#include <G3D/G3DAll.h>
#include <GLG3D/GLG3D.h>

class EPhoton
{
public:
    class EqualsFunc : EqualsTrait<EPhoton> {
    public:
        static bool equals(const EPhoton& p, const EPhoton& q) {
//            return (p.m_location == q.m_location) && (p.m_propagationDirection == q.m_propagationDirection) && (p.m_power == q.m_power);;
            return (p.m_propagationRay.origin() == q.m_propagationRay.origin()) && (p.m_propagationRay.direction() == q.m_propagationRay.direction())&& (p.m_power == q.m_power);;
        }
    };

    class PosFunc : PositionTrait<EPhoton> {
    public:
        static void getPosition(const EPhoton d, Vector3& pos) {
            pos = d.m_propagationRay.direction(); //m_location;
        }
    };

private:
    Ray           m_propagationRay;
    Power3        m_power;

public:
    EPhoton(void);
    EPhoton(Point3 location, Vector3 propagationDirection, Power3 power);
    EPhoton(Ray propagationRay, Power3 power);

    ~EPhoton(void);
    const Point3 position(void) const;
    const Vector3 direction(void) const;
    const Ray propagationRay(void) const;
    const Power3 power(void) const;
    bool operator==(const EPhoton& other) const;

};

#endif