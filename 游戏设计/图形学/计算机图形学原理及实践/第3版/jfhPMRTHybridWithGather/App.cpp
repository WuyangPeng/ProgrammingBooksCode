
/**
  @file App.cpp PHOTON MAP/RAY TRACE HYBRID with GATHER
 */
#include "App.h"

 
G3D_START_AT_MAIN();

int main(int argc, char** argv) {
    GApp::Settings settings;
    settings.window.caption     = " JFH Photon Mapping with Ray Tracing and Gather";
    settings.window.width       = 900;  
    settings.window.height      = 900; 
    return App(settings).run();
}

App::App(const GApp::Settings& settings) : 
    GApp(settings),
    m_maxBounces(9),         // Max recursive depth used in preview raytracer
    m_nPhotons(20),       // How many photons to shoot //10000
    m_pointLights(false),    // Include point lights in computations? 
    m_areaLights(true),      // Include area lights in computations? 
    m_whichRenderer(false),  // Raytrace instead of photon mapping when true
    m_whichWorld(2),  
    m_showPhotonArrows(false), // In preview world, show each photon with an arrow pointing towards the source of light
    m_showPhotonDots(false),   // Preview each photon as a colored dot
    m_primaryRaysPerPixel(10), // How many rays to trace through each pixel
    m_gatherRaysPerSample(60), // When using final gathering, how many samples to take in estimating the integral
    m_world(NULL),             // Reference to currently loaded world
    m_diffuseDirectSamples(20),  // When computing direct light reflected by diffuse surfaces, how many samples to take
    m_DDiff(true),             // Which terms in the expanded rendering equation to use (for the next 5 items)
    m_DImp(true),
    m_IDiff(true),
    m_IImp(true),
    m_emit(true),
    m_useGather(false),         // Use final gathering when true. 
    m_scaleFactor(0.3f),       // Make displayed image only this large, relative to the preview display
	m_resultsWindow(NULL),     // At startup, there's no window displaying current results
    m_photonMap(0.4f) {       // gather radius is the initializer for the photon map
}

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
    m_prevCFrame =  debugCamera()->frame();

	// The large window will display a preview of the scene made with a basic rasterizing renderer. It needs a lighting environment: 
    m_lighting = Lighting::create();
    m_lighting->lightArray.append(Light::directional("light1", Vector3(1,2,1), Color3::fromARGB(0xfcf6eb)));
    m_lighting->lightArray.append(Light::directional("light2", Vector3(-1,-0.5f,-1), Color3::fromARGB(0x1e324d)));

    makeGUI();
    onRender();
}

void App::makeGUI() {
    message("Building GUI");
    GuiWindow::Ref window = GuiWindow::create("Controls", debugWindow->theme(), Rect2D::xywh(0,0,0,0), GuiTheme::TOOL_WINDOW_STYLE);
    GuiPane* pane = window->pane();
    pane->addLabel("Use WASD keys + right mouse to move");
    pane->addButton("Render High Res.", this, &App::onRender);
    pane->addNumberBox("Photon count", &m_nPhotons, "", GuiTheme::LOG_SLIDER, 10, 10000000);
    pane->addNumberBox("Max bounces", &m_maxBounces, "", GuiTheme::LINEAR_SLIDER, 1, 16, 3);
    pane->addNumberBox("Prim. Rays/Pix", &m_primaryRaysPerPixel, "", GuiTheme::LOG_SLIDER, 1, 4096, 1);
    pane->addCheckBox("Use point lights?", &m_pointLights);
    pane->addCheckBox("Use area lights?", &m_areaLights);
    pane->addCheckBox("Raytrace instead of hybrid", &m_whichRenderer); 
    pane->addCheckBox("Show photons as arrows", &m_showPhotonArrows); 
    pane->addCheckBox("Show photons as dots", &m_showPhotonDots); 
    pane->addNumberBox("Which world?", &m_whichWorld, "", GuiTheme::LINEAR_SLIDER, 0, 7, 1);
    pane->addCheckBox("Direct Diffuse?", &m_DDiff);
    pane->addNumberBox(G3D::GuiText("Dir. Diff Samples?",0, 9), &m_diffuseDirectSamples, "", GuiTheme::LINEAR_SLIDER, 5, 200, 20);
    pane->addCheckBox("Direct Impulse?", &m_DImp);
    pane->addCheckBox("Indirect Diffuse?", &m_IDiff);
    pane->addCheckBox("Indirect Impulse?", &m_IImp);
    pane->addCheckBox("Emitted light", &m_emit);
    pane->addCheckBox("Final Gather?", &m_useGather);
    pane->addNumberBox("Gather Samples?.....", &m_gatherRaysPerSample, "", GuiTheme::LINEAR_SLIDER, 1, 200, 1);
    pane->addNumberBox("Scale", &m_scaleFactor, "", GuiTheme::LINEAR_SLIDER, -0.0f, 1.15f, 0.1f);
    window->pack();
    window->setVisible(true);
    addWidget(window);
    message("Done with GUI");
}

void App::onGraphics(RenderDevice* rd, Array<shared_ptr<Surface>>& surface3D, Array<Surface2D::Ref>& surface2D) {
    if (! m_prevCFrame.fuzzyEq(debugCamera()->frame())) {
        rayTraceImage(0.2f, 1);
        m_prevCFrame = debugCamera()->frame();
    }


	// This part differs from the pathtracer: it's a "Solid" rendering of the world to be used as a preview, and a viewer
	// for the photon locations and their associated incoming-light directions. 
    rd->clear();
    rd->pushState();
    {
        rd->setRenderMode(RenderDevice::RENDER_SOLID);
        Surface::Environment environment;
        environment.setData(m_lighting, shared_ptr<AmbientOcclusion>(), shared_ptr<Texture>(), shared_ptr<Texture>());
        Surface::render(rd, debugCamera()->frame(), debugCamera()->projection(), m_world->surfaces(), m_world->surfaces(), m_lighting, environment);


        rd->setProjectionAndCameraMatrix(activeCamera()->projection(), debugCamera()->frame());
        Surface::renderWireframe(rd, m_world->surfaces(), Color3::white()*0.5f);
        Draw::axes(rd);

        typedef PointHashGrid<IPhoton, IPhoton::PosFunc, EqualsTrait<IPhoton> >::Iterator PhotonIterator;

        if (m_showPhotonArrows) {
            for (PhotonIterator i = m_photonMap.begin(); i != m_photonMap.end(); ++i ){
                IPhoton ip = *i;
                Color3 c = ip.power() / ip.power().max();
                Draw::arrow(ip.position(), ip.directionToSource()/10, rd, c, 0.2f);
            }
        }

        if (m_showPhotonDots) {
            rd->setPointSize(0.2f);
            rd->beginPrimitive(PrimitiveType::POINTS);

            for (PhotonIterator i = m_photonMap.begin(); i != m_photonMap.end(); ++i ){
                IPhoton ip = *i;
                Color3 c = ip.power() / ip.power().max();
                rd->setColor(c);
                rd->sendVertex(ip.position());
            }
            rd->endPrimitive();
        }
    }
    rd->popState();
    Surface2D::sortAndRender(rd, surface2D);
}

void App::onCleanup() {
    delete m_world;
    m_world = NULL;
}

static G3D::Random rnd(0xF018A4D2, false);

void App::message(const std::string& msg) const {
    renderDevice->setColorClearValue(Color3::red()*0.5);
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
    m_world = new World(m_whichWorld);

    if (m_whichRenderer) {
        rayTraceImage(m_scaleFactor, m_primaryRaysPerPixel);
        timer.after("Ray Trace");
    }
    else {
        photonRenderImage(m_scaleFactor);
        timer.after("Photon Map Path Trace Hybrid");
    }
    debugPrintf("%f s\n", timer.elapsedTime());
	if (m_resultsWindow) {
		//m_resultsWindow->close();
	}
    m_resultsWindow = show(m_result);
    m_currentImage->save("result.png");
}

void App::rayTraceImage(float scale, int numRays) {
    int width  = window()->width()  * scale;
    int height = window()->height() * scale;

    if (notNull(m_currentImage) || (m_currentImage->width() != width) || (m_currentImage->height() != height)) {
        m_currentImage = Image3::createEmpty(width, height);
    }
    m_primaryRaysPerPixel = numRays;
    GThread::runConcurrently2D(Point2int32(0, 0), Point2int32(width, height), this, &App::trace);

    // Post-process
    Texture::Ref src = Texture::fromImage("Source", m_currentImage);
    if (notNull(m_result)) {
        m_result->resize(width, height);
    }
    m_film->exposeAndRender(renderDevice, m_debugCamera->filmSettings(), src, m_result);
}





void App::trace(int x, int y) {
    Color3 sum = Color3::black();
    if (m_primaryRaysPerPixel == 1) {
        sum = rayTrace(debugCamera()->worldRay(x + 0.5f, y + 0.5f, m_currentImage->rect2DBounds()), m_world);
    } else {
        for (int i = 0; i < m_primaryRaysPerPixel; ++i) {
            sum += rayTrace(debugCamera()->worldRay(x + rnd.uniform(), y + rnd.uniform(), m_currentImage->rect2DBounds()), m_world);
        }
    }
    m_currentImage->set(x, y, sum / m_primaryRaysPerPixel);
}


Radiance3 App::rayTrace(const Ray& ray, World* world, int bounce) {
    Radiance3 radiance = Radiance3::zero();

    shared_ptr<Surfel> surfel;
    float dist = inf();
    if (world->intersect(ray, dist, surfel)) {
        // Shade this point (direct illumination)
        for (int L = 0; L < world->lightArray.size(); ++L) {
            const shared_ptr<Light>& light = world->lightArray[L];

            if (m_pointLights) {
                // Shadow rays
                if (world->lineOfSight(surfel->position + surfel->geometricNormal * 0.0001f, light->frame().translation)) {
                    Vector3 w_i = light->frame().translation - surfel->position;
                    const float distance2 = w_i.squaredLength();
                    w_i /= sqrt(distance2);
					
                    // Attenduated radiance
                    const Irradiance3& E_i = light->bulbPower() / (4.0f * pif() * distance2);

                    radiance += 
                        surfel->finiteScatteringDensity(PathDirection::EYE_TO_SOURCE, w_i, -ray.direction()) * 
                        E_i *
                        max(0.0f, w_i.dot(surfel->shadingNormal));

                    debugAssert(radiance.isFinite());
                }
            }
        }

        // Indirect illumination
        // Ambient
        radiance += surfel->reflectivity(rnd) * world->ambient;

        // Specular
        if (bounce < m_maxBounces) {
            // Perfect reflection and refraction
            Surfel::ImpulseArray impulseArray;
            surfel->getImpulses(PathDirection::EYE_TO_SOURCE, -ray.direction(), impulseArray);

            for (int i = 0; i < impulseArray.size(); ++i) {
                const Surfel::Impulse& impulse = impulseArray[i];
                Ray secondaryRay = Ray::fromOriginAndDirection(surfel->position, impulse.direction).bumpedRay(0.0001f);
                debugAssert(secondaryRay.direction().isFinite());
                radiance += rayTrace(secondaryRay, world, bounce + 1) * impulse.magnitude;
                debugAssert(radiance.isFinite());
            }
        }
    } else {
        // Hit the sky
        radiance = world->ambient;
    }

    return radiance;
}


void App::photonRenderImage(float scale) {
    int width  = window()->width()  * scale;
    int height = window()->height() * scale;
    if (isNull(m_currentImage) || (m_currentImage->width() != width) || (m_currentImage->height() != height)) {
        m_currentImage = Image3::createEmpty(width, height);
    }

    const int maxThreads =
#ifdef G3D_DEBUG
        1;
#else
        System::numCores();
#endif

    buildPhotonMap();

    GThread::runConcurrently2D(Point2int32(0, 0), Point2int32(width, height), this, &App::photonRender, maxThreads);

    // Post-process
    Texture::Ref src = Texture::fromImage("Source", m_currentImage);
    m_film->exposeAndRender(renderDevice, m_debugCamera->filmSettings(), src, m_result);
}


