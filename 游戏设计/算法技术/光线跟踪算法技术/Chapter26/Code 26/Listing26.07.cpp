RGBColor							
Matte::global_shade(ShadeRec& sr) {
	RGBColor L;
	
	if (sr.depth == 0)
		L = area_light_shade(sr); 
	
	Vector3D 	wi;
	Vector3D 	wo 		= -sr.ray.d;
	float 		pdf;
	RGBColor 	f 		= diffuse_brdf->sample_f(sr, wo, wi, pdf);   
	float 		ndotwi 	= sr.normal * wi;
	Ray 		reflected_ray(sr.hit_point, wi);
	
	L += f * sr.w.tracer_ptr->trace_ray(reflected_ray, sr.depth + 1) * ndotwi / pdf;
	
	return (L);
}
