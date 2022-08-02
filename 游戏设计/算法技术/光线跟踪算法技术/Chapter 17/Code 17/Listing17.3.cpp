Vector3D
AmbientOccluder::get_direction(void) {
	Point3D sp = sampler_ptr->sample_hemisphere();
	return (sp.x * u + sp.y * v + sp.z * w);
}	
