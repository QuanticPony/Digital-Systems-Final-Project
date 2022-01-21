/*
 * Block.cpp
 *
 *  Created on: 7 ene 2022
 *      Author: QuanticPony
 */

Block::Block(float mass_initial, float width, float height, float x_initial, float y_initial, float vx_initial, float vy_initial, bool is_moveable) {
	inv_mass = 1/mass_initial;
	w = width;
	h = height;
	position.x = x_initial;
	position.y = y_initial;
	velocity.x = vx_initial;
	velocity.y = vy_initial;
	moveable = is_moveable;
	radius = sqrtf(w*w/4 + h*h/4);

	
}

void Block::update_sides()
{
	sides[0] = Line(position.sume(Vector2D(-w/2, -h/2)), position.sume(Vector2D(-w/2, h/2)));
	sides[1] = Line(position.sume(Vector2D(-w/2, h/2)), position.sume(Vector2D(w/2, h/2)));
	sides[2] = Line(position.sume(Vector2D(w/2, h/2)), position.sume(Vector2D(w/2, -h/2)));
	sides[3] = Line(position.sume(Vector2D(w/2, -h/2)), position.sume(Vector2D(-w/2, -h/2)));
}

Block::Block() {
	inv_mass = 1;
	w = h = 5;
	position.x = 0;
	position.y = 0;
	velocity.x = 0;
	velocity.y = 0;
	radius = sqrtf(w*w + h*h);
	moveable = true;
}

Block::~Block() {
	// TODO Auto-generated destructor stub
}


void Block::evolve(float delta_t){
	// static float g = 0.5*WINDOW_HEIGHT;

	// velocity.add(Vector2D(0, -g*delta_t*delta_t));
	position.add(velocity.multiply(delta_t));
}