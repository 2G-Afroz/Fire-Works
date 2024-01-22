#include "../include/Firework2D.h"
#include "../include/Utils.h"

Firework2D::Firework2D(Vector2 position, Vector2 velocity, Vector2 acceleration, Color color , int size, bool exploder, Sound wistle, Sound brust)
	: Particle2D(position, velocity, acceleration, color, size), exploder(exploder), wistle(wistle), brust(brust), initAccnY(acceleration.y) {
		if(!exploder)
			PlaySound(wistle);
}

Firework2D::Firework2D(Vector2 position, Vector2 velocity, Vector2 acceleration, int size, bool exploder, Sound wistle, Sound brust)
	: Particle2D(position, velocity, acceleration, size), exploder(exploder), wistle(wistle), brust(brust), initAccnY(acceleration.y) {
		if(!exploder)
			PlaySound(wistle);
}

void Firework2D::update() {
	Particle2D::update();
	SetSoundVolume(wistle, map(accn.y, 0, initAccnY, 0, 0.5f));
}

void Firework2D::explode(std::vector<Particle2D>& exploders){
	PlaySound(brust);
	for(int i = 0; i < 600; i++){
    exploders.push_back(
      Particle2D(
        pos,
        {0, GetRandomValue(180, 220)/1000.0f},
        {GetRandomValue(-400, 400)/150.0f, (float)GetRandomValue(-800, 0)/150.0f},
		color,
		2
      )
    );
  }
}

Vector2 Firework2D::getAccn(){
	return accn;
}

Vector2 Firework2D::getVelocity(){
	return vel;
}