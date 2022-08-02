void
ViewPlane::set_sampler(Sampler* sp) {
	
	if (sampler_ptr) {
		delete sampler_ptr;
		sampler_ptr = NULL;
	}
		
	num_samples = sp->get_num_samples();
	sampler_ptr = sp;
}
