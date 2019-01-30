#include "main.h"

#ifndef VISERION_H
#define VISERION_H

class Viserion {
public:
    Viserion() {}
    Viserion(float x, float y, color_t color);
    glm::vec3 position;
    void draw(glm::mat4 VP);
    void tick();
    double dsp;
    double speed_x;
    double speed_y;
    void set_speed(double speed_x, double speed_y);
    void set_speed_x(double speed_x);
    void set_speed_y(double speed_y);
    void set_position(float x, float y);
    bounding_box_t bounds;
    double timing;
private:
    VAO *head;
    VAO *body;
    VAO *wing;
};

#endif