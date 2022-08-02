void
ThinLens::set_sampler(Sampler* sp) {

	if (sampler_ptr) {
		delete sampler_ptr;
		sampler_ptr = NULL;
	}

	sampler_ptr = sp;
	sampler_ptr->map_samples_to_unit_disk();	
}
