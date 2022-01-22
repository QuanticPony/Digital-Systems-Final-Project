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

#define SEGMENTS_IN_CIRCLE 20

#include "physics.h"

float my_random()
{
	return ((float)rand() / (RAND_MAX));
}

int counter = 0;

void init_simulation(Simulation &simulation)
{
    simulation.balls[0] = Particle(100, 50, WINDOW_WIDTH/10, 51, 0.00001, 0, true);

	for (int i = 0; i < simulation.blocks_number; i++)
	{
        float w, h;
        w = 0.05*(1+my_random())*WINDOW_WIDTH;
        h = 0.15*(0.5+my_random())*WINDOW_HEIGHT;
        simulation.blocks[i] = Block(1000, w, h, 3*WINDOW_WIDTH/4, h/2, -15, 0, false);

        if (my_random()<0.3) {
            simulation.blocks[i].position.y = my_random() * (WINDOW_HEIGHT - h) + h/2 + 1;
        }
        else{
            simulation.blocks[i].position.y = h/2 + 1;
        }

        if(i>0) {
            simulation.blocks[i].position.x = 0.7 * my_random() * WINDOW_WIDTH + simulation.blocks[i-1].position.x;
        }
        else{
            simulation.blocks[i].position.x = (1.3) * WINDOW_WIDTH;
        }
		
	}
	simulation.lines[0] = Line(50, 0, 1, WINDOW_WIDTH, 1, false);
}

Simulation *simulation;
My_Renderer *my_renderer;
Particle *dinosaur;
bool can_jump;

#include "physics/Keyboard.h"

void display()
{
    if (dinosaur->position.y < dinosaur->radius*1.1){
        can_jump = true;
    }
    for (int bb=0; bb<simulation->blocks_number; bb++){
        if (dinosaur->position.subtract(simulation->blocks[bb].position).modulus() < 1.1*(dinosaur->radius + simulation->blocks[bb].radius))
            can_jump = true;
    }
    for (int i = 0; i < 10; i++)
    {
        if (Collisions::colliding(simulation->lines[0], *dinosaur)){
            dinosaur->position.y = dinosaur->radius+1;
            dinosaur->velocity.y = 0;
        }
        if (dinosaur->position.y > dinosaur->radius *1.1){
            dinosaur->velocity.y -= 50 *simulation->delta_t * simulation->delta_t;
        }
        simulation->evolve(1);
    }
    if (simulation->blocks[simulation->blocks_number-1].position.x <= 0){
        Particle temporal_dinosaur = *dinosaur;
        init_simulation(*simulation);
        dinosaur = simulation->balls;
        *dinosaur = temporal_dinosaur;
    }

    if (dinosaur->velocity.x < -0.1){
        stop_handler(true);
    }
    dinosaur->velocity.x = 0;
    
	
	my_renderer->clear();
	my_renderer->render(simulation->lines, simulation->lines_number, 1,1,1);
	my_renderer->render(simulation->balls, simulation->balls_number, 0,1,0);
	my_renderer->render(simulation->blocks, simulation->blocks_number, 1,0,0);
	
    // glRasterPos2f(5, 5);
    char score[1];
    sprintf(score, "%d", counter);
    glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (unsigned char*) score);
    glRasterPos2f(0.8, 0.9);
    my_renderer->swap_buffers();
    counter += 1;
    Sleep(1);
}

void display_static()
{
	my_renderer->clear();
	my_renderer->render(simulation->lines, simulation->lines_number, 1,1,1);
	my_renderer->render(simulation->balls, simulation->balls_number, 0,1,0);
	my_renderer->render(simulation->blocks, simulation->blocks_number, 1,0,0);

    char score[1];
    sprintf(score, "%d", counter);
    glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (unsigned char*) score);
    glRasterPos2f(0.8, 0.9);
    my_renderer->swap_buffers();

	my_renderer->swap_buffers();
}

void player_keyboard(unsigned char key, int x, int y){
	if (key=='r'){
        counter = 0;
    }
    if (key==' '){
        printf("Pulsacion:\n");
        printf("%.2f", dinosaur->velocity.y);        
        if (can_jump) {
            dinosaur->velocity.y = 200 * sqrtf(simulation->delta_t);
            can_jump = false;
        }
	}
	else keyboard(key, x, y);
}

int main(int argc, char **argv)
{
	X_MAX = WINDOW_WIDTH;
	Y_MAX = WINDOW_HEIGHT;

	Simulation _s(1, 1, 10);
    _s.delta_t = 0.02;
	simulation = &_s;

	My_Renderer _mr(X_MIN, X_MAX, Y_MIN, Y_MAX);
	my_renderer = &_mr;

	dinosaur = simulation->balls;

	init_simulation(*simulation);

	glutDisplayFunc(display);
	glutIdleFunc(display);
	glutKeyboardFunc(player_keyboard);
	glutSpecialFunc(special_keyboard);

	glutMainLoop();
	return 0;
}