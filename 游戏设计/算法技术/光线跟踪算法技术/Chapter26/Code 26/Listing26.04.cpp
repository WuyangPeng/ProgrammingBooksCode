RGBColor							
Matte::path_shade(ShadeRec& sr) {
	Vector3D 	wo = -sr.ray.d;
	Vector3D 	wi;
	float 		pdf;
	RGBColor 	f = diffuse_brdf->sample_f(sr, wo, wi, pdf);   
	float 		ndotwi = sr.normal * wi;
	Ray 		reflected_ray(sr.hit_point, wi);
	
	return (f * sr.w.tracer_ptr->trace_ray(reflected_ray, sr.depth + 1) * ndotwi / pdf);
}
