/*
 * Line.h
 *
 *  Created on: 7 ene 2022
 *      Author: QuanticPony
 */

#ifndef LINE_H_
#define LINE_H_
#include "Vector2D.h"

class Line {
public:
	Vector2D position;
	Vector2D velocity;
    Vector2D line;
	float inv_mass;
    float left, right, top, bottom;
	bool moveable;

	Vector2D midpoint();
	Line(float mass, float x1, float y1, float x2, float y2, bool is_moveable);
    Line(Vector2D p1, Vector2D p2);
	static bool colliding(Line line1, Line line2);
	Line();
	virtual ~Line();
};

#include "Line.cpp"

#endif /* LINE_H_ */
