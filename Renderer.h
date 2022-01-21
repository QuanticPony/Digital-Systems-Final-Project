/*
 * Renderer.h
 *
 *  Created on: 9 ene 2022
 *      Author: QuanticPony
 */

#ifndef RENDERER_H_
#define RENDERER_H_

#include <iostream>
#include <GL/glut.h>

class My_Renderer
{
public:
    float X_MIN = 0;
    float Y_MIN = 0;
    float X_MAX = 10;
    float Y_MAX = 10;

    float x_scale = 1;
    float y_scale = 1;

    My_Renderer(float X_MIN, float X_MAX, float Y_MIN, float Y_MAX); //Constructor. Max and min positions in simulation are needed for conversions
    // virtual ~My_Renderer();

    float x_convertor(float x); //Converts x position to display relative units
    float y_convertor(float y); //Converts y position to display relative units
    void render(Particle *balls, int balls_number); //Renders the given Particles
    void render(Line *lines, int lines_number); //Renders the given Lines
    void render(Block *blocks, int blocks_number); //Renders the given Blocks

    void swap_buffers(); //Swap buffers, must be used to render a frame in the display
    void clear(); //Clears the actual buffer

    void draw(Particle ball); //Draws a single Particle
    void draw(Line line); //Draws a single Line
    void draw(Block block); //Draws a single Block
};

#include "Renderer.cpp"

#endif // RENDERER_H_