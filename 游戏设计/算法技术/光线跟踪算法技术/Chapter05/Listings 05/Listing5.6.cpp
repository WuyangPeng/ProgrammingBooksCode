void 												
World::render_scene(void) const {
	RGBColour	pixel_color;	 	
	Ray			ray;					
	float		zw		= 100.0;		
	Point2D		sp;		// sample point in [0, 1] x [0, 1] 
	Point2D 	pp;		// sample point on a pixel

	open_window(vp.hres, vp.vres);  
	ray.d = Vector3D(0, 0, -1);

	for (int r = 0; r < vp.vres; r++)				// up
		for (int c = 0; c <= vp.hres; c++) {		// across 

			pixel_color = black;

			for (int j = 0; j < vp.num_samples; j++) {	
				sp = vp.sampler_ptr->sample_unit_square();
				pp.x = vp.s * (c - 0.5 * vp.hres + sp.x);
				pp.y = vp.s * (r - 0.5 * vp.vres + sp.y);
				ray.o = Point3D(pp.x, pp.y, zw);				
				pixel_color += tracer_ptr->trace_ray(ray);        
			}

			pixel_color /= vp.num_samples; 	// average the colors
			display_pixel(r, c, pixel_color);
		}
}	 
