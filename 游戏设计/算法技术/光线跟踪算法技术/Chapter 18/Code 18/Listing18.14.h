class EnvironmentLight: public Light {	
	public:
		// constructors etc...
	
		void 
		set_sampler(Sampler* sampler); 
	
		virtual Vector3D												
		get_direction(ShadeRec& s);
	
		virtual RGBColor						
		L(ShadeRec& sr);
	
		virtual bool									
		in_shadow(const Ray& ray, const ShadeRec& sr) const;
		
		virtual float									
		pdf(const ShadeRec& sr) const;
	
	private:
	
		Sampler*	sampler_ptr;
		Material* 	material_ptr;
		Vector3D	u, v, w;		
		Vector3D	wi;
};
