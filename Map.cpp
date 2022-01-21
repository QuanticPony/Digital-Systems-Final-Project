/*
 * Map.cpp
 *
 *  Created on: 7 ene 2022
 *      Author: QuanticPony
 */

#include "Map.h"

Map::Map(float mass_initial, float radius_initial, float x_initial, float y_initial, float vx_initial, float vy_initial) {
	inv_mass = 1/mass_initial;
	radius = radius_initial;
	position.x = x_initial;
	position.y = y_initial;
	velocity.x = vx_initial;
	velocity.y = vy_initial;
}

Map::Map() {
	inv_mass = 1;
	position.x = 0;
	position.y = 0;
	velocity.x = 0;
	velocity.y = 0;
	radius = 0.5;
}

Map::~Map() {
	// TODO Auto-generated destructor stub
}

bool Map::colliding(Map ball)
{
    float sumRadius = radius + ball.radius;
    return position.difference(ball.position).modulus() <= sumRadius;
}

void Map::resolveCollision(Map &ball)
{
	float inv_M = 1/(1/inv_mass + 1/ball.inv_mass);
	
	Vector2D dV = velocity.subtract(ball.velocity);
	Vector2D dX = position.subtract(ball.position);
	float dX_m = dX.modulus();

	float dot = dV.dot(dX);
	if (dot>=0){
		return;
	}
	// printf("%.3f - %.3f\n", dot/dX_m, -2*inv_M/ball.inv_mass);
	velocity.add(dX.multiply(-2*inv_M/ball.inv_mass*dot/dX_m/dX_m));
	dX.scale(-1);
	dV.scale(-1);
	ball.velocity.add(dX.multiply(-2*inv_M/inv_mass*dot/dX_m/dX_m));
}