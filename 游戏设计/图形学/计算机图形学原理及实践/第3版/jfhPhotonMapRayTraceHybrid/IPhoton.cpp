#include "IPhoton.h"


IPhoton::IPhoton(void)
{
}


IPhoton::~IPhoton(void)
{
}

bool IPhoton::operator==(const IPhoton& q) {
    return (m_position == q.m_position) && (m_directionToSource == q.m_directionToSource) && (m_power == q.m_power);;
}

IPhoton::IPhoton(Point3 position, Vector3 directionToSource, Power3 power){
    m_position = position;
    m_directionToSource = directionToSource;
    m_power = power;
}

const Vector3 IPhoton::directionToSource(void) const{
    return m_directionToSource;
}

const Point3 IPhoton::position(void) const{
    return m_position;
}

const Power3 IPhoton::power(void) const{
    return m_power;
}
