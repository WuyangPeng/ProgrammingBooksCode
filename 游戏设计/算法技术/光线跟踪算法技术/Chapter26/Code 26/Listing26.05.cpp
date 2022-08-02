RGBColor
Reflective::path_shade(ShadeRec& sr) {		
	Vector3D 	wo = -sr.ray.d;
	Vector3D 	wi;	
	float 		pdf;
	RGBColor 	fr = reflective_brdf->sample_f(sr, wo, wi, pdf); 
	Ray 		reflected_ray(sr.hit_point, wi);
					
	return (fr * sr.w.tracer_ptr->trace_ray(reflected_ray, sr.depth + 1) * (sr.normal * wi) / pdf);
}
