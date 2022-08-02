// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


// This builds the scene for Figure 29.26

void 												
World::build(void) {
	int num_samples = 16;
	
	vp.set_hres(400);
	vp.set_vres(400);
	vp.set_samples(num_samples);
	
	tracer_ptr = new RayCast(this);
	
	Pinhole* pinhole_ptr = new Pinhole;
	pinhole_ptr->set_eye(10, 8, 30); 
	pinhole_ptr->set_lookat(0, 2, 0); 
	pinhole_ptr->set_view_distance(2000.0); 	  
	pinhole_ptr->compute_uvw();
	set_camera(pinhole_ptr);
	

	Directional* light_ptr1 = new Directional;
	light_ptr1->set_direction(10, 10, 5);				
	light_ptr1->scale_radiance(1.5); 
	light_ptr1->set_shadows(true);
	add_light(light_ptr1);	
	
	Directional* light_ptr2 = new Directional;
	light_ptr2->set_direction(0, 0, 1);				
	light_ptr2->scale_radiance(1.5); 
	light_ptr2->set_shadows(false);
	add_light(light_ptr2);	
	
	
	// product jar
	
	Matte* matte_ptr = new Matte;
	matte_ptr->set_ka(0.25);
	matte_ptr->set_kd(0.75);
	matte_ptr->set_cd(0.9, 1.0, 0.9);     	// pale green
	
	Matte* body_matte_ptr = new Matte;
	body_matte_ptr->set_ka(0.25);
	body_matte_ptr->set_kd(0.75);
	body_matte_ptr->set_cd(red);
	
	Image* image_ptr = new Image;						
	image_ptr->read_ppm_file("label.ppm");
	
	CylindricalMap* cylindical_map_ptr = new CylindricalMap;   
	
	ImageTexture* image_texture_ptr = new ImageTexture(image_ptr); 
	image_texture_ptr->set_mapping(cylindical_map_ptr);
	
	SV_Matte* sv_matte_ptr = new SV_Matte;		
	sv_matte_ptr->set_ka(0.25);
	sv_matte_ptr->set_kd(0.75);
	sv_matte_ptr->set_cd(image_texture_ptr);
	
	
	// The product jar is centered on the y axis
	// The radius of the cap is body_radius - top_bevel_radius
	// The texture image used here completely covers the vertical curved surface
	// of the body. This has vertical extent from bottom + bottom_bevel_radius
	// to body top - bottom_bevel_radius.
	// If you use the body_matte_ptr defined above for the body, it will be rendered red.
	// See extra image in the Chapter 29 download.
	
	
	double bottom 				= 0.0;		// along y axis
	double body_top 			= 3.6;		// along y axis
	double cap_top 				= 4.1;		// along y axis
	double body_radius 			= 3.0;
	double bottom_bevel_radius 	= 0.5;	  	
	double top_bevel_radius 	= 0.5;		
	double cap_bevel_radius 	= 0.05;		
	
	ProductJar* product_jar_ptr = new ProductJar(	bottom,
													body_top,
													cap_top,
													body_radius,
													bottom_bevel_radius,
													top_bevel_radius,
													cap_bevel_radius);
	product_jar_ptr->set_material(matte_ptr);
//	product_jar_ptr->set_body_material(body_matte_ptr);		// renders vertical body surface red
	product_jar_ptr->set_body_material(sv_matte_ptr);
	
	Instance* rotated_jar_ptr = new Instance(product_jar_ptr);
	rotated_jar_ptr->rotate_y(180); 		// for Figure 29.26(a)
//	rotated_jar_ptr->rotate_y(100);  		// for Figure 29.26(b)
	add_object(rotated_jar_ptr);


	// ground plane
	
	Matte* matte_ptr2 = new Matte;		
	matte_ptr2->set_ka(0.25);
	matte_ptr2->set_kd(0.5);
	matte_ptr2->set_cd(0.5);
	
	Plane* plane_ptr = new Plane(Point3D(0.0), Normal(0, 1, 0));
	plane_ptr->set_material(matte_ptr2);
	add_object(plane_ptr);
}


