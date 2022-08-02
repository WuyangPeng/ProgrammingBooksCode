// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


// This builds the scene for Figure 28.45

void 												
World::build(void) {
	int num_samples = 16;
	
	vp.set_hres(600);	  		
	vp.set_vres(600);
	vp.set_samples(num_samples);    
	vp.set_max_depth(4);
		
	tracer_ptr = new Whitted(this);
	
	background_color = RGBColor(0.75);  
	
	Ambient* ambient_ptr = new Ambient;
	ambient_ptr->scale_radiance(1.0);
	set_ambient_light(ambient_ptr);	

	
	Pinhole* pinhole_ptr = new Pinhole;
	pinhole_ptr->set_eye(10, 12, 20); 
	pinhole_ptr->set_lookat(-3.75, 3, 0);     
	pinhole_ptr->set_view_distance(1500.0);	
	pinhole_ptr->compute_uvw();     
	set_camera(pinhole_ptr);
	
	PointLight* light_ptr1 = new PointLight;
	light_ptr1->set_location(20, 25, -20);  
	light_ptr1->scale_radiance(3.0);  
	light_ptr1->set_shadows(true);
	add_light(light_ptr1);
	
	
	float c = 1.75;  // this allows us to adjust the filter color without changing the hue
	RGBColor glass_color(0.27*c, 0.49*c, 0.42*c);  

		
	Dielectric* glass_ptr = new Dielectric;
	glass_ptr->set_eta_in(1.50);		// glass
	glass_ptr->set_eta_out(1.0);		// air
	glass_ptr->set_cf_in(glass_color);
	glass_ptr->set_cf_out(white); 
	
	double 	thickness 	= 0.25;
	double 	height 		= 4.0;
	double 	delta 		= 1.0;			// length change of each box
		
	int 	num_boxes 	= 10;
	double 	x_min 		= -10.0;		// where the boxes start in the x direction
	double 	gap 		= 0.5;   		// gap between the boxes
	
	for (int j = 0; j < num_boxes; j++) {
		double length = thickness + j * delta;
		Point3D p0(x_min + j * (thickness + gap), 0.0, -length);
		Point3D p1(x_min + j * (thickness + gap) + thickness, height, 0.0);
		
		Box* box_ptr = new Box(p0, p1);     
		box_ptr->set_material(glass_ptr);
		add_object(box_ptr);
	}
	
	
	// plane
	
	Matte* matte_ptr = new Matte;		
	matte_ptr->set_ka(0.5);
	matte_ptr->set_kd(0.65);
	matte_ptr->set_cd(0.75);
	
	Plane* plane_ptr = new Plane(Point3D(0.0), Normal(0, 1, 0));
	plane_ptr->set_material(matte_ptr);
	add_object(plane_ptr);
}


