/*
 * Renderer.h
 *
 *  Created on: 9 ene 2022
 *      Author: QuanticPony
 */

My_Renderer::My_Renderer(float X_MIN, float X_MAX, float Y_MIN, float Y_MAX)
{
    this->X_MIN = X_MIN;
    this->Y_MIN = Y_MIN;
    this->X_MAX = X_MAX;
    this->Y_MAX = Y_MAX;

    char param[] = "prueba3";
    char *argv[] = {param, NULL};
    int argc = 1;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
    glClearColor(0, 0, 0, 1);

    glutCreateWindow("Prueba 3");

    glutPositionWindow(100, 100);
    glutReshapeWindow(1200, 900);
}

void My_Renderer::clear()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void My_Renderer::swap_buffers()
{
    glutSwapBuffers();
    glutPostRedisplay();
}

void My_Renderer::render(Particle *balls, int balls_number, float R, float G, float B)
{
    for (int b = 0; b < balls_number; b++)
    {
        draw(balls[b], R, G, B);
    }
}

void My_Renderer::render(Line *lines, int lines_number, float R, float G, float B)
{
    for (int l = 0; l < lines_number; l++)
    {
        draw(lines[l], R, G, B);
    }
}

void My_Renderer::render(Block *blocks, int blocks_number, float R, float G, float B)
{
    for (int B = 0; B < blocks_number; B++)
    {
        draw(blocks[B], R, G, B);
    }
}

float My_Renderer::x_convertor(float x)
{
    return 2 * (x - X_MIN) / (float)(X_MAX - X_MIN) - 1;
}

float My_Renderer::y_convertor(float y)
{
    return 2 * (y - Y_MIN) / (float)(Y_MAX - Y_MIN) - 1;
}

void My_Renderer::draw(Particle ball, float R, float G, float B)
{
    static float cosfs[SEGMENTS_IN_CIRCLE];
    static float sinfs[SEGMENTS_IN_CIRCLE];
    static bool first = true;
    if (first)
    {
        float ankle;
        for (int i = 0; i < SEGMENTS_IN_CIRCLE; i++)
        {
            ankle = 2.0f * 3.1415926f * float(i) / float(SEGMENTS_IN_CIRCLE);
            cosfs[i] = cosf(ankle);
            sinfs[i] = sinf(ankle);
        }
        first = false;
    }

    glColor3f(R, G, B);
    glBegin(GL_LINE_LOOP);
    for (int ii = 0; ii < SEGMENTS_IN_CIRCLE; ii++)
    {
        float x = ball.radius * cosfs[ii] * x_scale;
        float y = ball.radius * sinfs[ii] * y_scale;

        glVertex2f(x_convertor(x + ball.position.x), y_convertor(y + ball.position.y));
    }
    glEnd();
}

void My_Renderer::draw(Line line, float R, float G, float B)
{
    glColor3f(R, G, B);
    glBegin(GL_LINES);
    glVertex2f(x_convertor(line.position.x), y_convertor(line.position.y));
    glVertex2f(x_convertor(line.line.x + line.position.x), y_convertor(line.line.y + line.position.y));
    glEnd();
}

void My_Renderer::draw(Block block, float R, float G, float B)
{
    glColor3f(R, G, B);
    glBegin(GL_QUADS);
    glVertex2f(x_convertor(block.position.x - block.w / 2), y_convertor(block.position.y - block.h / 2));
    glVertex2f(x_convertor(block.position.x - block.w / 2), y_convertor(block.position.y + block.h / 2));
    glVertex2f(x_convertor(block.position.x + block.w / 2), y_convertor(block.position.y + block.h / 2));
    glVertex2f(x_convertor(block.position.x + block.w / 2), y_convertor(block.position.y - block.h / 2));
    glEnd();
}