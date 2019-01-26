#include "viserion.h"
#include "main.h"

Viserion::Viserion(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->timing = 720;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data[] = {
        -5.0f,-5.0f,-5.0f, // triangle 1 : begin
        -5.0f,-5.0f, 5.0f,
        -5.0f, 5.0f, 5.0f, // triangle 1 : end
        5.0f, 5.0f,-5.0f, // triangle 2 : begin
        -5.0f,-5.0f,-5.0f,
        -5.0f, 5.0f,-5.0f, // triangle 2 : end
        5.0f,-5.0f, 5.0f,
        -5.0f,-5.0f,-5.0f,
        5.0f,-5.0f,-5.0f,
        5.0f, 5.0f,-5.0f,
        5.0f,-5.0f,-5.0f,
        -5.0f,-5.0f,-5.0f,
        -5.0f,-5.0f,-5.0f,
        -5.0f, 5.0f, 5.0f,
        -5.0f, 5.0f,-5.0f,
        5.0f,-5.0f, 5.0f,
        -5.0f,-5.0f, 5.0f,
        -5.0f,-5.0f,-5.0f,
        -5.0f, 5.0f, 5.0f,
        -5.0f,-5.0f, 5.0f,
        5.0f,-5.0f, 5.0f,
        5.0f, 5.0f, 5.0f,
        5.0f,-5.0f,-5.0f,
        5.0f, 5.0f,-5.0f,
        5.0f,-5.0f,-5.0f,
        5.0f, 5.0f, 5.0f,
        5.0f,-5.0f, 5.0f,
        5.0f, 5.0f, 5.0f,
        5.0f, 5.0f,-5.0f,
        -5.0f, 5.0f,-5.0f,
        5.0f, 5.0f, 5.0f,
        -5.0f, 5.0f,-5.0f,
        -5.0f, 5.0f, 5.0f,
        5.0f, 5.0f, 5.0f,
        -5.0f, 5.0f, 5.0f,
        5.0f,-5.0f, 5.0f
    };

    this->bounds.x = x;
    this->bounds.y = y;
    this->bounds.width = 10.0f;
    this->bounds.height = 10.0f;
    //  = {x, y, 5.0f, 5.0f};
    this->object = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data, color, GL_FILL);
}

void Viserion::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(5.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    Matrices.model *= translate;
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Viserion::set_speed(double speed_x, double speed_y) {
    this->speed_x = speed_x;
    this->speed_y = speed_y;
}

void Viserion::set_speed_x(double speed_x) {
    this->speed_x = speed_x;
}

void Viserion::set_speed_y(double speed_y) {
    this->speed_y = speed_y;
}

void Viserion::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
    this->bounds.x = x;
    this->bounds.y = y;
}

void Viserion::tick() {
    this->timing--;
    // this->rotation += speed;
    this->position.x -= speed_x;
    this->position.y += speed_y;
    
    if (timing == 0) {
        iceshot();
        this->timing = 180;
    }

    this->bounds.x = this->position.x;
    this->bounds.y = this->position.y;
}

