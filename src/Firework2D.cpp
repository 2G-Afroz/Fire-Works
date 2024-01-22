#include "../include/Firework2D.h"
#include "../include/Utils.h"

Firework2D::Firework2D(Vector2 position, Vector2 velocity, Vector2 acceleration, Color color , int size, bool exploder, Sound wistle, Sound brust)
	: Particle2D(position, velocity, acceleration, color, size), exploder(exploder), wistle(wistle), brust(brust), initAccnY(acceleration.y) {
		if(!exploder)
			PlaySound(wistle);
}

void Firework2D::update() {
	Particle2D::update();
	SetSoundVolume(wistle, map(accn.y, 0, initAccnY, 0, 0.5f));
}

Vector2 Firework2D::getAccn(){
	return accn;
}

Vector2 Firework2D::getVelocity(){
	return vel;
}