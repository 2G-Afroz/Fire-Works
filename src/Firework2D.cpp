#include "../include/Firework2D.h"

Firework2D::Firework2D(Vector2 position, Vector2 velocity, Vector2 acceleration, Color color , int size, bool exploder, Sound wistle, Sound brust)
	: Particle2D(position, velocity, acceleration, color, size), exploder(exploder), wistle(wistle), brust(brust), vol(1) {
		if(!exploder)
			PlaySound(wistle);
}

void Firework2D::update() {
	if(accn.x >= vel.x){
		Particle2D::update();
	}
}