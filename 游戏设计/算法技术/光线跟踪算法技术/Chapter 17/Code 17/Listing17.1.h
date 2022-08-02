class AmbientOccluder: public Light {
	public:
	
		AmbientOccluder(void); 
				...  							
	
		void
		set_sampler(Sampler* s_ptr);
	
		virtual Vector3D						
		get_direction(ShadeRec& sr);
	
		virtual bool									
		in_shadow(const Ray& ray, const ShadeRec& sr) const;
	
		virtual RGBColor
		L(ShadeRec& sr);
	
	private:
	
		float		ls;
		RGBColour	color;
		float 		min_amount;	    
		Vector3D 	u, v, w;		
		Sampler*	sampler_ptr;
};
