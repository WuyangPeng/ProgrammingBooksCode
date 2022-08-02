Vector3D								
EnvironmentLight::get_direction(ShadeRec& sr) {
	w = sr.normal;
	v = (0.0034, 1, 0.0071) ^ w;
	v.normalize();
	u = v ^ w;
	Point3D sp = sampler_ptr->sample_hemisphere();	
	wi = sp.x * u + sp.y * v + sp.z * w;

	return (wi);
}
