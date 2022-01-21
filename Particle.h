/*
 * Particle.h
 *
 *  Created on: 5 ene 2022
 *      Author: QuanticPony
 */

#ifndef PARTICLE_H_
#define PARTICLE_H_

#include "Vector2D.h"

class Particle
{
public:
	Vector2D position, velocity;
	float radius;
	float inv_mass;
	bool moveable;

	Particle(float mass, float radius, float x_initial, float y_initial, float vx_initial, float vy_initial, bool is_moveable);
	Particle();
	virtual ~Particle();

	void evolve(float dt); // Evolves the particle the given diferential time
};

#include "Particle.cpp"

#endif /* PARTICLE_H_ */
