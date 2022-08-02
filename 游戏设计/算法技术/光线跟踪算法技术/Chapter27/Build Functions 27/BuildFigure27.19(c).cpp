// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


// This builds the scene for Figure 27.19(c)

// You can implement the flat-rimmed bowl object as an exercise.
// See Exercise 19.25

void 												
World::build(void) {
	int num_samples = 4;   // at max_depth = 10, this renders very slowly
	
	vp.set_hres(600);	  		
	vp.set_vres(600);
	vp.set_max_depth(10);
	vp.set_samples(num_samples);
	
	Ambient* ambient_ptr = new Ambient;
	ambient_ptr->scale_radiance(0.25);
	set_ambient_light(ambient_ptr);
	
	background_color = RGBColor(0.0, 0.3, 0.25);
	
	tracer_ptr = new Whitted(this);
	
	Pinhole* pinhole_ptr = new Pinhole;
	pinhole_ptr->set_eye(1, 7.5, 20);
	pinhole_ptr->set_lookat(0, -0.35, 0);
	pinhole_ptr->set_view_distance(5250.0); 
	pinhole_ptr->compute_uvw();
	set_camera(pinhole_ptr);
	
		
	PointLight* light_ptr = new PointLight;
	light_ptr->set_location(20, 20, 15);
	light_ptr->scale_radiance(2.75);
	light_ptr->set_shadows(true);
	add_light(light_ptr);
	
		
	// transparent bowl
	
	Transparent* glass_ptr = new Transparent;
	glass_ptr->set_ks(0.5);
	glass_ptr->set_exp(2000.0);
	glass_ptr->set_ior(1.5);
	glass_ptr->set_kr(0.1);
	glass_ptr->set_kt(0.9);
		
	double 	inner_radius = 0.9;
	double 	outer_radius = 1.0;
	
	FlatRimmedBowl* bowl_ptr = new FlatRimmedBowl(inner_radius, outer_radius);
	bowl_ptr->set_material(glass_ptr);
	add_object(bowl_ptr);
	
	
	// the two spheres in the bowl just touch its inner surface
	
	// red sphere
		
	Reflective*	reflective_ptr1 = new Reflective;
	reflective_ptr1->set_ka(0.6);	
	reflective_ptr1->set_kd(0.4); 
	reflective_ptr1->set_cd(red);		 
	reflective_ptr1->set_ks(0.5);
	reflective_ptr1->set_exp(2000.0);
	reflective_ptr1->set_kr(0.25);
	
	
	double radius = 0.4;
	double theta = 55.0;
	theta = 3.1415926 * theta / 180.0;
	double xc = -(0.9 - radius) * cos(theta);
	double yc = -(0.9 - radius) * sin(theta);
	Sphere* sphere_ptr2 = new Sphere(Point3D(xc, yc, 0), radius);
	sphere_ptr2->set_material(reflective_ptr1);
	add_object(sphere_ptr2);
	
	
	// yellow sphere
		
	Reflective*	reflective_ptr2 = new Reflective;
	reflective_ptr2->set_ka(0.6);	
	reflective_ptr2->set_kd(0.4); 
	reflective_ptr2->set_cd(1, 1, 0);			// yellow 
	reflective_ptr2->set_ks(0.5);
	reflective_ptr2->set_exp(2000.0);
	reflective_ptr2->set_kr(0.5);
	
	
	radius = 0.35;
	theta = 35.0;
	theta = 3.1415926 * theta / 180.0;
	xc = (0.9 - radius) * cos(theta);
	yc = -(0.9 - radius) * sin(theta);
	Sphere* sphere_ptr3 = new Sphere(Point3D(xc, yc, 0), radius);
	sphere_ptr3->set_material(reflective_ptr2);
	add_object(sphere_ptr3);
	
	
	// rectangle
	
	Checker3D* checker_ptr = new Checker3D;
	checker_ptr->set_size(1.0);		
	checker_ptr->set_color1(white);  	
	checker_ptr->set_color2(0.5);
	
	SV_Matte* sv_matte_ptr = new SV_Matte;		
	sv_matte_ptr->set_ka(0.8);
	sv_matte_ptr->set_kd(0.85);
	sv_matte_ptr->set_cd(checker_ptr);
	
	Point3D p0(-2, -1, -5);
	Vector3D a(0, 0, 9);
	Vector3D b(4, 0, 0);
	
	Rectangle* rectangle_ptr = new Rectangle(p0, a, b);  
	rectangle_ptr->set_material(sv_matte_ptr);
	add_object(rectangle_ptr);	
}

