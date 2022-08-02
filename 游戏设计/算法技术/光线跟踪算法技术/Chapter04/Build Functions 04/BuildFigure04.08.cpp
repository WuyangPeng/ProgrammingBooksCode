// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

// This builds the scene for Figure 4.8
// The plane has a 3D checker texture. See Chapter 29 

void 												
World::build(void) {
	int num_samples = 1;  // use 1 for 4.8(a), 64 for 4.8(b)
	
	Jittered* sampler_ptr = new Jittered(num_samples);
	
	vp.set_hres(300);	  		
	vp.set_vres(200);
	vp.set_samples(num_samples);		// for 4.8(a) (one regular sample per pixel)
//	vp.set_sampler(sampler_ptr);		// for 4.8(b)	
	vp.set_max_depth(0);		
	
	background_color = RGBColor(0.25);
	
	Ambient* ambient_ptr = new Ambient;
	ambient_ptr->scale_radiance(1.0);
	set_ambient_light(ambient_ptr);
	
	tracer_ptr = new RayCast(this);
	
	Pinhole* pinhole_ptr = new Pinhole;
	pinhole_ptr->set_eye(100, 500, 100);   
	pinhole_ptr->set_lookat(0, 450, 0);    
	pinhole_ptr->set_view_distance(175);	
	pinhole_ptr->compute_uvw();     
	set_camera(pinhole_ptr);
	
	
	// directional light 
	
	Directional* light_ptr3 = new Directional;
	light_ptr3->set_direction(0, 1, 0); 
	light_ptr3->scale_radiance(4.0);
	light_ptr3->set_shadows(false);
	add_light(light_ptr3);
		
	
	// plane
		
	Checker3D* checker3D_ptr = new Checker3D;
	checker3D_ptr->set_size(250.0);
	checker3D_ptr->set_color1(black);  	
	checker3D_ptr->set_color2(white); 
	
	SV_Matte* sv_matte_ptr = new SV_Matte;		
	sv_matte_ptr->set_ka(0.5);
	sv_matte_ptr->set_kd(0.35);
	sv_matte_ptr->set_cd(checker3D_ptr);	
	
	Plane* plane_ptr = new Plane(Point3D(0.0), Normal(0.0, 1.0, 0.0));
	plane_ptr->set_material(sv_matte_ptr);
	add_object(plane_ptr);		
}




