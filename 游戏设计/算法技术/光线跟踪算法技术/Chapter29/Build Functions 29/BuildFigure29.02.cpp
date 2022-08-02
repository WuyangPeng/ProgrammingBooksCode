// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


// This builds the scene for Figure 29.2

// Although this build function doesn't render the textures, it defines the textured materials
// as well as the un-textured (plain) materials.
// This will allow you to implement and render the textures one at a time.

// The main differences are in which materials are applied to the objects
// The walls and the grout do not have textures
// The bath water is bump mapped

// The bath water is Ken Musgrave's beautifully simple water simulation implemented as a bump map.
// See Musgrave (2003b), where it's implemented as a RenderMan displacement map.
// Actually, it's only simple if you have implemented a vector fractional Brownian motion (fBm) noise function.
// This has a lot of code behind it. See Chapter 31.
// In my ray tracer, water is the only application of vector noise.
// Bump mapping didn't make it into the book, but I'll include the bump mapping classes in the Chapter 31 download.

// Figures 29.1 and 29.2 in the book were rendered before I was using the etas 
// in the Dielectric material. The etas make the materials that are under the water darker, thereby 
// making the water edge visible on the bath sides.
// I've compensated for this by making the filter color lighter.

// Noise details in the wood, sandstone, and water are slightly different from the image in the book.
// The sandstone is different because the original image used row 5 in the sandstone texture ramp image,
// but the current code uses row 0.



void 												
World::build(void) {
//	int num_samples = 1;			// development
	int num_samples = 16;			// production
	
//	vp.set_hres(475);				// development
//	vp.set_vres(250); 
	vp.set_hres(950);				// production
	vp.set_vres(500);
	vp.set_samples(num_samples);	
	vp.set_max_depth(2);
		
	Ambient* ambient_ptr = new Ambient;
	ambient_ptr->scale_radiance(0.5);
	set_ambient_light(ambient_ptr);
	
	tracer_ptr = new Whitted(this);
	
	Pinhole* pinhole_ptr = new Pinhole;
	pinhole_ptr->set_eye(0, 15, 50);
	pinhole_ptr->set_lookat(0.4, 3.0, 0.0); 
//	pinhole_ptr->set_view_distance(600.0);		// for 475 x 250
	pinhole_ptr->set_view_distance(1200.0);   	// for 950 X 500
	pinhole_ptr->compute_uvw();
	set_camera(pinhole_ptr);
	
	PointLight* light_ptr = new PointLight;
	light_ptr->set_location(14, 50, 50);  
	light_ptr->scale_radiance(3.0);  
	light_ptr->set_shadows(true);
	add_light(light_ptr);
	
	
	
	// ************************************************************************************************* walls
	
	// these are not textured
	
	// back wall 
	
	Matte* matte_ptr1 = new Matte;		
	matte_ptr1->set_ka(0.75);
	matte_ptr1->set_kd(0.5);
	matte_ptr1->set_cd(0.85);  
	
	Plane* back_wall_ptr = new Plane(Point3D(0, 0, 0), Normal(0, 0, 1));
	back_wall_ptr->set_material(matte_ptr1);
	add_object(back_wall_ptr);
	
	
	// front wall 
	
	Matte* matte_ptr2 = new Matte;		
	matte_ptr2->set_ka(1.0);
	matte_ptr2->set_kd(0.5);
	matte_ptr2->set_cd(white);
	
	Plane* front_wall_ptr = new Plane(Point3D(0, 0, 51), Normal(0, 0, -1));
	front_wall_ptr->set_material(matte_ptr2);
	add_object(front_wall_ptr);
	
	
	// left wall 
	
	Matte* matte_ptr3 = new Matte;		
	matte_ptr3->set_ka(0.25);
	matte_ptr3->set_kd(0.75);
	matte_ptr3->set_cd(0.75, 1.0, 1.0);    
	
	Plane* left_wall_ptr = new Plane(Point3D(-15, 0, 0), Normal(1, 0, 0));
	left_wall_ptr->set_material(matte_ptr3);
	add_object(left_wall_ptr);

	
	// right wall 
	
	Matte* matte_ptr4 = new Matte;		
	matte_ptr4->set_ka(0.5);
	matte_ptr4->set_kd(0.5);
	matte_ptr4->set_cd(0.75, 1.0, 1.0); 

	Plane* right_wall_ptr = new Plane(Point3D(15, 0, 0), Normal(-1, 0, 0));
	right_wall_ptr->set_material(matte_ptr4);
	add_object(right_wall_ptr);
	
	
	// there is no ceiling
	
	
	
	// ************************************************************************************************* floor planks
	
	// plain material	
	
	Phong* phong_ptr = new Phong;		
	phong_ptr->set_ka(0.5);  
	phong_ptr->set_kd(1.0);
	phong_ptr->set_ks(0.2);  
	phong_ptr->set_exp(20.0);
	phong_ptr->set_cd(0.5, 0.3, 0.1);
			
	// the floor is a simulation of wood planks using beveled boxes with random lengths in the x direction
	
	double 	x0 					= -15.0;				// planks start at x = x0
	double 	z0 					= 0.0;					// planks start at z = z0
	double 	min_length 			= 4.0;   				// minumum plank length in x direction
	double 	max_length 			= 10.0;	  				// maximum plank length in x direction
	double 	plank_thickness 	= 1.0;					// common plank thickness - in y direction
	double 	y0					= -plank_thickness; 	// places top of planks at y = 0;
	double	plank_width			= 1.0;  				// common plank width 
	double 	plank_bevel			= 0.25;    				// the bevel radius
	int 	num_x_planks		= 6;					// number of planks in the x direction (a single column)
	int 	num_z_columns		= 50;  					// number of plank columns in the z direction
		
	Grid* planks_ptr = new Grid;
	
	for (int iz = 0; iz < num_z_columns; iz++) {     // to the front
		double p0x = x0;
		
		for (int ix = 0; ix < num_x_planks; ix++) {  // to the right
			TInstance* wood_ptr = new TInstance(new Wood(RGBColor(0.5, 0.3, 0.1), black));
			wood_ptr->scale(5.0);
			wood_ptr->rotate_y(90);
			set_rand_seed(ix * 1000 + iz * 10000);  // this must go right here
			wood_ptr->translate(10.0 * (2.0 * rand_float() - 1.0), 20.0 * (2.0 * rand_float() - 1.0), 30.0 * (2.0 * rand_float() - 1.0));
			
			SV_Phong* sv_phong_ptr = new SV_Phong;		
			sv_phong_ptr->set_ka(0.5);  
			sv_phong_ptr->set_kd(1);
			sv_phong_ptr->set_ks(0.2);  
			sv_phong_ptr->set_exp(20.0);
			sv_phong_ptr->set_cd(wood_ptr);
			sv_phong_ptr->set_cs(new ConstantColor());   // white, by default
				
			set_rand_seed(ix * 10000 + iz * 100);
			double plank_length = min_length + rand_float() * (max_length - min_length);
						
			Point3D p0(p0x ,y0, iz * plank_width);
			Point3D p1(p0x + plank_length, y0 + plank_thickness, (iz + 1) * plank_width);
		
			BeveledBox* plank_ptr = new BeveledBox(p0, p1, plank_bevel);
//			plank_ptr->set_material(phong_ptr);				// plain
			plank_ptr->set_material(sv_phong_ptr);	// textured
			planks_ptr->add_object(plank_ptr);
			
			p0x += plank_length;
		}
	}
		
	planks_ptr->setup_cells();
	add_object(planks_ptr);      
	
	
	
	// ************************************************************************************************* checkered cylinder
	
	// plain material 
	
	Matte* matte_ptr5 = new Matte;		
	matte_ptr5->set_ka(0.25);
	matte_ptr5->set_kd(0.95);
	matte_ptr5->set_cd(0.1, 0.4, 0.15);

	// textured material
	// this is a checker image
	
	Image* image_ptr1 = new Image;					
	image_ptr1->read_ppm_file("GreenAndYellow.ppm");
	CylindricalMap* cylindrical_map_ptr = new CylindricalMap;   
	ImageTexture* image_texture_ptr1 = new ImageTexture(image_ptr1); 
	image_texture_ptr1->set_mapping(cylindrical_map_ptr);

	SV_Matte* sv_matte_ptr1 = new SV_Matte;		
	sv_matte_ptr1->set_ka(0.25);
	sv_matte_ptr1->set_kd(0.95);
	sv_matte_ptr1->set_cd(image_texture_ptr1);
	
	OpenCylinder* cylinder_ptr1 = new OpenCylinder(-1.0, 1.0, 1.0);  // default
	cylinder_ptr1->set_material(matte_ptr5);			// plain
	cylinder_ptr1->set_material(sv_matte_ptr1); 		// textured
	
	Instance* cylinder_ptr2 = new Instance(cylinder_ptr1); 
	cylinder_ptr2->translate(Vector3D(0, 1, 0));
	cylinder_ptr2->scale(2, 2.5, 2);
	cylinder_ptr2->translate(Vector3D(-11, 0, 12));
	add_object(cylinder_ptr2);
	
	
	// a disk for the cylinder top
	// this is a 2D procedural checker texture designed to match the checkers
	// on the curved surface
	
	DiskChecker* disk_checker_ptr = new DiskChecker;
	disk_checker_ptr->set_num_angle_checkers(20);
	disk_checker_ptr->set_num_radial_checkers(4);
	disk_checker_ptr->set_angle_line_width(0.0);
	disk_checker_ptr->set_radial_line_width(0.0);
	disk_checker_ptr->set_color1(0.08, 0.39, 0.14);  	// dark green
	disk_checker_ptr->set_color2(1.0, 1.0, 0.5);		// yellow
	
	SV_Matte* sv_matte_ptr2 = new SV_Matte;		
	sv_matte_ptr2->set_ka(0.35);
	sv_matte_ptr2->set_kd(0.5);
	sv_matte_ptr2->set_cd(disk_checker_ptr);
	
	Disk* disk_ptr = new Disk;					// default - center (0, 0, 0), radius 1
//	disk_ptr->set_material(matte_ptr5);			// plain
	disk_ptr->set_material(sv_matte_ptr2);		// textured
	Instance* cylinder_top_ptr = new Instance(disk_ptr);
	cylinder_top_ptr->scale(2, 1, 2);
	cylinder_top_ptr->translate(-11, 5, 12);
	add_object(cylinder_top_ptr); 
	
	
	
	
	// ************************************************************************************************* Earth sphere
	
	// plain material
	
	Matte* matte_ptr6 = new Matte;		
	matte_ptr6->set_ka(0.5);
	matte_ptr6->set_kd(0.5);
	matte_ptr6->set_cd(0.2, 0.5, 1);

	// Earth image texture
	
	Image* image_ptr2 = new Image;					
//	image_ptr2->read_ppm_file("EarthLowRes.ppm");
	image_ptr2->read_ppm_file("EarthHighRes.ppm");
	SphericalMap* spherical_map_ptr = new SphericalMap;   
	ImageTexture* image_texture_ptr2 = new ImageTexture(image_ptr2); 
	image_texture_ptr2->set_mapping(spherical_map_ptr);
	
	SV_Matte* sv_matte_ptr3 = new SV_Matte;		
	sv_matte_ptr3->set_ka(0.5);
	sv_matte_ptr3->set_kd(0.95);
	sv_matte_ptr3->set_cd(image_texture_ptr2);
	
	Sphere* sphere_ptr = new Sphere;
//	sphere_ptr->set_material(matte_ptr6);				// plain 
	sphere_ptr->set_material(sv_matte_ptr3);			// textured with Earth image
		
	Instance* earth_ptr = new Instance(sphere_ptr);
	earth_ptr->rotate_y(75);
	earth_ptr->scale(3);
	earth_ptr->translate(-11, 8, 12);
	add_object(earth_ptr);
	


	// ************************************************************************************************* picture on back wall
	
	// this is initially constructed in the (x, z) plane, and then moved to the back wall
	// the picture and its frame are stored in a compound object:
	
	Compound* framed_picture_ptr = new Compound;
	
	// dimensions
	
	double a = 3.5;  	// +ve x coordinate of untransformed image
	double b = 5.05; 	// +ve z coordinate of untransformed image
	double w = 1.0;		// width of the frame
	
	
	// plain material picture
	
	Matte* matte_ptr7 = new Matte;		
	matte_ptr7->set_ka(0.75);
	matte_ptr7->set_kd(0.5);
	matte_ptr7->set_cd(0.3, 0.65, 0.71);
	
	// the image is applied to a rectangle
	
	Image* image_ptr3 = new Image;					
	image_ptr3->read_ppm_file("BlueGlass.ppm");
	
	SquareMap* square_map_ptr = new SquareMap;   
	
	ImageTexture* image_texture_ptr3 = new ImageTexture(image_ptr3); 
	image_texture_ptr3->set_mapping(square_map_ptr);
	
	SV_Matte* sv_matte_ptr4 = new SV_Matte;		
	sv_matte_ptr4->set_ka(0.5);
	sv_matte_ptr4->set_kd(0.75);
	sv_matte_ptr4->set_cd(image_texture_ptr3);
	
	
	// construct the picture
	
	Rectangle* rectangle_ptr = new Rectangle;
//	rectangle_ptr->set_material(matte_ptr7);  		// plain
	rectangle_ptr->set_material(sv_matte_ptr4);  	// textured with Blue Glass
	
	Instance* picture_ptr = new Instance(rectangle_ptr);  
	picture_ptr->scale(a, 1, b);

	
	// construct the frame
	
	// plain material for the frame
	
	Matte* matte_ptr8 = new Matte;		
	matte_ptr8->set_ka(0.75);
	matte_ptr8->set_kd(0.5);
	matte_ptr8->set_cd(0.5, 0.3, 0.14);
	
	
	// wood materials for the frame

	// for front and back sides

	TInstance* wood_ptr1 = new TInstance(new Wood(RGBColor(0.55, 0.43, 0.13), black));
	wood_ptr1->scale(Vector3D(2));
	wood_ptr1->rotate_y(90);
	
	SV_Matte* sv_matte_ptr5 = new SV_Matte;		
	sv_matte_ptr5->set_ka(1.0);
	sv_matte_ptr5->set_kd(1.0);
	sv_matte_ptr5->set_cd(wood_ptr1);
	
	// for right and left sides

	TInstance* wood_ptr2 = new TInstance(new Wood(RGBColor(0.55, 0.43, 0.13), black));
	wood_ptr2->scale(2.0);

	SV_Matte* sv_matte_ptr6 = new SV_Matte;		
	sv_matte_ptr6->set_ka(1.0);
	sv_matte_ptr6->set_kd(1.0);
	sv_matte_ptr6->set_cd(wood_ptr2);
	
		
	// construct the frame: two triangles per side
	
	// front side: +ve z before any transformations
	
	Triangle* triangle_ptr1 = new Triangle (Point3D(-a, 0, b), Point3D(-a - w, 0, b + w), Point3D(a + w, 0, b + w));
	triangle_ptr1->set_material(sv_matte_ptr5);
	framed_picture_ptr->add_object(triangle_ptr1);
	
	Triangle* triangle_ptr2 = new Triangle (Point3D(-a, 0, b), Point3D(a + w, 0, b + w), Point3D(a, 0, b));
	triangle_ptr2->set_material(sv_matte_ptr5);
	framed_picture_ptr->add_object(triangle_ptr2);
	
	
	// back side: -ve z before any transformations
	
	Triangle* triangle_ptr3 = new Triangle (Point3D(a, 0, -b), Point3D(a + w, 0, -b - w), Point3D(-a - w, 0, -b - w));
	triangle_ptr3->set_material(sv_matte_ptr5);
	framed_picture_ptr->add_object(triangle_ptr3);
	
	Triangle* triangle_ptr4 = new Triangle (Point3D(a, 0, -b), Point3D(-a - w, 0, -b - w), Point3D(-a, 0, -b));
	triangle_ptr4->set_material(sv_matte_ptr5);
	framed_picture_ptr->add_object(triangle_ptr4);
	
	
	// right side: +ve x before any transformations
	
	Triangle* triangle_ptr5 = new Triangle (Point3D(a, 0, b), Point3D(a + w, 0, b + w), Point3D(a + w, 0, -b - w));
	triangle_ptr5->set_material(sv_matte_ptr6);
	framed_picture_ptr->add_object(triangle_ptr5);
	
	Triangle* triangle_ptr6 = new Triangle (Point3D(a, 0, b), Point3D(a + w, 0, -b - w), Point3D(a, 0, -b));
	triangle_ptr6->set_material(sv_matte_ptr6);
	framed_picture_ptr->add_object(triangle_ptr6);
	
	
	// left side: -ve x before any transformations
	
	Triangle* triangle_ptr7 = new Triangle (Point3D(-a, 0, -b), Point3D(-a - w, 0, -b - w), Point3D(-a - w, 0, b + w));
	triangle_ptr7->set_material(sv_matte_ptr6);
	framed_picture_ptr->add_object(triangle_ptr7);
	
	Triangle* triangle_ptr8 = new Triangle (Point3D(-a, 0, -b), Point3D(-a - w, 0, b + w), Point3D(-a, 0, b));
	triangle_ptr8->set_material(sv_matte_ptr6);
	framed_picture_ptr->add_object(triangle_ptr8);
	
//	framed_picture_ptr->set_material(matte_ptr8);    // plain material for the frame - replaces all the wood textures - see Listing 19.13
	framed_picture_ptr->add_object(picture_ptr);	
	
	
	Instance* wall_picture_ptr = new Instance(framed_picture_ptr);	
	wall_picture_ptr->rotate_y(90);
	wall_picture_ptr->rotate_x(90);
	wall_picture_ptr->translate(-6, 8, 0.5);
	add_object(wall_picture_ptr);
	


	// ************************************************************************************************* bunny
	
	// plain material for the bunny	
	
	Matte* matte_ptr9 = new Matte;		
	matte_ptr9->set_ka(0.25);
	matte_ptr9->set_kd(0.75);   
	matte_ptr9->set_cd(0.8);	
	
	// ramp based marble texture
	
	Image* image_ptr4 = new Image;						
	image_ptr4->read_ppm_file("GrayMarbleRamp.ppm");
	
	int 	num_octaves = 4;
	float	fbm_amount 	= 3.0;
	TInstance* marble_ptr = new TInstance(new RampFBmTexture(image_ptr4, num_octaves, fbm_amount));
	marble_ptr->scale(0.0075);  // the bunny is small
	marble_ptr->translate(0.5, 0.0, 0.0);
	marble_ptr->rotate_x(100);
	marble_ptr->rotate_z(30);
	marble_ptr->rotate_y(20);

	// marble material

	SV_Matte* sv_matte_ptr7 = new SV_Matte;		
	sv_matte_ptr7->set_ka(0.25);
	sv_matte_ptr7->set_kd(0.75);
	sv_matte_ptr7->set_cd(marble_ptr);
	
	Mesh* mesh_ptr = new Mesh;
//	const char* fileName = "Bunny4K.ply"; 		// development 
	const char* fileName = "Bunny16K.ply";   	// production
	
	Grid* grid_ptr = new Grid(mesh_ptr);
	grid_ptr->read_smooth_triangles(fileName);
//	grid_ptr->set_material(matte_ptr9);			// plain
	grid_ptr->set_material(sv_matte_ptr7); 		// textured
	grid_ptr->setup_cells();
	
	Instance* bunny_ptr = new Instance(grid_ptr);
	bunny_ptr->scale(47.0);
	bunny_ptr->translate(-3.25, -1.65, 10);
	add_object(bunny_ptr);	
	
	
	
	// ************************************************************************************************* bath sides
	
	// the front and back sides of the bath run right across the bath in the x direction
	// the left and right sides fit between the front and back in the z direction
	// the sides are rows of beveled boxes with a random sandstone texture applied
	// these are stored in a single grid
	
	double 	bath_xmin 			= 1.0;
	double 	bath_zmin 			= 0.0;  
	double 	bath_xmax 			= 15.0;
	double 	bath_zmax 			= 15.0;   
	double 	x_size 				= bath_xmax - bath_xmin;
	double 	z_size 				= bath_zmax - bath_zmin;
	double 	thickness 			= 1.5;  	// common box thickness = side thickness
	double 	bath_height 		= 2.5;		// common box height 
	double 	bath_bevel_radius	= 0.25;  
	int  	num_xboxes			= 4;		// number of boxes along the back and front sides
	int 	num_zboxes			= 3;		// number of boxes along the left and right sides
		
	float 	bath_ka 			= 0.5;  	// common material property
	float 	bath_kd 			= 0.85; 	// common material property
	
	
	// plain material 
	
	Matte* matte_ptr10 = new Matte;				
	matte_ptr10->set_ka(bath_ka);
	matte_ptr10->set_kd(bath_kd);
	matte_ptr10->set_cd(0.53, 0.51, 0.45);
	
	
	// sandstone texture
	
	// Sandstone is implemented with a ramp marble texture
	
	Image* image_ptr5 = new Image;						
	image_ptr5->read_ppm_file("sandstone_ramp1.ppm");
	
	num_octaves = 4;
	fbm_amount	= 0.1;
	
	Grid* bath_ptr = new Grid;
	
	// build back - runs in x direction
	
	for (int j = 0; j < num_xboxes; j++) {
	
		// put a sandstone texture with a random set of intrinsic transformations on the beveled boxes
				
		TInstance* sandstone_ptr = new TInstance(new RampFBmTexture(image_ptr5, num_octaves, fbm_amount));
		sandstone_ptr->scale(2.0);
		set_rand_seed(j * 10);
		sandstone_ptr->rotate_x(20.0 * (2.0 * rand_float() - 1.0));
		sandstone_ptr->rotate_y(30.0 * (2.0 * rand_float() - 1.0));
		sandstone_ptr->rotate_z(45.0 * (2.0 * rand_float() - 1.0));
		sandstone_ptr->translate(10.0 * (2.0 * rand_float() - 1.0), 20.0 * (2.0 * rand_float() - 1.0), 30.0 * (2.0 * rand_float() - 1.0));
		
		SV_Matte* sv_matte_ptr = new SV_Matte;		
		sv_matte_ptr->set_ka(bath_ka);
		sv_matte_ptr->set_kd(bath_kd);
		sv_matte_ptr->set_cd(sandstone_ptr);
				
		BeveledBox* box_ptr = new BeveledBox(	Point3D(bath_xmin + j * (x_size / num_xboxes), 0, bath_zmin), 
												Point3D(bath_xmin + (j + 1) * (x_size / num_xboxes), bath_height, bath_zmin + thickness),
												bath_bevel_radius);
		box_ptr->set_material(sv_matte_ptr);
		bath_ptr->add_object(box_ptr);
	}
		
	// build front - runs in xw direction
	
	for (int j = 0; j < num_xboxes; j++) {
				
		TInstance* sandstone_ptr = new TInstance(new RampFBmTexture(image_ptr5, num_octaves, fbm_amount));
		sandstone_ptr->scale(2.0);
		set_rand_seed(j * 1000000);
		sandstone_ptr->rotate_x(20.0 * (2.0 * rand_float() - 1.0));
		sandstone_ptr->rotate_y(30.0 * (2.0 * rand_float() - 1.0));
		sandstone_ptr->rotate_z(45.0 * (2.0 * rand_float() - 1.0));
		sandstone_ptr->translate(10.0 * (2.0 * rand_float() - 1.0), 20.0 * (2.0 * rand_float() - 1.0), 30.0 * (2.0 * rand_float() - 1.0));
			
		SV_Matte* sv_matte_ptr = new SV_Matte;		
		sv_matte_ptr->set_ka(bath_ka);
		sv_matte_ptr->set_kd(bath_kd);
		sv_matte_ptr->set_cd(sandstone_ptr);
		
		BeveledBox* box_ptr = new BeveledBox(	Point3D(bath_xmin + j * (x_size / num_xboxes), 0, bath_zmax - thickness), 
												Point3D(bath_xmin + (j + 1) * (x_size / num_xboxes), bath_height, bath_zmax),
												bath_bevel_radius);
		box_ptr->set_material(sv_matte_ptr);
		bath_ptr->add_object(box_ptr);
	}
	
	
	// build left side - runs in yw direction
	
	for (int j = 0; j < num_zboxes; j++) {
		
		TInstance* sandstone_ptr = new TInstance(new RampFBmTexture(image_ptr5, num_octaves, fbm_amount));
		sandstone_ptr->scale(2.0);
		set_rand_seed(j * 1000);
		sandstone_ptr->rotate_x(20.0 * (2.0 * rand_float() - 1.0));
		sandstone_ptr->rotate_y(30.0 * (2.0 * rand_float() - 1.0));
		sandstone_ptr->rotate_z(45.0 * (2.0 * rand_float() - 1.0));
		sandstone_ptr->translate(10.0 * (2.0 * rand_float() - 1.0), 20.0 * (2.0 * rand_float() - 1.0), 30.0 * (2.0 * rand_float() - 1.0));
	
		SV_Matte* sv_matte_ptr = new SV_Matte;		
		sv_matte_ptr->set_ka(bath_ka);
		sv_matte_ptr->set_kd(bath_kd);
		sv_matte_ptr->set_cd(sandstone_ptr);
		
		BeveledBox* box_ptr = new BeveledBox(	Point3D(bath_xmin, 0, bath_zmin + thickness + j * ((z_size - 2 * thickness) / num_zboxes)),
												Point3D(bath_xmin + thickness, bath_height, bath_zmin + thickness + (j + 1) * ((z_size - 2 * thickness) / num_zboxes)),
												bath_bevel_radius);
		box_ptr->set_material(sv_matte_ptr);
		bath_ptr->add_object(box_ptr);
	}
	
	
	// build right side - runs in yw direction
	
	for (int j = 0; j < num_zboxes; j++) {
		
		TInstance* sandstone_ptr = new TInstance(new RampFBmTexture(image_ptr5, num_octaves, fbm_amount));
		sandstone_ptr->scale(2.0);
		set_rand_seed(j * 10000);
		sandstone_ptr->rotate_x(20.0 * (2.0 * rand_float() - 1.0));
		sandstone_ptr->rotate_y(30.0 * (2.0 * rand_float() - 1.0));
		sandstone_ptr->rotate_z(45.0 * (2.0 * rand_float() - 1.0));
		sandstone_ptr->translate(10.0 * (2.0 * rand_float() - 1.0), 20.0 * (2.0 * rand_float() - 1.0), 30.0 * (2.0 * rand_float() - 1.0));
	
		SV_Matte* sv_matte_ptr = new SV_Matte;		
		sv_matte_ptr->set_ka(bath_ka);
		sv_matte_ptr->set_kd(bath_kd);
		sv_matte_ptr->set_cd(sandstone_ptr);
		
		BeveledBox* box_ptr = new BeveledBox(	Point3D(bath_xmax - thickness, 0, bath_zmin + thickness + j * ((z_size - 2 * thickness) / num_zboxes)),
												Point3D(bath_xmax, bath_height, bath_zmin + thickness + (j + 1) * ((z_size - 2 * thickness) / num_zboxes)),
												bath_bevel_radius);
		box_ptr->set_material(sv_matte_ptr);
		bath_ptr->add_object(box_ptr);
	}
		
//	bath_ptr->set_material(matte_ptr10);  // sets plain material for all boxes
	bath_ptr->setup_cells();
	add_object(bath_ptr);
	
	
	
	// ************************************************************************************************* bath water
	
	// the bath water
	// this is a bump mapped rectangle with a transparent material	
	
	float c = 1.2;
	RGBColor water_color(0.50 * c, 0.8 * c, 0.8 * c); 
	Dielectric* water_ptr = new Dielectric;
	water_ptr->set_eta_in(1.33);		// water
	water_ptr->set_eta_out(1.0);		// air
	water_ptr->set_cf_in(water_color);
	water_ptr->set_cf_out(white);
	water_ptr->set_shadows(false);
	
	double waterHeight = bath_height - 0.45;
	Rectangle* water_surface_ptr = new Rectangle(	Point3D(bath_xmin + thickness - bath_bevel_radius, waterHeight, bath_zmin + thickness - bath_bevel_radius), 
													Vector3D(0, 0, z_size - 2 * thickness + 2 * bath_bevel_radius), 
													Vector3D(x_size - 2 * thickness + 2 * bath_bevel_radius, 0, 0),
													Normal(0, 1, 0));

	water_surface_ptr->set_shadows(false);
	water_surface_ptr->set_material(water_ptr);
//	add_object(water_surface_ptr);					// no bump map - use this for Figure 29.1

	// the bump mapped object
	
			num_octaves 		= 2;
	float 	lacunarity 			= 2.0;
	float 	gain 				= 0.33333;
	float 	perturbation_amount = 1.0;
	
	FBM_Bump* fBm_bump_ptr = new FBM_Bump(num_octaves, lacunarity, gain, perturbation_amount);    // Ken Musgrave's water
	
	BumpedObject* bumped_water_ptr = new BumpedObject;
	bumped_water_ptr->set_material(water_ptr);
	bumped_water_ptr->set_object(water_surface_ptr);
	bumped_water_ptr->set_bump_map(fBm_bump_ptr);
	add_object(bumped_water_ptr);					// use this for Figure 29.2





	// ************************************************************************************************* tiles

	// build reflective tiles on the wall behind the bath
	// these are beveled boxes with a spatially varying reflective material
	// there is grout between the tiles which is a rectangle just in front of the back wall
	// because the reflective material has no ambient, there are black areas in the image where the tiles are reflected in each other
	// this can be minimised by placing the back wall at z = 0.1 for a bevel radius of 0.25 and thickness of 0.6
	// this is where the grout rectangle should be.
		
	double 	tile_size 			= 3.25;	  						// tiles are square with dimensions tile_size in the x and y directions
	double	tile_thickness		= 0.6;							// tile thickness in the z direction 
	double	grout_width			= 0.25;							// the grout width
	double 	tiles_xmin 			= bath_xmin;					// left boundary of the tiles is at left side of bath
	double 	tiles_ymin 			= bath_height + grout_width; 	// tiles start at bath height + the grout width
	double 	tiles_zmin			= -tile_thickness / 2.0; 		// back wall goes through the middle of the tiles
	double 	tiles_zmax			= tile_thickness / 2.0;
	double 	tile_bevel_radius	= 0.25;    						// the bevel radius
	int 	num_x_tiles			= 4;							// number of tiles in the x direction
	int 	num_y_tiles			= 3;							// number of tiles in the y direction
	
	
	// plain material
	
	Reflective* reflective_ptr = new Reflective;		
	reflective_ptr->set_cr(0.75, 1.0, 0.85);
	reflective_ptr->set_kr(1.0);
		
	Grid* tiles_ptr = new Grid;
	
	for (int ix = 0; ix < num_x_tiles; ix++) {    	// across
		for (int iy = 0; iy < num_y_tiles; iy++) {  // up
			
			// the noise
			
			CubicNoise* noise_ptr = new CubicNoise;	
			noise_ptr->set_num_octaves(4);
			noise_ptr->set_gain(0.5);	
			noise_ptr->set_lacunarity(2.0);
			
			// the texture:

			TurbulenceTexture* texture_ptr = new TurbulenceTexture(noise_ptr);			
			texture_ptr->set_color(0.75, 1.0, 0.85);		// green
			texture_ptr->set_min_value(0.25);
	//		texture_ptr->set_max_value(1.0);   // original - now renders darker
			texture_ptr->set_max_value(1.2);   // new value - lighter
			
			TInstance* scaled_texture_ptr = new TInstance(texture_ptr); 
			scaled_texture_ptr->scale(0.5);
			
			// the material
			
			SV_Reflector* reflector_ptr = new SV_Reflector;
			reflector_ptr->set_kr(1.0);
			reflector_ptr->set_cr(scaled_texture_ptr);
			
			// the tiles
						
			Point3D p0(tiles_xmin + ix * (tile_size + grout_width), tiles_ymin + iy * (tile_size + grout_width), tiles_zmin);
			Point3D p1(tiles_xmin + (ix + 1) * tile_size + ix * grout_width, tiles_ymin + (iy + 1) * tile_size + iy * grout_width, tiles_zmax);
			BeveledBox* tile_ptr = new BeveledBox(p0, p1, tile_bevel_radius);
//			tile_ptr->set_material(reflective_ptr);  	// plain
			tile_ptr->set_material(reflector_ptr);		// textured
			tiles_ptr->add_object(tile_ptr);
		}
	}
		
	tiles_ptr->setup_cells();

	 	
	// ************************************************************************************************* grout
	
	// this is not textured
	
	Matte* matte_ptr11 = new Matte;
	matte_ptr11->set_ka(0.5);
	matte_ptr11->set_kd(0.75);
	matte_ptr11->set_cd(0.92, 0.85, 0.6);
	
	Rectangle* grout_ptr = new Rectangle(	Point3D(tiles_xmin, bath_height, tile_thickness / 2.0 - tile_bevel_radius * 0.666),
											Vector3D(num_x_tiles * (tile_size + grout_width), 0.0, 0.0),
											Vector3D(0.0, num_y_tiles * (tile_size + grout_width), 0.0));
	grout_ptr->set_material(matte_ptr11);	
										
	Compound* tiles_and_grout_ptr = new Compound; 
	tiles_and_grout_ptr->add_object(tiles_ptr); 
	tiles_and_grout_ptr->add_object(grout_ptr);
	
	Instance* instance_ptr = new Instance(tiles_and_grout_ptr);
	instance_ptr->translate(0, 0, -0.99 * (tile_thickness / 2.0 - tile_bevel_radius * 0.666));
	add_object(instance_ptr);
												
}


