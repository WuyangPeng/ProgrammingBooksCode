// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


// This builds the scene for Figure 28.34(b)

// All the images with the camera inside the transparent sphere render slowly
// Try these with one sample per pixel

void 												
World::build(void) {
	int num_samples = 16;
	
	vp.set_hres(600);	  		
	vp.set_vres(600);
	vp.set_samples(num_samples);
	vp.set_max_depth(4);
		
	background_color = RGBColor(0.5, 0.5, 1.0);  // light blue
	
	tracer_ptr = new Whitted(this);
	
	
	Pinhole* pinhole_ptr = new Pinhole;
	pinhole_ptr->set_eye(0, 0, 2); 
	pinhole_ptr->set_lookat(0, 0, 10);    
	pinhole_ptr->set_view_distance(200.0);  
	pinhole_ptr->set_exposure_time(0.17);
	pinhole_ptr->compute_uvw();     
	set_camera(pinhole_ptr);
	
	
	Directional* light_ptr1 = new Directional;
	light_ptr1->set_direction(0, 1, 0);    // straight down
	light_ptr1->scale_radiance(3.0); 
	light_ptr1->set_shadows(true);
	add_light(light_ptr1);
	
	
	Directional* light_ptr2 = new Directional;
	light_ptr2->set_direction(0, -1, 0);    // straight up
	light_ptr2->scale_radiance(2.5); 
	light_ptr2->set_shadows(false);
	add_light(light_ptr2);
	
	
	// transparent sphere
	
	Dielectric* dielectric_ptr = new Dielectric;
	dielectric_ptr->set_eta_in(2.42);		// diamond
	dielectric_ptr->set_eta_out(1.0);		// air
	dielectric_ptr->set_cf_in(white);
	dielectric_ptr->set_cf_out(white); 
		
	Sphere* sphere_ptr1 = new Sphere(Point3D(0.0), 4.0);
	sphere_ptr1->set_material(dielectric_ptr);
	add_object(sphere_ptr1);	
	
	
	
	// a ring of spheres around the transparent sphere
	
	double scaling_factor 	= 2.0;  	// used to scale the radii of the ring and spheres
	double 	sphere_radius 	= 1.75 * scaling_factor;
	double 	ring_radius 	= 10.0 * scaling_factor;
	int 	num_spheres 	= 20;
	int 	delta_theta 	= 20;

	RGBColor color1(1, 0.5, 0);          // orange
	RGBColor color2(0.0, 0.5, 0.25);	  // cyan
	
	
	// Phong material for top half of each sphere
	
	Phong* phong_ptr1 = new Phong;		
	phong_ptr1->set_ka(0.2);
	phong_ptr1->set_kd(1.0);
	phong_ptr1->set_cd(color1);
	phong_ptr1->set_exp(100.0);
	phong_ptr1->set_ks(0.5);
	phong_ptr1->set_cs(1, 1, 0);
	
	
	// reflective material for bottom half of each sphere
	
	Reflective* reflective_ptr2 = new Reflective;
	reflective_ptr2->set_ka(0.2);
	reflective_ptr2->set_kd(1.0);
	reflective_ptr2->set_cd(color2);
	reflective_ptr2->set_exp(100.0);
	reflective_ptr2->set_ks(0.5);
	reflective_ptr2->set_cs(1, 1, 0);
	reflective_ptr2->set_kr(0.2);
	
	
	for (int j = 0; j < num_spheres; j++) {
		double xc = ring_radius * sin (j * delta_theta * PI / 180.0);
		double zc = ring_radius * cos (j * delta_theta * PI / 180.0);
		Point3D center(xc, 0, zc);
		
		ConvexPartSphere* top_half_ptr = new ConvexPartSphere(center, sphere_radius, 0, 360, 0, 90);
		top_half_ptr->set_material(phong_ptr1);
		add_object(top_half_ptr);
		
		ConvexPartSphere* bottom_half_ptr = new ConvexPartSphere(center, sphere_radius, 0, 360, 90, 180);
		bottom_half_ptr->set_material(reflective_ptr2);
		add_object(bottom_half_ptr);
	}
	

	// ground plane with checker
	
	Checker3D* checker3D_ptr = new Checker3D;
	checker3D_ptr->set_size(4.2); 
	checker3D_ptr->set_color1(white);    	
	checker3D_ptr->set_color2(0.5);
	
	SV_Matte* sv_matte_ptr = new SV_Matte;		
	sv_matte_ptr->set_ka(0.4);
	sv_matte_ptr->set_kd(0.6);
	sv_matte_ptr->set_cd(checker3D_ptr);
		
	Plane* plane_ptr = new Plane(Point3D(0, -4.5, 0), Normal(0, 1, 0)); 
	plane_ptr->set_material(sv_matte_ptr);
	add_object(plane_ptr);
}


