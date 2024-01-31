#include "../include/Firework2D.h"

Firework2D::Firework2D(Vector2 position, Vector2 velocity, Vector2 acceleration, Color color , int size, bool exploder, Sound wistle, Sound brust)
	: Particle2D(position, velocity, acceleration, color, size), exploder(exploder), wistle(wistle), brust(brust), initAccnY(acceleration.y), colorAlpha(1) {
		if(!exploder)
			PlaySound(wistle);
}

Firework2D::Firework2D(Vector2 position, Vector2 velocity, Vector2 acceleration, int size, bool exploder, Sound wistle, Sound brust)
	: Particle2D(position, velocity, acceleration, size), exploder(exploder), wistle(wistle), brust(brust), initAccnY(acceleration.y), colorAlpha(1) {
		if(!exploder)
			PlaySound(wistle);
}

void Firework2D::update() {
	Particle2D::update();
	if(exploder){
		accn.x /= 1.03f;
		accn.y /= 1.03f;
		color = ColorAlpha(color, colorAlpha-=0.012);
	} else {
		SetSoundVolume(wistle, map(accn.y * -1, 0, initAccnY * -1, 0, 0.5f));
	}
}

void Firework2D::explode(std::vector<Firework2D>& exploders){
	PlaySound(brust);

	for(float a = 0; a < PI * 2; a+=0.01){
		exploders.push_back(
			Firework2D(
				pos,
				{0, 0.1},
				{cos(a) * GetRandomValue(1, 800)/100, sin(a) * GetRandomValue(1, 800)/100},
				color,
				std::max(1, size/5),
				true,
				wistle,
				brust
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

float Firework2D::getColorAlpha(){
	return colorAlpha;
}