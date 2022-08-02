// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


// This builds the scene for Figure 29.27

// The sky images are courtesy of Lopez-Fabrega Design, http://www.lfgrafix.com.
// You can download JPEG images of the skies from this site.
// PPM files of the skies are in the TextureFiles.zip download.


void 												
World::build(void) {
	int num_samples = 100;
	
	vp.set_hres(600);
	vp.set_vres(400);
	vp.set_samples(num_samples);
	vp.set_max_depth(5);
	
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
	
		
	PointLight* light_ptr = new PointLight;
	light_ptr->set_location(150, 250, -150);   
	light_ptr->scale_radiance(1.5);
	light_ptr->set_shadows(true);
	add_light(light_ptr);
	
	
	// image
	
	Image* image_ptr = new Image;	
	image_ptr->read_ppm_file("EveningSky.ppm");			// for Figure 29.27(a)
//	image_ptr->read_ppm_file("MorningSky.ppm");			// for Figure 29.27(b)	
	
	
	// image texture
	 
	HemisphericalMap* map_ptr = new HemisphericalMap;  
	ImageTexture* texture_ptr = new ImageTexture; 
	texture_ptr->set_image(image_ptr);
	texture_ptr->set_mapping(map_ptr);
	
	
	// spatially varying material
	
	SV_Emissive* sv_emissive_ptr = new SV_Emissive;
	sv_emissive_ptr->set_ce(texture_ptr);
	sv_emissive_ptr->scale_radiance(1.0);
	
	
	EnvironmentLight* environment_light_ptr = new EnvironmentLight;
	environment_light_ptr->set_material(sv_emissive_ptr);
	environment_light_ptr->set_sampler(new MultiJittered(num_samples));
	environment_light_ptr->set_shadows(true);
	add_light(environment_light_ptr);


	
	// large concave hemisphere for direct rendering of the skies
	
	ConcaveHemisphere* unit_hemisphere_ptr = new ConcaveHemisphere;
	Instance* hemisphere_ptr = new Instance(unit_hemisphere_ptr); 
	hemisphere_ptr->set_shadows(false);
	hemisphere_ptr->scale(1000000.0);
	hemisphere_ptr->rotate_y(-30);   
	hemisphere_ptr->set_material(sv_emissive_ptr);
	add_object(hemisphere_ptr);							
	
	
	// the other objects
	
	// large sphere - reflective
	
	Reflective* reflective_ptr1 = new Reflective;			
	reflective_ptr1->set_kr(0.9);
	reflective_ptr1->set_cr(1.0, 0.75, 0.5);       // pink
	
	Sphere* sphere_ptr1 = new Sphere(Point3D(38, 20, -24), 20);
	sphere_ptr1->set_material(reflective_ptr1);
	add_object(sphere_ptr1);
	
	
	// small sphere - non reflective
	
	Matte* matte_ptr1 = new Matte;			
	matte_ptr1->set_ka(0.2); 
	matte_ptr1->set_kd(0.5);
	matte_ptr1->set_cd(0.85);
	
	Sphere* sphere_ptr2 = new Sphere(Point3D(34, 12, 13), 12);
	sphere_ptr2->set_material(matte_ptr1);
	add_object(sphere_ptr2);
	
	
	// medium sphere - reflective
	
	Sphere* sphere_ptr3 = new Sphere(Point3D(-7, 15, 42), 16);
	sphere_ptr3->set_material(reflective_ptr1);
	add_object(sphere_ptr3);
	
	
	// cylinder - reflective
	
	Reflective* reflective_ptr2 = new Reflective;	
	reflective_ptr2->set_kr(0.9);
	reflective_ptr2->set_cr(1.0, 1.0, 0.5);   // lemon
	
	double bottom 	= 0.0;
	double top 		= 85.0; 
	double radius	= 22.0;
	SolidCylinder* cylinder_ptr = new SolidCylinder(bottom, top, radius);
	cylinder_ptr->set_material(reflective_ptr2);
	add_object(cylinder_ptr);

	
	// box - non reflective
	
	Matte* matte_ptr2 = new Matte;			
	matte_ptr2->set_ka(0.2); 
	matte_ptr2->set_kd(0.5);
	matte_ptr2->set_cd(0.95);
	
	Box* box_ptr = new Box(Point3D(-35, 0, -110), Point3D(-25, 60, 65));
	box_ptr->set_material(matte_ptr2);
	add_object(box_ptr);				
	
	
	// ground plane:
	
	Matte* matte_ptr3 = new Matte;			
	matte_ptr3->set_ka(0.15); 
	matte_ptr3->set_kd(0.5);	
	matte_ptr3->set_cd(0.7);    
	
	Plane* plane_ptr = new Plane(Point3D(0, 0.01, 0), Normal(0, 1, 0));
	plane_ptr->set_material(matte_ptr3);
	add_object(plane_ptr);
}


