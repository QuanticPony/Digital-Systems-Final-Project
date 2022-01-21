/*
 * Particle.cpp
 *
 *  Created on: 5 ene 2022
 *      Author: QuanticPony
 */

#include <GL/glut.h>

Particle::Particle(float mass_initial, float radius_initial, float x_initial, float y_initial, float vx_initial, float vy_initial, bool is_moveable) {
	inv_mass = 1/mass_initial;
	radius = radius_initial;
	position.x = x_initial;
	position.y = y_initial;
	velocity.x = vx_initial;
	velocity.y = vy_initial;
	moveable = is_moveable;
}

Particle::Particle() {
	inv_mass = 1;
	position.x = 0;
	position.y = 0;
	velocity.x = 0;
	velocity.y = 0;
	radius = 0.5;
	moveable = true;
}

Particle::~Particle() {
	// TODO Auto-generated destructor stub
}

void Particle::evolve(float dt){
	// static float g = 0.5*WINDOW_HEIGHT;

	// velocity.add(Vector2D(0, -g*dt*dt));
	position.add(velocity.multiply(dt));
}