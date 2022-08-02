#pragma once
/**
  @file IPhoton.h

 A class to represent a photon that has arrived at a surface. The photon has a "power",
 a "position" on the surface, and a direction back towards the source.
 */
#ifndef IPhoton_h
#define IPhoton_h

#include <G3D/G3DAll.h>
#include <GLG3D/GLG3D.h>

class IPhoton
{
public:
    class EqualsFunc : EqualsTrait<IPhoton> {
    public:
        static bool equals(const IPhoton& p, const IPhoton& q) {
            return (p.m_position == q.m_position) && (p.m_directionToSource == q.m_directionToSource) && (p.m_power == q.m_power);;
        }
    };

    class PosFunc : PositionTrait<IPhoton> {
    public:
        static void getPosition(const IPhoton d, Vector3& pos) {
            pos = d.m_position;
        }
    };

private:
    Point3        m_position;
    Vector3       m_directionToSource;
    Power3        m_power;

public:
    IPhoton(void);
    IPhoton(Point3 position, Vector3 directionToSource, Power3 power);

    ~IPhoton(void);
    const Point3 position(void) const;
    const Vector3 directionToSource(void) const;
    const Power3 power(void) const;
    bool operator==(const IPhoton& other);

};

#endif