 
/**
  @file App.cpp PHOTON MAP/RAY TRACE HYBRID
 */
#include "App.h"
#include "../jfhPathTrace/World.h"
/*
//#include "World.h"
#include "../jfhPhotonMap/LightList.h"
#include "../jfhPhotonMap/EPhoton.h"
#include "../jfhPhotonMap/IPhoton.h"
*/

G3D_START_AT_MAIN();

int main(int argc, char** argv) {
    GApp::Settings settings;
    settings.window.caption     = " JFH Photon Mapping with Ray Tracing";
    settings.window.width       = 900; //960; 
    settings.window.height      = 900; //640;
    return App(settings).run();
}

App::App(const GApp::Settings& settings) : 
    GApp(settings),
    m_maxBounces(3), 
    m_nPhotons(1000), 
    m_pointLights(true),
    m_areaLights(true),
    m_whichRenderer(false),
    m_whichWorld(4),
    m_showPhotonArrows(false),
    m_showPhotonDots(false),
    m_primaryRaysPerPixel(1),
    m_gatherRaysPerSample(3),
    m_world(NULL),
    m_diffuseDirectSamples(20),
    m_DDiff(true),
    m_DImp(true),
    m_IDiff(true),
    m_IImp(true),
    m_emit(true),
    m_scaleFactor(0.3f),
    m_photonMap(0.05f) { // gather radius
}

void App::onInit() {
    message("Loading...");
    m_world = new World(m_whichWorld);

    showRenderingStats = false;
    developerWindow->setVisible(false);
    developerWindow->cameraControlWindow->setVisible(false);

    // Starting position
    defaultCamera.setCoordinateFrame(CFrame::fromXYZYPRDegrees(0.0f, 0.3f, 0.0f, 0.0f, 0.0f, 0.0f));
    m_prevCFrame = defaultCamera.coordinateFrame();

    m_lighting = Lighting::create();
    m_lighting->lightArray.append(GLight::directional(Vector3(1,2,1), Color3::fromARGB(0xfcf6eb)));
    m_lighting->lightArray.append(GLight::directional(Vector3(-1,-0.5f,-1), Color3::fromARGB(0x1e324d)));

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
    pane->addNumberBox("Which world?", &m_whichWorld, "", GuiTheme::LINEAR_SLIDER, 0, 5, 1);
    pane->addCheckBox("Direct Diffuse?", &m_DDiff);
    pane->addNumberBox(G3D::GuiText("Dir. Diff Samples?",0, 9), &m_diffuseDirectSamples, "", GuiTheme::LINEAR_SLIDER, 1, 200, 1);
    pane->addCheckBox("Direct Impulse?", &m_DImp);
    pane->addCheckBox("Indirect Diffuse?", &m_IDiff);
    pane->addCheckBox("Indirect Impulse?", &m_IImp);
    pane->addCheckBox("Emitted light", &m_emit);

    pane->addNumberBox("Scale", &m_scaleFactor, "", GuiTheme::LINEAR_SLIDER, -0.0f, 1.1f, 0.1f);
    window->pack();
    window->setVisible(true);
    addWidget(window);
    message("Done with GUI");
}

void App::onGraphics(RenderDevice* rd, Array<shared_ptr<Surface>>& surface3D, Array<Surface2D::Ref>& surface2D) {
    if (! m_prevCFrame.fuzzyEq(defaultCamera.coordinateFrame())) {
        rayTraceImage(0.2f, 1);
        m_prevCFrame = defaultCamera.coordinateFrame();
    }

    rd->clear();
    rd->pushState();
    {
        rd->setRenderMode(RenderDevice::RENDER_SOLID);
        Surface::sortAndRender(rd, defaultCamera, m_world->surfaces(), m_lighting, 0); // m_world->GLights(), 0);
        rd->setProjectionAndCameraMatrix(defaultCamera);
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

Radiance3 App::rayTrace(const Ray& ray, World* world, const Color3& extinction_i, int bounce) {
    Radiance3 radiance = Radiance3::zero();

    SurfaceElement surfel;
    float dist = inf();
    if (world->intersect(ray, dist, surfel)) {
        // Shade this point (direct illumination)
        for (int L = 0; L < world->lightArray.size(); ++L) {
            const GLight& light = world->lightArray[L];
			if (!m_pointLights) continue;

            // Shadow rays
            if (world->lineOfSight(surfel.geometric.location + surfel.geometric.normal * 0.0001f, light.position.xyz())) {
                Vector3 w_i = light.position.xyz() - surfel.shading.location;
                const float distance2 = w_i.squaredLength();
                w_i /= sqrt(distance2);

                // Attenduated radiance
                const Irradiance3& E_i = light.color / (4.0f * pif() * distance2);

                radiance += 
                    surfel.evaluateBSDF(w_i, -ray.direction()) * 
                    E_i *
                    max(0.0f, w_i.dot(surfel.shading.normal));

                debugAssert(radiance.isFinite());
            }
        }

        // Indirect illumination
        // Ambient
        radiance += surfel.material.lambertianReflect * world->ambient;

        // Specular
        if (bounce < m_maxBounces) {
            // Perfect reflection and refraction
            SmallArray<SurfaceElement::Impulse, 3> impulseArray;
            surfel.getBSDFImpulses(-ray.direction(), impulseArray);

            for (int i = 0; i < impulseArray.size(); ++i) {
                const SurfaceElement::Impulse& impulse = impulseArray[i];
                Ray secondaryRay = Ray::fromOriginAndDirection(surfel.geometric.location, impulse.w).bumpedRay(0.0001f);
                debugAssert(secondaryRay.direction().isFinite());
                radiance += rayTrace(secondaryRay, world, impulse.extinction, bounce + 1) * impulse.magnitude;
                debugAssert(radiance.isFinite());
            }
        }
    } else {
        // Hit the sky
        radiance = world->ambient;
    }

    return radiance;
}

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
        rayTraceImage(m_scaleFactor, 3); // 3 rays per pixel as a default for comparison
        timer.after("Ray Trace");
    }
    else {
        photonRenderImage(m_scaleFactor);
		timer.after("Photon Map Ray Trace Hybrid");
    }
    debugPrintf("%f s\n", timer.elapsedTime());
    show(m_currentImage);
//    m_result->toImage3unorm8()->save("result.png");
    //m_currentImage->toImage3unorm8()->save("result.png");
	 m_currentImage->save("result.png");
}

void App::trace(int x, int y) {
    Color3 sum = Color3::black();
    if (m_primaryRaysPerPixel == 1) {
        sum = rayTrace(defaultCamera.worldRay(x + 0.5f, y + 0.5f, m_currentImage->rect2DBounds()), m_world);
    } else {
        for (int i = 0; i < m_primaryRaysPerPixel; ++i) {
            sum += rayTrace(defaultCamera.worldRay(x + rnd.uniform(), y + rnd.uniform(), m_currentImage->rect2DBounds()), m_world);
        }
    }
    m_currentImage->set(x, y, sum / m_primaryRaysPerPixel);
}

void App::rayTraceImage(float scale, int numRays) {
    int width  = window()->width()  * scale;
    int height = window()->height() * scale;

    if (m_currentImage.isNull() || (m_currentImage->width() != width) || (m_currentImage->height() != height)) {
        m_currentImage = Image3::createEmpty(width, height);
    }
    m_primaryRaysPerPixel = numRays;
    GThread::runConcurrently2D(Point2int32(0, 0), Point2int32(width, height), this, &App::trace);

    // Post-process
    Texture::Ref src = Texture::fromImage("Source", m_currentImage);
    if (m_result.notNull()) {
        m_result->resize(width, height);
    }
    m_film->exposeAndRender(renderDevice, src, m_result);
}

void App::photonRenderImage(float scale) {
    int width  = window()->width()  * scale;
    int height = window()->height() * scale;
    if (m_currentImage.isNull() || (m_currentImage->width() != width) || (m_currentImage->height() != height)) {
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
    if (m_result.notNull()) {
        m_result->resize(width, height);
    }
    m_film->exposeAndRender(renderDevice, src, m_result);
}


