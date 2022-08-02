// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

// This builds the scene for Figure 12.13
// The code for the WireframeBox class is in the Code download

void 												
World::build(void) {
	int num_samples = 16;
	
	vp.set_hres(200);	  		
	vp.set_vres(200);
	vp.set_samples(num_samples);
	vp.set_pixel_size(0.0325); 
	
	tracer_ptr = new RayCast(this);	
	background_color = black;
	
	float vpd = 10.0; 
	
	Pinhole* left_camera_ptr = new Pinhole;
	left_camera_ptr->set_view_distance(vpd);   
	set_camera(left_camera_ptr);
	
	Pinhole* right_camera_ptr = new Pinhole;
	right_camera_ptr->set_view_distance(vpd);   
	set_camera(right_camera_ptr);
	
	StereoCamera* stereo_ptr = new StereoCamera(left_camera_ptr, right_camera_ptr);
	stereo_ptr->use_parallel_viewing();
// 	stereo_ptr->use_transverse_viewing();
	stereo_ptr->set_pixel_gap(5);
	stereo_ptr->set_eye(-2, 0, 5);    
	stereo_ptr->set_lookat(0.0);
	stereo_ptr->compute_uvw();
	stereo_ptr->set_stereo_angle(5.0);  // in degrees
	stereo_ptr->setup_cameras(); 
	set_camera(stereo_ptr);
	
	Directional* light_ptr = new Directional;
	light_ptr->set_direction(Vector3D(20, 30, 40)); 
	light_ptr->scale_radiance(2.5);
	light_ptr->set_shadows(true);
	add_light(light_ptr);
			
	Phong* phong_ptr = new Phong;			
	phong_ptr->set_cd(0.7);					
	phong_ptr->set_ka(0.3);    
	phong_ptr->set_kd(1);
	phong_ptr->set_ks(0.3);
	phong_ptr->set_exp(50);
	
	Point3D p0(-1.0);
	Point3D p1(1.0);
	float bevel_radius = 0.04;
	
	WireframeBox* box_ptr = new WireframeBox(p0, p1, bevel_radius);
	box_ptr->set_material(phong_ptr);
	add_object(box_ptr);	
}



