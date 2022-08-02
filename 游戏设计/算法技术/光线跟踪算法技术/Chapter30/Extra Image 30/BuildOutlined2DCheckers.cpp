// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


// This builds a sphere, cylinder, cone, box and plane with 2D checker textures.
// These textures can only be applied to generic objects.
// In this figure all checkers are rendered with colored outlines. 

void 												
World::build(void) {
	int num_samples = 16;
	
	vp.set_hres(880);
	vp.set_vres(300);
	vp.set_samples(num_samples);
	
	tracer_ptr = new RayCast(this);
	background_color = RGBColor(0.5);
	
	Pinhole* pinhole_ptr = new Pinhole;
	pinhole_ptr->set_eye(100, 100, 300); 
	pinhole_ptr->set_lookat(-0.2, 1.0, 0);  
	pinhole_ptr->set_view_distance(12000.0);              
	pinhole_ptr->compute_uvw();     
	set_camera(pinhole_ptr); 
	
	Directional* light_ptr1 = new Directional;
	light_ptr1->set_direction(0, 0, 1);
	light_ptr1->scale_radiance(1.5);
	add_light(light_ptr1);
	
	// sphere
	
	SphereChecker* sphere_checker_ptr = new SphereChecker;
	sphere_checker_ptr->set_num_horizontal_checkers(16);
	sphere_checker_ptr->set_num_vertical_checkers(8);
	sphere_checker_ptr->set_horizontal_line_width(0.1);
	sphere_checker_ptr->set_vertical_line_width(0.25);
	sphere_checker_ptr->set_color1(white);
	sphere_checker_ptr->set_color2(black);
	sphere_checker_ptr->set_line_color(red);
	
	SV_Matte* sv_matte_ptr1 = new SV_Matte;		
	sv_matte_ptr1->set_ka(0.75);
	sv_matte_ptr1->set_kd(0.75);
	sv_matte_ptr1->set_cd(sphere_checker_ptr);
	
	Instance* sphere_ptr = new Instance(new Sphere);
	sphere_ptr->set_material(sv_matte_ptr1);
	sphere_ptr->scale(2.5);
	sphere_ptr->translate(-9.5, -1, 0);
	add_object(sphere_ptr);

	
	// cylinder
	
	// This must be built out of separate parts so that we can have different textures 
	// on the top, bottom, and curved surfaces
	
	// material for the curved surface
		
	CylinderChecker* cylinder_checker_ptr = new CylinderChecker;
	cylinder_checker_ptr->set_num_horizontal_checkers(12);
	cylinder_checker_ptr->set_num_vertical_checkers(6);
	cylinder_checker_ptr->set_horizontal_line_width(0.1);
	cylinder_checker_ptr->set_vertical_line_width(0.2);
	cylinder_checker_ptr->set_color1(white);
	cylinder_checker_ptr->set_color2(black);
	cylinder_checker_ptr->set_line_color(red);
	
	SV_Matte* sv_matte_ptr2 = new SV_Matte;		
	sv_matte_ptr2->set_ka(0.75);
	sv_matte_ptr2->set_kd(0.75);
	sv_matte_ptr2->set_cd(cylinder_checker_ptr);
	
	OpenCylinder* curved_surface_ptr = new OpenCylinder;
	curved_surface_ptr->set_material(sv_matte_ptr2);
	
	
	// material for the top surface
	
	DiskChecker* disk_checker_ptr = new DiskChecker;
	disk_checker_ptr->set_num_angular_checkers(12);     
	disk_checker_ptr->set_num_radial_checkers(3);
	disk_checker_ptr->set_angular_line_width(0.1);
	disk_checker_ptr->set_radial_line_width(0.2);
	disk_checker_ptr->set_color1(white);
	disk_checker_ptr->set_color2(black);
	disk_checker_ptr->set_line_color(green);
	
	SV_Matte* sv_matte_ptr5 = new SV_Matte;		
	sv_matte_ptr5->set_ka(0.75);
	sv_matte_ptr5->set_kd(0.75);
	sv_matte_ptr5->set_cd(disk_checker_ptr);
	
	Instance* top_ptr = new Instance(new Disk);
	top_ptr->set_material(sv_matte_ptr5);
	top_ptr->translate(0, 1, 0);
	
	// I haven't included the bottom of the cylinder
	
	Compound* generic_cylinder_ptr = new Compound;
	generic_cylinder_ptr->add_object(curved_surface_ptr);
	generic_cylinder_ptr->add_object(top_ptr);	

	Instance* cylinder_ptr = new Instance(generic_cylinder_ptr);
	cylinder_ptr->scale(1.95, 2.95, 1.95); 
	cylinder_ptr->translate(-3.5, 0.5, 0);   
	add_object(cylinder_ptr);
	

	// cone
	
	ConeChecker* cone_checker_ptr = new ConeChecker;
	cone_checker_ptr->set_num_horizontal_checkers(12);
	cone_checker_ptr->set_num_vertical_checkers(8);
	cone_checker_ptr->set_horizontal_line_width(0.25);
	cone_checker_ptr->set_vertical_line_width(0.1);
	cone_checker_ptr->set_color1(white);
	cone_checker_ptr->set_color2(black);
	cone_checker_ptr->set_line_color(red);
		
	SV_Matte* sv_matte_ptr3 = new SV_Matte;		
	sv_matte_ptr3->set_ka(0.75);
	sv_matte_ptr3->set_kd(0.75);
	sv_matte_ptr3->set_cd(cone_checker_ptr);
	
	// I haven't included the bottom of the cone
	
	Instance* cone_ptr = new Instance(new OpenCone);
	cone_ptr->set_material(sv_matte_ptr3);
	cone_ptr->scale(2.5);
	cone_ptr->translate(2.35, -1.5, 0);
	add_object(cone_ptr);

	
	// box
	
	// This has to have a separate Rectangle object for each face.
	// A default rectangle is (x, z) in the set [-1, 1] X [-1, 1], y = 0.
	
	// We need separate checker textures on each face to make the colors and the
	// line thicknesses match up
	
	
	// front (+ve z) face
	
	RectangleChecker* rectangle_checker_ptr1 = new RectangleChecker;
	rectangle_checker_ptr1->set_num_x_checkers(4);
	rectangle_checker_ptr1->set_num_z_checkers(4);
	rectangle_checker_ptr1->set_x_line_width(0.15);
	rectangle_checker_ptr1->set_z_line_width(0.25);
	rectangle_checker_ptr1->set_color1(white);
	rectangle_checker_ptr1->set_color2(black);
	rectangle_checker_ptr1->set_line_color(red);
		
	SV_Matte* sv_matte_ptr4 = new SV_Matte;		
	sv_matte_ptr4->set_ka(0.75);
	sv_matte_ptr4->set_kd(0.75);
	sv_matte_ptr4->set_cd(rectangle_checker_ptr1);
		
	Instance* front_face_ptr = new Instance(new Rectangle);
	front_face_ptr->set_material(sv_matte_ptr4);
	front_face_ptr->rotate_x(90);
	front_face_ptr->translate(0, 0, 1);
	
	
	// top (+ve y) face
		
	RectangleChecker* rectangle_checker_ptr2 = new RectangleChecker;
	rectangle_checker_ptr2->set_num_x_checkers(4);
	rectangle_checker_ptr2->set_num_z_checkers(4);
	rectangle_checker_ptr2->set_x_line_width(0.15);
	rectangle_checker_ptr2->set_z_line_width(0.15);
	rectangle_checker_ptr2->set_color1(black);
	rectangle_checker_ptr2->set_color2(white);
	rectangle_checker_ptr2->set_line_color(green);
		
	SV_Matte* sv_matte_ptr6 = new SV_Matte;		
	sv_matte_ptr6->set_ka(0.75);
	sv_matte_ptr6->set_kd(0.75);
	sv_matte_ptr6->set_cd(rectangle_checker_ptr2);
		
	Instance* top_face_ptr = new Instance(new Rectangle);
	top_face_ptr->set_material(sv_matte_ptr6);
	top_face_ptr->translate(0, 1, 0);
	
	
	// right (+ve x) face
	
	RectangleChecker* rectangle_checker_ptr3 = new RectangleChecker;
	rectangle_checker_ptr3->set_num_x_checkers(4);
	rectangle_checker_ptr3->set_num_z_checkers(4);
	rectangle_checker_ptr3->set_x_line_width(0.25);
	rectangle_checker_ptr3->set_z_line_width(0.15);
	rectangle_checker_ptr3->set_color1(white);
	rectangle_checker_ptr3->set_color2(black);
	rectangle_checker_ptr3->set_line_color(blue);
		
	SV_Matte* sv_matte_ptr7 = new SV_Matte;		
	sv_matte_ptr7->set_ka(0.75);
	sv_matte_ptr7->set_kd(0.75);
	sv_matte_ptr7->set_cd(rectangle_checker_ptr3);
	
	Instance* right_face_ptr = new Instance(new Rectangle);
	right_face_ptr->set_material(sv_matte_ptr7);
	right_face_ptr->rotate_z(-90);
	right_face_ptr->translate(1, 0, 0);
	
	
	// you can construct the left, back, and bottom faces in a similar way
	
	Compound* generic_box_ptr = new Compound;
	generic_box_ptr->add_object(front_face_ptr);
	generic_box_ptr->add_object(top_face_ptr);
	generic_box_ptr->add_object(right_face_ptr);	
	
	Instance* box_ptr = new Instance(generic_box_ptr);
	box_ptr->scale(2.0); 
	box_ptr->translate(9, 1, 0);  
	add_object(box_ptr);
	
	
	
	// ground plane
		
	PlaneChecker* plane_checker_ptr = new PlaneChecker;
	plane_checker_ptr->set_size(1.5); 
	plane_checker_ptr->set_outline_width(0.1);
	plane_checker_ptr->set_color1(0.35);
	plane_checker_ptr->set_color2(0.5);
	plane_checker_ptr->set_outline_color(yellow);
		
	SV_Matte* sv_matte_ptr8 = new SV_Matte;		
	sv_matte_ptr8->set_ka(0.75);
	sv_matte_ptr8->set_kd(0.75);
	sv_matte_ptr8->set_cd(plane_checker_ptr);
	
	Instance* plane_ptr = new Instance(new Plane); // a generic plane is the (x, z) plane
	plane_ptr->set_material(sv_matte_ptr8);
	plane_ptr->translate(0, -4.5, 0);  
	add_object(plane_ptr);
}


