// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

// This builds the scene for Figure 25.7

void 												
World::build(void) {
	int num_samples = 100;
	
	vp.set_hres(400);	  		
	vp.set_vres(400);
	vp.set_samples(num_samples);
	vp.set_max_depth(1);

	background_color = RGBColour(0.8, 0.9, 1);   // light blue
	
	tracer_ptr = new AreaLighting(this);	 
	
	Ambient* ambient_ptr = new Ambient;	
	ambient_ptr->scale_radiance(0.5);
	set_ambient_light(ambient_ptr);
	
	Pinhole* pinhole_ptr = new Pinhole;	
	pinhole_ptr->set_eye(0, 0, 20);     	
	pinhole_ptr->set_view_distance(3500); 
	pinhole_ptr->set_lookat(0);		
	pinhole_ptr->compute_uvw();     
	set_camera(pinhole_ptr);
	
	
	// glossy reflector sphere	
	
	float exp = 1.0;  
	
	GlossyReflector* glossy_ptr = new GlossyReflector;
	glossy_ptr->set_samples(num_samples, exp);			
	glossy_ptr->set_ka(0.0); 
	glossy_ptr->set_kd(0.0);
	glossy_ptr->set_ks(0.0);
	glossy_ptr->set_exp(exp);
	glossy_ptr->set_cd(black);
	glossy_ptr->set_kr(0.8);
	glossy_ptr->set_exponent(exp);
	glossy_ptr->set_cr(white); 
	
	Sphere* sphere_ptr = new Sphere;  
	sphere_ptr->set_material(glossy_ptr);
	add_object(sphere_ptr);
}


