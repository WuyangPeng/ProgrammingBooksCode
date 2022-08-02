// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


// This builds the scene for Figure 28.21(a)

void 												
World::build(void) {
	int num_samples = 25;
	
	vp.set_hres(600);
	vp.set_vres(600);
	vp.set_samples(num_samples);
	vp.set_max_depth(5);
	
	background_color = RGBColor(0.9, 0.9, 1);  // pale blue
	
	tracer_ptr = new Whitted(this);
	
	Ambient* ambient_ptr = new Ambient;
	ambient_ptr->scale_radiance(0.5);
	set_ambient_light(ambient_ptr);
	
		
	Pinhole* pinhole_ptr = new Pinhole;
	pinhole_ptr->set_eye(0, 1.5, 3); 
	pinhole_ptr->set_lookat(0.0); 
	pinhole_ptr->set_view_distance(495.0);	
	pinhole_ptr->compute_uvw();
	set_camera(pinhole_ptr);
	
		
	PointLight* light_ptr = new PointLight;
	light_ptr->set_location(10, 20, 20);
	light_ptr->scale_radiance(15.0);
	light_ptr->set_shadows(false);
	add_light(light_ptr);
	
	
	// matte sphere inside cube
		
	Matte* matte_ptr = new Matte;			
	matte_ptr->set_ka(0.5); 
	matte_ptr->set_kd(0.5);
	matte_ptr->set_cd(0.0, 0.25, 1.0); 	 
	
	Sphere*	sphere_ptr = new Sphere(Point3D(0.0, -0.25, -1.0), 0.5);
	sphere_ptr->set_material(matte_ptr); 
	add_object(sphere_ptr);
	
	
	// transparent cube
	
	RGBColor glass_color(0.64, 0.98, 0.88);	// light cyan
	
	Dielectric* glass_ptr = new Dielectric;
	glass_ptr->set_exp(2000.0);  
	glass_ptr->set_eta_in(1.5);					// glass
	glass_ptr->set_eta_out(1.0);				// air
	glass_ptr->set_cf_in(glass_color);
	glass_ptr->set_cf_out(white); 
	glass_ptr->set_shadows(false);
		
	Box* box_ptr = new Box(Point3D(-1.0), Point3D(1.0));
	box_ptr->set_material(glass_ptr);
	add_object(box_ptr);
		
	
	// plane
	
	Checker3D* checker_ptr = new Checker3D;
	checker_ptr->set_size(4.0); 
	checker_ptr->set_color1(1, 1, 0.4);    		// yellow
	checker_ptr->set_color2(1, 0.5, 0);   		// orange
	
	SV_Matte* sv_matte_ptr = new SV_Matte;		
	sv_matte_ptr->set_ka(0.5);
	sv_matte_ptr->set_kd(0.1);
	sv_matte_ptr->set_cd(checker_ptr);
	
	Plane* plane_ptr = new Plane(Point3D(0, -10.1, 0), Normal(0, 1, 0)); 
	plane_ptr->set_material(sv_matte_ptr);	
	add_object(plane_ptr);
}


