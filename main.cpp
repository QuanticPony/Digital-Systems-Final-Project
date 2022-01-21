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
#include "Particle.cpp"


#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

float my_random()
{
	return ((float) rand() / (RAND_MAX)) + 1;
}


int WINDOW_WIDTH = 1920;
int WINDOW_HEIGHT = 1080;

#define SEGMENTS_IN_CIRCLE 8

int ball_number = 300;

float X_MIN = 0;
float Y_MIN = 0;
float X_MAX = 10;
float Y_MAX = 10;


float x_convertor(float x){
	return 2*(x-X_MIN)/(X_MAX-X_MIN)-1 ;
}

float y_convertor(float y){
	return 2*(y-Y_MIN)/(Y_MAX-Y_MIN)-1 ;
}

/* Handler for window-repaint event. Call back when the window first appears and
   whenever the window needs to be re-painted. */
void DrawCircle(float cx, float cy, float r, int num_segments)
{
	glBegin(GL_LINE_LOOP);
	for (int ii = 0; ii < num_segments; ii++)
	{
		float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments); // get the current angle

		float x = r * cosf(theta); // calculate the x component
		float y = r * sinf(theta); // calculate the y component

		glVertex2f(x_convertor(x + cx), y_convertor(y + cy)); // output vertex
	}
	glEnd();
}

float delta_t = 0.02;



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
		p.velocity.y = -p.velocity.y;
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

void display()
{
	// Particle ball(1, 0, 0.5, 0.1, 0);
	glClearColor(0.0f, 0.0f, 0.0f, 0.3f); // Set background color to black and opaque

	Particle balls[ball_number];

	for (int i = 0; i < ball_number; i++)
	{
		balls[i].position.x = my_random()*WINDOW_WIDTH;
		balls[i].position.y = my_random()*WINDOW_HEIGHT;
	
		balls[i].velocity.x = my_random()*20-5;
		balls[i].velocity.y = my_random()*20-5;

		balls[i].inv_mass = 1;
		balls[i].radius = my_random()*6 + 4;
		balls[i].inv_mass = 1/balls[i].radius;
		// balls[i].position.x = i==0? 200: 1000;
		// balls[i].position.y = i==0? 50: 50;
		// balls[i].velocity.x = i==0? 10: -10;
		// balls[i].velocity.y = 0;
		// balls[i].radius = 50;
		// balls[i].inv_mass = 1;
	}
	

	for (int i = 0; i < 10; i++)
	{
		 // Clear the color buffer
		// Draw a Red 1x1 Square centered at origin
		/*
		glBegin(GL_QUADS);              // Each set of 4 vertices form a quad
		   glColor3f(1.0f, 0.0f, 0.0f); // Red
		   glVertex2f(-0.5f, -0.5f);    // x, y
		   glVertex2f( 0.5f, -0.5f);
		   glVertex2f( 0.5f,  0.5f);
		   glVertex2f(-0.5f,  0.5f);
		glEnd();
		*/
		for (int b = 0; b < ball_number; b++)
		{
			ensure_in_box(balls[b]);

			for (int bb = b + 1; bb < ball_number; bb++)  
			{  
				if (balls[b].colliding(balls[bb]))  
				{
					balls[b].resolveCollision(balls[bb]);
				}
			}
		}
		

		if (i%10==0) {
			glClear(GL_COLOR_BUFFER_BIT);
			for (int b = 0; b < ball_number; b++) 
				DrawCircle(balls[b].position.x, balls[b].position.y, balls[b].radius, SEGMENTS_IN_CIRCLE);
			// printf("%.2f - %.2f\n", balls[0].position.x, balls[1].position.x);
			glutSwapBuffers();
			glutPostRedisplay();
			Sleep(15);
		}

		if (i==9) i=-1;
	}
}

/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char **argv)
{
	glutInit(&argc, argv); // Initialize GLUT
	// glutInitDisplayMode(GLUT_DOUBLE);
	// glutInitDisplayMode();s
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	//glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	X_MAX = WINDOW_WIDTH;
	Y_MAX = WINDOW_HEIGHT;
	glutCreateWindow("Circle moving"); // Create a window with the given title
									   //    glutInitWindowSize(1280, 720);   // Set the window's initial width & height
	glutFullScreen();
	glutInitWindowPosition(0, 0); // Position the window's initial top-left corner
	glutDisplayFunc(display);	  // Register display callback handler for window re-paint

	glutMainLoop();				  // Enter the infinitely event-processing loop
	return 0;
}
