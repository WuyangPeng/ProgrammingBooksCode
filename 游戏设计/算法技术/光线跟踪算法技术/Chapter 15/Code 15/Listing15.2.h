class Phong: public Material {		
	public:
	
		// contructors, etc ...
	
		virtual RGBColor									
		shade(ShadeRec& s);		
	
	protected:
	
		Lambertian*		ambient_brdf;
		Lambertian*		diffuse_brdf;
		GlossySpecular*	specular_brdf;
};
