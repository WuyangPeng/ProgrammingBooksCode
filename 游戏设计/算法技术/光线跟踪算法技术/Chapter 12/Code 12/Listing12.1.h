typedef enum {
	parallel, 
	transverse
} ViewingType;

#include "Camera.h"

class StereoCamera: public Camera {						
	public:
	
		// constructors, etc.
		
		void 
		setup_cameras(void);

		virtual void 												
		render_scene(World& w);
		
	private:
		
		ViewingType	viewing_type;		// parallel or transverse viewing
		int			pixel_gap;			// gap in pixels between the left and right images
		float		beta;				// stereo separation angle	
		Camera*		left_camera_ptr;	// left eye camera
		Camera*		right_camera_ptr;	// right eye camera
};

