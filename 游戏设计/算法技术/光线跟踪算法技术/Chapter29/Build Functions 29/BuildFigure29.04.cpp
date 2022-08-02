// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


// This builds the scene for Figure 29.4

void 												
World::build(void) {
	int num_samples = 16;
	
	vp.set_hres(400);
	vp.set_vres(400); 
	vp.set_samples(num_samples);
	vp.set_max_depth(0);
		
	background_color = RGBColor(0.0);
	
	tracer_ptr = new RayCast(this);
	
	Pinhole* pinhole_ptr = new Pinhole;
	pinhole_ptr->set_eye(5, 1.5, 8);
	pinhole_ptr->set_lookat(0.25, 0.0, 0.0); 
	pinhole_ptr->set_view_distance(1000.0);
	pinhole_ptr->compute_uvw();
	set_camera(pinhole_ptr);
	
	Directional* light_ptr = new Directional;
	light_ptr->set_direction(-15, 20, 25);  
	light_ptr->scale_radiance(2.5);  
	light_ptr->set_shadows(true);
	add_light(light_ptr);
	
	// image:

	Image* image_ptr = new Image;					
	image_ptr->read_ppm_file("Lightlace.ppm");
	
	// mapping:
	
	SquareMap* map_ptr = new SquareMap;   
	
	// image texture:
	
	ImageTexture* texture_ptr = new ImageTexture(image_ptr); 
	texture_ptr->set_mapping(map_ptr);
	
	// spatially varying material:
		
	SV_Matte* sv_matte_ptr = new SV_Matte;		
	sv_matte_ptr->set_ka(0.40);
	sv_matte_ptr->set_kd(0.95);
	sv_matte_ptr->set_cd(texture_ptr);
	
	// generic rectangle:
	
	Rectangle* rectangle_ptr = new Rectangle;
	rectangle_ptr->set_material(sv_matte_ptr);
	
	// transformed rectangle:
	
	Instance* lightlace_ptr = new Instance(rectangle_ptr);  
	lightlace_ptr->scale(1.0, 1.0, 1.5);
	lightlace_ptr->rotate_z(90);
	lightlace_ptr->rotate_y(90);
	add_object(lightlace_ptr);
	
	// ground plane
	
	Matte* matte_ptr1 = new Matte;		
	matte_ptr1->set_ka(0.25);
	matte_ptr1->set_kd(0.5);
	matte_ptr1->set_cd(1.0);
	 
	Plane* plane_ptr = new Plane(Point3D(0.0, -1.0, 0.0), Normal(0.0, 1.0, 0.0));
	plane_ptr->set_material(matte_ptr1);
	add_object(plane_ptr);
}