void						
Pinhole::render_stereo(World& w, float x, int pixel_offset) {
	RGBColour	L;	 	
	Ray			ray;
	ViewPlane	vp 			= w.vp;					
	int 		depth 		= 0;  
	Point2D 	sp; 				// sample point in [0, 1] X [0, 1]
	Point2D 	pp;					// sample point on the pixel
	
	vp.s /= zoom;	
	ray.o = eye;
	
	for (int r = 0; r < vp.vres; r++)			// up
		for (int c = 0; c < vp.hres; c++) {		// across 					
			L = black; 	

			for (int j = 0; j < vp.num_samples; j++) {	
				sp = vp.sampler_ptr->sample_unit_square();
				pp.x = vp.s * (c - 0.5 * vp.hres + sp.x) + x; 	// asymmetric view frustum
				pp.y = vp.s * (r - 0.5 * vp.vres + sp.y);
				ray.d = get_direction(pp);				
				L += w.tracer_ptr->trace_ray(ray, depth);
			}
										
			L /= vp.num_samples;
			L *= exposure_time;	
			w.display_pixel(r, c + pixel_offset, L);
		} 
}
