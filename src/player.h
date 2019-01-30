#include "main.h"

#ifndef PLAYER_H
#define PLAYER_H

class Player {
public:
    Player() {}
    Player(float x, float y, color_t color);
    glm::vec3 position;
    void draw(glm::mat4 VP);
    void tick();
    void draw_flame(glm::mat4 VP);
    void draw_flame2(glm::mat4 VP);
    void draw_shield(glm::mat4 VP);
    double dsp;
    double speed_x;
    double speed_y;
    double drag_x;
    double drag_y;
    void set_speed(double speed_x, double speed_y);
    void set_speed_x(double speed_x);
    void set_speed_y(double speed_y);
    void set_position(float x, float y);
    bounding_box_t bounds;
    double score;
private:
    VAO *head;
    VAO *body;
    VAO *back;
    VAO *propel;
    VAO *gun;
    VAO *shield;
};

#endif