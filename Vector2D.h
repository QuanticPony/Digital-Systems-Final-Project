/*
 * Vector2D.h
 *
 *  Created on: 6 ene 2022
 *      Author: QuanticPony
 */

#ifndef VECTOR2D_H_
#define VECTOR2D_H_

class Vector2D
{
public:
	float x, y;

	Vector2D(float x_initial, float y_initial);
	Vector2D(); // Default constructor to null
	virtual ~Vector2D();

	float modulus(); // Returns the modulus of the main vector

	void add(Vector2D vector); // Adds the given vector to the main vector
	void scale(float value);   // Scale by value the main vector
	void aply_transformation(float x_scale, float y_scale); // Aplies a linear scaling transformation

	Vector2D normal();					// Returns the anticlockwise perpendicular vector
	Vector2D sume(Vector2D vector);		// Returns the sum of the vectors
	Vector2D subtract(Vector2D vector); // Returns the main vector minus the given vector
	Vector2D multiply(float value);		// Returns vector scaled by the given value
	Vector2D unitary();					// Returns unitary vector with the same direction
	Vector2D transform(float x_scale, float y_scale); // Retuns a linear scaling transformation of the min vector

	float dot(Vector2D vector); // Dot product with the given vector
};

#include "Vector2D.cpp"

#endif /* VECTOR2D_H_ */
