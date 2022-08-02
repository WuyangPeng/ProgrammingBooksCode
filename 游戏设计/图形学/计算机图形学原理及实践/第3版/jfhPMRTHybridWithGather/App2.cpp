/**
  @file App2.cpp PHOTON MAP/RAY TRACE HYBRID with GATHER
 */
#include "App.h"

static G3D::Random rnd(0xF018A4D2, false);
static const float RAY_BUMP_EPSILON = 0.5 * units::millimeters();

void App::photonRender(int x, int y) {
    Radiance3 L(0.0f);
    for (int i = 0; i < m_primaryRaysPerPixel; i++) {
        const Ray r = debugCamera()->worldRay(x + rnd.uniform(), y + rnd.uniform(), m_currentImage->rect2DBounds());
        L += estimateTotalRadiance(r, 0, m_useGather); 
    }
    m_currentImage->set(x, y, L / m_primaryRaysPerPixel);
}


Radiance3 App::estimateTotalRadiance(const Ray& r, int depth, bool useGather) {
    Radiance3 L(0.0f);

    if (m_emit) L += estimateEmittedLight(r);

    L += estimateTotalScatteredRadiance(r, depth, useGather);
    return L;
}


Radiance3 App::estimateEmittedLight(Ray r){
    Radiance3 L(0.0f);
    shared_ptr<Surfel> surfel;
    float dist = inf();

    if (m_world->intersect(r, dist, surfel)) {
        L += surfel->emittedRadiance(-r.direction());
    }

    return L;
}


Radiance3 App::estimateTotalScatteredRadiance(const Ray& r, int depth, bool useGather) {
    Radiance3 L(0.0f);
    shared_ptr<Surfel> surfel;
    float dist = inf();
    if (m_world->intersect(r, dist, surfel)) {
        L += estimateReflectedDirectLight(r, surfel, depth);
        if (m_IImp || depth > 0) L += estimateImpulseScatteredIndirectLight(r, surfel, depth + 1, useGather);
        if (m_IDiff || depth > 0) L += estimateDiffuselyReflectedIndirectLight(r, surfel, depth + 1, useGather);
    }

    return L;
}


Radiance3 App::estimateReflectedDirectLight(const Ray& r,  const shared_ptr<Surfel>& surfel, int depth){
    Radiance3 L(0.0f);
    if (m_DDiff || depth > 0) L += estimateDiffuselyReflectedDirectLight(r, surfel);
    if (m_DImp || depth > 0) L += estimateImpulseScatteredDirectLight(r, surfel);
    return L;
}


Radiance3 App::estimateImpulseScatteredDirectLight(const Ray& ray, const shared_ptr<Surfel>& surfel){
    Radiance3 L(0.0f);
    Surfel::ImpulseArray impulseArray;
    
    surfel->getImpulses(PathDirection::EYE_TO_SOURCE, -ray.direction(), impulseArray);
    for (int i = 0; i < impulseArray.size(); ++i) {
        float dist = inf();
        shared_ptr<Surfel> surfel2; 
        const Surfel::Impulse& impulse = impulseArray[i];
        
        Ray r(surfel->position, impulse.direction);
        r = r.bumpedRay(RAY_BUMP_EPSILON * sign(surfel->geometricNormal.dot(r.direction())), surfel->geometricNormal);
        
        if (m_world->intersect(r, dist, surfel2)) {
            L += impulse.magnitude * surfel2->emittedRadiance(- ray.direction());
        }
    }

    return L;
}


Radiance3 App::estimateImpulseScatteredIndirectLight(const Ray& ray, const shared_ptr<Surfel>& surfel, int depth, bool useGather){
    Radiance3 L(0.0f);

    if (depth > m_maxBounces) {
        // We've hit the ray tracer's maximum ray depth
        return L;
    }

    Surfel::ImpulseArray impulseArray;
    
    surfel->getImpulses(PathDirection::EYE_TO_SOURCE, -ray.direction(), impulseArray);
    for (int i = 0; i < impulseArray.size(); ++i) {
        const Surfel::Impulse& impulse = impulseArray[i];
        
        Ray r(surfel->position, impulse.direction);
        r = r.bumpedRay(RAY_BUMP_EPSILON * sign(surfel->geometricNormal.dot(r.direction())), surfel->geometricNormal);
        L += impulse.magnitude * estimateTotalScatteredRadiance(r, depth + 1, useGather);
    }

    return L;
}


Radiance3 App::estimateDiffuselyReflectedDirectLight(const Ray& ray, const shared_ptr<Surfel>& surfel){
    Radiance3 radiance(0.0f);
    if (m_pointLights) {
        for (int L = 0; L < m_world->lightArray.size(); ++L) {
            const shared_ptr<Light>& light = m_world->lightArray[L];

                // Shadow rays
            if (m_world->lineOfSight(surfel->position + surfel->geometricNormal * 0.0001f, light->frame().translation)) {
                Vector3 w_i = light->frame().translation - surfel->position;
                const float distance2 = w_i.squaredLength();
                w_i /= sqrt(distance2);

                // Attenuated radiance
                const Irradiance3& E_i = light->bulbPower() / (4.0f * pif() * distance2);

                radiance += 
                    (surfel->finiteScatteringDensity(PathDirection::EYE_TO_SOURCE, w_i, -ray.direction()) * 
                    E_i *
                    max(0.0f, w_i.dot(surfel->shadingNormal)));
                debugAssert(radiance.isFinite());
            }
        }
    }       

    // Shade this point (direct illumination from AreaLights)
    if (m_areaLights) {
        for (int L = 0; L < m_world->lightArray2.size(); ++L) {
            shared_ptr<AreaLight> light = m_world->lightArray2[L];
            for (int i = 0; i < m_diffuseDirectSamples; i++) {
                shared_ptr<Surfel> lightsurfel = light->samplePoint(rnd);
                Point3 Q = lightsurfel->position;

                if (m_world->lineOfSight(surfel->position + surfel->geometricNormal * 0.0001f, Q + 0.0001f * lightsurfel->geometricNormal)) {
                    Vector3 w_i = Q - surfel->position;
                    const float distance2 = w_i.squaredLength();
                    w_i /= sqrt(distance2);

                    radiance += 
                        (surfel->finiteScatteringDensity(PathDirection::EYE_TO_SOURCE, w_i, -ray.direction()) * 
                        (light->power()/pif()) *
                        max(0.0f, w_i.dot(surfel->shadingNormal))
                        * max(0.0f, -w_i.dot(lightsurfel->geometricNormal) / distance2)) / m_diffuseDirectSamples;
                    debugAssert(radiance.isFinite());                
                }    
            }
        }
    }
        
    return radiance;
}


Radiance3 App::estimateDiffuselyReflectedIndirectLight(const Ray& r, const shared_ptr<Surfel>& surfel, int depth, bool useGather){
    Radiance3 L(0.0f);

    if (!useGather){
        Array<IPhoton> photonArray;
        m_photonMap.getIntersectingMembers(Sphere(surfel->position, m_photonMap.gatherRadius()), photonArray);

        for (int i = 0; i < photonArray.size(); i++){
            const IPhoton& p = photonArray[i];
            //const float cos_theta_i = max(0.0f, surfel.shading.normal.dot(p.directionToSource()));

            L += p.power() * // cos_theta_i * 
                m_photonMap.kernel(p.position(), surfel->position) *
                surfel->finiteScatteringDensity(PathDirection::EYE_TO_SOURCE, p.directionToSource(), -r.direction());
        }
        return L;
    } else { //gathering
        for (int i = 0; i < m_gatherRaysPerSample; i++) {
            // draw a sample, ray, from the BRDF TOWARDS a light source
            Vector3 w_i = -r.direction();
            Vector3 w_o = Vector3::cosHemiRandom(surfel->geometricNormal, rnd);
            Ray gatherRay = Ray(surfel->position, w_o).bumpedRay(RAY_BUMP_EPSILON * sign(surfel->geometricNormal.dot( w_o)));

            Color3 coeff;
            L += pif() * surfel->finiteScatteringDensity(PathDirection::EYE_TO_SOURCE, w_i, w_o) * estimateTotalScatteredRadiance(gatherRay, depth + 1, false);            
        }
        return L/ m_gatherRaysPerSample;
    }
}


void App::buildPhotonMap(){
    message("Building Photon Map");
    m_photonMap.clear();
    LightList lightList(&(m_world->lightArray), &(m_world->lightArray2), rnd);

    //emit 10000 photons at a time
    for (int i = m_nPhotons; i > 0; i -= 10000) {
        G3D::Array<EPhoton> ephotons;
        int count = min(i, 10000);
        for (int j = count; j > 0; j--) {
            ephotons.append(lightList.emitPhoton(m_nPhotons));
        }
        // now we have an array of emitted photons; need to trace each one and insert
        // the results into the photon map. 

        Array<IPhoton> ips;
        for (int i = 0; i < ephotons.size(); i++) {
            EPhoton ep = ephotons[i];
            photonTrace(ep, ips);
            m_photonMap.insert(ips);
        }    
    }
    char strmessage[100];
    sprintf(strmessage, "Done building photon map; %d photons in map", m_photonMap.size());
    message(strmessage);
}


void App::photonTrace(const EPhoton& ep, Array<IPhoton>& ips) {
    ips.fastClear();
    photonTraceHelper(ep, ips, 0);
}


/**
   Recursively trace an EPhoton through the scene, accumulating IPhotons
   at each diffuse bounce
*/
void App::photonTraceHelper(const EPhoton& ep, Array<IPhoton>& ips, int bounces) {
    // Trace an EPhoton  (assumed to be "bumped" from the surface if necessary)
    // through the scene. At each interserction, 
    // * store an IPhoton in "ips"
    // * scatter or die.
    // * if scatter, "bump" the outgoing ray to get an EPhoton to use in recursive trace.

    if (bounces > m_maxBounces) {
        return;
    }

    shared_ptr<Surfel> surfel;
    float dist = inf();
    Ray ray(ep.position(), ep.direction());

    // STILL NEED TO ADDRESS TRANSPORT OF FLUX AT XMISSIVE SURFACES!
    if (m_world->intersect(ray, dist, surfel)) {
        if (bounces > 0) {
            ips.append(IPhoton(surfel->position, -ray.direction(), ep.power()));
        }
        // Recursive rays
        Vector3 w_i = -ray.direction();
        Vector3 w_o;
        Color3 coeff;
        float  eta_o(0.0f);
        Color3 extinction_o(0.0f);
        float  ignore(0.0f);
        Color3 foo = Color3(0.0f);

        surfel->scatter(PathDirection::SOURCE_TO_EYE, w_i, false, rnd, coeff, w_o);

        if (! w_o.isNaN()) { 
            // managed to bounce, so push it onwards
            Ray r(surfel->position, w_o);
            r = r.bumpedRay(RAY_BUMP_EPSILON * sign(surfel->geometricNormal.dot( w_o)), surfel->geometricNormal);
            EPhoton ep2(r, ep.power() * coeff);
            photonTraceHelper(ep2, ips, bounces+1);
        }
    }

}
