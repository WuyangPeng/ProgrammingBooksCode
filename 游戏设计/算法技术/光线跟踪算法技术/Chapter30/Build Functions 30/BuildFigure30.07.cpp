// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


// This builds the scene for Figure 30.7

void 												
World::build(void) {	
	int num_samples = 16;
	
	vp.set_hres(904);
	vp.set_vres(300);
	vp.set_samples(num_samples);
	
	tracer_ptr = new RayCast(this);
	background_color = RGBColor(0.75);
			
	Ambient* ambient_ptr = new Ambient;
	ambient_ptr->scale_radiance(0.5);    
	set_ambient_light(ambient_ptr);
	

	Pinhole* pinhole_ptr = new Pinhole;
	pinhole_ptr->set_eye(0, 0, 200);         
	pinhole_ptr->set_lookat(0.0); 
	pinhole_ptr->set_view_distance(9600.0);  
	pinhole_ptr->compute_uvw(); 
	set_camera(pinhole_ptr);
	
		
	PointLight* light_ptr = new PointLight;
	light_ptr->set_location(50, 100, 100);  
	light_ptr->scale_radiance(4.0);   
	light_ptr->set_shadows(false);
	add_light(light_ptr);
	
	
	// the spheres
	
	Checker3D* checker_ptr = new Checker3D;
	checker_ptr->set_size(1.0);
	checker_ptr->set_color1(black);
	checker_ptr->set_color2(white);
	
	TInstance* translated_checker_ptr = new TInstance(checker_ptr);
	translated_checker_ptr->translate(0.5, 0.5, 0.0);
	
	SV_Matte* sv_matte_ptr = new SV_Matte;		
	sv_matte_ptr->set_ka(0.5);
	sv_matte_ptr->set_kd(0.75);
	sv_matte_ptr->set_cd(translated_checker_ptr);
	
	double radius;
	
	
	// sphere 1	
	
	radius = 3.0;
	Instance* sphere_ptr1 = new Instance(new Sphere(Point3D(0.0), radius));
	sphere_ptr1->set_material(sv_matte_ptr);
	sphere_ptr1->translate(-6.25, 0.0, 0.0);
	add_object(sphere_ptr1);
	
	
	// sphere 2
	
	radius = 2.25;	
	Instance* sphere_ptr2 = new Instance(new Sphere(Point3D(0.0), radius));
	sphere_ptr2->set_material(sv_matte_ptr);
	sphere_ptr2->translate(-1.0, 0.0, 0.0);
	add_object(sphere_ptr2);
	
	
	// sphere 3
	
	radius = 1.75;	
	Instance* sphere_ptr3 = new Instance(new Sphere(Point3D(0.0), radius));
	sphere_ptr3->set_material(sv_matte_ptr);
	sphere_ptr3->translate(3.0, 0.0, 0.0);
	add_object(sphere_ptr3);
	
	
	// sphere 4
	
	radius = 1.0;	
	Instance* sphere_ptr4 = new Instance(new Sphere(Point3D(0.0), radius));
	sphere_ptr4->set_material(sv_matte_ptr);
	sphere_ptr4->translate(5.75, 0.0, 0.0);
	add_object(sphere_ptr4);
	
	
	// sphere 5
	
	radius = 0.75;	
	Instance* sphere_ptr5 = new Instance(new Sphere(Point3D(0.0), radius));
	sphere_ptr5->set_material(sv_matte_ptr);
	sphere_ptr5->translate(7.5, 0.0, 0.0);
	add_object(sphere_ptr5);
	
	
	// sphere 6
	
	radius = 0.5;	
	Instance* sphere_ptr6 = new Instance(new Sphere(Point3D(0.0), radius));
	sphere_ptr6->set_material(sv_matte_ptr);
	sphere_ptr6->translate(8.75, 0.0, 0.0);
	add_object(sphere_ptr6);
}


	