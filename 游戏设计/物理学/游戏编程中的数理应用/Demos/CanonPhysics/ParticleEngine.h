#ifndef PARTICLEENGINE_H
#define PARTICLEENGINE_H

#include <vector>

class ParticleEngine
{
	public:
		void Create(float _x, float _y);
		void Update(void);
		void Render(void) const;

		inline static ParticleEngine &instance(void)
		{
			static ParticleEngine inst;
			return inst;
		}

	private:
		enum { MAX_PARTICLES = 30, };

		struct Particle
		{
			float x, y;
			float vel_x, vel_y;
			float red, green, blue, alpha;
		};

		std::vector<Particle> activeList;
		std::vector<Particle> deadList;

		ParticleEngine(void);
		~ParticleEngine(void) { }
};

#endif
