/*
 * Vector2D.cpp
 *
 *  Created on: 5 ene 2022
 *      Author: QuanticPony
 */

#include "Vector2D.h"
#include <cmath>

Vector2D::Vector2D(float x_initial, float y_initial) {
	x = x_initial;
	y = y_initial;
}

Vector2D::Vector2D() {
	x = 0;
	y = 0;
}

Vector2D::~Vector2D() {
	// TODO Auto-generated destructor stub
}

float Vector2D::modulus()
{
    return sqrtf(x*x + y*y);
}

Vector2D Vector2D::normal()
{
    return Vector2D(-y, x);
}

Vector2D Vector2D::unitary()
{
	float norm = modulus();
	return multiply(1/norm);
}

void Vector2D::add(Vector2D vector)
{
	x += vector.x;
	y += vector.y;
}

void Vector2D::aply_transformation(float x_scale, float y_scale)
{
	x *= x_scale;
	y *= y_scale;
}

Vector2D Vector2D::multiply(float value)
{
	return Vector2D(x*value, y*value);
}

void Vector2D::scale(float value)
{
	x *= value;
	y *= value;
}

Vector2D Vector2D::sume(Vector2D vector)
{
	return Vector2D(x+vector.x, y+vector.y);
}

Vector2D Vector2D::subtract(Vector2D vector)
{
	return Vector2D(x-vector.x, y-vector.y);
}

Vector2D Vector2D::transform(float x_scale, float y_scale)
{
	return Vector2D(x*x_scale, y*y_scale);
}

float Vector2D::dot(Vector2D vector)
{
	return x*vector.x + y*vector.y;
}