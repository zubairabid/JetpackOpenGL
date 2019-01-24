#include "main.h"

#ifndef PARALLAX_H
#define PARALLAX_H

class Parallax {
public:
    Parallax() {}
    Parallax(float x, float y, color_t color, int count, int cycles);
    glm::vec3 position;
    void draw(glm::mat4 VP);
    void tick();
    double speed_x;
    double speed_y;
    int counter;
    int store;
    int cycles;
    void set_speed(double speed_x, double speed_y);
    void set_speed_x(double speed_x);
    void set_speed_y(double speed_y);
    void set_position(float x, float y);
    bounding_box_t bounds;
    double score;
private:
    VAO *object;
};

#endif