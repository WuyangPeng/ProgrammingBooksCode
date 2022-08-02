// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

// This builds the scene for Figure 23.10(a)
// The scene is Naomi Hatchman's penguin with flat shading

void 												
World::build(void) {
	int num_samples = 16;
	  
	vp.set_hres(400);      
	vp.set_vres(400);    
	vp.set_max_depth(0);
	vp.set_samples(num_samples);
	vp.set_pixel_size(1.0);	
	
	background_color = black;
	
	tracer_ptr = new RayCast(this);

	Pinhole* pinhole_ptr = new Pinhole;	    
	pinhole_ptr->set_eye(50, 40, 110);
	pinhole_ptr->set_lookat(1, 0, 0);
	pinhole_ptr->set_view_distance(1500);  
	pinhole_ptr->compute_uvw();     
	set_camera(pinhole_ptr); 
	
	Directional* directional_ptr = new Directional;    
	directional_ptr->set_direction(0.75, 1, 1);  
	directional_ptr->scale_radiance(2.5);
	directional_ptr->set_shadows(true);
	add_light(directional_ptr);
	
	
	float ka = 0.25;   	
	float kd = 0.75;	
	
	RGBColour body_color(0.5, 0.5, 1.0);
	RGBColour wing_color(0.5, 1.0, 0.4);
	RGBColour feet_color(1.0, 0.8, 0.34);
	RGBColour eyeball_color(1.0);
	RGBColour eyelid_color(1, 0, 0);
		
	// body
	
	Matte* matte_ptr1 = new Matte;			
	matte_ptr1->set_ka(ka);
	matte_ptr1->set_kd(0.75);    
	matte_ptr1->set_cd(body_color);		
	
	Grid* body_ptr = new Grid;
	body_ptr->read_flat_triangles("penguin_body.ply");
	body_ptr->set_material(matte_ptr1);  
	body_ptr->setup_cells();
	add_object(body_ptr);
	
	// wings
	
	Matte* matte_ptr2 = new Matte;			
	matte_ptr2->set_ka(ka);
	matte_ptr2->set_kd(0.5);    
	matte_ptr2->set_cd(wing_color);
	
	Grid* left_wing_ptr = new Grid;
	left_wing_ptr->read_flat_triangles("penguin_left_wing.ply");
	left_wing_ptr->set_material(matte_ptr2);  
	left_wing_ptr->setup_cells();
	
	Grid* right_wing_ptr = new Grid;
	right_wing_ptr->read_flat_triangles("penguin_right_wing.ply");
	right_wing_ptr->set_material(matte_ptr2);  
	right_wing_ptr->setup_cells();
	
	
	// feet
	
	Matte* matte_ptr3 = new Matte;			
	matte_ptr3->set_ka(ka);
	matte_ptr3->set_kd(0.5);    
	matte_ptr3->set_cd(feet_color);
	
	Grid* left_foot_ptr = new Grid;
	left_foot_ptr->read_flat_triangles("penguin_left_foot.ply");
	left_foot_ptr->set_material(matte_ptr3);  
	left_foot_ptr->setup_cells();
	
	Grid* right_foot_ptr = new Grid;
	right_foot_ptr->read_flat_triangles("penguin_right_foot.ply");
	right_foot_ptr->set_material(matte_ptr3);  
	right_foot_ptr->setup_cells();
	
	
	// eyeballs
	
	Matte* matte_ptr4 = new Matte;			
	matte_ptr4->set_ka(ka);
	matte_ptr4->set_kd(kd);    
	matte_ptr4->set_cd(eyeball_color);
	
	Grid* left_eyeball_ptr = new Grid;
	left_eyeball_ptr->read_flat_triangles("penguin_left_eyeball.ply");
	left_eyeball_ptr->set_material(matte_ptr4);  
	left_eyeball_ptr->setup_cells();
	
	Grid* right_eyeball_ptr = new Grid;
	right_eyeball_ptr->read_flat_triangles("penguin_right_eyeball.ply");
	right_eyeball_ptr->set_material(matte_ptr4);  
	right_eyeball_ptr->setup_cells();
	
	
	// eyelids
	
	Matte* matte_ptr5 = new Matte;			
	matte_ptr5->set_ka(ka);
	matte_ptr5->set_kd(kd);    
	matte_ptr5->set_cd(eyelid_color);
	
	Grid* left_lower_eyelid_ptr = new Grid;
	left_lower_eyelid_ptr->read_flat_triangles("penguin_left_lower_eyelid.ply");
	left_lower_eyelid_ptr->set_material(matte_ptr5);  
	left_lower_eyelid_ptr->setup_cells();
	
	Grid* right_lower_eyelid_ptr = new Grid;
	right_lower_eyelid_ptr->read_flat_triangles("penguin_right_lower_eyelid.ply");
	right_lower_eyelid_ptr->set_material(matte_ptr5);  
	right_lower_eyelid_ptr->setup_cells();
	
	
	Grid* left_upper_eyelid_ptr = new Grid;
	left_upper_eyelid_ptr->read_flat_triangles("penguin_left_upper_eyelid.ply");
	left_upper_eyelid_ptr->set_material(matte_ptr5);  
	left_upper_eyelid_ptr->setup_cells();
	
	Grid* right_upper_eyelid_ptr = new Grid;
	right_upper_eyelid_ptr->read_flat_triangles("penguin_right_upper_eyelid.ply");
	right_upper_eyelid_ptr->set_material(matte_ptr5);  
	right_upper_eyelid_ptr->setup_cells();
	
	
	
	// complete penguin
	
	Grid* penguin_ptr = new Grid;
	penguin_ptr->add_object(body_ptr);
	penguin_ptr->add_object(left_wing_ptr);
	penguin_ptr->add_object(right_wing_ptr);
	penguin_ptr->add_object(left_foot_ptr);
	penguin_ptr->add_object(right_foot_ptr);
	penguin_ptr->add_object(left_eyeball_ptr);
	penguin_ptr->add_object(right_eyeball_ptr);
	penguin_ptr->add_object(left_lower_eyelid_ptr);
	penguin_ptr->add_object(right_lower_eyelid_ptr);
	penguin_ptr->add_object(left_upper_eyelid_ptr);
	penguin_ptr->add_object(right_upper_eyelid_ptr);
	
	penguin_ptr->setup_cells();
	add_object(penguin_ptr);
}

