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

int WINDOW_WIDTH = 1920;
int WINDOW_HEIGHT = 1080;

#ifndef SEGMENTS_IN_CIRCLE
#define SEGMENTS_IN_CIRCLE 13
#endif

float X_MIN = 0;
float Y_MIN = 0;
float X_MAX = WINDOW_WIDTH;
float Y_MAX = WINDOW_HEIGHT;

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include "physics/Vector2D.h"
#include "physics/Line.h"
#include "physics/Particle.h"
#include "physics/Block.h"
#include "physics/Collisions.h"

#include "physics/Renderer.h"
#include "physics/Simulation.h"