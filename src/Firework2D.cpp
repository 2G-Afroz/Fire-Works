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


void Firework2D::explodeRectangle(std::vector<Firework2D>& exploders) {
	PlaySound(brust);

	for(int i = 0; i < 600; i++){
		exploders.push_back(
			Firework2D(
				pos,
				{0, GetRandomValue(180, 220)/1000.0f},
				{GetRandomValue(-800, 800)/91.0f, (float)GetRandomValue(-1200, 400)/91.0f},
				color,
				std::max(1, size/5),
				true,
				wistle,
				brust
			)
		);
	}
}

void Firework2D::explodeHeart(std::vector<Firework2D>& exploders) {
	PlaySound(brust);

	// Bottom Heart 'V'
	for(float ang = 0; ang < PI; ang+=0.005){
		// This formula is used to create SuperShape
		float x = pow(abs(cos(ang)), 2) * GetRandomValue(400, 850)/100.0f  * sgn(cos(ang));
		float y = pow(abs(sin(ang)), 2) * GetRandomValue(400, 850)/100.0f * sgn(sin(ang));
    	exploders.push_back(
			Firework2D(
				pos,
				{0, GetRandomValue(200, 230)/1000.0f},
				{x, y},
				color,
				std::max(1, size/5),
				true,
				wistle,
				brust
			)
		);
	}
	// Left Arc
	for(float ang = 3 * PI / 4; ang < 7 * PI / 4 + 0.5f; ang+=0.01){
		// This formula is used to create SuperShape
		float x = pow(abs(cos(ang)), 1) * GetRandomValue(250, 560)/100.0f * sgn(cos(ang));
		float y = pow(abs(sin(ang)), 1) * GetRandomValue(250, 560)/100.0f * sgn(sin(ang));
		exploders.push_back(
			Firework2D(
				//{pos.x - 60, pos.y - 60},
				pos,
				{0, GetRandomValue(180, 220)/1000.0f},
				{x - 3, y - 3},
				color,
				std::max(1, size/5),
				true,
				wistle,
				brust
			)
		);
	}
	// Right Arc
	for(float ang = 5 * PI / 4 - 0.5f; ang < 9 * PI / 4; ang+=0.01){
		// This formula is used to create SuperShape
		float x = pow(abs(cos(ang)), 1) * GetRandomValue(250, 560)/100.0f * sgn(cos(ang));
		float y = pow(abs(sin(ang)), 1) * GetRandomValue(250, 560)/100.0f * sgn(sin(ang));
		exploders.push_back(
			Firework2D(
				//{pos.x - 60, pos.y - 60},
				pos,
				{0, GetRandomValue(180, 220)/1000.0f},
				{x + 3, y - 3},
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