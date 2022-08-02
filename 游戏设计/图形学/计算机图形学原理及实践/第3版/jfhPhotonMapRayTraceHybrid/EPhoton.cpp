#include "EPhoton.h"

EPhoton::EPhoton(void)
{
}

EPhoton::~EPhoton(void)
{
}

bool EPhoton::operator==(const EPhoton& q) const {
    Ray z;
    return (m_propagationRay.origin() == q.m_propagationRay.origin()) && (m_propagationRay.direction() == q.m_propagationRay.direction())&& (m_power == q.m_power);;
}

EPhoton::EPhoton(Point3 location, Vector3 propagationDirection, Power3 power){

    m_propagationRay.set(location, propagationDirection);
    m_power = power;
}

EPhoton::EPhoton(Ray propagationRay, Power3 power){
    m_propagationRay = propagationRay;
    m_power = power;
}

const G3D::Vector3 EPhoton::direction(void) const  {
    return m_propagationRay.direction();
}

const Ray EPhoton::propagationRay(void) const  {
    return m_propagationRay;
}

const G3D::Point3 EPhoton::position(void) const  {
    return m_propagationRay.origin();
}

const G3D::Power3 EPhoton::power(void) const  {
    return m_power;
}