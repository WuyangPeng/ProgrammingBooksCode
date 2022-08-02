/**
  @file World.h
  @author John Hughes
  A class to generate one of eight sample worlds for testing rendering.
 */
#ifndef World_h
#define World_h

#include <G3D/G3DAll.h>
#include "SurfaceSampler.h"
#include "AreaLight.h"

/** \brief The scene.*/
class World {
private:

    Array<Tri>                      m_triArray;
    Array<shared_ptr<Surface> >     m_surfaceArray;
    TriTree                         m_triTree;

    enum Mode {TRACE, INSERT}       m_mode;

private:

    void loadWorld0();
    void loadWorld1();
    void loadWorld2();
    void loadWorld3(); 
    void loadWorld4(); 
    void loadWorld5(); 
    void loadWorld6(); 
    void loadWorld7(); 

public:

    Array<shared_ptr<Light> >        lightArray;
    Array<shared_ptr<AreaLight> >    lightArray2;
    Color3                  ambient;
    static const int        m_nWorlds = 8;

    World(int whichWorld);

    /** Returns true if there is an unoccluded line of sight from v0
        to v1.  This is sometimes called the visibilty function in the
        literature.*/
    bool lineOfSight(const Point3& v0, const Point3& v1) const;

    void begin();
    void end();
    
    void insert(const shared_ptr<ArticulatedModel>& model, const CFrame& frame = CFrame());
    void insert(const shared_ptr<Surface>& m);

    void addPointLight(const Point3& position, const Color3& powerInWatts);
    void addSquareLight(float edgeLength, const Point3& center, const Vector3& axisTangent, const Vector3& normal, const UniversalMaterial::Specification& material, const Color3& powerInWatts);
    UniversalMaterial::Specification makeMaterial(const Color3& lambertColor, float lambertFraction, const Color3& specularColor, float specularFraction, float shininess);
    void addSphere(const Point3& center, float radius, const UniversalMaterial::Specification& material);
    void addSquare(float edgeLength, const Point3& center, const Vector3& horizontalTangent, const Vector3& normal, const UniversalMaterial::Specification& material);
    void addTransparentSphere(const Point3& center, float radius, float interiorEta, float exteriorEta, 
                              const Color3& transmissiveColor, float transmissiveFraction,
                              const Color3& lambertianColor, float lambertianFraction, 
                              const Color3& specularColor, float specularFraction, float shininess);

    /**\brief Trace the ray into the scene and return the first
       surface hit.

       \param ray In world space 

       \param distance On input, the maximum distance to trace to.  On
       output, the distance to the closest surface.

       \param surfel Will be initialized by the routine.

       \return True if anything was hit
     */
    bool intersect(const Ray& ray, float& distance, class shared_ptr<Surfel>& surfel) const;

    const Array<shared_ptr<Surface> >& surfaces();
};
#endif
