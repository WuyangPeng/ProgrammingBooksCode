// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


// This builds the scene for testing a textured environment light

void 												
World::build(void) {
	int num_samples = 1;
	
	vp.set_hres(600);				
	vp.set_vres(600);
	vp.set_samples(num_samples);
	vp.set_max_depth(5);
	
	tracer_ptr = new AreaLighting(this);	
		
	AmbientOccluder* ambient_occluder_ptr = new AmbientOccluder;
	ambient_occluder_ptr->set_sampler(new MultiJittered(num_samples));
	ambient_occluder_ptr->set_min_amount(0.5);
	set_ambient_light(ambient_occluder_ptr);

			
	Pinhole* pinhole_ptr = new Pinhole;
	pinhole_ptr->set_eye(0, 150, 0); 		
	pinhole_ptr->set_lookat(0, 40, 0);  
	pinhole_ptr->set_view_distance(200);    
	pinhole_ptr->compute_uvw(); 
	set_camera(pinhole_ptr);
	
	
	// image
	
	Image* image_ptr = new Image;	
	image_ptr->read_ppm_file("CyanToYellow.ppm");
	
	
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
	
	Matte* matte_ptr1 = new Matte;			
	matte_ptr1->set_ka(0.2); 
	matte_ptr1->set_kd(0.5);
	matte_ptr1->set_cd(0.85);
	
	
	// cylinder
		
	double bottom 	= 0.0;
	double top 		= 85.0; 
	double radius	= 40.0;
	SolidCylinder* cylinder_ptr = new SolidCylinder(bottom, top, radius);
	cylinder_ptr->set_material(matte_ptr1);
	add_object(cylinder_ptr);

	
	// ground plane:
	
	Plane* plane_ptr = new Plane(Point3D(0.0), Normal(0, 1, 0));
	plane_ptr->set_material(matte_ptr1);
	add_object(plane_ptr);
}


