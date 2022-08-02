// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

// This builds the scene for Figure 25.13.

void 												
World::build(void) {
	int num_samples = 1;
	
	vp.set_hres(600);			
	vp.set_vres(600); 
	vp.set_samples(num_samples);
	vp.set_max_depth(1);
		
	tracer_ptr = new AreaLighting(this);	
				
	Pinhole* pinhole_ptr = new Pinhole;
	pinhole_ptr->set_eye(-150, 75, 500); 
	pinhole_ptr->set_lookat(-6, 50, 0);
	pinhole_ptr->set_view_distance(3000);	
	pinhole_ptr->compute_uvw(); 
	set_camera(pinhole_ptr);
	
	
	PointLight* light_ptr1 = new PointLight;
	light_ptr1->set_location(250, 500, 250); 
	light_ptr1->scale_radiance(2.0);   
	light_ptr1->set_shadows(true); 
    add_light(light_ptr1);

	float exp = 1.0;  	
	GlossyReflector* glossy_ptr = new GlossyReflector;
	glossy_ptr->set_sampler(new PureRandom(num_samples), exp);		// for Figure 25.13(a)
//	glossy_ptr->set_sampler(new Regular(num_samples), exp);			// for Figure 25.13(b)
//	glossy_ptr->set_sampler(new Hammersley(num_samples), exp);		// for Figure 25.13(c)		
	glossy_ptr->set_ka(0.0); 
	glossy_ptr->set_kd(0.0);
	glossy_ptr->set_ks(0.0);
	glossy_ptr->set_exp(exp);
	glossy_ptr->set_cd(1.0, 1.0, 0.3);
	glossy_ptr->set_kr(0.9);
	glossy_ptr->set_exponent(exp);
	glossy_ptr->set_cr(1.0, 1.0, 0.3);  // lemon
	
	Sphere* sphere_ptr1 = new Sphere(Point3D(-6, 55, 0), 40);
	sphere_ptr1->set_material(glossy_ptr);
	add_object(sphere_ptr1);
		
	
	//cylinder
	
	Matte* matte_ptr = new Matte;		
	matte_ptr->set_ka(0.15);
	matte_ptr->set_kd(0.75);
	matte_ptr->set_cd(0.5, 1.0, 0.5);   // green

	double bottom = -100;
	double top = 15;       
	double radius = 30;
	Instance* cylinder_ptr = new Instance(new SolidCylinder(bottom, top, radius));
	cylinder_ptr->translate(-6, 0, 0);
	cylinder_ptr->set_material(matte_ptr);
	add_object(cylinder_ptr);
	
	
	Image* image_ptr = new Image;
	image_ptr->read_ppm_file("uffizi_probe_small.ppm");  // for testing 
//	image_ptr->read_ppm_file("uffizi_probe_large.ppm");  // for production

	
	LightProbe* light_probe_ptr = new LightProbe; 
	light_probe_ptr->set_map_type(panoramic);   		
	
	ImageTexture* image_texture_ptr = new ImageTexture(image_ptr); 
	image_texture_ptr->set_mapping(light_probe_ptr);
	
	SV_Matte* sv_matte_ptr = new SV_Matte;		
	sv_matte_ptr->set_ka(1);
	sv_matte_ptr->set_kd(0.85);  
	sv_matte_ptr->set_cd(image_texture_ptr);
	
	Sphere* unit_sphere_ptr = new Sphere;
	unit_sphere_ptr->set_shadows(false);	
	
	Instance* sphere_ptr2 = new Instance(unit_sphere_ptr); 
	sphere_ptr2->scale(1000000.0);
	sphere_ptr2->set_material(sv_matte_ptr);
	add_object(sphere_ptr2);
}


