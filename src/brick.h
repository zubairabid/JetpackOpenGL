#include "main.h"

#ifndef BRICK_H
#define BRICK_H


class Brick {
public:
    Brick() {}
    Brick(float x, float y, color_t color);
    glm::vec3 position;
    void draw(glm::mat4 VP);
    bounding_box_t bounds;
    void tick();
    double speed_x;
    double speed_y;
    void set_speed(double speed_x, double speed_y);
    void set_speed_x(double speed_x);
    void set_speed_y(double speed_y);
private:
    VAO *object;
};

#endif // BRICK_H
