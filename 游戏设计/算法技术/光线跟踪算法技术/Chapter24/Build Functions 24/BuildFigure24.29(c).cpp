// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

// This builds the scene for Figure 24.29(c)
// panoramic is declared in LightProbe.h, which is #included in World.h

void 												
World::build(void) {
	int num_samples = 1;
	
	vp.set_hres(600);			
	vp.set_vres(600); 
	vp.set_samples(num_samples);
	vp.set_max_depth(1);
	
	tracer_ptr = new Whitted(this);	
	
	Pinhole* pinhole_ptr = new Pinhole;
	pinhole_ptr->set_eye(100, -15, 500); 
	pinhole_ptr->set_lookat(0, -15, 0);	
	pinhole_ptr->set_view_distance(800);	
	pinhole_ptr->compute_uvw(); 
	set_camera(pinhole_ptr);
	
		
	Reflective* reflective_ptr = new Reflective;			
	reflective_ptr->set_ka(0.0); 
	reflective_ptr->set_kd(0.0);
	reflective_ptr->set_ks(0.0);
	reflective_ptr->set_cd(0.0);
	reflective_ptr->set_kr(0.9);
	reflective_ptr->set_cr(1.0, 0.75, 0.25);  // orange

	
	// beveled box
	
	Point3D p0(-100);
	Point3D p1(100);	
	double bevel_radius = 50;
	
	BeveledBox* beveled_box_ptr = new BeveledBox(p0, p1, bevel_radius);	
	beveled_box_ptr->set_material(reflective_ptr);

	Instance* rotated_beveled_box_ptr = new Instance(beveled_box_ptr);
	rotated_beveled_box_ptr->rotate_y(-20);
	rotated_beveled_box_ptr->rotate_x(39);
	add_object(rotated_beveled_box_ptr);
	
	
	// large sphere with Uffizi image
	
	Image* image_ptr = new Image;
	image_ptr->read_ppm_file("uffizi_probe_small.ppm");   // for testing 
//	image_ptr->read_ppm_file("uffizi_probe_large.ppm");   // for production
	
	LightProbe* light_probe_ptr = new LightProbe; 
	light_probe_ptr->set_map_type(panoramic);      		
	
	ImageTexture* texture_ptr = new ImageTexture(image_ptr); 
	texture_ptr->set_mapping(light_probe_ptr);
	
	SV_Matte* sv_matte_ptr = new SV_Matte;
	sv_matte_ptr->set_ka(1.0);
	sv_matte_ptr->set_kd(0.85);
	sv_matte_ptr->set_cd(texture_ptr);
	
	Sphere* unit_sphere_ptr = new Sphere;
	unit_sphere_ptr->set_shadows(false);	
	
	Instance* sphere_ptr = new Instance(unit_sphere_ptr); 
	sphere_ptr->set_material(sv_matte_ptr);
	sphere_ptr->scale(1000000.0);
	add_object(sphere_ptr);
}


