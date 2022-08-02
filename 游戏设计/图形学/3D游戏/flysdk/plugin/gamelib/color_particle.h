// color_particle implemets a particle with 
// color and transparency
class color_particle : public particle
{	
	public:

		vector color;	// the particle color
		int texture;	// texture image
		float size;		
	
	// moves the particle dt ms
	int step(int dt);

	// draws the particle
	void draw();
};
