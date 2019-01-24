#include "main.h"

#ifndef COIN_H
#define COIN_H


class Coin1 {
public:
    Coin1() {}
    Coin1(float x, float y, color_t color);
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

class Coin2 {
public:
    Coin2() {}
    Coin2(float x, float y, color_t color);
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

class Coin3 {
public:
    Coin3() {}
    Coin3(float x, float y, color_t color);
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
