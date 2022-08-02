void 
StereoCamera::setup_cameras(void) {
	double r = eye.distance(lookat);
	double x = r * tan(0.5 * beta * PI_ON_180);  //  half the camera separation distance
		
	left_camera_ptr->set_eye(eye - x * u);
	left_camera_ptr->set_lookat(lookat - x * u);
	left_camera_ptr->compute_uvw();
	
	right_camera_ptr->set_eye(eye + x * u);
	right_camera_ptr->set_lookat(lookat + x * u);
	right_camera_ptr->compute_uvw();
}
