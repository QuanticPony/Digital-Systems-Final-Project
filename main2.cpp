/*
 * main.cpp
 *
 *  Created on: 5 January 2022
 *      Author: QuanticPony
 */

#include <stdio.h>
#include <math.h>
#include <windows.h> // For MS Windows
#include <GL/glut.h> // GLUT, includes glu.h and gl.h

#include "main.h"

#include "Vector2D.h"
#include "Line.h"
#include "Particle.h"
#include "Block.h"
#include "Collisions.h"

#include "Renderer.h"
#include "Simulation.h"

int ball_number = 400;

float my_random()
{
	return ((float) rand() / (RAND_MAX)) + 1;
}

void ensure_in_box(Particle &p){
	if (p.position.x < X_MIN+p.radius)
	{
		p.position.x = 2*(X_MIN+p.radius) - p.position.x;
		p.velocity.x = -p.velocity.x;
	}
	else if (p.position.x > X_MAX-p.radius)
	{
		p.position.x = 2*(X_MAX-p.radius) - p.position.x;
		p.velocity.x = -p.velocity.x;
	}

	p.position.x += p.velocity.x * delta_t;


	if (p.position.y < Y_MIN+p.radius)
	{
		p.position.y = 2*(Y_MIN+p.radius) - p.position.y;
		p.velocity.y = -p.velocity.y + 0.5 * WINDOW_HEIGHT * delta_t * delta_t;
	}
	else if (p.position.y > Y_MAX-p.radius)
	{
		p.position.y = 2*(Y_MAX-p.radius) - p.position.y;
		p.velocity.y = -p.velocity.y;
	}
	else {
		p.velocity.y -= 0.5 * WINDOW_HEIGHT * delta_t * delta_t;
	}
	p.position.y += p.velocity.y * delta_t;
}

void init_simulation()
{
	Particle balls[ball_number];

	for (int i = 0; i < ball_number; i++)
	{
		balls[i].position.x = my_random()*WINDOW_WIDTH;
		balls[i].position.y = my_random()*WINDOW_HEIGHT;
	
		balls[i].velocity.x = my_random()*20-5;
		balls[i].velocity.y = my_random()*20-5;

		balls[i].inv_mass = 1;
		balls[i].radius = my_random()*3 + 3;
		balls[i].inv_mass = 1/balls[i].radius;

		// balls[i].position.x = i==0? 200: 1000;
		// balls[i].position.y = i==0? 50: 50;
		// balls[i].velocity.x = i==0? 10: -10;
		// balls[i].velocity.y = 0;
		// balls[i].radius = 50;
		// balls[i].inv_mass = 1;
	}
	
	for (int b = 0; b < ball_number; b++)
	{

		for (int bb = b + 1; bb < ball_number; bb++)  
		{  
            if (Collisions::colliding(balls[b], balls[bb])){
                // printf("Collision");
                Collisions::resolveCollision(balls[b], balls[bb]);
            }
		}
        ensure_in_box(balls[b]);
        
	}
	
}

/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char **argv)
{
	glutInit(&argc, argv); // Initialize GLUT
	// glutInitDisplayMode(GLUT_DOUBLE);
	// glutInitDisplayMode();s
	// glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	//glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	X_MAX = WINDOW_WIDTH;
	Y_MAX = WINDOW_HEIGHT;
	
	My_Renderer my_renderer(ball_number);
	init_simulation();

	glutDisplayFunc();	  // Register display callback handler for window re-paint

	glutMainLoop();				  // Enter the infinitely event-processing loop
	return 0;
}
