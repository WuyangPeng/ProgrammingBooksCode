// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


// This builds the scene for Figure 28.25

void 												
World::build(void) {
	int num_samples = 1;  // this figure does not need antialiasing
	
	vp.set_hres(600);	  		
	vp.set_vres(600);
	vp.set_samples(num_samples);	
	vp.set_max_depth(10);		
	
	background_color = black;
	
	tracer_ptr = new Whitted(this);
	
	Ambient* ambient_ptr = new Ambient;
	ambient_ptr->scale_radiance(0.25);
	set_ambient_light(ambient_ptr);
	
		
	Pinhole* pinhole_ptr = new Pinhole;
	pinhole_ptr->set_eye(0, 1000, 0);   
	pinhole_ptr->set_lookat(0);    
	pinhole_ptr->set_view_distance(200000.0);	
	pinhole_ptr->compute_uvw();     
	set_camera(pinhole_ptr);
	
		
	// transparent box
		
	Dielectric* dielectric_ptr = new Dielectric;
	dielectric_ptr->set_eta_in(1.5);   
	dielectric_ptr->set_eta_out(1.0);
	dielectric_ptr->set_cf_in(white);
	dielectric_ptr->set_cf_out(white);
	
	Point3D p0(-1.0, 0.0, -1.0);
	Point3D p1(1.0, 0.1, 1.0);
	
	Box* box_ptr1 = new Box(p0, p1);
	box_ptr1->set_material(dielectric_ptr);
	add_object(box_ptr1);
	
	
	// plane
		
	Emissive* emissive_ptr = new Emissive;
	emissive_ptr->set_ce(white);
	emissive_ptr->scale_radiance(1.0);
	
	Plane* plane_ptr = new Plane(Point3D(0.0, -4.0, 0.0), Normal(0, 1, 0));
	plane_ptr->set_material(emissive_ptr);
	add_object(plane_ptr);
}


