void
AmbientOccluder::set_sampler(Sampler* s_ptr) {
	if (sampler_ptr) {
		delete sampler_ptr;
		sampler_ptr = NULL;
	}
	
	sampler_ptr = s_ptr;
	sampler_ptr->map_samples_to_hemisphere(1);
}
