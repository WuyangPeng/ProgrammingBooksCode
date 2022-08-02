// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


// This builds the scene for Figure 28.7

void 												
World::build(void) {
	int num_samples = 25;
	
	vp.set_hres(600);      
	vp.set_vres(600);
	vp.set_max_depth(3);
	vp.set_samples(num_samples);
	
	background_color = RGBColor(0.5, 0.6666, 0.5);  // light green
	
	tracer_ptr = new Whitted(this);	

	FishEye* fisheye_ptr = new FishEye;
	fisheye_ptr->set_eye(0.0, 0.1, 0.0);
	fisheye_ptr->set_lookat(0, 10, 0);
	fisheye_ptr->set_rectangular(true);
	fisheye_ptr->set_field_of_view(265.0);
	fisheye_ptr->compute_uvw();  
	set_camera(fisheye_ptr);
	
		
	Directional* light_ptr1 = new Directional; 
	light_ptr1->set_direction(0, 1, 0);
	light_ptr1->scale_radiance(5.0);
	light_ptr1->set_shadows(false);
	add_light(light_ptr1);
	
	
	Transparent* glass_ptr = new Transparent;
	glass_ptr->set_ks(0.0);
	glass_ptr->set_exp(1.0);
	glass_ptr->set_ior(1.5);			
	glass_ptr->set_kr(0.1);     
	glass_ptr->set_kt(0.9);   
	
	Dielectric* dielectric_ptr = new Dielectric;
	dielectric_ptr->set_cd(0);
	dielectric_ptr->set_ka(0.0);
	dielectric_ptr->set_kd(0.0);
	dielectric_ptr->set_ks(0.0);
	dielectric_ptr->set_exp(1.0);
	dielectric_ptr->set_eta_in(1.5);
	dielectric_ptr->set_eta_out(1.0);
	
	double radius 	= 250.0;
	double bottom 	= 10.0;
	double top 		= 10.1;
	SolidCylinder* cylinder_ptr = new SolidCylinder(bottom, top, radius);
	cylinder_ptr->set_material(glass_ptr);				// for Figure 28.7(a)
//	cylinder_ptr->set_material(dielectric_ptr);			// for Figure 28.7(b)
	add_object(cylinder_ptr);
	
	
	// plane with checker
	
	Checker3D* checker_ptr = new Checker3D;
	checker_ptr->set_size(10.0);
	checker_ptr->set_color1(black);  
	checker_ptr->set_color2(1.0, 0.7, 0.2);  // orange	
	
	SV_Matte* sv_matte_ptr5 = new SV_Matte;		
	sv_matte_ptr5->set_ka(0.25);
	sv_matte_ptr5->set_kd(0.5);
	sv_matte_ptr5->set_cd(checker_ptr);

	Plane* plane_ptr2 = new Plane(Point3D(0.0), Normal(0, 1, 0));
	plane_ptr2->set_material(sv_matte_ptr5);
	plane_ptr2->set_shadows(false);
	add_object(plane_ptr2);	
}


