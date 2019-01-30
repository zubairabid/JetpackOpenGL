#include "main.h"

#ifndef BOOMERANG_H
#define BOOMERANG_H

class Boomerang {
public:
    Boomerang() {}
    Boomerang(float x, float y, color_t color, int count);
    glm::vec3 position;
    void draw(glm::mat4 VP);
    void tick();
    double speed_x;
    double speed_y;
    int counter;
    int store;
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