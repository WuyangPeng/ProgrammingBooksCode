// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

// This builds the Scene for Figure 24.34
// Texture mapping is discussed in Chapter 29
// panoramic is declared in LightProbe.h, which is #included in World.h

#include "Maths.h"

void 												
World::build(void) {
	int num_samples = 16;
	
	vp.set_hres(600);			
	vp.set_vres(600);  
	vp.set_samples(num_samples);
	vp.set_pixel_size(1.0);
	vp.set_max_depth(1);
	
	tracer_ptr = new Whitted(this);		
			
	Pinhole* pinhole_ptr = new Pinhole;
	pinhole_ptr->set_eye(400, 125, 500);   
	pinhole_ptr->set_lookat(0.0, -50, 0);
	pinhole_ptr->set_view_distance(550);
	pinhole_ptr->compute_uvw(); 
	set_camera(pinhole_ptr);
	
	
	Compound* spheres = new Compound;
		
	float  kr = 0.9;
	double radius = 100.0;
	
	// reflective sphere centered at the origin

	Reflective* reflective_ptrc = new Reflective;			
	reflective_ptrc->set_ka(0.0); 
	reflective_ptrc->set_kd(0.0);
	reflective_ptrc->set_ks(0.0);
	reflective_ptrc->set_cd(0.0);
	reflective_ptrc->set_kr(kr);
	reflective_ptrc->set_cr(0.65, 0.75, 1.0);   // pale blue
		
	Sphere* sphere_ptr = new Sphere(Point3D(0.0), radius);
	sphere_ptr->set_shadows(false);
	sphere_ptr->set_material(reflective_ptrc);
	spheres->add_object(sphere_ptr);
	
	// define materials for the surrounding spheres
	
	vector<Reflective*> materials;	
	
	Reflective* reflective_ptr0 = new Reflective;			
	reflective_ptr0->set_ka(0.0); 
	reflective_ptr0->set_kd(0.0);
	reflective_ptr0->set_ks(0.0);
	reflective_ptr0->set_cd(0.0);
	reflective_ptr0->set_kr(kr);
	reflective_ptr0->set_cr(0.5, 1.0, 0.5);  // light green
	materials.push_back(reflective_ptr0);

	Reflective* reflective_ptr1 = new Reflective;			
	reflective_ptr1->set_ka(0.0); 
	reflective_ptr1->set_kd(0.0);
	reflective_ptr1->set_ks(0.0);
	reflective_ptr1->set_cd(0.0);
	reflective_ptr1->set_kr(kr);
	reflective_ptr1->set_cr(0.4, 1.0, 1.0);  // cyan
	materials.push_back(reflective_ptr1);
	
	Reflective* reflective_ptr2 = new Reflective;			
	reflective_ptr2->set_ka(0.0); 
	reflective_ptr2->set_kd(0.0);
	reflective_ptr2->set_ks(0.0);
	reflective_ptr2->set_cd(0.0);
	reflective_ptr2->set_kr(kr);
	reflective_ptr2->set_cr(1.0, 1.0, 0.4);  // lemon
	materials.push_back(reflective_ptr2);
	
	Reflective* reflective_ptr3 = new Reflective;			
	reflective_ptr3->set_ka(0.0); 
	reflective_ptr3->set_kd(0.0);
	reflective_ptr3->set_ks(0.0);
	reflective_ptr3->set_cd(0.0);
	reflective_ptr3->set_kr(kr);
	reflective_ptr3->set_cr(1.0, 0.5, 1.0);  // mauve
	materials.push_back(reflective_ptr3);
	
	Reflective* reflective_ptr4 = new Reflective;			
	reflective_ptr4->set_ka(0.0); 
	reflective_ptr4->set_kd(0.0);
	reflective_ptr4->set_ks(0.0);
	reflective_ptr4->set_cd(0.0);
	reflective_ptr4->set_kr(kr);
	reflective_ptr4->set_cr(1.0, 0.75, 0.25);  // orange
	materials.push_back(reflective_ptr4);
	
	Reflective* reflective_ptr5 = new Reflective;			
	reflective_ptr5->set_ka(0.0); 
	reflective_ptr5->set_kd(0.0);
	reflective_ptr5->set_ks(0.0);
	reflective_ptr5->set_cd(0.0);
	reflective_ptr5->set_kr(kr);
	reflective_ptr5->set_cr(0.5, 0.5, 1.0);  // blue
	materials.push_back(reflective_ptr5);
	

	// define ring of reflective spheres that just touch the center sphere
	// these are initially in the (x, z) plane
	
	float  num_spheres = 6;
	double theta = 0.0;
	double delta_theta = 2.0 * PI / num_spheres;
	
	for (int j = 0; j < num_spheres; j++) {
		Point3D center((2.0 * radius) * sin(theta), 0.0, (2.0 * radius) * cos(theta));
		Sphere* sphere_ptr = new Sphere(center, radius);
		sphere_ptr->set_material(materials[j]);
		spheres->add_object(sphere_ptr);
		theta += delta_theta;
	}
		
	// now rotate the spheres

	Instance* rotated_spheres_ptr = new Instance(spheres);
	rotated_spheres_ptr->rotate_x(40.0);
	rotated_spheres_ptr->rotate_z(-40.0);
	add_object(rotated_spheres_ptr);

	
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
	
	Instance* sphere_ptr1 = new Instance(unit_sphere_ptr); 
	sphere_ptr1->set_material(sv_matte_ptr);
	sphere_ptr1->scale(1000000.0);
	add_object(sphere_ptr1);
}


