#include "World.h"
#include "SurfaceSampler.h"
#include "AreaLight.h"

World::World(int whichWorld) : m_mode(TRACE) {
    if (whichWorld >= m_nWorlds) {
        debugPrintf("Can't load world %d\n", whichWorld);
        exit(-1);
    }
    
    switch (whichWorld) {
        case 0:
            loadWorld0();
            break;
        case 1:
            loadWorld1();
            break;
        case 2:
            loadWorld2();
            break;
        case 3:
            loadWorld3();
            break;
        case 4:
            loadWorld4();
            break;
        case 5:
            loadWorld5();
            break;
        case 6:
            loadWorld6();
            break;
        case 7:
            loadWorld7();
            break;
        default:
            debugPrintf("Can't load world %d\n", whichWorld);
            exit(-1);
            break;
    }
}


void World::begin() {
    debugAssert(m_mode == TRACE);
    m_surfaceArray.clear();
    m_triArray.clear();
    m_mode = INSERT;
}


void World::insert(const shared_ptr<ArticulatedModel>& model, const CFrame& frame) {
    Array<shared_ptr<Surface>> posed;
    model->pose(posed, frame);
    for (int i = 0; i < posed.size(); ++i) {
        insert(posed[i]);
    }
}


void World::insert(const shared_ptr<Surface>& m) {
    debugAssert(m_mode == INSERT);
    m_surfaceArray.append(m);
}


void World::end() {
    m_triTree.setContents(m_surfaceArray);
    debugAssert(m_mode == INSERT);
    m_mode = TRACE;
}


bool World::lineOfSight(const Point3& v0, const Point3& v1) const {
    debugAssert(m_mode == TRACE);
    
    const Vector3& d = v1 - v0;
    float len = d.length();
    const Ray& ray = Ray::fromOriginAndDirection(v0, d / len);
    float distance = len;
    Tri::Intersector intersector;

    return ! m_triTree.intersectRay(ray, intersector, distance);
}


bool World::intersect(const Ray& ray, float& distance, shared_ptr<Surfel>& surfel) const {
    debugAssert(m_mode == TRACE);

    Tri::Intersector intersector;
    if (m_triTree.intersectRay(ray, intersector, distance)) {
        surfel.reset(new UniversalSurfel(intersector));
        return true;
    } else {
        return false;
    }
}


const Array<shared_ptr<Surface>>& World::surfaces() {
    return m_surfaceArray;
}

//====================================================================================================

void World::loadWorld0() {
    Array<shared_ptr<Surface>> posed;

    begin();
    {
        // Point light

        addPointLight(Vector3(0, 2.9f, -2), Color3::white() * 80); // in Watts

        float squareLightEdgeLength = 3.0f;
        Power3 squareLightPower = Power3(Color3::white() * 60);

        addSquareLight(squareLightEdgeLength, Point3(0.0f, 3.0f, -1.0f), Vector3(1,0,0), Vector3(0, -1, 0), 
            makeMaterial(Color3::black(), 1.0f, Color3::black(), 0.0f, 1.0f),  squareLightPower);

        {
            // A sphere, slightly to right, shiny and red.
            addSphere(Point3(1.00f, 1.0f, -3.0f), 1.0f, 
                makeMaterial(Color3::fromARGB(0xff0101), 0.8f, Color3::white(), 0.2f, 1.0f));

            // And a  ground plane...
            addSquare(4.0, Point3(0.0f, -0.2f, -2.0f),  Vector3(1.0f, 0.0f, 0.0f),  Vector3(0.0f, 1.0f, 0.0f),
                makeMaterial(Color3::fromARGB(0xffffff), 0.9f, Color3::white(), 0.0f, 1.0));

            // And a  back plane...
            addSquare(4.0, Point3(0.0f, 2.0f, -4.00f),  Vector3(1.0f, 0.0f, 0.0f),  Vector3(0.0f, 0.0f, 1.0f),
                makeMaterial(Color3::fromARGB(0xbbbbff), 0.9f, Color3::white(), 0.0f, 1.0));
        }
    }
    end();
}
//====================================================================================================

static shared_ptr<ArticulatedModel> loadScaledModel(const std::string& filename, float scale) {
    ArticulatedModel::Specification s;
    s.filename = System::findDataFile(filename);
    s.scale = scale;
    return ArticulatedModel::create(s);
}


void World::loadWorld1() {

    Array<shared_ptr<Surface>> posed;
    UniversalMaterial::Specification areaLightMaterial;
    UniversalMaterial::Specification rightMaterial;
    shared_ptr<ArticulatedModel> squareLight = loadScaledModel("squarex8.ifs", 10.0f);

    begin();
    {
        addPointLight(Vector3(0, 10, -3), Color3::white() * 1200); // 1200 watts

        float squareLightEdgeLength = 10.0f;
        Power3 squareLightPower = Power3(Color3::white() * 600);
        addSquareLight(squareLightEdgeLength, Point3(0.0f, 10.0f, 5.0f), Vector3(1,0,0), Vector3(0, -1, 0), 
            makeMaterial(Color3::black(), 1.0f, Color3::black(), 0.0f, 1.0f),  squareLightPower);

        {
            // A sphere, slightly to right, shiny and red.
            addSphere(Point3(1.00f, 1.0f, -3.0f), 1.0f, 
                makeMaterial(Color3::fromARGB(0xff0101), 0.8f, Color3::white(), 0.2f, 1.0f));

        }
        // LEFT sphere, glass version
        {
            // small green glass sphere on left
            addTransparentSphere(
                Point3(-0.95f, 0.7f, -3.0f), 0.7f, 
 //               1.05f, 1.00f, //original values
                1.55f, 1.00f, 
                Color3::fromARGB(0xccffcc), 1.0f,
                Color3::black(), 0.0f,
                Color3::white(), 0.0f,
                1.0f);
        }

        // And a  ground plane...
        addSquare(4.0, Point3(0.0f, -0.2f, -2.0f),  Vector3(1.0f, 0.0f, 0.0f),  Vector3(0.0f, 1.0f, 0.0f),
            makeMaterial(Color3::fromARGB(0xffffff), 0.9f, Color3::white(), 0.0f, 1.0));

        // And a  back plane...
        addSquare(4.0, Point3(0.0f, 2.0f, -4.00f),  Vector3(1.0f, 0.0f, 0.0f),  Vector3(0.0f, 0.0f, 1.0f),
            makeMaterial(Color3::fromARGB(0xbbbbff), 0.9f, Color3::white(), 0.0f, 1.0));
    }
    end();

}

//====================================================================================================

void World::loadWorld2() {
    begin();
    {    
		// A point light, so the raytracer can see the scene!
		addPointLight(Vector3(0.0f, 0.98f, -2.55f), Color3::white() * 25.0f); // Left in to make raytracing have something to show

		//Area light
        float squareLightEdgeLength = 0.35f;
        Power3 squareLightPower = Power3(Color3::white() * 25);

        addSquareLight(squareLightEdgeLength, Point3(0.0f, 0.99f, -2.5f), Vector3(1,0,0), Vector3(0, -1, 0), 
            makeMaterial(Color3::white(), 1.0f, Color3::white(), 0.0f, 1.0f),  squareLightPower);

		//floor
		addSquare(2.02f, Point3(0.0f, -1.f, -2.5f),  Vector3(1.0f, 0.0f, 0.0f),  Vector3(0.0f, 1.0f, 0.0f),
            makeMaterial(Color3(0.725f, 0.71f, 0.68f), 1.0f, Color3::white(), 0.0f, 1.0));

		//ceiling
		addSquare(2.02f, Point3(0.0f,  1.0f, -2.5f),  Vector3(1.0f, 0.0f, 0.0f),  Vector3(0.0f, -1.0f, 0.0f),
            makeMaterial(Color3(0.725f, 0.71f, 0.68f), 1.0f, Color3::white(), 0.0f, 1.0));

		//back wall
		addSquare(2.02f, Point3(0.0f,  0.0f, -3.5f),  Vector3(1.0f, 0.0f, 0.0f),  Vector3(0.0f, 0.0f, 1.0f),
            makeMaterial(Color3(0.725f, 0.71f, 0.68f), 1.0f, Color3::white(), 0.0f, 1.0));

		//left wall
		addSquare(2.02f, Point3(-1.0f,  0.0f, -2.5f),  Vector3(0.0f, 1.0f, 0.0f),  Vector3(1.0f, 0.0f, 0.0f),
            makeMaterial(Color3(0.63f, 0.065f, 0.05f), 1.0f, Color3::white(), 0.0f, 1.0));
		//right wall
		addSquare(2.02f, Point3(1.0f,  0.0f, -2.5f),  Vector3(0.0f, 1.0f, 0.0f),  Vector3(-1.0f, 0.0f, 0.0f),
            makeMaterial(Color3(0.14f, 0.45f, 0.091f), 1.0f, Color3::white(), 0.0f, 1.0));
    }
    end();
}
//====================================================================================================

void World::loadWorld3(){ //+++

    float squareLightEdgeLength = 0.25f;


    begin();
    {
		// A point light, so the raytracer can see the scene!
		addPointLight(Vector3(-0.15f, 0.65f, -0.2f), Color3::white() * 12.0f); // Left in to make raytracing have something to show

        Power3 squareLightPower = Power3(Color3::white() * 12);

        addSquareLight(squareLightEdgeLength, Point3(-0.15f, .65f, -0.2f), Vector3(1,0,0), Vector3(0, 0, -1), 
            makeMaterial(Color3::black(), 1.0f, Color3::black(), 0.0f, 1.0f),  squareLightPower);

        {
            // magenta diffuse sphere on right
            addSphere(Point3(0.25f, 0.35f, -0.41f), 0.15f, 
                makeMaterial(Color3::fromARGB(0xff01ff), 0.8f, Color3::white(), 0.0f, 1.0f));

            // small green glass sphere on left
            addTransparentSphere(
//                Point3(-0.2f, 0.35f, -0.41f), 0.15f, 
                Point3(-0.2f, 0.41f, -0.37f), 0.15f, 
//                1.04f, 1.00f, 
                1.32f, 1.00f, 
                Color3::fromARGB(0x01ff01), 1.0f,
                Color3::black(), 0.0f,
                Color3::white(), 0.2f,
                1.0f);

            // ground plane
            addSquare(1.0, Point3(-0.15f, 0.2f, -0.41f),  Vector3(2.0f, 0.0f, 0.0f),  Vector3(0.0f, 1.0f, 0.0f),
                makeMaterial(Color3::fromARGB(0xffffff), 0.75f, Color3::white(), 0.0f, 1.0));

            // And a  back plane...
            addSquare(1.0, Point3(-0.15f, 0.8f, -0.91f),  Vector3(2.0f, 0.0f, 0.0f),  Vector3(0.0f, 0.0f, 1.0f), 
                makeMaterial(Color3::fromARGB(0xbbbbff), 0.75f, Color3::white(), 0.0f, 1.0));

        }
        
    }
    end();
}

//====================================================================================================

void World::loadWorld4(){ // +++
    
    float squareLightEdgeLength = 1.41428f;


    begin();
    {
        Power3 squareLightPower = Power3(Color3::white() * 2);
        float offset = 0.2f;

        addSquareLight(squareLightEdgeLength, Point3(0.0f, 0.6f+offset, -2.1f), Vector3(1,0,0), Vector3(0, -1, 1), 
                    makeMaterial(Color3::black(), 1.0f, Color3::black(), 0.0f, 1.0f),  squareLightPower);

        // plane orthogonal to square light, and same size, very reflective
        addSquare(1.41428f, Point3(0.0f, -0.4f+offset, -2.1f),  Vector3(1.0f, 0.0f, 0.0f),  Vector3(0.0f, 1.0f, 1.0f),
            makeMaterial(Color3::fromARGB(0xffffff), 0.0f, Color3::white(), 1.0f, 1.0));
        // and a red plane behind it to provide a border...
        addSquare(1.6f, Point3(0.0f, -0.45f+offset, -2.15f),  Vector3(1.0f, 0.0f, 0.0f),  Vector3(0.0f, 1.0f, 1.0f),
            makeMaterial(Color3::fromARGB(0xffbbbb), 0.7f, Color3::white(), 0.0f, 0.0));
    }
    end();
}

//====================================================================================================

void World::loadWorld5(){ 
    
    float squareLightEdgeLength = 1.0f;


    begin();
    {
        Power3 squareLightPower = Power3(Color3::white() * 20);
        
        addSquareLight(squareLightEdgeLength, Point3(0.0f, 1.5f, -1.2f), Vector3(1,0,0), Vector3(0.0f, 0.0f, 1.0f), 
                       makeMaterial(Color3::black(), 1.0f, Color3::black(), 0.0f, 1.0f),  squareLightPower);

        addSquare(1.0f, Point3(0.0f, 0.5f, -1.0f),  Vector3(1.0f, 0.0f, 0.0f),  Vector3(0.0f, 0.0f, 1.0f),
                  makeMaterial(Color3::fromARGB(0xffffff), 1.0f, Color3::white(), 0.0f, 1.0));
        addSquare(1.0f, Point3(0.0f, 0.0f, -0.5f),  Vector3(1.0f, 0.0f, 0.0f),  Vector3(0.0f, 1.0f, 0.0f),
                  makeMaterial(Color3::fromARGB(0xff2222), 1.0f, Color3::fromARGB(0xff2222), 0.0f, 1.0));
    }
    end();
}
//====================================================================================================
void World::loadWorld6() {
    Array<shared_ptr<Surface>> posed;
    UniversalMaterial::Specification areaLightMaterial;

    begin();
    {
        addPointLight(Vector3(0, 2.9f, -1), Color3::white() * 80); 

        float squareLightEdgeLength = 3.0f;
        Power3 squareLightPower = Power3(Color3::white() * 80);

        addSquareLight(squareLightEdgeLength, Point3(0.0f, 3.0f, -1.0f), Vector3(1,0,0), Vector3(0, -1, 0.0f), 
            makeMaterial(Color3::black(), 1.0f, Color3::black(), 0.0f, 0.0f),  squareLightPower);
        {
            // A sphere, slightly to right, shiny and red.

            UniversalMaterial::Specification rightMaterial;

            // And a  ground plane...
/*
            shared_ptr<ArticulatedModel> ground =
                ArticulatedModel::create(PARSE_ANY(
                    ArticulatedModel::Specification {
                        filename = "squarex8.ifs";
                        scale = 4;
                        preprocess = {
                            setMaterial(all(), UniversalMaterial::Specification {
                                lambertian = Color3(1,1,1);
                                glossy     = Color3(0,0,0);
                            });
                        };
                })); */
			addSquare(4.0, Point3(0.0f, -0.2f, -2.0f),  Vector3(1.0f, 0.0f, 0.0f),  Vector3(0.0f, 1.0f, 0.0f),
            makeMaterial(Color3::fromARGB(0xffffff), 1.0f, Color3::black(), 0.0f, 1.0));

//            insert(ground, CFrame::fromXYZYPRDegrees(0.0f, -0.2f, -2.0f, 0.0f, 270.0f)); 
        }
    }
    end();
}

//==============================================

void World::loadWorld7() {

    Array<shared_ptr<Surface>> posed;
    UniversalMaterial::Specification areaLightMaterial;
    UniversalMaterial::Specification rightMaterial;
    shared_ptr<ArticulatedModel> squareLight = loadScaledModel("squarex8.ifs", 10.0f);

    begin();
    {
        //addPointLight(Vector3(0, 10, -3), Color3::white() * 1200); // 1200 watts

        float squareLightEdgeLength = 3.0f;
        Power3 squareLightPower = Power3(Color3::white() * 300);
        addSquareLight(squareLightEdgeLength, Point3(5.0f, 10.0f, 0.0f), Vector3(1,0,0), Vector3(0, -1, 0), 
            makeMaterial(Color3::black(), 1.0f, Color3::black(), 0.0f, 1.0f),  squareLightPower);

        {
            // A sphere, slightly to right, shiny and red.
            addSphere(Point3(1.00f, 1.0f, -3.0f), 1.0f, 
                makeMaterial(Color3::fromARGB(0xff0101), 0.8f, Color3::white(), 0.2f, 1.0f));

        }
        // LEFT sphere, glass version
        {
            // small green glass sphere on left
            addTransparentSphere(
                Point3(0.f, 5.0f, -5.0f), 0.7f, 
                1.55f, 1.00f, 
                Color3::fromARGB(0xccffcc), 1.0f,
                Color3::black(), 0.0f,
                Color3::white(), 0.0f,
                1.0f);
        }

        // And a  ground plane...
        addSquare(4.0, Point3(0.0f, -0.2f, -2.0f),  Vector3(1.0f, 0.0f, 0.0f),  Vector3(0.0f, 1.0f, 0.0f),
            makeMaterial(Color3::fromARGB(0xffffff), 0.9f, Color3::white(), 0.0f, 1.0));

        // And a  back plane...
        addSquare(4.0, Point3(0.0f, 2.0f, -4.00f),  Vector3(1.0f, 0.0f, 0.0f),  Vector3(0.0f, 0.0f, 1.0f),
            makeMaterial(Color3::fromARGB(0xbbbbff), 0.9f, Color3::white(), 0.0f, 1.0));
    }
    end();

}

//============================================================

void World::addPointLight(const Vector3& position, const Color3& powerInWatts) {
    lightArray.append(Light::point("light", position, powerInWatts));
}


void World::addSquareLight(float edgeLength, const Point3& center, const Vector3& axisTangent, const Vector3& normal, const UniversalMaterial::Specification& material, const Color3& powerInWatts){
    Radiance3 squareLightRadiance = powerInWatts/ (pif() * edgeLength*edgeLength); 

    UniversalMaterial::Specification areaLightMaterial = material;
    areaLightMaterial.setEmissive(squareLightRadiance);

    shared_ptr<ArticulatedModel> square = loadScaledModel("squarex8.ifs", edgeLength);
    square->rootArray()[0]->meshArray()[0]->material = UniversalMaterial::create(areaLightMaterial);

    // First, insert the square into the scene. 
    Vector3 uNormal = normal / normal.length();
    Vector3 firstTangent(axisTangent / axisTangent.length());
    Vector3 secondTangent(uNormal.cross(firstTangent));

    Matrix3 rotmat(
        firstTangent.x, secondTangent.x, uNormal.x, 
        firstTangent.y, secondTangent.y, uNormal.y, 
        firstTangent.z, secondTangent.z, uNormal.z);

    CoordinateFrame cFrame(rotmat, center); 
    insert(square, cFrame); 

    // And now add it to the light list as well
    Array<shared_ptr<Surface>> posed;
    square->pose(posed, cFrame); 
    for (int i = 0; i < posed.size(); ++i) {
        lightArray2.append(AreaLight::fromSampler(SurfaceSampler::fromSurface(posed[i]), powerInWatts));
    }
}

// shininess ranges from 0.0 (dull) to 1.0 (mirror)
UniversalMaterial::Specification World::makeMaterial(const Color3& lambertColor, float lambertFraction, const Color3& specularColor, float specularFraction, float shininess) {
    UniversalMaterial::Specification material;
    material.setGlossy(specularColor * specularFraction);
    material.setShininess(shininess);
    material.setLambertian(lambertColor * lambertFraction);
    return material;
}


void World::addSphere(const Point3& center, float radius, const UniversalMaterial::Specification& material){
    shared_ptr<ArticulatedModel> sphere = loadScaledModel("sphere.ifs", radius);
    sphere->rootArray()[0]->meshArray()[0]->material = UniversalMaterial::create(material);
    insert(sphere, CFrame::fromXYZYPRDegrees(center.x, center.y, center.z, 0));
}


void World::addTransparentSphere(const Point3& center, float radius, float interiorEta, float exteriorEta, 
    const Color3& transmissiveColor, float transmissiveFraction,
    const Color3& lambertianColor, float lambertianFraction, 
    const Color3& specularColor, float specularFraction, float shininess){

    shared_ptr<ArticulatedModel> sphere = loadScaledModel("sphere.ifs", radius);
    // Use the outside of the object as the interface into glass from air

    UniversalMaterial::Specification glassAir;
    glassAir.setGlossy(specularColor * specularFraction);
    glassAir.setShininess(shininess);
    glassAir.setLambertian(lambertianColor * lambertianFraction);
    glassAir.setEta(interiorEta, exteriorEta);
    glassAir.setTransmissive(transmissiveColor * transmissiveFraction);

    sphere->rootArray()[0]->meshArray()[0]->material = UniversalMaterial::create(glassAir);
    sphere->rootArray()[0]->meshArray()[0]->twoSided = true;

    insert(sphere, CFrame::fromXYZYPRDegrees(center.x, center.y, center.z, 0));
}


void World::addSquare(float edgeLength, const Point3& center, const Vector3& axisTangent, const Vector3& normal, const UniversalMaterial::Specification& material){
    shared_ptr<ArticulatedModel> square = loadScaledModel("squarex8.ifs", edgeLength);
    square->rootArray()[0]->meshArray()[0]->material = UniversalMaterial::create(material);

    Vector3 uNormal = normal / normal.length();
    Vector3 firstTangent(axisTangent / axisTangent.length());
    Vector3 secondTangent(uNormal.cross(firstTangent));

    Matrix3 rotmat(
        firstTangent.x, secondTangent.x, uNormal.x, 
        firstTangent.y, secondTangent.y, uNormal.y, 
        firstTangent.z, secondTangent.z, uNormal.z);

    CoordinateFrame cFrame(rotmat, center); 
    insert(square, cFrame); 
}
