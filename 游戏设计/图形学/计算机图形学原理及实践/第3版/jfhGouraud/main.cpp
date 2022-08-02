/**

  Example of using G3D shaders and GUIs.
  
 */
#include <G3D/G3DAll.h>
#include <GLG3D/GLG3D.h>

class App : public GApp {
private:
    shared_ptr<Lighting>            lighting;
    shared_ptr<ArticulatedModel>    model;

    shared_ptr<Shader>              gouraudShader;
    
    float                           diffuseScalar;
    int                             diffuseColorIndex;

    float                           specularScalar;
    int                             specularColorIndex;

    float                           reflect;
    float                           shine;

    ////////////////////////////////////
    // GUI

    /** For dragging the model */
    shared_ptr<ThirdPersonManipulator>   manipulator;
    Array<GuiText>                  colorList;

    void makeGui();
    void makeColorList();
    void makeLighting();
    void configureShaderArgs(const Lighting::Ref localLighting, Args& args);

public:

    App() : diffuseScalar(0.6f), specularScalar(0.5f), reflect(0.1f), shine(20.0f) {}

    virtual void onInit();
    virtual void onGraphics3D(RenderDevice* rd, Array<shared_ptr<Surface> >& surface3D);
};


void App::onInit() {
    //
	createDeveloperHUD();
    window()->setCaption("Pixel Shader Demo");
        
    gouraudShader = Shader::fromFiles("gouraud.vrt", "gouraud.pix");
    ArticulatedModel::Specification spec;
    spec.filename = System::findDataFile("teapot/teapot.obj");
    spec.scale = 0.015f;
    spec.stripMaterials = true;
    spec.preprocess.append(ArticulatedModel::Instruction(Any::parse("setCFrame(root(), Point3(0, -0.5, 0));")));
    model = ArticulatedModel::create(spec);

    makeLighting();
    makeColorList();
    makeGui();

    // Color 1 is red
    diffuseColorIndex = 1;
    // Last color is white
    specularColorIndex = colorList.size() - 1;
    
    m_debugCamera->setPosition(Vector3(1.0f, 1.0f, 2.5f));
    m_debugCamera->setFieldOfView(45 * units::degrees(), FOVDirection::VERTICAL);
    m_debugCamera->lookAt(Point3::zero());

    // Add axes for dragging and turning the model
    manipulator = ThirdPersonManipulator::create();
    addWidget(manipulator);

    // Turn off the default first-person camera controller and developer UI
    m_debugController->setEnabled(false);
    developerWindow->setVisible(false);
    developerWindow->cameraControlWindow->setVisible(false);

    showRenderingStats = false;
}


void App::onGraphics3D(RenderDevice* rd, Array<shared_ptr<Surface> >& surface3D) {
    // Bind the main frameBuffer
    rd->pushState(m_frameBuffer); {
        rd->clear();

        rd->setProjectionAndCameraMatrix(m_debugCamera->projection(), m_debugCamera->frame());
        
        Draw::skyBox(rd, lighting->environmentMapTexture, lighting->environmentMapConstant);
        
        rd->pushState(); {
            Array< shared_ptr<Surface> > mySurfaces;
            // Pose our model based on the manipulator axes
            model->pose(mySurfaces, manipulator->frame());
            
            // Set up shared arguments
            Args args;
            configureShaderArgs(lighting, args);
            
            // Send model geometry to the graphics card
            CFrame cframe;
            for (int i = 0; i < mySurfaces.size(); ++i) {

                // Downcast to UniversalSurface to access its fields
                shared_ptr<UniversalSurface> surface = dynamic_pointer_cast<UniversalSurface>(mySurfaces[i]);
                if (notNull(surface)) {
                    surface->getCoordinateFrame(cframe);
                    rd->setObjectToWorldMatrix(cframe);
                    surface->gpuGeom()->setShaderArgs(args);

                    // (If you want to manually set the material properties and vertex attributes
                    // for shader args, they can be accessed from the fields of the gpuGeom.)

                    rd->apply(gouraudShader, args);
                }
            }
        } rd->popState();
        
        // Render other objects, e.g., the 3D widgets
        Surface::Environment env;
        Surface::render(rd, m_debugCamera->frame(), m_debugCamera->projection(), surface3D, surface3D, lighting, env);   
    } rd->popState();

    // Perform gamma correction, bloom, and SSAA, and write to the native window frame buffer
    m_film->exposeAndRender(rd, m_debugCamera->filmSettings(), m_colorBuffer0, 1);

}
    
    
void App::configureShaderArgs(const shared_ptr<Lighting> lighting, Args& args) {
    const shared_ptr<Light>&  light         = lighting->lightArray[0];
    const Color3&       diffuseColor  = colorList[diffuseColorIndex].element(0).color(Color3::white()).rgb();
    const Color3&       specularColor = colorList[specularColorIndex].element(0).color(Color3::white()).rgb();
    
    
    // Viewer
    args.setUniform("wsEyePosition",       m_debugCamera->frame().translation);
    
    // Lighting
    args.setUniform("wsLight",             light->position().xyz().direction());
    args.setUniform("lightColor",          light->color);
    args.setUniform("ambient",             Color3(0.3f));
    args.setUniform("environmentMap",      lighting->environmentMapTexture);
    args.setUniform("environmentConstant", lighting->environmentMapConstant);
    
    // UniversalMaterial
    args.setUniform("diffuseColor",        diffuseColor);
    args.setUniform("diffuse",       diffuseScalar);
    
    args.setUniform("specularColor",       specularColor);
    args.setUniform("specularScalar",      specularScalar);
    
    args.setUniform("shine",               shine);
    args.setUniform("reflect",             reflect);
}


void App::makeColorList() {
    GFont::Ref iconFont = GFont::fromFile(System::findDataFile("icon.fnt"));

    // Characters in icon font that make a solid block of color
    static const char* block = "gggggg";

    float size = 18;
    int N = 10;
    colorList.append(GuiText(block, iconFont, size, Color3::black(), Color4::clear()));
    for (int i = 0; i < N; ++i) {
        colorList.append(GuiText(block, iconFont, size, Color3::rainbowColorMap((float)i / N), Color4::clear()));
    }
    colorList.append(GuiText(block, iconFont, size, Color3::white(), Color4::clear()));
}


void App::makeGui() {
    GuiWindow::Ref gui = GuiWindow::create("UniversalMaterial Parameters");    
    GuiPane* pane = gui->pane();

    pane->beginRow();
    pane->addSlider("Lambertian", &diffuseScalar, 0.0f, 1.0f);
    pane->addDropDownList("", colorList, &diffuseColorIndex)->setWidth(80);
    pane->endRow();

    pane->beginRow();
    pane->addSlider("Glossy",    &specularScalar, 0.0f, 1.0f);
    pane->addDropDownList("", colorList, &specularColorIndex)->setWidth(80);
    pane->endRow();
    
    pane->addSlider("Mirror",     &reflect, 0.0f, 1.0f);
    pane->addSlider("Smoothness", &shine, 1.0f, 100.0f);
    
    gui->pack();
    addWidget(gui);
    gui->moveTo(Point2(10, 10));
}


void App::makeLighting() {
    Lighting::Specification spec;
    spec.lightArray.append(Light::directional("Light", Vector3(1.0f, 1.0f, 1.0f), Color3(1.0f), false));

    // The environmentMap is a cube of six images that represents the incoming light to the scene from
    // the surrounding environment.  G3D specifies all six faces at once using a wildcard and loads
    // them into an OpenGL cube map.
    spec.environmentMapConstant = 1.0f;
    spec.environmentMapTexture.filename   = FilePath::concat(System::findDataFile("noonclouds"), "noonclouds_*.png");
    spec.environmentMapTexture.dimension  = Texture::DIM_CUBE_MAP;
    spec.environmentMapTexture.settings   = Texture::Settings::cubeMap();
    spec.environmentMapTexture.preprocess = Texture::Preprocess::gamma(2.1f);
    // Reduce memory size required to work on older GPUs
    spec.environmentMapTexture.preprocess.scaleFactor = 0.25f;
    spec.environmentMapTexture.settings.interpolateMode = Texture::BILINEAR_NO_MIPMAP;
    
    lighting = Lighting::create(spec);
}

G3D_START_AT_MAIN();

int main(int argc, char** argv) {
#   ifdef G3D_WINDOWS
      if (! FileSystem::exists("gouraud.pix", false) && FileSystem::exists("G3D.sln", false)) {
          // The program was started from within Visual Studio and is
          // running with cwd = G3D/VC10/.  Change to
          // the appropriate sample directory.
          chdir("../samples/pixelShader/data-files");
      } else if (FileSystem::exists("data-files")) {
          chdir("data-files");
      }
#   endif

    return App().run();
}
