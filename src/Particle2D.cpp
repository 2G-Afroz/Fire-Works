#include "../include/Particle2D.h"
#include <raylib.h>


Particle2D::Particle2D() {
	this->pos = {0, 0};
	this->vel = {0, 0};
	this->accn = {0, 0};
	this->color = WHITE;
	this->size = 5;
}
Particle2D::Particle2D(Vector2 position, Vector2 velocity, Vector2 acceleration) {
	this->pos = position;
	this->vel = velocity;
	this->accn = acceleration;
	this->color = WHITE;
	this->size = 5;
}
Particle2D::Particle2D(Vector2 position, Vector2 velocity, Vector2 acceleration, int size) {
	this->pos = position;
	this->vel = velocity;
	this->accn = acceleration;
	this->color = WHITE;
	this->size = size;
}
Particle2D::Particle2D(Vector2 position, Vector2 velocity, Vector2 acceleration, Color color) {
	this->pos = position;
	this->vel = velocity;
	this->accn = acceleration;
	this->color = color;
	size = 5;
}
Particle2D::Particle2D(Vector2 position, Vector2 velocity, Vector2 acceleration, Color color, int size) {
	this->pos = position;
	this->vel = velocity;
	this->accn = acceleration;
	this->color = color;
	this->size = size;
}
void Particle2D::update() {
	pos.x += accn.x;
	pos.y += accn.y;

	accn.x += vel.x;
	accn.y += vel.y;
}
void Particle2D::show() {
	DrawCircle(pos.x, pos.y, size, color);
}