// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


// This builds the scene for Figure 30.2

void 												
World::build(void) {
	int num_samples = 16;
	
	vp.set_hres(880);
	vp.set_vres(300);
	vp.set_samples(num_samples);
	
	tracer_ptr = new RayCast(this);
	background_color = RGBColor(0.5);
	
	Pinhole* pinholePtr = new Pinhole;
	pinholePtr->set_eye(100, 100, 300); 
	pinholePtr->set_lookat(-0.2, 1.0, 0); 
	pinholePtr->set_vpd(12000.0);              
	pinholePtr->compute_uvw();     
	set_camera(pinholePtr); 
	
	Directional* light_ptr = new Directional;
	light_ptr->set_direction(0, 0, 1);
	light_ptr->scale_radiance(1.5);
	add_light(light_ptr);
	
	
	// sphere
	
	Checker3D* checker_pt1 = new Checker3D;
	checker_pt1->set_size(1.0);
	checker_pt1->set_color1(black);
	checker_pt1->set_color2(white);
	
	SV_Matte* sv_matte_ptr1 = new SV_Matte;		
	sv_matte_ptr1->set_ka(0.75);
	sv_matte_ptr1->set_kd(0.75);
	sv_matte_ptr1->set_cd(checker_pt1);
	
	Sphere* sphere_ptr = new Sphere(Point3D(-9.5, -1, 0), 2.5);
	sphere_ptr->set_material(sv_matte_ptr1);
	add_object(sphere_ptr);
	
	
	// cylinder
	
	Checker3D* checker_ptr2 = new Checker3D;
	checker_ptr2->set_size(1.0);
	checker_ptr2->set_color1(black);
	checker_ptr2->set_color2(white);
	
	SV_Matte* sv_matte_ptr2 = new SV_Matte;		
	sv_matte_ptr2->set_ka(0.75);
	sv_matte_ptr2->set_kd(0.75);
	sv_matte_ptr2->set_cd(checker_ptr2);

	Instance* cylinder_ptr = new Instance(new SolidCylinder(-2.5, 4.0, 1.95)); 
	cylinder_ptr->translate(-3.5, 0, 0);
	cylinder_ptr->transform_texture(false);
	cylinder_ptr->set_material(sv_matte_ptr2);
	add_object(cylinder_ptr);


	// cone
	
	Checker3D* checker_ptr3 = new Checker3D;
	checker_ptr3->set_size(1.0);
	checker_ptr3->set_color1(black);
	checker_ptr3->set_color2(white);
	
	SV_Matte* sv_matte_ptr3 = new SV_Matte;		
	sv_matte_ptr3->set_ka(0.75);
	sv_matte_ptr3->set_kd(0.75);
	sv_matte_ptr3->set_cd(checker_ptr3);
	
	Instance* cone_ptr = new Instance(new OpenCone);
	cone_ptr->scale(2.5);  
	cone_ptr->translate(2.35, -1.5, 0);
	cone_ptr->transform_texture(false);
	cone_ptr->set_material(sv_matte_ptr3);
	add_object(cone_ptr);
	
	
	// box
	
	Checker3D* checker_ptr4 = new Checker3D;
	checker_ptr4->set_size(1.0);
	checker_ptr4->set_color1(black);
	checker_ptr4->set_color2(white);
	
	SV_Matte* sv_matte_ptr4 = new SV_Matte;		
	sv_matte_ptr4->set_ka(0.75);
	sv_matte_ptr4->set_kd(0.75);
	sv_matte_ptr4->set_cd(checker_ptr4);

	Box* box_ptr = new Box(Point3D(7, -1.0, -2), Point3D(11, 3, 2));
	box_ptr->set_material(sv_matte_ptr4);
	add_object(box_ptr);
	
	
	// ground plane
	
	Checker3D* checker_ptr5 = new Checker3D;
	checker_ptr5->set_size(1.5);
	checker_ptr5->set_color1(0.35);
	checker_ptr5->set_color2(0.5);
		
	SV_Matte* sv_matte_ptr5 = new SV_Matte;		
	sv_matte_ptr5->set_ka(0.75);
	sv_matte_ptr5->set_kd(0.75);
	sv_matte_ptr5->set_cd(checker_ptr5);

	Plane* plane_ptr = new Plane(Point3D(0, -4.5, 0), Normal(0, 1, 0));
	plane_ptr->set_material(sv_matte_ptr5);
	add_object(plane_ptr);
}


