// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

// This builds the scene for Figure 17.12
// Triangle meshes are discussed in Chapter 23
// The bunny PLY files are in the Chapter 23 archive

void 												
World::build(void) {
	int num_samples = 256; 
	
	vp.set_hres(400);
	vp.set_vres(400);
	vp.set_samples(num_samples);
	
	tracer_ptr = new RayCast(this);
	
	MultiJittered* sampler_ptr = new MultiJittered(num_samples);
	
	AmbientOccluder* acl_ptr = new AmbientOccluder;
	acl_ptr->set_min_amount(1.0);    	// for Figure 17.12(a)
//	acl_ptr->set_min_amount(0.25);		// for Figure 17.12(b)
//	acl_ptr->set_min_amount(0.0);		// for Figure 17.12(c)
	acl_ptr->set_sampler(sampler_ptr);
	set_ambient_light(acl_ptr);
	
	Pinhole* pinhole_ptr = new Pinhole;
	
	// for regular view	
	
	pinhole_ptr->set_eye(20, 10, 40);
	pinhole_ptr->set_lookat(-0.025, 0.11, 0.0);  
	pinhole_ptr->set_view_distance(70000);	
	pinhole_ptr->compute_uvw();
	set_camera(pinhole_ptr);
	
	
	Directional* light_ptr1 = new Directional;
	light_ptr1->set_direction(20, 40, 20);
	light_ptr1->scale_radiance(1.5); 
	light_ptr1->set_shadows(true);
	add_light(light_ptr1);

	
	float ka = 0.5;		// used for all materials

	Matte* matte_ptr1 = new Matte;			
	matte_ptr1->set_ka(ka);		
	matte_ptr1->set_kd(0.5);
	matte_ptr1->set_cd(0.5, 0.75, 1);   // pale blue for bunny
	
//	const char* file_name = "Bunny4K.ply"; 		// 4000 triangles
	const char* file_name = "Bunny10K.ply"; 	// 10000 triangles - needs the normals reversed
//	const char* file_name = "Bunny16K.ply"; 	// 16000 triangles
//	const char* file_name = "Bunny69K.ply"; 	// 69000 triangles
	
	Grid* bunny_ptr = new Grid;
	bunny_ptr->reverse_mesh_normals();				// only required for the Bunny10K.ply file
//	bunny_ptr->read_flat_triangles(file_name);		// read PLY file
	bunny_ptr->read_smooth_triangles(file_name);	// read PLY file
	bunny_ptr->set_material(matte_ptr1);
	bunny_ptr->setup_cells();
	
	Instance* rotated_bunny_ptr = new Instance(bunny_ptr);
	rotated_bunny_ptr->set_material(matte_ptr1);
	rotated_bunny_ptr->rotate_y(40);
	add_object(rotated_bunny_ptr);
	
	
	// rectangle parameters
	
	Point3D p0(-0.13, 0.033, -0.1);  	// common corner
	float height = 0.25;  				// y direction
	float width = 0.45;  				// x direction	
	float depth = 0.45;   				// z direction	

	// horizontal rectangle 
	
	Matte* matte_ptr2 = new Matte;			
	matte_ptr2->set_ka(ka);		
	matte_ptr2->set_kd(0.5);
	matte_ptr2->set_cd(white);
	
	Rectangle* rectangle_ptr1 = new Rectangle(p0, Vector3D(0, 0,depth), Vector3D(width, 0, 0));
	rectangle_ptr1->set_material(matte_ptr2);
	add_object(rectangle_ptr1);	
	
	// rectangle perpendicular to x axis
	
	Matte* matte_ptr3 = new Matte;			
	matte_ptr3->set_ka(ka);		
	matte_ptr3->set_kd(0.75);
	matte_ptr3->set_cd(0.5, 1, 0.75);
	
	Rectangle* rectangle_ptr2 = new Rectangle(p0, Vector3D(0, height, 0), Vector3D(0, 0, depth));
	rectangle_ptr2->set_material(matte_ptr3);
	add_object(rectangle_ptr2);	
	
	// rectangle perpendicular to w axis
	
	Matte* matte_ptr4 = new Matte;			
	matte_ptr4->set_ka(ka);		
	matte_ptr4->set_kd(0.5);
	matte_ptr4->set_cd(1, 1, 0.5);
	
	Rectangle* rectangle_ptr3 = new Rectangle(p0, Vector3D(width, 0, 0), Vector3D(0, height, 0));
	rectangle_ptr3->set_material(matte_ptr4);
	add_object(rectangle_ptr3);
}


