void
ViewPlane::set_samples(const int n) {
	num_samples = n;
	
	if (sampler_ptr) {
		delete sampler_ptr;
		sampler_ptr = NULL;
	}
	
	if (num_samples > 1)		
		sampler_ptr = new MultiJittered(num_samples);
	else
		sampler_ptr = new Regular(1);
}
