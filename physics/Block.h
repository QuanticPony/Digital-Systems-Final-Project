/*
 * Block.h
 *
 *  Created on: 7 ene 2022
 *      Author: QuanticPony
 */

#ifndef BLOCK_H_
#define BLOCK_H_
#include "Vector2D.h"
#include "Line.h"

class Block {
public:
	Vector2D position, velocity;
	float w,h;
	float inv_mass;
	float radius;
	bool moveable;
	Line sides[4];
	Block(float mass_initial, float width, float height, float x_initial, float y_initial, float vx_initial, float vy_initial, bool is_moveable);
	Block();
	void evolve(float delta_t);
	void update_sides();
	virtual ~Block();
};

#include "Block.cpp"

#endif /* BLOCK_H_ */
