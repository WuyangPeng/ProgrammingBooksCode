// 	Copyright (C) Kevin Suffern 2000-2008.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


// This builds the scene for Figure 31.38.

// This was re-rendered from scratch, and the instrinsic sandstone transformations 
// are different. 
// The cylinders are also slightly different. 
// There is no ground plane.

void 												
World::build(void) {
	int num_samples = 16;
	
	vp.set_hres(800);
	vp.set_vres(400);
	vp.set_samples(num_samples);
	
	Ambient* ambient_ptr = new Ambient;
	ambient_ptr->scale_radiance(0.5);
	set_ambient_light(ambient_ptr);
	
	background_color = black;
	tracer_ptr = new RayCast(this);
	
	
	Pinhole* pinhole_ptr = new Pinhole;
	pinhole_ptr->set_eye(0, 25, 50);
	pinhole_ptr->set_lookat(0.0); 
	pinhole_ptr->set_view_distance(5320.0); 
	pinhole_ptr->compute_uvw();
	set_camera(pinhole_ptr);
	
	
	PointLight* light_ptr = new PointLight;
	light_ptr->set_location(30, 40, 35); 
	light_ptr->scale_radiance(5.0);
	add_light(light_ptr);
	
	
	// noise parameters
	// gain = 0.5, lacunarity = 2.0 by default
	
	int 	num_octaves = 4;			
	float 	fbm_amount 	= 0.05; 
	

	// cylinder parameters
	
	double bottom 	= -1.75; 
	double top 		= 1.75; 
	double radius 	= 0.9;
	
	
	// far left cylinder:
	
	Image* image_ptr1 = new Image;						
	image_ptr1->read_ppm_file("sandstone_ramp1.ppm");
	
	TInstance* sandstone_ptr1 = new TInstance(new RampFBmTexture(image_ptr1, num_octaves, fbm_amount));
	sandstone_ptr1->scale(1.0, 2.0, 1.0);
	sandstone_ptr1->rotate_z(110.0);
	sandstone_ptr1->translate(1.0, 4.0, 0.0);
	
	SV_Matte* sv_matte_ptr1 = new SV_Matte;		
	sv_matte_ptr1->set_ka(0.35);
	sv_matte_ptr1->set_kd(0.75);
	sv_matte_ptr1->set_cd(sandstone_ptr1);
	
	Instance* cylinder_ptr1 = new Instance(new SolidCylinder(bottom, top, radius)); 
	cylinder_ptr1->set_material(sv_matte_ptr1);
	cylinder_ptr1->rotate_y(-30);
	cylinder_ptr1->translate(-3.0, 0.0, 0.0);
	add_object(cylinder_ptr1);
	
	
	// left middle cylinder:
	
	Image* image_ptr2 = new Image;						
	image_ptr2->read_ppm_file("sandstone_ramp2.ppm");
	
	TInstance* sandstone_ptr2 = new TInstance(new RampFBmTexture(image_ptr2, num_octaves, fbm_amount));
	sandstone_ptr2->scale(1.0, 2.0, 1.0);
	sandstone_ptr2->rotate_z(110.0);
	sandstone_ptr2->translate(0.5, 0.0, 0.0);
	
	SV_Matte* sv_matte_ptr2 = new SV_Matte;		
	sv_matte_ptr2->set_ka(0.35);
	sv_matte_ptr2->set_kd(0.75);
	sv_matte_ptr2->set_cd(sandstone_ptr2);
	
	Instance* cylinder_ptr2 = new Instance(new SolidCylinder(bottom, top, radius)); 
	cylinder_ptr2->set_material(sv_matte_ptr2);
	cylinder_ptr2->rotate_y(-30);
	cylinder_ptr2->translate(-1.0, 0.0, 0.0);
	add_object(cylinder_ptr2);
	
	
	// right middle cylinder:
	
	Image* image_ptr3 = new Image;						
	image_ptr3->read_ppm_file("sandstone_ramp3.ppm");
	
	TInstance* sandstone_ptr3 = new TInstance(new RampFBmTexture(image_ptr3, num_octaves, fbm_amount));
	sandstone_ptr3->scale(1.0, 2.0, 1.0);
	sandstone_ptr3->rotate_z(110.0);
	sandstone_ptr3->translate(0.5, -2.0, 0.0);
	
	
	SV_Matte* sv_matte_ptr3 = new SV_Matte;		
	sv_matte_ptr3->set_ka(0.35);
	sv_matte_ptr3->set_kd(0.75);
	sv_matte_ptr3->set_cd(sandstone_ptr3);
	
	Instance* cylinder_ptr3 = new Instance(new SolidCylinder(bottom, top, radius)); 
	cylinder_ptr3->set_material(sv_matte_ptr3);
	cylinder_ptr3->rotate_y(-30);
	cylinder_ptr3->translate(1.0, 0.0, 0.0);
	add_object(cylinder_ptr3);
	
	
	// far right cylinder:
	
	Image* image_ptr4 = new Image;						
	image_ptr4->read_ppm_file("sandstone_ramp4.ppm");
	
	TInstance* sandstone_ptr4 = new TInstance(new RampFBmTexture(image_ptr4, num_octaves, fbm_amount));
	sandstone_ptr4->scale(1.0, 2.0, 1.0);
	sandstone_ptr4->rotate_z(110.0);
	sandstone_ptr4->translate(0.0, -1.0, 0.0);
	
	
	SV_Matte* sv_matte_ptr4 = new SV_Matte;		
	sv_matte_ptr4->set_ka(0.35);
	sv_matte_ptr4->set_kd(0.75);
	sv_matte_ptr4->set_cd(sandstone_ptr4);
	
	Instance* cylinder_ptr4 = new Instance(new SolidCylinder(bottom, top, radius)); 
	cylinder_ptr4->set_material(sv_matte_ptr4);
	cylinder_ptr4->rotate_y(-30);
	cylinder_ptr4->translate(3.0, 0.0, 0.0);
	add_object(cylinder_ptr4);
}


