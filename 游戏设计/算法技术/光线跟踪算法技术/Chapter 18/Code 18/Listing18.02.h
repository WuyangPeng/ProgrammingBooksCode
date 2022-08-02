class Emissive: public Material {	
	private:
	
		float		ls;		// radiance scaling factor						 
		RGBColor 	ce;		// color
	
	public:
	
		// constructors, set functions, etc ...
	
		void
		scale_radiance(const float _ls);
	
		void									
		set_ce(const float r, const float g, const float b);
		
		virtual RGBColor
		get_Le(ShadeRec& sr) const;	
	
		virtual RGBColor										
		shade(ShadeRec& sr);
	
		virtual RGBColor										
		area_light_shade(ShadeRec& sr);	
};
