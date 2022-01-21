/*
 * Keyboard.h
 *
 *  Created on: 9 ene 2022
 *      Author: QuanticPony
 */

#ifndef KEYBOARD_H_
#define KEYBOARD_H_

#include <iostream>

void stop_handler(bool want_stopped)
{
    static bool stopped = false;
    if (!stopped && want_stopped){
        glutIdleFunc([](){ Sleep(50); });
        glutDisplayFunc(display_static);
        stopped = true;
    }
    if (stopped && !want_stopped){
        glutIdleFunc(display);
        glutDisplayFunc(display);
        stopped = false;
    }
}

void keyboard(unsigned char key, int x, int y)
{
    static bool fullscreen = false;
    switch (key)
    {
    case 'f':
        if (fullscreen)
        {
            glutPositionWindow(100, 100);
            glutReshapeWindow(1200, 900);
        }
        else
        {
            glutFullScreen();
        }
        fullscreen = !fullscreen;
        break;

    case 'r':
        init_simulation(*simulation);
        stop_handler(false);
        break;

    case 's':
        stop_handler(true);
        break;

    case 'c':
        stop_handler(false);
        break;

    case 27:
        exit(0);

    default:
        break;
    }
}

void special_keyboard(int key, int x, int y)
{
    static float delta_t = simulation->delta_t;
    static bool time_forwards = true;
    switch (key)
    {
    case GLUT_KEY_LEFT:
        if (time_forwards && delta_t <= 0.001)
        {
            time_forwards = false;
            simulation->invert_time();
        }
        if (time_forwards)
            delta_t *= 0.9;
        else
            delta_t *= 1.1;

        simulation->delta_t = delta_t;
        break;

    case GLUT_KEY_RIGHT:
        if (!time_forwards && delta_t <= 0.001)
        {
            time_forwards = true;
            simulation->invert_time();
        }
        if (time_forwards)
            delta_t *= 1.1;
        else
            delta_t *= 0.9;

        simulation->delta_t = delta_t;
        break;
    }
}
#endif // KEYBOARD_H_