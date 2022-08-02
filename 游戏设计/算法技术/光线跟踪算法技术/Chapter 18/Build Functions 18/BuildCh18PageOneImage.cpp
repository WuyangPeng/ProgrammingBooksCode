// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.
// This builds the scene for the Chapter 18 page 1 image

// The illumination is from a lemon environment light as discussed in Section 18.10
// and a jittered directional light from Exercise 18.3. The code for the function
// JitteredDirectional::get_direction is analogous to the code in LIsting 18.18. 
// The un-jittered direction should be normalized in the set_direction function, and the 
// jittered direction should be normalized in the get_direction function. The set_jittered_amount 
// function sets "r". The simplest way to implement the JitteredDirectional class is to let it inherit 
// from Directional.

void 												
World::build(void)
{
	int num_samples = 256;
	
	vp.set_hres(600);
	vp.set_vres(400);
	vp.set_samples(num_samples);
	vp.set_max_depth(0);
		
	tracer_ptr = new AreaLighting(this);	
		
	AmbientOccluder* ambient_occluder_ptr = new AmbientOccluder;
	ambient_occluder_ptr->set_sampler(new MultiJittered(num_samples));
	ambient_occluder_ptr->set_min_amount(0.5);
	set_ambient_light(ambient_occluder_ptr);

			
	Pinhole* pinhole_ptr = new Pinhole;
	pinhole_ptr->set_eye(100, 45, 100);  
	pinhole_ptr->set_lookat(-10, 40, 0);   
	pinhole_ptr->set_view_distance(400);   
	pinhole_ptr->compute_uvw(); 
	set_camera(pinhole_ptr);
		
	JitteredDirectional* light_ptr = new JitteredDirectional;
	light_ptr->set_direction(150, 50, -50);   
	light_ptr->set_color(1.0, 0.25, 0.0);  // orange
	light_ptr->set_jitter_amount(0.2);
	light_ptr->scale_radiance(4.0);       
	light_ptr->set_shadows(true);
	add_light(light_ptr);
	
	Emissive* emissive_ptr = new Emissive;
	emissive_ptr->set_ce(1.0, 1.0, 0.5); 	// lemon
	emissive_ptr->scale_radiance(0.9);
	
	ConcaveHemisphere* hemisphere_ptr = new ConcaveHemisphere;
	hemisphere_ptr->set_radius(1000000.0);
	hemisphere_ptr->set_material(emissive_ptr);
	hemisphere_ptr->set_shadows(false);
	add_object(hemisphere_ptr);
	
	EnvironmentLight* environmentLight_ptr = new EnvironmentLight;
	environmentLight_ptr->set_material(emissive_ptr);
	environmentLight_ptr->set_sampler(new MultiJittered(num_samples));
	environmentLight_ptr->set_shadows(true);
	add_light(environmentLight_ptr);
	
	
	float ka = 0.2;  // commom ambient reflection coefficient
	
	// large sphere
		
	Matte* matte_ptr1 = new Matte;			
	matte_ptr1->set_ka(ka); 
	matte_ptr1->set_kd(0.60);
	matte_ptr1->set_cd(0.75);
	
	Sphere* sphere_ptr1 = new Sphere(Point3D(38, 20, -24), 20);
	sphere_ptr1->set_material(matte_ptr1);
	add_object(sphere_ptr1);
	
	
	// small sphere
	
	Matte* matte_ptr2 = new Matte;			
	matte_ptr2->set_ka(ka); 
	matte_ptr2->set_kd(0.4);
	matte_ptr2->set_cd(0.25, 1.0, 0.35);       // green
	
	Sphere* sphere_ptr2 = new Sphere(Point3D(34, 12, 13), 12);
	sphere_ptr2->set_material(matte_ptr2);
	add_object(sphere_ptr2);
	
	
	// medium sphere
	
	Matte* matte_ptr3 = new Matte;			
	matte_ptr3->set_ka(ka); 
	matte_ptr3->set_kd(0.5);
	matte_ptr3->set_cd(0.75);
	
	Sphere* sphere_ptr3 = new Sphere(Point3D(-7, 15, 42), 16);
	sphere_ptr3->set_material(matte_ptr3);
	add_object(sphere_ptr3);

	
	// cylinder
	
	Phong* phong_ptr = new Phong;			
	phong_ptr->set_ka(ka); 
	phong_ptr->set_kd(0.25);
	phong_ptr->set_cd(0.60);
	phong_ptr->set_ks(0.5);
	phong_ptr->set_exp(100);
	
	float bottom 	= 0.0;
	float top 		= 85; 
	float radius	= 22;
	SolidCylinder* cylinder_ptr = new SolidCylinder(bottom, top, radius);
	cylinder_ptr->set_material(phong_ptr);
	add_object(cylinder_ptr);

	
	// box
	
	Matte* matte_ptr4 = new Matte;			
	matte_ptr4->set_ka(ka); 
	matte_ptr4->set_kd(0.5);
	matte_ptr4->set_cd(0.95);
	
	Box* box_ptr = new Box(Point3D(-35, 0, -110), Point3D(-25, 60, 65));
	box_ptr->set_material(matte_ptr4);
	add_object(box_ptr);
	

	// ground plane 
		
	Matte* matte_ptr5 = new Matte;			
	matte_ptr5->set_ka(0.15); 
	matte_ptr5->set_kd(0.5);	
	matte_ptr5->set_cd(0.7);    
	
	Plane* plane_ptr = new Plane(Point3D(0, 0.01, 0), Normal(0, 1, 0));
	plane_ptr->set_material(matte_ptr5);
	add_object(plane_ptr);
}


