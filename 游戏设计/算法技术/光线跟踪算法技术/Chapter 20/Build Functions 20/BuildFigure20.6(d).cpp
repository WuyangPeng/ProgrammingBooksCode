// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

// This builds the scene for Figure 20.6(d)

void 												
World::build(void) {
	int num_samples = 25;
	
	vp.set_hres(600);	  		
	vp.set_vres(600);
	vp.set_samples(num_samples);
	
	tracer_ptr = new RayCast(this);
	
	Pinhole* pinhole_ptr = new Pinhole;
	pinhole_ptr->set_eye(60, 40, 80);
	pinhole_ptr->set_lookat(0.0);
	pinhole_ptr->set_view_distance(12000); 
	pinhole_ptr->compute_uvw();
	set_camera(pinhole_ptr);
		
	PointLight* light_ptr = new PointLight;
	light_ptr->set_location(100, 100, 60);
	light_ptr->scale_radiance(3.0);
	light_ptr->set_shadows(true);
	add_light(light_ptr);
	
	SphereChecker* checker_ptr = new SphereChecker;
	checker_ptr->set_num_vertical(45);
	checker_ptr->set_num_horizontal(20);
	checker_ptr->set_vertical_line_width(0.1);
	checker_ptr->set_horizontal_line_width(0.1);
	checker_ptr->set_color1(white);
	checker_ptr->set_color2(white);
	checker_ptr->set_line_color(black);
			
	SV_Matte* sv_matte_ptr = new SV_Matte;						
	sv_matte_ptr->set_ka(0.2);    
	sv_matte_ptr->set_kd(0.6);
	sv_matte_ptr->set_cd(checker_ptr);
	
	Sphere* sphere_ptr = new Sphere;
	sphere_ptr->set_material(sv_matte_ptr);
	
	Instance* ellipsoid_ptr = new Instance(sphere_ptr);
	ellipsoid_ptr->scale(2.5, 0.25, 2.5);   
	add_object(ellipsoid_ptr);
}

