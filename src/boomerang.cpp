#include "boomerang.h"
#include "main.h"

Boomerang::Boomerang(float x, float y, color_t color, int count) {
    this->counter = count;
    this->store = count;
    this->position = glm::vec3(x, y, 0);
    this->score = 0;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data[] = {
        -0.4f,-0.4f,-0.4f, // triangle 1 : begin
        -0.4f,-0.4f, 0.4f,
        -0.4f, 0.4f, 0.4f, // triangle 1 : end
        0.4f, 0.4f,-0.4f, // triangle 2 : begin
        -0.4f,-0.4f,-0.4f,
        -0.4f, 0.4f,-0.4f, // triangle 2 : end
        0.4f,-0.4f, 0.4f,
        -0.4f,-0.4f,-0.4f,
        0.4f,-0.4f,-0.4f,
        0.4f, 0.4f,-0.4f,
        0.4f,-0.4f,-0.4f,
        -0.4f,-0.4f,-0.4f,
        -0.4f,-0.4f,-0.4f,
        -0.4f, 0.4f, 0.4f,
        -0.4f, 0.4f,-0.4f,
        0.4f,-0.4f, 0.4f,
        -0.4f,-0.4f, 0.4f,
        -0.4f,-0.4f,-0.4f,
        -0.4f, 0.4f, 0.4f,
        -0.4f,-0.4f, 0.4f,
        0.4f,-0.4f, 0.4f,
        0.4f, 0.4f, 0.4f,
        0.4f,-0.4f,-0.4f,
        0.4f, 0.4f,-0.4f,
        0.4f,-0.4f,-0.4f,
        0.4f, 0.4f, 0.4f,
        0.4f,-0.4f, 0.4f,
        0.4f, 0.4f, 0.4f,
        0.4f, 0.4f,-0.4f,
        -0.4f, 0.4f,-0.4f,
        0.4f, 0.4f, 0.4f,
        -0.4f, 0.4f,-0.4f,
        -0.4f, 0.4f, 0.4f,
        0.4f, 0.4f, 0.4f,
        -0.4f, 0.4f, 0.4f,
        0.4f,-0.4f, 0.4f
    };

    this->bounds.x = x;
    this->bounds.y = y;
    this->bounds.width = 0.8f;
    this->bounds.height = 0.8f;
    //  = {x, y, 0.4f, 0.4f};
    this->object = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data, color, GL_FILL);
}

void Boomerang::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(0.4f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    Matrices.model *= translate;
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Boomerang::set_speed(double speed_x, double speed_y) {
    this->speed_x = speed_x;
    this->speed_y = speed_y;
}

void Boomerang::set_speed_x(double speed_x) {
    this->speed_x = speed_x;
}

void Boomerang::set_speed_y(double speed_y) {
    this->speed_y = speed_y;
}

void Boomerang::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
    this->bounds.x = x;
    this->bounds.y = y;
}

void Boomerang::tick() {
    // this->rotation += speed;
    this->position.x -= speed_x;
    this->position.y += speed_y;

    if ( this->counter >= store / 2 ) {
        this->speed_y -= 0.0015;
        this->speed_x += 0.009;
    }
    else {
        // this->speed_y += 0.01;
        this->speed_x -= 0.009;
    }

    if (this->speed_y > 0) {
        this->counter++;
    }
    else {
        this->counter--;
    }

    
    this->bounds.x = this->position.x;
    this->bounds.y = this->position.y;
}

