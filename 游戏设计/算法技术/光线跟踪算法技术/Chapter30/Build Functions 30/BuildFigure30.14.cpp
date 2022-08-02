// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


// This builds the scene for Figure 30.14 

// With the value of eps in Listing 30.2, there are minor shading anomalies
// particularly in Figure 30.14(c). Making eps smaller, eg eps = 0.0000001,
// fixes these, but re-introduces the shading problems in Figure 30.3.


void 												
World::build(void){
	int num_samples = 16;

	vp.set_hres(400);
	vp.set_vres(400);
	vp.set_samples(num_samples);
	
	background_color = RGBColor(0.5);
	tracer_ptr = new RayCast(this);	
			
	Pinhole* pinhole_ptr = new Pinhole;
	pinhole_ptr->set_eye(12, 15, 30);
	pinhole_ptr->set_lookat(0, 0, 0); 
	pinhole_ptr->set_view_distance(3500.0); 	  
	pinhole_ptr->compute_uvw();
	set_camera(pinhole_ptr);
			
	Directional* light_ptr = new Directional;
	light_ptr->set_direction(10, 10, 20);
	light_ptr->scale_radiance(3.5);
	add_light(light_ptr);
	
	Checker3D* checker_ptr = new Checker3D;
	checker_ptr->set_size(0.6708);	// For Figure 30.14(a)
//	checker_ptr->set_size(0.416);	// For Figure 30.14(b)
//	checker_ptr->set_size(0.3);		// For Figure 30.14(c)
	checker_ptr->set_color1(white);  	 
	checker_ptr->set_color2(black);
	
	SV_Matte* sv_matte_ptr = new SV_Matte;		
	sv_matte_ptr->set_ka(0.25);
	sv_matte_ptr->set_kd(0.6);
	sv_matte_ptr->set_cd(checker_ptr);
		
	double bottom 	= -0.9;
	double top 		= 0.9;
	double radius 	= 1.5;

	OpenCylinder* cylinder_ptr = new OpenCylinder(bottom, top, radius);
	cylinder_ptr->set_material(sv_matte_ptr);
	add_object(cylinder_ptr);
}


