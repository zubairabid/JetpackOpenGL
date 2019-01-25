#include "special.h"
#include "main.h"

Special1::Special1(float x, float y, color_t color, int count) {
    this->counter = count;
    this->store = count;
    this->position = glm::vec3(x, y, 0);
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data[] = {
        -0.6f,-0.6f,-0.6f, // triangle 1 : begin
        -0.6f,-0.6f, 0.6f,
        -0.6f, 0.6f, 0.6f, // triangle 1 : end
        0.6f, 0.6f,-0.6f, // triangle 2 : begin
        -0.6f,-0.6f,-0.6f,
        -0.6f, 0.6f,-0.6f, // triangle 2 : end
        0.6f,-0.6f, 0.6f,
        -0.6f,-0.6f,-0.6f,
        0.6f,-0.6f,-0.6f,
        0.6f, 0.6f,-0.6f,
        0.6f,-0.6f,-0.6f,
        -0.6f,-0.6f,-0.6f,
        -0.6f,-0.6f,-0.6f,
        -0.6f, 0.6f, 0.6f,
        -0.6f, 0.6f,-0.6f,
        0.6f,-0.6f, 0.6f,
        -0.6f,-0.6f, 0.6f,
        -0.6f,-0.6f,-0.6f,
        -0.6f, 0.6f, 0.6f,
        -0.6f,-0.6f, 0.6f,
        0.6f,-0.6f, 0.6f,
        0.6f, 0.6f, 0.6f,
        0.6f,-0.6f,-0.6f,
        0.6f, 0.6f,-0.6f,
        0.6f,-0.6f,-0.6f,
        0.6f, 0.6f, 0.6f,
        0.6f,-0.6f, 0.6f,
        0.6f, 0.6f, 0.6f,
        0.6f, 0.6f,-0.6f,
        -0.6f, 0.6f,-0.6f,
        0.6f, 0.6f, 0.6f,
        -0.6f, 0.6f,-0.6f,
        -0.6f, 0.6f, 0.6f,
        0.6f, 0.6f, 0.6f,
        -0.6f, 0.6f, 0.6f,
        0.6f,-0.6f, 0.6f
    };

    this->bounds.x = x;
    this->bounds.y = y;
    this->bounds.width = 1.2f;
    this->bounds.height = 1.2f;
    //  = {x, y, 0.6f, 0.6f};
    this->object = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data, color, GL_FILL);
}

void Special1::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(0.6f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    Matrices.model *= translate;
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Special1::set_speed_x(double speed_x) {
    this->speed_x = speed_x;
}

void Special1::set_speed_y(double speed_y) {
    this->speed_y = speed_y;
}

void Special1::set_speed(double speed_x, double speed_y) {
    this->speed_x = speed_x;
    this->speed_y = speed_y;
}

void Special1::tick() {
    // this->rotation += speed;
    this->position.x -= speed_x;
    this->position.y += speed_y;
    
    this->speed_x = 0.1;

    if ( this->counter >= store / 2 ) {
        this->speed_y -= 0.01;
    }
    else {
        this->speed_y += 0.01;
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


Special2::Special2(float x, float y, color_t color, int count) {
    this->counter = count;
    this->store = count;
    this->position = glm::vec3(x, y, 0);
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data[] = {
        -0.6f,-0.6f,-0.6f, // triangle 1 : begin
        -0.6f,-0.6f, 0.6f,
        -0.6f, 0.6f, 0.6f, // triangle 1 : end
        0.6f, 0.6f,-0.6f, // triangle 2 : begin
        -0.6f,-0.6f,-0.6f,
        -0.6f, 0.6f,-0.6f, // triangle 2 : end
        0.6f,-0.6f, 0.6f,
        -0.6f,-0.6f,-0.6f,
        0.6f,-0.6f,-0.6f,
        0.6f, 0.6f,-0.6f,
        0.6f,-0.6f,-0.6f,
        -0.6f,-0.6f,-0.6f,
        -0.6f,-0.6f,-0.6f,
        -0.6f, 0.6f, 0.6f,
        -0.6f, 0.6f,-0.6f,
        0.6f,-0.6f, 0.6f,
        -0.6f,-0.6f, 0.6f,
        -0.6f,-0.6f,-0.6f,
        -0.6f, 0.6f, 0.6f,
        -0.6f,-0.6f, 0.6f,
        0.6f,-0.6f, 0.6f,
        0.6f, 0.6f, 0.6f,
        0.6f,-0.6f,-0.6f,
        0.6f, 0.6f,-0.6f,
        0.6f,-0.6f,-0.6f,
        0.6f, 0.6f, 0.6f,
        0.6f,-0.6f, 0.6f,
        0.6f, 0.6f, 0.6f,
        0.6f, 0.6f,-0.6f,
        -0.6f, 0.6f,-0.6f,
        0.6f, 0.6f, 0.6f,
        -0.6f, 0.6f,-0.6f,
        -0.6f, 0.6f, 0.6f,
        0.6f, 0.6f, 0.6f,
        -0.6f, 0.6f, 0.6f,
        0.6f,-0.6f, 0.6f
    };

    this->bounds.x = x;
    this->bounds.y = y;
    this->bounds.width = 1.2f;
    this->bounds.height = 1.2f;
    //  = {x, y, 0.6f, 0.6f};
    this->object = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data, color, GL_FILL);
}

void Special2::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(0.6f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    Matrices.model *= translate;
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Special2::set_speed_x(double speed_x) {
    this->speed_x = speed_x;
}

void Special2::set_speed_y(double speed_y) {
    this->speed_y = speed_y;
}

void Special2::set_speed(double speed_x, double speed_y) {
    this->speed_x = speed_x;
    this->speed_y = speed_y;
}

void Special2::tick() {
    // this->rotation += speed;
    this->position.x -= speed_x;
    this->position.y += speed_y;
    
    this->speed_x = 0.05;
    if ( this->counter >= store / 2 ) {
        this->speed_y -= 0.01;
    }
    else {
        this->speed_y += 0.01;
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
