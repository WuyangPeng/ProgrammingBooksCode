#include "LightList.h"


LightList::LightList(Array<shared_ptr<Light>>* pointLightArray, Array<shared_ptr<AreaLight>>*  areaLightArray, G3D::Random& rnd) :
m_rnd(rnd)
{
    m_pointLightArray = pointLightArray;
    m_areaLightArray = areaLightArray;
    //m_rnd = rnd; //G3D::Random(0xF018A4D3, false);
    count0 = 0;

    initialize();
}

void LightList::initialize(void)
{
    // Compute total power in all spectral bands.
    m_nPointLights = m_pointLightArray->size();
    m_nAreaLights = m_areaLightArray->size();

    for (int L = 0; L < m_nPointLights; ++L) {
        const shared_ptr<Light>& light = (*m_pointLightArray)[L];
        m_totalPower += light->emittedPower();
    }

    for (int L = 0; L < m_nAreaLights; ++L) {
        const shared_ptr<AreaLight> light = (*m_areaLightArray)[L];
        m_totalPower += light->power();
    }
    // Compute probability of emission from each light
    for (int L = 0; L < m_nPointLights; ++L) {
        const shared_ptr<Light>& light = (*m_pointLightArray)[L];
        m_probability.append(light->emittedPower().average() / m_totalPower.average());
    }

    for (int L = 0; L < m_nAreaLights; ++L) {
        const shared_ptr<AreaLight> light = (*m_areaLightArray)[L];
        m_probability.append(light->power().average() / m_totalPower.average());
    }
}

// emit a EPhoton; argument is total number of photons to be emitted
EPhoton LightList::emitPhoton(int nEmitted)
{


    int selected = 0; // default light; handles the (very rare) case where u = 1.0f
    float u = m_rnd.uniform();

    for (int L = 0; L < m_probability.size(); L++) {
        u = u - m_probability[L];
        if (u < 0.0) {
            selected = L;
            break;
        }
    }
    if (selected == 0) count0++;

    if (selected < m_nPointLights) {
        return pointLightEmit((*m_pointLightArray)[selected], nEmitted, m_probability[selected]);
    }
    else {
        return areaLightEmit((*m_areaLightArray)[selected -  m_nPointLights], nEmitted, m_probability[selected]);
    }
}

EPhoton LightList::pointLightEmit(shared_ptr<Light> light, int nEmitted, float prob){
    float x, y, z;
    m_rnd.sphere(x, y, z);
    Vector3 direction(x, y, z);
    Power3 power = light->emittedPower() / (nEmitted * prob);
    Point3 origin(0.0f,0.0f,0.0f);
    const Point3& location = origin + light->frame().translation;

    return EPhoton(location, direction, power);
}


EPhoton LightList::areaLightEmit(shared_ptr<AreaLight> light, int nEmitted, float prob){
    shared_ptr<Surfel> surfel = light->samplePoint(m_rnd);
    Power3 power = light->power() / (nEmitted * prob);
    const Vector3& direction = Vector3::cosHemiRandom(surfel->geometricNormal, m_rnd);
            
    return EPhoton(surfel->position, direction, power);
}

Vector3 LightList::perpVec(Vector3 v){
    float x = abs(v[0]); float y = abs(v[1]); float z = abs(v[2]);

    int bestIndex = 0;
    float bestVal = max(x, max(y, z)) + 1.0;

    if (abs(x) < abs(y)){
        bestIndex = 0;
        bestVal = abs(x);
    }
    else {
        bestIndex = 1;
        bestVal = abs(y);
    }
    if (z < bestVal) {
        bestIndex = 2;
    }
    float entries[3];
    entries[bestIndex] = 1.0f;

    Vector3 u(entries);
    u = (u - v.dot(u) * v).direction();
    return u;
}

LightList::~LightList(void)
{
}

