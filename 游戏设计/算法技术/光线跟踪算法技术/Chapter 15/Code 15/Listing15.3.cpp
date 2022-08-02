RGBColor
Phong::shade(ShadeRec& sr) {
	Vector3D 	wo 			= -sr.ray.d;
	RGBColor 	L 			= ambient_brdf->rho(sr, wo) * sr.w.ambient_ptr->L(sr);
	int 		num_lights	= sr.w.lights.size();
	
	for (int j = 0; j < num_lights; j++) {
		Vector3D wi = sr.w.lights[j]->get_direction(sr);    
		float ndotwi = sr.normal * wi;
	
		if (ndotwi > 0.0) 
			L += (	diffuse_brdf->f(sr, wo, wi) + 
					specular_brdf->f(sr, wo, wi)) * sr.w.lights[j]->L(sr) * ndotwi;
	}
	
	return (L);
}
