/*
 * Collisions.cpp
 *
 *  Created on: 7 ene 2022
 *      Author: QuanticPony
 */
#ifndef COLLISIONS_H_
#define COLLISIONS_H_

#include "Line.h"
#include "Particle.h"
#include "Block.h"

class Collisions
{
public:
    Collisions();
    virtual ~Collisions();

    static bool colliding(Line line1, Line line2);
    static bool colliding(Line line1, Particle ball);
    static bool colliding(Line line, Block block);
    static bool colliding(Particle ball1, Particle ball2);
    static bool colliding(Block block, Particle ball);

    static void resolveCollision(Line &line1, Line &line2);
    static void resolveCollision(Line &line1, Particle &ball);
    static void resolveCollision(Line &line, Block &block);
    static void resolveCollision(Particle &ball1, Particle &ball2);
    static void resolveCollision(Block &block, Particle &ball);  
};

#include "Collisions.cpp"

#endif //PARTICLE_H_