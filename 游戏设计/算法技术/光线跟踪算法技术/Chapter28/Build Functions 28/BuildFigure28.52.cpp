// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


// This builds the scene for Figure 28.52

// The object is a transparent cube with spherical caps cut from four faces
// There is a reflective sphere at the center
// The class CutFace is in the Chapter 28 download
// The cube has edge length 4. This should be defined as a variable

// This build function (deliberately) renders a bit darker than the image in the book

// The inspiration came from the acrylic sculpures "Titiopoli's Ligththouse" and "Dodecker" by the American 
// sculptor Bruce Beasley


void 												
World::build(void) {
	int num_samples = 25;
	
	vp.set_hres(600);	  		
	vp.set_vres(600);
	vp.set_samples(num_samples);
	vp.set_max_depth(12);    

	background_color = RGBColor(0.8, 0.9, 1);
	
	tracer_ptr = new Whitted(this);
	
	Ambient* ambient_ptr = new Ambient;
	ambient_ptr->scale_radiance(0.5);
	set_ambient_light(ambient_ptr);

	
	Pinhole* pinhole_ptr = new Pinhole;
	pinhole_ptr->set_eye(10, -1, 4);     
	pinhole_ptr->set_lookat(0, 0, 0);    
	pinhole_ptr->set_view_distance(700.0);	
	pinhole_ptr->compute_uvw();     
	set_camera(pinhole_ptr);
	
	PointLight* light_ptr = new PointLight;
	light_ptr->set_location(10, 30, 30); 
	light_ptr->scale_radiance(3.0);        
	light_ptr->set_shadows(true);
	add_light(light_ptr);
	
	
	// reflective unit sphere
	
	Reflective*	reflective_ptr = new Reflective;
	reflective_ptr->set_ka(1.0);	
	reflective_ptr->set_kd(0.5);  
	reflective_ptr->set_cd(1, 0.5, 0);			// orange
	reflective_ptr->set_ks(0.5);
	reflective_ptr->set_exp(500.0);
	reflective_ptr->set_kr(0.5);
	reflective_ptr->set_shadows(false);
		
	Sphere* sphere_ptr = new Sphere;
	sphere_ptr->set_material(reflective_ptr);
	

	Dielectric* glass_ptr = new Dielectric;
	glass_ptr->set_eta_in(1.5);
	glass_ptr->set_eta_out(1.0);
	double c = 0.9;
	glass_ptr->set_cf_in(0.9 * c, 1 * c, 0.85 * c);
	glass_ptr->set_cf_out(white);


	// concave cap
	
	double radius 			= 1.5;									
	double min_angle 		= 115;  			
	double max_angle 		= 180;
	double displacement 	= -radius * cos(min_angle * PI_ON_180);
	double rim_radius 		= radius * sin(min_angle * PI_ON_180);
	Point3D center(0.0);
		
	ConcavePartSphere* part_sphere_ptr = new ConcavePartSphere(center, radius, 0, 360, min_angle, max_angle); 
	
	Instance* concave_cap_ptr = new Instance (part_sphere_ptr); 
	concave_cap_ptr->translate(0, displacement, 0);


	CutFace* cut_face_ptr = new CutFace(4.0, rim_radius);
	
	
	// put these two objects in a compound object so that they can be transformed together
	
	Compound* facet_ptr = new Compound;
	facet_ptr->add_object(concave_cap_ptr);
	facet_ptr->add_object(cut_face_ptr);
	facet_ptr->set_material(glass_ptr);

	// define the six cube faces

	// front face (+ve z)
	
	Instance* front_ptr = new Instance(facet_ptr); 
	front_ptr->rotate_x(90);
	front_ptr->translate(0, 0, 2);	
	
	
	// back face (-ve z)
	
	Instance* back_ptr = new Instance(facet_ptr); 
	back_ptr->rotate_x(-90);
	back_ptr->translate(0, 0, -2);
	
		
	// bottom face (-ve y)
	
	Instance* bottom_ptr = new Instance(facet_ptr); 
	bottom_ptr->rotate_z(180);
	bottom_ptr->translate(0, -2, 0);
	
	
	// top face (+ve y)
	
	Instance* top_ptr = new Instance(facet_ptr); 
	top_ptr->translate(0, 2, 0);
	
	
	
	
	// a rectangle for the left and right cube faces

	Point3D p0(-2.0, 0.0, -2.0);
	Vector3D a(0.0, 0.0, 4.0);
	Vector3D b(4.0, 0.0, 0.0);
	Rectangle* rect = new Rectangle(p0, a, b);  
	rect->set_material(glass_ptr);
	
	
	// left face (-ve x)
	
	Instance* left_ptr = new Instance(rect); 
	left_ptr->rotate_z(90);
	left_ptr->translate(-2, 0, 0);
	
	
	// right face (+ve x)
	
	Instance* right_ptr = new Instance(rect); 
	right_ptr->rotate_z(-90);
	right_ptr->translate(2, 0, 0);
	
	
	// put all six faces into a compound object so we can rotate it
	
	Compound* cube_ptr = new Compound;
	cube_ptr->add_object(front_ptr);			// facet
	cube_ptr->add_object(back_ptr);				// facet
	cube_ptr->add_object(top_ptr);				// facet
	cube_ptr->add_object(bottom_ptr);			// facet
	cube_ptr->add_object(left_ptr);				// rectangle
	cube_ptr->add_object(right_ptr);			// rectangle
	cube_ptr->add_object(sphere_ptr);
	
	Instance* cube_ptr2 = new Instance(cube_ptr);
	cube_ptr2->rotate_z(45);
	cube_ptr2->rotate_x(35);
	add_object(cube_ptr2);
	
	
	
	// ground plane with checker
		
	Checker3D* checker_ptr = new Checker3D;
	checker_ptr->set_size(1.0);
	checker_ptr->set_color1(white);  
	checker_ptr->set_color2(0.5);
		
	SV_Matte* sv_matte_ptr = new SV_Matte;		
	sv_matte_ptr->set_ka(0.5);
	sv_matte_ptr->set_kd(0.75);
	sv_matte_ptr->set_cd(checker_ptr);

	Plane* plane_ptr1 = new Plane(Point3D(0, -4.01, 0), Normal(0, 1, 0));  
	plane_ptr1->set_material(sv_matte_ptr);
	add_object(plane_ptr1);	
}

	
