// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


// This builds the scene for Figure 30.8

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
	
	
	double radius;	
	
	// sphere 1
	
	TInstance* transformed_checker_ptr1 = new TInstance(checker_ptr);
	transformed_checker_ptr1->translate(0.5, 0.5, 0.0);
	
	SV_Matte* sv_matte_ptr1 = new SV_Matte;		
	sv_matte_ptr1->set_ka(0.5);
	sv_matte_ptr1->set_kd(0.75);
	sv_matte_ptr1->set_cd(transformed_checker_ptr1);	
	
	radius = 3.0;
	Instance* sphere_ptr1 = new Instance(new Sphere(Point3D(0.0), radius));
	sphere_ptr1->set_material(sv_matte_ptr1);
	sphere_ptr1->translate(-6.25, 0.0, 0.0);
	add_object(sphere_ptr1);
	
	
	// sphere 2
	
	TInstance* transformed_checker_ptr2 = new TInstance(checker_ptr);
	transformed_checker_ptr2->scale(0.75);
	transformed_checker_ptr2->translate(0.375, 0.375, 0.0);
	
	SV_Matte* sv_matte_ptr2 = new SV_Matte;		
	sv_matte_ptr2->set_ka(0.5);
	sv_matte_ptr2->set_kd(0.75);
	sv_matte_ptr2->set_cd(transformed_checker_ptr2);	
	
	radius = 2.25;	
	Instance* sphere_ptr2 = new Instance(new Sphere(Point3D(0.0), radius));
	sphere_ptr2->set_material(sv_matte_ptr2);
	sphere_ptr2->translate(-1.0, 0.0, 0.0);
	add_object(sphere_ptr2);
	
	
	// sphere 3
	
	TInstance* transformed_checker_ptr3 = new TInstance(checker_ptr);
	transformed_checker_ptr3->scale(0.5833333);
	transformed_checker_ptr3->translate(0.29166, 0.29166, 0.0);
	
	SV_Matte* sv_matte_ptr3 = new SV_Matte;		
	sv_matte_ptr3->set_ka(0.5);
	sv_matte_ptr3->set_kd(0.75);
	sv_matte_ptr3->set_cd(transformed_checker_ptr3);	
	
	radius = 1.75;	
	Instance* sphere_ptr3 = new Instance(new Sphere(Point3D(0.0), radius));
	sphere_ptr3->set_material(sv_matte_ptr3);
	sphere_ptr3->translate(3.0, 0.0, 0.0);
	add_object(sphere_ptr3);
	
	
	// sphere 4
	
	TInstance* transformed_checker_ptr4 = new TInstance(checker_ptr);
	transformed_checker_ptr4->scale(0.3333333);
	transformed_checker_ptr4->translate(0.166666, 0.166666, 0.0);
	
	SV_Matte* sv_matte_ptr4 = new SV_Matte;		
	sv_matte_ptr4->set_ka(0.5);
	sv_matte_ptr4->set_kd(0.75);
	sv_matte_ptr4->set_cd(transformed_checker_ptr4);	
	
	radius = 1.0;	
	Instance* sphere_ptr4 = new Instance(new Sphere(Point3D(0.0), radius));
	sphere_ptr4->set_material(sv_matte_ptr4);
	sphere_ptr4->translate(5.75, 0.0, 0.0);
	add_object(sphere_ptr4);
	
	
	// sphere 5
	
	TInstance* transformed_checker_ptr5 = new TInstance(checker_ptr);
	transformed_checker_ptr5->scale(0.25);
	transformed_checker_ptr5->translate(0.125, 0.125, 0.0);
	
	SV_Matte* sv_matte_ptr5 = new SV_Matte;		
	sv_matte_ptr5->set_ka(0.5);
	sv_matte_ptr5->set_kd(0.75);
	sv_matte_ptr5->set_cd(transformed_checker_ptr5);
	
	radius = 0.75;	
	Instance* sphere_ptr5 = new Instance(new Sphere(Point3D(0.0), radius));
	sphere_ptr5->set_material(sv_matte_ptr5);
	sphere_ptr5->translate(7.5, 0.0, 0.0);
	add_object(sphere_ptr5);
	
	
	// sphere 6
	
	TInstance* transformed_checker_ptr6 = new TInstance(checker_ptr);
	transformed_checker_ptr6->scale(0.166666);
	transformed_checker_ptr6->translate(0.083333, 0.083333, 0.0);
	
	SV_Matte* sv_matte_ptr6 = new SV_Matte;		
	sv_matte_ptr6->set_ka(0.5);
	sv_matte_ptr6->set_kd(0.75);
	sv_matte_ptr6->set_cd(transformed_checker_ptr6);
	
	radius = 0.5;	
	Instance* sphere_ptr6 = new Instance(new Sphere(Point3D(0.0), radius));
	sphere_ptr6->set_material(sv_matte_ptr6);
	sphere_ptr6->translate(8.75, 0.0, 0.0);
	add_object(sphere_ptr6);
}


	