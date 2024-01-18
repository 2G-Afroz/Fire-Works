/**
 * @file Particle2D.cpp
 * @author Md Afroz Alam (2gafroz.tech)
 * @brief This C++ class defines a 2D particle with position, velocity, acceleration, color, and size.
 * 	It provides methods for updating and rendering the particle using the Raylib library.
 * @version 0.1
 * @date 2024-01-18
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <raylib.h>

class Particle2D {
	private:
		Vector2 pos, vel, accn;
		Color color;
		int size;
	
	public:
		/**
		 * @brief Construct a new Particle2D object.
		 * 
		 * @param position Inistion position of the particle.
		 * @param velocity Initial velocity of the particle.
		 * @param acceleration Initial acceleration of the particle.
		 */
		Particle2D(Vector2 position, Vector2 velocity, Vector2 acceleration) {
			this->pos = position;
			this->vel = velocity;
			this->accn = acceleration;
			color = WHITE;
			size = 2;
		}

		/**
		 * @brief Construct a new Particle2D object.
		 * 
		 * @param position Inistion position of the particle.
		 * @param velocity Initial velocity of the particle.
		 * @param color Initial color of the particle.
		 */
		Particle2D(Vector2 position, Vector2 velocity, Vector2 acceleration, Color color) {
			this->pos = position;
			this->vel = velocity;
			this->accn = acceleration;
			this->color = color;
			size = 2;
		}

		/**
		 * @brief Construct a new Particle2D object.
		 * 
		 * @param position Inistion position of the particle.
		 * @param velocity Initial velocity of the particle.
		 * @param color Initial color of the particle.
		 * @param size Initial size of the particle.
		 */
		Particle2D(Vector2 position, Vector2 velocity, Vector2 acceleration, Color color, int size) {
			this->pos = position;
			this->vel = velocity;
			this->accn = acceleration;
			this->color = color;
			this->size = size;
		}

		/**
		 * @brief This method updates the position and acceleration of the particle
		 * according to the velocity.
		 * 
		 */
		void update() {
			pos.x += accn.x;
			pos.y += accn.y;

			accn.x += vel.x;
			accn.y += vel.y;
		}

		/**
		 * @brief This method draws a circle at the current value of position.
		 * 
		 */
		void show() {
			DrawCircle(pos.x, pos.y, size, color);
		}
};