/**
  @file App.h PHOTON MAP/RAY TRACE HYBRID

  This is a simple photon-mapping-with-ray-tracing demo.
 */
#ifndef App_h
#define App_h

#include <G3D/G3DAll.h>
#include <GLG3D/GLG3D.h>
#include "../jfhPathTrace/World.h"

#include "EPhoton.h"
#include "IPhoton.h"
#include "PhotonMap.h"
#include "LightList.h"

class World;

class App : public GApp {
private:
    
    int                 m_maxBounces;
    int                 m_nPhotons;
	bool				m_pointLights; // true if these are turned on
	bool				m_areaLights;
	bool				m_whichRenderer; // true if raytracer rather than pathtracer
    World*              m_world;
	bool				m_showWireframe; // true if we should show the wireframe model.
	bool				m_showPhotonArrows; // true if we want photons visualized as arrows. 
	bool				m_showPhotonDots; // true if we want photons visualized as dots. 
    int                 m_primaryRaysPerPixel;
    int                 m_gatherRaysPerSample;
	Lighting::Ref		m_lighting;
	int					m_whichWorld; // which of the several candidate worlds we're rendering
	int					m_diffuseDirectSamples; // number of samples to take in computing diffusely refl area lights
	bool				m_DDiff;      // show direct light diffusely reflected? 
	bool				m_DImp;       // show direct light impulse-reflected?
	bool				m_IDiff;      // show indirect light diffusely reflected?
	bool				m_IImp;       // show indirect light impulse-reflected? 
	bool				m_emit;       // show emitted light

	float				m_scaleFactor; // how much to scale down images by.
	PhotonMap			m_photonMap;  // photon map to be filled in by renderer. 

    Texture::Ref        m_result;     // Image produced by renderer

    /** Used to pass information from rayTraceImage() to trace() */
    Image3::Ref         m_currentImage;
    
    /** Position during the previous frame */
    CFrame              m_prevCFrame;

    /** Called from onInit() */
    void makeGUI();

    /** Trace a single ray backwards. */
    Radiance3 rayTrace(const Ray& ray, World* world, const Color3& extinction_i = Color3::zero(), int bounces = 1);

    /** PATH Trace a single ray backwards. */
    Radiance3 pathTrace(const Ray& ray, World* world, bool includeEmissive);

    /** Trace a whole image. */
    void rayTraceImage(float scale, int numRays);

    /** Photon-map a whole image. */
    void photonRenderImage(float scale);

	/** Show a full-screen message */
    void message(const std::string& msg) const;

    /** Trace one pixel of m_currentImage */
    void trace(int x, int y);

    /** Determine image value at (x,y) by lookup in the Photon Map */
    void photonRender(int x, int y);

    /** Build a photon map for the scene */
    void buildPhotonMap();
    void photonTrace(const EPhoton& ep, Array<IPhoton>& ips);
    void photonTraceHelper(const EPhoton& ep, Array<IPhoton>& ips, int bounceCount);

    /*====================*/
    Radiance3 estimateTotalRadiance(const Ray& r, int depth);
    Radiance3 estimateEmittedLight(Ray r);
	Radiance3 estimateTotalScatteredRadiance(const Ray& r, int depth);

    Radiance3 estimateReflectedDirectLight(const Ray& r, const SurfaceElement& surfel, int depth);
    Radiance3 estimateDiffuselyReflectedDirectLight(const Ray& r, const SurfaceElement& surfel);
    Radiance3 estimateImpulseScatteredDirectLight(const Ray& r, const SurfaceElement& surfel);

    Radiance3 estimateDiffuselyReflectedIndirectLight(const Ray& r, const SurfaceElement& surfel);
    Radiance3 estimateImpulseScatteredIndirectLight(const Ray& r, const SurfaceElement& surfel, int depth);

public:

    App(const GApp::Settings& settings = GApp::Settings());

    virtual void onInit();

    /** Callback for the render button */
    void onRender();

    virtual void onGraphics(RenderDevice* rd, Array<shared_ptr<Surface>>& posed3D, Array<Surface2D::Ref>& posed2D);
    virtual void onCleanup();
};

#endif
