void 												
StereoCamera::render_scene(World& w) {
	ViewPlane	vp 		= w.vp;					
	int 		hres	= vp.hres;
	int 		vres 	= vp.vres;
	
	w.open_window(2 * hres + pixel_gap, vres);  
						
	double r = eye.distance(lookat);
	double x = r * tan(0.5 * beta * PI_ON_180);  
		
	if (viewing_type == parallel) {
		left_camera_ptr->render_stereo(w, x, 0);						// left view on left
		right_camera_ptr->render_stereo(w, -x, hres + pixel_gap);   	// right view on right
	}
	
	if (viewing_type == transverse) {
		right_camera_ptr->render_stereo(w, -x, 0);   					// right view on left
		left_camera_ptr->render_stereo(w, x, hres + pixel_gap);    		// left view on right
	}
} 
