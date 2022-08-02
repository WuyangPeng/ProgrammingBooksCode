// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


// This builds the scene for Figure 28.16

void 												
World::build(void) {
	int num_samples = 100;
	
	vp.set_hres(600);	  		
	vp.set_vres(600);
	vp.set_samples(num_samples);	
	vp.set_max_depth(9);		
	
	background_color = RGBColor(0.5);
	
	tracer_ptr = new AreaLighting(this);
	
	Ambient* ambient_ptr = new Ambient;
	set_ambient_light(ambient_ptr);
	
	
	Pinhole* pinhole_ptr = new Pinhole;
	pinhole_ptr->set_eye(-4, 4, 20);  
	pinhole_ptr->set_lookat(-0.2, -0.5, 0);     
	pinhole_ptr->set_view_distance(6000.0);	
	pinhole_ptr->compute_uvw();     
	set_camera(pinhole_ptr);
	

	// rectangular area light
	
	Emissive* emissive_ptr = new Emissive;
	emissive_ptr->scale_radiance(40.0);		
	emissive_ptr->set_ce(white);
	
	Point3D center(5, 6, 10);
	double width = 4.0;
	double height = 5.0;
	
	Point3D p0(-0.5 * width, center.y - 0.5 * height, center.z);
	Vector3D a(width, 0.0, 0.0);
	Vector3D b(0.0, height, 0.0);
	Normal normal(0, 0, -1);
	
	Rectangle* rectangle_ptr = new Rectangle(p0, a, b, normal);
	rectangle_ptr->set_material(emissive_ptr);
	rectangle_ptr->set_sampler(new MultiJittered(num_samples));
	rectangle_ptr->set_shadows(false);
	add_object(rectangle_ptr);	
	
	AreaLight* area_light_ptr = new AreaLight;
	area_light_ptr->set_object(rectangle_ptr);
	area_light_ptr->set_shadows(true);
	add_light(area_light_ptr);

	
	// transparent bunny
	
	Dielectric* dielectric_ptr = new Dielectric;
	dielectric_ptr->set_ka(0.0);
	dielectric_ptr->set_kd(0.0); 
	dielectric_ptr->set_ks(0.2);     
	dielectric_ptr->set_exp(2000.0);
	dielectric_ptr->set_eta_in(1.5);   
	dielectric_ptr->set_eta_out(1.0);
	dielectric_ptr->set_cf_in(0.75, 0.45, 0);   // orange
	dielectric_ptr->set_cf_out(white);
		
	const char* file_name = "Bunny4K.ply"; 	

	Mesh* mesh_ptr = new Mesh;
	Grid* bunny_ptr = new Grid(mesh_ptr);
	bunny_ptr->read_smooth_triangles(file_name);	
	bunny_ptr->set_material(dielectric_ptr); 	
	bunny_ptr->setup_cells();

	Instance* big_bunny_ptr = new Instance(bunny_ptr);
	big_bunny_ptr->scale(10.0);
	big_bunny_ptr->translate(0, -1.5, 0.0);
	add_object(big_bunny_ptr);
	
	
	PlaneChecker* plane_checker_ptr = new PlaneChecker;
	plane_checker_ptr->set_size(0.25);		
	plane_checker_ptr->set_outline_width(0.02);
	plane_checker_ptr->set_color1(0.75);
	plane_checker_ptr->set_color2(0.75);  
	plane_checker_ptr->set_outline_color(black); 
	
	SV_Matte* sv_matte_ptr = new SV_Matte;		
	sv_matte_ptr->set_ka(0.15);
	sv_matte_ptr->set_kd(0.65);
	sv_matte_ptr->set_cd(plane_checker_ptr);
	
	// ground plane	
	
	Plane* plane_ptr1 = new Plane(Point3D(0, -1.175, 0), Normal(0, 1, 0));
	plane_ptr1->set_material(sv_matte_ptr);
	plane_ptr1->set_shadows(false);
	add_object(plane_ptr1);
		
	// back plane

	Instance* plane_ptr2 = new Instance(new Plane(Point3D(0), Normal(0, 1, 0)));
	plane_ptr2->set_material(sv_matte_ptr);
	plane_ptr2->rotate_x(90);
	plane_ptr2->translate(0, 0, -2);
	plane_ptr2->set_shadows(false);
	add_object(plane_ptr2);
	
	
		
}


