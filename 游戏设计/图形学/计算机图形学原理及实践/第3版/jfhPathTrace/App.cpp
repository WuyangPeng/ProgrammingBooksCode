
/**
  @file App.cpp PATH TRACING
 */
// Exercise: this program assumes that all light sources are in empty space (i.e., there's never a lamp inside a glass sphere). 
// WHERE is that assumption encoded? 
#include "App.h"

#include "World.h"

G3D_START_AT_MAIN();

int main(int argc, char** argv) {
    GApp::Settings settings;
    settings.window.caption     = "JFH Path Trace";
    settings.window.width       = 900;  
    settings.window.height      = 900; 
    return App(settings).run();
}

App::App(const GApp::Settings& settings) : 
GApp(settings),
    m_maxBounces(3),        // Max recursive depth used in preview raytracer
    m_pointLights(false),   // Include point lights in computations? 
    m_areaLights(true),     // Include area lights in computations? 
    m_whichRenderer(false), // Raytrace instead of pathtracing when true    
    m_whichWorld(2),        // Start by loading/rendering world number 2   
    m_primaryRaysPerPixel(1),                                              
    m_world(NULL),          // Reference to currently loaded world
    m_direct(true),         // Include direct light in computations?
    m_direct_s(true),       // Include specularly-reflected direct light? 
    m_indirect(true),       // Include indirect light in computations?
    m_emit(true),           // Include emitted light in computations?
    m_scaleFactor(0.2f) // Image is displayed in a large window, but may be rendered 
                      // smaller, for speed, and then scaled up. This says to
                      // initially render at 1/5 resolution in each axis, speeding
                      // results up by a factor of about 25, but losing a lot of 
                      // detail.
{}


void App::onInit() {
    message("Loading...");
    m_world = new World(m_whichWorld);

    showRenderingStats = false;

    createDeveloperHUD();
    developerWindow->setVisible(false);
    developerWindow->cameraControlWindow->setVisible(false);
    
    // Starting position
    debugCamera()->setFrame(CFrame::fromXYZYPRDegrees(0.0f, 0.3f, 0.0f, 0.0f, 0.0f, 0.0f));
    debugCamera()->filmSettings().setBloomStrength(0.0f);
    m_prevCFrame = debugCamera()->frame();
    
    makeGUI();
    onRender();
}

void App::makeGUI() {
    message("Building GUI");
    shared_ptr<GuiWindow> window = GuiWindow::create("Controls", debugWindow->theme(), Rect2D::xywh(0,0,0,0), GuiTheme::TOOL_WINDOW_STYLE);
    GuiPane* pane = window->pane();
    pane->addLabel("Use WASD keys + right mouse to move");
    pane->addButton("Render High Res.", this, &App::onRender);
    
    pane->addNumberBox("Max bounces", &m_maxBounces, "", GuiTheme::LINEAR_SLIDER, 1, 16, 1);
    pane->addNumberBox("Prim. Rays/Pix", &m_primaryRaysPerPixel, "", GuiTheme::LOG_SLIDER, 1, 4096, 1);
    pane->addCheckBox("Use point lights?", &m_pointLights);
    pane->addCheckBox("Use area lights?", &m_areaLights);
    pane->addCheckBox("Direct light", &m_direct);
    pane->addCheckBox("Specular Direct light", &m_direct_s);
    pane->addCheckBox("Indirect light", &m_indirect);
    pane->addCheckBox("Emitted light", &m_emit);
    pane->addCheckBox("Raytrace instead of pathtrace", &m_whichRenderer); 
    pane->addNumberBox("Which world?", &m_whichWorld, "", GuiTheme::LINEAR_SLIDER, 0, World::m_nWorlds-1, 1);
    pane->addNumberBox("Scale", &m_scaleFactor, "", GuiTheme::LINEAR_SLIDER, -0.0f, 1.001f, 0.1f);
    window->pack();
    window->setVisible(true);
    addWidget(window);
    message("Done with GUI");
}


// Called whenever the window needs to be updated
void App::onGraphics(RenderDevice* rd, Array<shared_ptr<Surface>>& surface3D, Array<Surface2D::Ref>& surface2D) {
// If the previous and current camera positions differ, do a quick raytrace to 
// show the new view
    if (! m_prevCFrame.fuzzyEq(debugCamera()->frame())) {
        rayTraceImage(0.2f, 1);
        m_prevCFrame = debugCamera()->frame();
    }
// rd is the “render device”; the following lines update
// the image shown on that device, by using the image we’ve produced (m_result)
// as a texture for the background. 

    rd->clear();
    
	if (notNull(m_result)) {
        rd->push2D();
        rd->setTexture(0, m_result);
        Draw::rect2D(rd->viewport(), rd);
        rd->pop2D();
    }
	
    Surface2D::sortAndRender(rd, surface2D);
}


void App::onCleanup() {
}

static const float RAY_BUMP_EPSILON = 0.5 * units::millimeters();//0.0001f;

// A single random number generator used in all places that need it. 
static Random rnd(0xF018A4D2, false);


void App::message(const std::string& msg) const {
    renderDevice->clear();
    renderDevice->push2D();
        debugFont->draw2D(renderDevice, msg, renderDevice->viewport().center(), 12, 
            Color3::white(), Color4::clear(), GFont::XALIGN_CENTER, GFont::YALIGN_CENTER);
    renderDevice->pop2D();

    // Force update so that we can see the message
    renderDevice->swapBuffers();
}

void App::onRender() {
    message("Rendering...");

    Stopwatch timer;
    if (m_world) delete m_world;

    m_world = new World(m_whichWorld);
    if (m_whichRenderer) {
        rayTraceImage(m_scaleFactor, m_primaryRaysPerPixel);
        timer.after("Ray Trace");
       }
    else {
        pathTraceImage(m_scaleFactor, m_primaryRaysPerPixel);
        timer.after("Path Trace");
    }
    debugPrintf("%f s\n", timer.elapsedTime());
	m_currentImage->save("result.png");
}

void App::rayTraceImage(float scale, int numRays) {
    int width  = int(window()->width()  * scale);
    int height = int(window()->height() * scale);
    
    if (isNull(m_currentImage) || (m_currentImage->width() != width) || (m_currentImage->height() != height)) {
        m_currentImage = Image3::createEmpty(width, height);
    }
    m_primaryRaysPerPixel = numRays;
    GThread::runConcurrently2D(Point2int32(0, 0), Point2int32(width, height), this, &App::trace);

    // Post-process
    shared_ptr<Texture> src = Texture::fromImage("Source", m_currentImage);
    if (m_result) {
        m_result->resize(width, height);
    }
    m_film->exposeAndRender(renderDevice, m_debugCamera->filmSettings(), src, m_result);
}

void App::trace(int x, int y) {
    Color3 sum = Color3::black();
    
    if (m_primaryRaysPerPixel == 1) {
        sum = rayTrace(debugCamera()->worldRay(x + 0.5f, y + 0.5f, m_currentImage->rect2DBounds()));
    } else {
        for (int i = 0; i < m_primaryRaysPerPixel; ++i) {
            sum += rayTrace(debugCamera()->worldRay(x + rnd.uniform(), y + rnd.uniform(), m_currentImage->rect2DBounds()));
        }
    }
    m_currentImage->set(x, y, sum / m_primaryRaysPerPixel);
}

Radiance3 App::rayTrace(const Ray& ray, int bounce) {
    Radiance3 radiance = Radiance3::zero();

    shared_ptr<Surfel> surfel;
    float dist = inf();
    if (m_world->intersect(ray, dist, surfel)) {
        // Shade this point (direct illumination)
        for (int L = 0; L < m_world->lightArray.size(); ++L) {
            const shared_ptr<Light>& light = m_world->lightArray[L];

            // Shadow rays
            if (m_world->lineOfSight(surfel->position + surfel->geometricNormal * 0.0001f, light->frame().translation)) {
                Vector3 w_i = light->frame().translation - surfel->position;
                const float distance2 = w_i.squaredLength();
                w_i /= sqrt(distance2);

                // Attenduated radiance
                const Irradiance3& E_i = light->bulbPower() / (4.0f * pif() * distance2);

                radiance += 
                    surfel->finiteScatteringDensity(w_i, -ray.direction()) * 
                    E_i *
                    max(0.0f, w_i.dot(surfel->shadingNormal));

                debugAssert(radiance.isFinite());
            }
        }

        // Indirect illumination
        // Ambient
        // radiance += surfel.material.lambertianReflect * world->ambient;

        // Specular
        if (bounce < m_maxBounces) {
            // Perfect reflection and refraction
            Surfel::ImpulseArray impulseArray;
            surfel->getImpulses(PathDirection::EYE_TO_SOURCE, -ray.direction(), impulseArray);
                
            for (int i = 0; i < impulseArray.size(); ++i) {
                const Surfel::Impulse& impulse = impulseArray[i];
                Ray secondaryRay = Ray::fromOriginAndDirection(surfel->position, impulse.direction).bumpedRay(RAY_BUMP_EPSILON);
                debugAssert(secondaryRay.direction().isFinite());
                radiance += rayTrace(secondaryRay, bounce + 1) * impulse.magnitude;
                debugAssert(radiance.isFinite());
            }
        }
    } else {
        // Hit the sky
        radiance = m_world->ambient;
    }

    return radiance;
}

void App::pathTraceImage(float scale, int numRays) {
    int width  = window()->width()  * scale;
    int height = window()->height() * scale;
    if (isNull(m_currentImage) || (m_currentImage->width() != width) || (m_currentImage->height() != height)) {
        m_currentImage = Image3::createEmpty(width, height);
    }
    m_primaryRaysPerPixel = numRays;

    const int maxThreads =
#ifdef G3D_DEBUG
  1;
#else
  System::numCores();
#endif
    GThread::runConcurrently2D(Point2int32(0, 0), Point2int32(width, height), this, &App::ptrace, maxThreads);

    // Post-process
    shared_ptr<Texture> src = Texture::fromImage("Source", m_currentImage);
    if (notNull(m_result)) {
        m_result->resize(width, height);
    }
    m_film->exposeAndRender(renderDevice, debugCamera()->filmSettings(), src, m_result);
    // show(m_result);
}

void App::ptrace(int x, int y) {
    Color3 sum = Color3::black();
	
    for (int i = 0; i < m_primaryRaysPerPixel; ++i) {
        sum += pathTrace(debugCamera()->worldRay(x + rnd.uniform(), y + rnd.uniform(), m_currentImage->rect2DBounds()), true);
    }
    m_currentImage->set(x, y, sum / m_primaryRaysPerPixel);
}

Radiance3 App::pathTrace(const Ray& ray, bool isEyeRay) {
    // trace a ray into the world. pathCount is the number of paths
    // that contribute to the radiance value, because we need to treat them all as separate contributions.
    // Probability is the probability of tracing this path at all in estimating the integral; we must 
    // divide by it when we compute the radiance. 
    Radiance3 radiance;

    shared_ptr<Surfel> surfel;
    float dist = inf();
    if (m_world->intersect(ray, dist, surfel)) {
        // this point could be an emitter...
        if (isEyeRay && m_emit) {
            radiance += surfel->emittedRadiance(-ray.direction());
        }

        // Shade this point (direct illumination from GLights)
//        if ((! isEyeRay) || m_direct) {
        if ((! isEyeRay) || m_direct) {
            radiance += estimateDirectLightFromPointLights(surfel, ray);
            radiance += estimateDirectLightFromAreaLights(surfel, ray);
        }

        if ((! isEyeRay) || m_indirect) {
            radiance += estimateIndirectLight(surfel, ray, isEyeRay);
        }
    }

    return radiance;
}


Radiance3 App::estimateDirectLightFromPointLights(const shared_ptr<Surfel>& surfel, const Ray& ray){
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
                    (surfel->finiteScatteringDensity(w_i, -ray.direction()) * 
                    E_i *
                    max(0.0f, w_i.dot(surfel->shadingNormal)));
                debugAssert(radiance.isFinite());
            }
        }
    }
    return radiance;
}


Radiance3 App::estimateDirectLightFromAreaLights(const shared_ptr<Surfel>& surfel, const Ray& ray) {
    Radiance3 radiance(0.0f);
    // Shade this point (direct illumination from AreaLights)
    if (m_areaLights) {
        for (int L = 0; L < m_world->lightArray2.size(); ++L) {
            shared_ptr<AreaLight> light = m_world->lightArray2[L];
            shared_ptr<Surfel> lightsurfel = light->samplePoint(rnd);
            const Point3& Q = lightsurfel->position;

            if (m_world->lineOfSight(surfel->position + surfel->geometricNormal * 0.0001f, Q + 0.0001f * lightsurfel->geometricNormal)) {
                Vector3 w_i = Q - surfel->position;
                const float distance2 = w_i.squaredLength();
                w_i /= sqrt(distance2);
			
                radiance +=
                    surfel->finiteScatteringDensity(w_i, -ray.direction()) * 
                    (light->power() / pif()) *
                    max(0.0f, w_i.dot(surfel->shadingNormal)) *
                    max(0.0f, -w_i.dot(lightsurfel->geometricNormal) / distance2);
                debugAssert(radiance.isFinite());                
            }
        }

		if (m_direct_s) {
			// now add in impulse-reflected light, too. 
			Surfel::ImpulseArray impulseArray;
            surfel->getImpulses(PathDirection::EYE_TO_SOURCE, -ray.direction(), impulseArray);
			for (int i = 0; i < impulseArray.size(); ++i) {
				const Surfel::Impulse& impulse = impulseArray[i];
				const Ray& secondaryRay = Ray::fromOriginAndDirection(surfel->position, impulse.direction).bumpedRay(RAY_BUMP_EPSILON);
				shared_ptr<Surfel> surfel2;
				float dist = inf();
				if (m_world->intersect(secondaryRay, dist, surfel2)) {
					// this point could be an emitter...
					if (m_emit) { 
						radiance += surfel2->emittedRadiance(-secondaryRay.direction()) * impulse.magnitude;
					}
				}
			}
		}

    }
    return radiance;
}


Radiance3 App::estimateIndirectLight(const shared_ptr<Surfel>& surfel, const Ray& ray, bool isEyeRay){
    Radiance3 radiance(0.0f);
    // Use recursion to estimate light running back along ray from surfel that arrives from 
    // INDIRECT sources, by making a single-sample estimate of the arriving light. 

    Vector3 w_o = -ray.direction();
    Vector3 w_i;
    Color3 coeff;

    if (!(isEyeRay) || m_indirect) {

        surfel->scatter(PathDirection::EYE_TO_SOURCE, w_o, false, rnd, coeff, w_i);
        if (! w_i.isNaN()) { 
            // see Veach, page 167.
            const float refractiveScale = square(surfel->etaPos / surfel->etaNeg); 

            // the final "false" makes sure that we do not include direct light. 
            radiance += refractiveScale * coeff * pathTrace(Ray(surfel->position, w_i).bumpedRay(RAY_BUMP_EPSILON * sign(surfel->geometricNormal.dot(w_i)), 
                surfel->geometricNormal), false); 
            // there's no  "w_i.dot(surfel.geometric.normal)" because it's included in "scatter" for the lambert case, and 
            // should NOT be there at all for the reflection or transmission case... 
        }
    }
    return radiance;
}
