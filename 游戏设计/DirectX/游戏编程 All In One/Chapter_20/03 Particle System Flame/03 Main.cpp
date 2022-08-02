		/* '03 Main.cpp' */

		/* Mirus window framework header */
	#include "mirus.h"

		/* Custom derived class */
	class CustomWindow : public mrWindow
	{
	public:
		mrScreen            m_kScreen;

			/* Our particle system */
		mrParticleSystem    m_kParticleSystem;

			/* Constructor / Destructor */
		CustomWindow (void) {};
		~CustomWindow (void) {};

			/* Window manipulation functions */
		mrBool32 Frame (void);

	};

		/* Render frame */
	mrBool32 CustomWindow::Frame(void)
	{
			/* Start rendering */
		m_kScreen.Clear (0, 0, 0, 0);
		m_kScreen.StartFrame ();

			/* Simulate according to elapsed time */
		if (m_kScreen.GetFPS () != 0)
		{
			m_kParticleSystem.Simulate (1/(mrReal32)m_kScreen.GetFPS ());
		}

			/* Render particle system and end frame */
		m_kParticleSystem.Render ();
		m_kScreen.EndFrame ();

		return mrTrue;
	}

		/* "WinMain Vs. main" */
	int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInst, 
																					LPSTR lpCmdLine, int nShowCmd)
	{
			/* Our window */
		CustomWindow  kWindow;

			/* Create window */
		kWindow.Create (hInstance, "04 Mirus Example");
		kWindow.SetSize (640, 480);
 
		kWindow.m_kScreen.Init (kWindow.GetHandle ());
		kWindow.m_kScreen.SetMode (false, 640,480,32,true);

			/* We need a texture for our particle system */
		mrRGBAImage rkImage;
		rkImage.LoadFromBitmap ("gradientcircle.bmp");

		mrTexture kTexture;
		kTexture.Create (&rkImage);

			/* Our system parameters */
		mrParticleSystemParams kParameters;

		kParameters.m_fSize       = 20;
		kParameters.m_fLifetime   = 0.3f;
		kParameters.m_iColor      = D3DCOLOR_RGBA (255, 208, 51, 136);
		kParameters.m_iFinalColor = D3DCOLOR_RGBA (255, 0, 0, 0);
		kParameters.m_kPosition   = mrVector2D (310,230);
		kParameters.m_fFinalSize  = 30;
		kParameters.m_fSpeed      = -4;
		kParameters.m_fDispersion = 0.02f;

			/* Create the particle system */
		kWindow.m_kParticleSystem.Create (kParameters, 200, 75, &kTexture);
 
		kWindow.Run ();
		return 0;
	}