/*
 * Simulation.cpp
 *
 *  Created on: 10 ene 2022
 *      Author: QuanticPony
 */

Simulation::Simulation(int lines_number, int balls_number, int blocks_number)
{
    this->lines_number = lines_number;
    this->balls_number = balls_number;
    this->blocks_number = blocks_number;
    this->lines = (Line*) malloc(sizeof(Line)*lines_number);
    this->balls = (Particle*) malloc(sizeof(Particle)*balls_number);
    this->blocks = (Block*) malloc(sizeof(Block)*blocks_number);
}

void Simulation::evolve(int iter_for_frames)
{
    // TODO: optimize collision detection
    for (int b = 0; b < balls_number; b++)
    {
        for (int bb = b + 1; bb < balls_number; bb++)
        {
            if (Collisions::colliding(balls[b], balls[bb]))
            {
                Collisions::resolveCollision(balls[b], balls[bb]);
            }
        }
        for (int ll = 0; ll < lines_number; ll++)
        {
            if (Collisions::colliding(lines[ll], balls[b]))
            {
                Collisions::resolveCollision(lines[ll], balls[b]);
            }
        }
        for (int bb = 0; bb < blocks_number; bb++)
        {
            if (Collisions::colliding(blocks[bb], balls[b]))
            {
                Collisions::resolveCollision(blocks[bb], balls[b]);
            }
        }
    }

    for (int b = 0; b < balls_number; b++)
    {
        balls[b].evolve(delta_t);
    }
    for (int b = 0; b < blocks_number; b++)
    {
        blocks[b].evolve(delta_t);
        blocks[b].update_sides();
    }

    ensure_in_bounds();
}

void Simulation::invert_time()
{
    for (int bb = 0; bb < balls_number; bb++)
    {
        balls[bb].velocity.scale(-1);
    }
    for (int bb = 0; bb < blocks_number; bb++)
    {
        blocks[bb].velocity.scale(-1);
    }
    for (int bb = 0; bb < lines_number; bb++)
    {
        lines[bb].velocity.scale(-1);
    }
}


void Simulation::ensure_in_bounds()
{
    for (int b = 0; b < balls_number; b++)
    {
        check_in_bounds(balls[b], 0.99);
    }
    // TODO: add the other objects
}

// TODO: add the other objects
void Simulation::check_in_bounds(Particle &p, float restitution)
{
    if (p.position.x < X_MIN + p.radius)
    {
        p.position.x = 2 * (X_MIN + p.radius) - p.position.x;
        p.velocity.x = -p.velocity.x * restitution;
    }
    else if (p.position.x > X_MAX - p.radius)
    {
        p.position.x = 2 * (X_MAX - p.radius) - p.position.x;
        p.velocity.x = -p.velocity.x * restitution;
    }

    if (p.position.y < Y_MIN + p.radius)
    {
        p.position.y = 2 * (Y_MIN + p.radius) - p.position.y;
        p.velocity.y = -p.velocity.y * restitution;
    }
    else if (p.position.y > Y_MAX - p.radius)
    {
        p.position.y = 2 * (Y_MAX - p.radius) - p.position.y;
        p.velocity.y = -p.velocity.y * restitution;
    }
}