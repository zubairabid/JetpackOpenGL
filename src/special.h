#include "main.h"

#ifndef SPECIAL_H
#define SPECIAL_H


class Special1 {
public:
    Special1() {}
    Special1(float x, float y, color_t color, int count);
    glm::vec3 position;
    void draw(glm::mat4 VP);
    bounding_box_t bounds;
    void tick();
    double speed_x;
    double speed_y;
    int counter;
    int store;
    void set_speed(double speed_x, double speed_y);
    void set_speed_x(double speed_x);
    void set_speed_y(double speed_y);
private:
    VAO *object;
};

class Special2 {
public:
    Special2() {}
    Special2(float x, float y, color_t color, int count);
    glm::vec3 position;
    void draw(glm::mat4 VP);
    bounding_box_t bounds;
    void tick();
    double speed_x;
    double speed_y;
    int counter;
    int store;
    void set_speed(double speed_x, double speed_y);
    void set_speed_x(double speed_x);
    void set_speed_y(double speed_y);
private:
    VAO *object;
};

#endif // BRICK_H
