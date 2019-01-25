#include "main.h"

#ifndef FIRELINES_H
#define FIRELINES_H

class Firelines {
public:
    Firelines() {}
    Firelines(float x, float y, color_t color);
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
    double score;
private:
    VAO *object;
};

#endif