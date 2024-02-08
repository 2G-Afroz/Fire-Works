#ifndef FIREWORK2D_H
#define FIREWORK2D_H

#include "../include/Particle2D.h"
#include "../include/Utils.h"
#include <algorithm>

class Firework2D : public Particle2D {
	private:
		bool exploder;
		Sound wistle, brust;
		float initAccnY;
		float colorAlpha;
	public:
		Firework2D(Vector2 position, Vector2 velocity, Vector2 acceleration, Color color , int size, bool exploder, Sound wistle, Sound brust);
		Firework2D(Vector2 position, Vector2 velocity, Vector2 acceleration, int size, bool exploder, Sound wistle, Sound brust);

		void update();

		void explode(std::vector<Firework2D>& exploders);
		void explodeRectangle(std::vector<Firework2D>& exploders);
		void explodeHeart(std::vector<Firework2D>& exploders);

		Vector2 getAccn();

		Vector2 getVelocity();

		float getColorAlpha();

};

#endif
