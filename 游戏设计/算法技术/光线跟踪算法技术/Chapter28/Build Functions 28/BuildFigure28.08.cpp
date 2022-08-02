// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


// This builds the scene for Figure 28.8

void 												
World::build(void) {
	int num_samples = 9;
	
	vp.set_hres(400);	  		
	vp.set_vres(400);
	vp.set_max_depth(6);   // depth 6 is necessary to get rays through the three cylinders
	vp.set_pixel_size(0.012);
	vp.set_samples(num_samples);
	
	background_color = black;
	
	tracer_ptr = new Whitted(this);
	
	
	// camera looks down y axis because disks have vertical axes	
	
	Orthographic* orthographic_ptr = new Orthographic;
	orthographic_ptr->set_eye(0.23, 100, 0);    
	orthographic_ptr->set_lookat(0.23, 0, 0);  
	orthographic_ptr->compute_uvw();     
	set_camera(orthographic_ptr);

	
	// top cylinder (in image)
	
	double top1 = 0.5;
	double bottom1 = 0.0;
	double radius = 1.25;
	
	RGBColor glass_color1(0, 1, 1);    // cyan
	
	Dielectric* glass_ptr1 = new Dielectric;
	glass_ptr1->set_eta_in(1.5);		// glass
	glass_ptr1->set_eta_out(1.0);		// air
	glass_ptr1->set_cf_in(glass_color1);
	glass_ptr1->set_cf_out(white); 
	
	Instance* cylinder_ptr1 = new Instance (new SolidCylinder(top1, bottom1, radius)); 
	cylinder_ptr1->translate(1, 0, 0);
	cylinder_ptr1->set_material(glass_ptr1);
	add_object(cylinder_ptr1);	
	
	
	// left cylinder
	
	double top2 = 1.5;
	double bottom2 = 1;
	
	RGBColor glass_color2(1, 1, 0);   // yellow
	
	Dielectric* glass_ptr2 = new Dielectric;
	glass_ptr2->set_eta_in(1.5);		// glass
	glass_ptr2->set_eta_out(1.0);		// air
	glass_ptr2->set_cf_in(glass_color2);
	glass_ptr2->set_cf_out(white); 
	
	Instance* cylinder_ptr2 = new Instance (new SolidCylinder(top2, bottom2, radius)); 
	cylinder_ptr2->translate(-0.5, 0, -0.866);
	cylinder_ptr2->set_material(glass_ptr2);
	add_object(cylinder_ptr2);	
	
	
	// right cylinder
	
	double top3 = 2.5;
	double bottom3 = 2;
	
	RGBColor glass_color3(1, 0, 1);    // majenta
	
	Dielectric* glass_ptr3 = new Dielectric;
	glass_ptr3->set_eta_in(1.5);		// glass
	glass_ptr3->set_eta_out(1.0);		// air
	glass_ptr3->set_cf_in(glass_color3);
	glass_ptr3->set_cf_out(white); 
	
	Instance* cylinder_ptr3 = new Instance (new SolidCylinder(top3, bottom3, radius)); 
	cylinder_ptr3->translate(-0.5, 0, 0.866);
	cylinder_ptr3->set_material(glass_ptr3);
	add_object(cylinder_ptr3);	
	
	
	// white plane below disks
	
	Emissive* emissive_ptr = new Emissive;
	emissive_ptr->scale_radiance(1.0);		// default
	emissive_ptr->set_ce(white);			// default
	
	Plane* plane_ptr = new Plane(Point3D(0, -1, 0), Normal(0, 1, 0)); 
	plane_ptr->set_material(emissive_ptr);
	add_object(plane_ptr);		
}

