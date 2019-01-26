#include "player.h"
#include "main.h"

Player::Player(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->score = 0;
    this->drag_x = 0;
    this->drag_y = 0;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data[] = {
        -1.0f,-1.0f,-1.0f, // triangle 1 : begin
        -1.0f,-1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f, // triangle 1 : end
        1.0f, 1.0f,-1.0f, // triangle 2 : begin
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f,-1.0f, // triangle 2 : end
        1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f,-1.0f,
        1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f,-1.0f, 1.0f,
        1.0f,-1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f,-1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f,-1.0f,
        -1.0f, 1.0f,-1.0f,
        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f,-1.0f, 1.0f
    };

    static const GLfloat triangle_vertex_buffer[] = {
        1.0f, -1.0f, 1.0f,
        1.0f, -1.0f, -1.0f,
        0.0f, -2.0f, 0.0f,
        1.0f, -1.0f, 1.0f,
        -1.0f, -1.0f, 1.0f,
        0.0f, -2.0f, 0.0f,
        -1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        0.0f, -2.0f, 0.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f, 1.0f,
        0.0f, -2.0f, 0.0f
    };

    static const GLfloat triangle2_vertex_buffer[] = {
        1.0f, 1.0f, -1.0f,
        1.0f, 1.0f, 1.0f,
        2.0f, 0.0f, 0.0f,
        1.0f, 1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        2.0f, 0.0f, 0.0f,
        -1.0f, -1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        2.0f, 0.0f, 0.0f,
        -1.0f, -1.0f, 1.0f,
        1.0f, -1.0f, -1.0f,
        2.0f, 0.0f, 0.0f        
    };

    static const GLfloat body_buf[] = {
        0.0f, 1.0f, 0.0f,
        0.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f
    };

    static const GLfloat head_buf[] = {
        0.0f, 1.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f
    };

    static const GLfloat back_buf[] = {
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f,
        -1.0f, 0.0f, 0.0f
    };

    static const GLfloat propel_buf[] = {
        0.0f, 0.0f, 0.0f,
        -1.0f, 0.0f, 0.0f,
        -0.5f, -1.0f, 0.0f
    };

    static const GLfloat gun_buf[] = {
        1.0f, -0.2f, 0.0f, 
        1.0f, 0.2f, 0.0f,
        1.5f, 0.0f, 0.0f
    };

    // static const GLfloat shield_vertex_buffer[] = {
    //     2.0f, 2.0f, 2.0f,
    //     -2.0f, 2.0f, 2.0f,
    // }
    

    this->bounds.x = x;
    this->bounds.y = y;
    this->bounds.width = 2.0f;
    this->bounds.height = 2.0f;
    //  = {x, y, 1.0f, 1.0f};
    this->object = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data, color, GL_FILL);
    this->flame = create3DObject(GL_TRIANGLES, 4*3, triangle_vertex_buffer, COLOR_RED, GL_FILL);
    this->flame2 = create3DObject(GL_TRIANGLES, 4*3, triangle2_vertex_buffer, COLOR_BLUE, GL_FILL);
    
    this->head = create3DObject(GL_TRIANGLES, 6*3, head_buf, color, GL_FILL);
    this->body = create3DObject(GL_TRIANGLES, 3*3, body_buf, color, GL_FILL);
    this->back = create3DObject(GL_TRIANGLES, 3*3, back_buf, color, GL_FILL);
    this->propel = create3DObject(GL_TRIANGLES, 3*3, propel_buf, COLOR_RED, GL_FILL);
    this->gun = create3DObject(GL_TRIANGLES, 3*3, gun_buf, COLOR_BLUE, GL_FILL);
}

void Player::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    Matrices.model *= translate;
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    // draw3DObject(this->object);
    // draw3DObject(this->flame);
    // draw3DObject(this->flame2);
    draw3DObject(this->head);
    draw3DObject(this->body);
    draw3DObject(this->back);
    
}

void Player::draw_flame(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    Matrices.model *= translate;
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    // draw3DObject(this->flame);
    draw3DObject(this->propel);
}

void Player::draw_flame2(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    Matrices.model *= translate;
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    // draw3DObject(this->flame2);
    draw3DObject(this->gun);
}


void Player::set_speed(double speed_x, double speed_y) {
    this->speed_x = speed_x;
    this->speed_y = speed_y;
}

void Player::set_speed_x(double speed_x) {
    this->speed_x = speed_x;
}

void Player::set_speed_y(double speed_y) {
    this->speed_y = speed_y;
}

void Player::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
    this->bounds.x = x;
    this->bounds.y = y;
}

void Player::tick() {
    this->position.x += drag_x;
    this->position.y += drag_y;
    // this->rotation += speed;
    this->position.x -= speed_x;
    this->position.y += speed_y;
    
    if (this->speed_y == 0) {
        this->speed_x = 0;
    }
    this->speed_y -= 0.01;
    
    this->bounds.x = this->position.x;
    this->bounds.y = this->position.y;
}

