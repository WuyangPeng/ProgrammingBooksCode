class Dielectric: public Phong {	
	public:
			...
		
		virtual RGBColor				
		shade(ShadeRec& s);	
		
	private:
		
		RGBColor 			cf_in;			// interior filter color 
		RGBColor 			cf_out;			// exterior filter color
		
		FresnelReflector*	fresnel_brdf;
		FresnelTransmitter*	fresnel_btdf;
};
