// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


// This builds the scene for Figure 27.30

// Since I've lost the original build function, the camera is in a slightly different 
// location, and this affects the refraction

void 												
World::build(void){
	int num_samples = 16;
	
	vp.set_hres(600);	  		
	vp.set_vres(600);
	vp.set_samples(num_samples);		
	vp.set_max_depth(5);		
	
	background_color = RGBColor(0.0, 0.3, 0.25);
	
	tracer_ptr = new Whitted(this);
	
	Ambient* ambient_ptr = new Ambient;
	ambient_ptr->scale_radiance(0.25);
	set_ambient_light(ambient_ptr);
		
	Pinhole* pinhole_ptr = new Pinhole;
	pinhole_ptr->set_eye(-5, 5.5, 35);      
	pinhole_ptr->set_lookat(1.25, 3.5, 0);     
	pinhole_ptr->set_view_distance(2400.0);  
	pinhole_ptr->compute_uvw();     
	set_camera(pinhole_ptr);
	
	
	// point light 
	
	PointLight* light_ptr1 = new PointLight;
	light_ptr1->set_location(40, 50, 0); 
	light_ptr1->scale_radiance(4.0);
	light_ptr1->set_shadows(true);
	add_light(light_ptr1);
	

	// point light 
	
	PointLight* light_ptr2 = new PointLight;
	light_ptr2->set_location(-10, 20, 10); 
	light_ptr2->scale_radiance(4.0);
	light_ptr2->set_shadows(true);
	add_light(light_ptr2);
	
	
	// directional light 
	
	Directional* light_ptr3 = new Directional;
	light_ptr3->set_direction(-1, 0, 0); 
	light_ptr3->scale_radiance(4.0);
	light_ptr3->set_shadows(true);
	add_light(light_ptr3);
	
	
	// transparent bunny
	
	Transparent* glass_ptr = new Transparent;
	glass_ptr->set_ks(0.2);
	glass_ptr->set_exp(2000.0);
	glass_ptr->set_ior(1.5);		
	glass_ptr->set_kr(0.1);
	glass_ptr->set_kt(0.9);
		
//	const char* fileName = "Bunny3K.ply"; 	// 4000 triangles
//	const char* fileName = "Bunny10K.ply"; 	// 10000 triangles
//	const char* fileName = "Bunny16K.ply"; 	// 16000 triangles
	const char* fileName = "Bunny69K.ply"; 	// 69000 triangles

	Mesh* mesh_ptr = new Mesh;
	Grid* bunny_ptr = new Grid(mesh_ptr);
//	bunny_ptr->read_flat_triangles(fileName);	
	bunny_ptr->read_smooth_triangles(fileName);	
	bunny_ptr->set_material(glass_ptr); 	
	bunny_ptr->setup_cells();

	Instance* big_bunny_ptr = new Instance(bunny_ptr);
	big_bunny_ptr->scale(45.0);
	big_bunny_ptr->translate(1.7, -1.5, 0.0);
	add_object(big_bunny_ptr);
	
	
	// red sphere
		
	Reflective*	reflective_ptr = new Reflective;
	reflective_ptr->set_ka(0.3);
	reflective_ptr->set_kd(0.3); 
	reflective_ptr->set_cd(red); 
	reflective_ptr->set_ks(0.2);
	reflective_ptr->set_exp(2000.0);
	reflective_ptr->set_kr(0.25);
	
	Sphere* sphere_ptr2 = new Sphere(Point3D(4, 4, -6), 3);
	sphere_ptr2->set_material(reflective_ptr);
	add_object(sphere_ptr2);

		
	Checker3D* checker_ptr = new Checker3D;
	checker_ptr->set_size(4.0);
	checker_ptr->set_color1(white);  
	checker_ptr->set_color2(0.75);	
	
	SV_Matte* sv_matte_ptr = new SV_Matte;		
	sv_matte_ptr->set_ka(0.5);
	sv_matte_ptr->set_kd(0.35);
	sv_matte_ptr->set_cd(checker_ptr);	
	
	
	// rectangle
	
	Point3D p0(-20, 0, -100);
	Vector3D a(0, 0, 120);
	Vector3D b(40, 0, 0);
	
	Rectangle* rectangle_ptr = new Rectangle(p0, a, b); 
	rectangle_ptr->set_material(sv_matte_ptr);
	add_object(rectangle_ptr);	
}


