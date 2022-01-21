/*
 * main.cpp
 *
 *  Created on: 5 January 2022
 *      Author: QuanticPony
 */

#include <stdio.h>
#include <math.h>
#include <windows.h>
#include <GL/glut.h>
#include <GL/freeglut.h>

#include "main.h"

#include "Vector2D.h"
#include "Line.h"
#include "Particle.h"
#include "Block.h"
#include "Collisions.h"

#include "Renderer.h"
#include "Simulation.h"

float my_random()
{
	return ((float)rand() / (RAND_MAX)) + 1;
}

void init_simulation(Simulation &simulation)
{
	for (int i = 0; i < simulation.balls_number; i++)
	{
		simulation.balls[i].position.x = my_random() * WINDOW_WIDTH;
		simulation.balls[i].position.y = my_random() * WINDOW_HEIGHT;

		simulation.balls[i].velocity.x = my_random() * 20 - 5;
		simulation.balls[i].velocity.y = my_random() * 20 - 5;

		simulation.balls[i].radius = my_random() * 10 + 1;
		simulation.balls[i].inv_mass = 1 / simulation.balls[i].radius;
		simulation.balls[i].moveable = true;

		// simulation.balls[i].position.x = WINDOW_WIDTH/2+5;
		// simulation.balls[i].position.y = WINDOW_HEIGHT * 3/4;
		// simulation.balls[i].velocity.x = 0;
		// simulation.balls[i].velocity.y = 0;
		// simulation.balls[i].radius = 30;
		// simulation.balls[i].inv_mass = 1;
		// simulation.balls[i].moveable = true;
	}
	simulation.lines[0] = Line(50, 0, 1, WINDOW_WIDTH, 1, false);
	simulation.lines[1] = Line(50, 0, WINDOW_HEIGHT-1, WINDOW_WIDTH, WINDOW_HEIGHT-1, false);

	simulation.blocks[0] = Block(1000, 200, 200, WINDOW_WIDTH*13/12, WINDOW_HEIGHT/2, -20, 0, true);
}

Simulation *simulation;
My_Renderer *my_renderer;
Block *in_front, *checker;

void display()
{
	simulation->evolve(10);
	my_renderer->clear();
	my_renderer->render(simulation->lines, simulation->lines_number);
	my_renderer->render(simulation->balls, simulation->balls_number);
	my_renderer->render(simulation->blocks, simulation->blocks_number);
	my_renderer->render(in_front, 1);
	my_renderer->render(checker, 1);
	my_renderer->swap_buffers();
}

void display_static()
{
	my_renderer->clear();
	my_renderer->render(simulation->lines, simulation->lines_number);
	my_renderer->render(simulation->balls, simulation->balls_number);
	my_renderer->render(simulation->blocks, simulation->blocks_number);
	my_renderer->swap_buffers();
}

void display_background()
{
	static bool first = true;

	my_renderer->clear();
	my_renderer->render(simulation->lines, simulation->lines_number);
	my_renderer->render(simulation->balls, simulation->balls_number);
	my_renderer->render(simulation->blocks, simulation->blocks_number);
	if (first) {
		my_renderer->render(in_front, 1);
	}
	my_renderer->swap_buffers();
	first = !first;
}

#include "Keyboard.h"

void checker_keyboard(unsigned char key, int x, int y){
	if (key==' '){
		stop_handler(true);
		glutIdleFunc([](){ Sleep(200); });
        glutDisplayFunc(display_background);
	}
	else keyboard(key, x, y);
}

int main(int argc, char **argv)
{
	X_MAX = WINDOW_WIDTH;
	Y_MAX = WINDOW_HEIGHT;

	Simulation _s(2, 60, 1);
	simulation = &_s;

	My_Renderer _mr(X_MIN, X_MAX, Y_MIN, Y_MAX);
	my_renderer = &_mr;

	Block _bb(1, WINDOW_WIDTH/3, WINDOW_HEIGHT, WINDOW_WIDTH/3, WINDOW_HEIGHT/2, 0, 0, false);
	in_front = &_bb;

	Block _cck(1, WINDOW_WIDTH/3, WINDOW_HEIGHT, 0, WINDOW_HEIGHT/2, 0, 0, false);
	checker = &_cck;
	
	init_simulation(*simulation);

	glutDisplayFunc(display);
	glutIdleFunc(display);
	glutKeyboardFunc(checker_keyboard);
	glutSpecialFunc(special_keyboard);

	glutMainLoop();
	return 0;
}