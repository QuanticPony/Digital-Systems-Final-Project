/*
 * Map.h
 *
 *  Created on: 7 ene 2022
 *      Author: QuanticPony
 */

#ifndef MAP_H_
#define MAP_H_
#include "Vector2D.cpp"

class Map {
public:
	Vector2D position, velocity;
	float radius;
	float inv_mass;
	Map(float mass, float radius, float x_initial, float y_initial, float vx_initial, float vy_initial);
	bool colliding(Map ball);
	void resolveCollision(Map &ball);
	Map();
	virtual ~Map();
};

#endif /* MAP_H_ */
