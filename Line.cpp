/*
 * Line.cpp
 *
 *  Created on: 7 ene 2022
 *      Author: QuanticPony
 */

#include <GL/glut.h>

Line::Line(){
    *this = Line(1,0,0,0,0,false);
}

Line::Line(float mass, float x1, float y1, float x2, float y2, bool is_moveable) {
    inv_mass = 1/mass;
	position.x = x1;
    position.y = y1;
    line.x = x2-x1;
    line.y = y2-y1;
    moveable = is_moveable;
    
    if (x1<x2) {
        left = x1;
        right = x2;
    }
    else {
        left = x2;
        right = x1;
    }
    if (y1<y2) {
        bottom = y1;
        top = y2;
    }
    else {
        bottom = y2;
        top = y1;
    }
}

Vector2D Line::midpoint(){
    return position.sume(line.multiply(0.5));
}

Line::Line(Vector2D p1, Vector2D p2) {
	position = p1;
    line = p2.subtract(p1);
}

Line::~Line() {
	// TODO Auto-generated destructor stub
}