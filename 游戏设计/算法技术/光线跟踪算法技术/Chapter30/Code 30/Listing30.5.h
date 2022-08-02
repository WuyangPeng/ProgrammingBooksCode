class TInstance: public Texture {	
	public:
	
		// constructors etc
	
		void 							
		set_texture(Texture* t_ptr);	
	
		virtual RGBColor&
		get_color(const shadeRec& sr) const;
	
		// affine tranformation functions:
	
		void												
		scale(const double sx, const double sy, const double sz);	
	
		// other affine transformations ...
	
	private:
	
		Texture* 	texture_ptr;	// texture being transformed
		Matrix		inv_matrix;		// inverse transformation matrix
};
