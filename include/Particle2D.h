#ifndef PARTICLE2D_H
#define PARTICLE2D_H

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
	protected:
		Vector2 pos, vel, accn;
		Color color;
		int size;

	public:
		/**
		 * @brief Construct a new Particle2D object
		 * 
		 * This is Default constructor.
		 */
		Particle2D();

		/**
		 * @brief Construct a new Particle2D object.
		 * 
		 * @param position Inistion position of the particle.
		 * @param velocity Initial velocity of the particle.
		 * @param acceleration Initial acceleration of the particle.
		 */
		Particle2D(Vector2 position, Vector2 velocity, Vector2 acceleration);

		/**
		 * @brief Construct a new Particle2D object.
		 * 
		 * @param position Inistion position of the particle.
		 * @param velocity Initial velocity of the particle.
		 * @param acceleration Initial acceleration of the particle.
		 * @param size Initial size of the particle.
		 */
		Particle2D(Vector2 position, Vector2 velocity, Vector2 acceleration, int size);

		/**
		 * @brief Construct a new Particle2D object.
		 * 
		 * @param position Inistion position of the particle.
		 * @param velocity Initial velocity of the particle.
		 * @param acceleration Initial acceleration of the particle.
		 * @param color Initial color of the particle.
		 */
		Particle2D(Vector2 position, Vector2 velocity, Vector2 acceleration, Color color);

		/**
		 * @brief Construct a new Particle2D object.
		 * 
		 * @param position Inistion position of the particle.
		 * @param velocity Initial velocity of the particle.
		 * @param acceleration Initial acceleration of the particle.
		 * @param color Initial color of the particle.
		 * @param size Initial size of the particle.
		 */
		Particle2D(Vector2 position, Vector2 velocity, Vector2 acceleration, Color color, int size);

		/**
		 * @brief This method updates the position and acceleration of the particle
		 * according to the velocity.
		 * 
		 */
		void update();

		/**
		 * @brief This method draws a circle at the current value of position.
		 * 
		 */
		void show();
};

#endif