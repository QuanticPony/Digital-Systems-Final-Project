/*
 * Simulation.h
 *
 *  Created on: 9 ene 2022
 *      Author: QuanticPony
 */

#ifndef SIMULATION_H_
#define SIMULATION_H_

#include <stdlib.h>

#include "Vector2D.h"
#include "Line.h"
#include "Particle.h"
#include "Block.h"
#include "Collisions.h"

class Simulation
{
public:
    float delta_t = 0.01; // Integrator step

    int lines_number;
    Line *lines;

    int balls_number;
    Particle *balls;

    int blocks_number;
    Block *blocks;

    Simulation(int lines_number, int balls_number, int blocks_number);
    // virtual ~Simulation();

    void evolve(int iter_for_frames);                            // Compute and updates simulation
    void ensure_in_bounds();                                     // Ensures objects stay in bounds
    static void check_in_bounds(Particle &p, float restitution); // Check and corrects a particle to be in bounds
    void invert_time(); //Inverts all velocities
};

#include "Simulation.cpp"

#endif // SIMULATION_H_