// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

// This builds the scene for Figure 24.31
// panoramic is declared in LightProbe.h, which is #included in World.h

void 												
World::build(void) {
	int num_samples = 16;
	
	vp.set_hres(600);			
	vp.set_vres(600); 
	vp.set_samples(num_samples);
	vp.set_max_depth(3);
		
	tracer_ptr = new Whitted(this);	
				
	Pinhole* pinhole_ptr = new Pinhole;
	pinhole_ptr->set_eye(-150, 75, 500); 
	pinhole_ptr->set_lookat(-6, 50, 0);
	pinhole_ptr->set_view_distance(3000);	
	pinhole_ptr->compute_uvw(); 
	set_camera(pinhole_ptr);
	
	
	PointLight* light_ptr1 = new PointLight;
	light_ptr1->set_location(250, 500, 250); 
	light_ptr1->scale_radiance(3.0); 
	light_ptr1->set_shadows(true); 
    add_light(light_ptr1);
    

	// bunny
	
	Reflective* reflective_ptr = new Reflective;			
	reflective_ptr->set_ka(0.0); 
	reflective_ptr->set_kd(0.0);
	reflective_ptr->set_ks(0.0);
	reflective_ptr->set_cd(0.0);
	reflective_ptr->set_kr(0.9);
	reflective_ptr->set_cr(0.5, 1.0, 0.5);  // light green
	
	Mesh* mesh_ptr = new Mesh;
	const char* file_name = "Bunny4K.ply";   		// Figure 24.31(a) & (b)
//	const char* file_name = "Bunny69K.ply"; 		// Figure 24.31(c) & (d)
	
	Grid* grid_ptr = new Grid(mesh_ptr);
//	grid_ptr->read_flat_triangles(file_name);		// Figure 24.31(a) & (c)
	grid_ptr->read_smooth_triangles(file_name);		// Figure 24.31(b) & (d)
	grid_ptr->setup_cells();

	Instance* bunny_ptr1 = new Instance(grid_ptr);
	bunny_ptr1->set_material(reflective_ptr);
	bunny_ptr1->scale(500.0);
	add_object(bunny_ptr1);
	
	
	//cylinder
	
	Matte* matte_ptr = new Matte;		
	matte_ptr->set_ka(0.15);
	matte_ptr->set_kd(0.75);
	matte_ptr->set_cd(1.0, 0.7, 0);   // orange

	double bottom = -100.0;
	double top = 15.0;       
	double radius = 30.0;
	Instance* cylinder_ptr = new Instance(new SolidCylinder(bottom, top, radius));
	cylinder_ptr->translate(-6, 0, 0);
	cylinder_ptr->set_material(matte_ptr);
	add_object(cylinder_ptr);
	
	
	// large sphere with Uffizi image
	
	Image* image_ptr = new Image;
	image_ptr->read_ppm_file("uffizi_probe_small.ppm");   // for testing 
//	image_ptr->read_ppm_file("uffizi_probe_large.ppm");   // for production
	
	LightProbe* light_probe_ptr = new LightProbe;   
	light_probe_ptr->set_map_type(panoramic);  		
	
	ImageTexture* texture_ptr = new ImageTexture(image_ptr); 
	texture_ptr->set_mapping(light_probe_ptr);
	
	SV_Matte* sv_matte_ptr = new SV_Matte;
	sv_matte_ptr->set_ka(1.0);
	sv_matte_ptr->set_kd(0.85);
	sv_matte_ptr->set_cd(texture_ptr);
	
	Sphere* unit_sphere_ptr = new Sphere;
	unit_sphere_ptr->set_shadows(false);	
	
	Instance* large_sphere_ptr = new Instance(unit_sphere_ptr); 
	large_sphere_ptr->set_material(sv_matte_ptr);
	large_sphere_ptr->scale(1000000.0);
	add_object(large_sphere_ptr);
}


