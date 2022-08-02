/**
  @file App.h  PATH TRACING

  This is a simple path tracing demo showing how to use the G3D ray tracing 
  primitives.  
   */
#ifndef App_h
#define App_h

#include <G3D/G3DAll.h>
#include <GLG3D/GLG3D.h>

#include "World.h"

class App : public GApp {
private:
    
    int                 m_maxBounces;
    bool                m_pointLights; // true if these are turned on
    bool                m_areaLights;
    bool                m_whichRenderer; // true if raytracer rather than pathtracer
    World*              m_world;
    int                 m_primaryRaysPerPixel;
    int                 m_whichWorld; // which of the several candidate worlds we're rendering    

    bool				m_direct;      // show direct lighting of first intersection point? 
    bool				m_direct_s;      // show SPECULAR reflections of direct lighting of first intersection point? 
	bool				m_indirect;    // show indirect lighting at first intersection point?
	bool				m_emit;        // show emitted light

    float               m_scaleFactor; // how much to scale down images by.

    Texture::Ref        m_result;     // Image produced by renderer

    /** Used to pass information from rayTraceImage() to trace() */
    Image3::Ref         m_currentImage;

    /** Position during the previous frame */
    CFrame              m_prevCFrame;

    /** Called from onInit() */
    void makeGUI();

    /** Ray-trace a single ray backwards. */
    Radiance3 rayTrace(const Ray& ray, int bounces = 1);

    /** Trace one pixel of m_currentImage */
    void trace(int x, int y);

	/** Ray-trace a whole image. */
    void rayTraceImage(float scale, int numRays);

    /** PATH Trace a single ray backwards. */
    Radiance3 pathTrace(const Ray& ray, bool isEyeRay);

    /** Estimate (exactly) the lighting from point lights */
    Radiance3 estimateDirectLightFromPointLights(const shared_ptr<Surfel>& surfel, const Ray& ray);

    /** Estimate the lighting from area lights with a single-sample per light */
    Radiance3 estimateDirectLightFromAreaLights(const shared_ptr<Surfel>& surfel, const Ray& ray);

    /** Estimate the indirect light at this point by a recursive path trace.  */
    Radiance3 estimateIndirectLight(const shared_ptr<Surfel>& surfel, const Ray& ray, bool isEyeRay);

    /** PATHTrace one pixel of m_currentImage */
    void ptrace(int x, int y);

	/** PATH-Trace a whole image. */
    void pathTraceImage(float scale, int numRays);

    /** Show a full-screen message */
    void message(const std::string& msg) const;

public:
    App(const GApp::Settings& settings = GApp::Settings());

    virtual void onInit();

    /** Callback for the render button */
    void onRender();

    virtual void onGraphics(RenderDevice* rd, Array<shared_ptr<Surface>>& posed3D, Array<Surface2D::Ref>& posed2D);
    virtual void onCleanup();
};

#endif
