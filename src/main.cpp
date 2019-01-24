#include "main.h"
#include "timer.h"
#include "ball.h"
#include "player.h"
#include "brick.h"
#include "coin.h"
#include "parallax.h"
#include "special.h"

using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/

// Ball ball1, ball2;
Player player1;
Brick bfloor[10];
Brick actualfloor[15];
Coin1 coins1[10];
Coin2 coins2[10];
Coin3 coins3[10];
Parallax par[3];
Special1 sp1;
Special2 sp2;

float screen_zoom = 0.3, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0;

Timer t60(1.0 / 60);

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // use the loaded shader program
    glUseProgram (programID);
    // Eye - Location of camera. Don't change unless you are sure!!
    glm::vec3 eye (0, 0, 100);
    // glm::vec3 eye ( 5*cos(camera_rotation_angle*M_PI/180.0f), 0, 5*sin(camera_rotation_angle*M_PI/180.0f) );
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    glm::vec3 target (0, 0, 0);
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    glm::vec3 up (0, 1, 0);
    // Compute Camera matrix (view)
    Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    // Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane
    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;
    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model





    // Scene render
    // 1. Drawing dummy floor
    // 2. Drawing actual floor
    // 3. Drawing coins
    // 4. Drawing fireline1
    // 5. Drawing player
    // 6. Drawing specials

    // 1
    for (int i = 0; i < 10; i++) {
        bfloor[i].draw(VP);
    }

    // 2
    for (int i = 0; i < 15; i++) {
        actualfloor[i].draw(VP);
    }

    // 3
    coins1[0].draw(VP);
    coins2[0].draw(VP);
    coins3[0].draw(VP);
    
    // 4
    for (int i = 0; i < 3; i++) {
        par[i].draw(VP);
    }

    // 5
    player1.draw(VP);

    // 6
    sp1.draw(VP);
    sp2.draw(VP);
}

void tick_input(GLFWwindow *window) {
    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int up = glfwGetKey(window, GLFW_KEY_UP);
    glfwSetScrollCallback(window, scroll_callback);
    
    if (left) {
        player1.set_speed_x(0.15);
    }
    else if (right) {
        player1.set_speed_x(-0.15);
    }
    if (up) {
        player1.set_speed_y(0.15);
    }

    reset_screen();
}

void tick_elements() {

    // Detect collision with Enemies:
    //      Detect collision with fireline 1
    //      Detect collision with fireline 2 TODO
    // Detect collision with floor
    // Detect collision with ceiling TODO
    // Detect collision with coins
    // Detect collision with special

    // Pan screen
    //      Move all other Elements to the left/right


    // COLLISIONS
    // Fireline 1
    for (int i = 0; i < 3; i++) {
        if ( detect_collision(player1.bounds, par[i].bounds) ) {
            cout << "DIE DIE DIE" << endl;
            player1.set_position(-100, 0);
        }
    }

    // Real floor
    for (int i = 0; i < 15; i++) {
        if ( detect_collision(player1.bounds, actualfloor[i].bounds) ) {
            if (player1.speed_y < 0) {
                player1.set_position(player1.bounds.x, actualfloor[i].bounds.y + actualfloor[i].bounds.height);
                player1.set_speed_y(0); 
            }
            // player1.set_position(player1.bounds.x, player1.bounds.y + player1speed_y);
        }
    }

    // Coin type 1
    if ( detect_collision(player1.bounds, coins1[0].bounds) ) {
        coins1[0].set_speed_y(1000);
        coins1[0].tick();
        player1.score += 1;
        cout << player1.score << endl;
    }
    // Coin type 2
    if ( detect_collision(player1.bounds, coins2[0].bounds) ) {
        coins2[0].set_speed_y(1000);
        coins2[0].tick();
        player1.score += 2;
        cout << player1.score << endl;
    }
    // Coin type 3
    if ( detect_collision(player1.bounds, coins3[0].bounds) ) {
        coins3[0].set_speed_y(1000);
        coins3[0].tick();
        player1.score += 3;
        cout << player1.score << endl;
    }
    
    // Special 1
    if ( detect_collision(player1.bounds, sp1.bounds) ) {
        sp1.set_speed_y(1000);
        sp1.tick();
        player1.score += 100;
        cout << player1.score << endl;
    }
    
    // Special 2
    if ( detect_collision(player1.bounds, sp2.bounds) ) {
        sp2.set_speed_y(1000);
        sp2.tick();
        player1.score += 100;
        cout << player1.score << endl;
    }
    

    // PANNING

    // If in pan range
    if ((player1.bounds.x >= 10 && player1.speed_x < 0) || (player1.bounds.x <= -10 && player1.speed_x > 0)) {
        cout << "Player position: " << player1.bounds.x << endl;
        
        // PAN ENVIRONMENT
        
        // Fireline 2 TODO

        // Fake floor
        for (int i = 0; i < 10; i++) {
            bfloor[i].set_speed_x(player1.speed_x);
            bfloor[i].tick();    
        }
        // Coins
        coins1[0].set_speed_x(player1.speed_x);
        coins1[0].tick();
        coins2[0].set_speed_x(player1.speed_x);
        coins2[0].tick();
        coins3[0].set_speed_x(player1.speed_x);
        coins3[0].tick();

        // Special
        sp1.set_speed_x(-player1.speed_x);
        sp1.tick();

        sp2.set_speed_x(-player1.speed_x);
        sp2.tick();

        // DO NOT MOVE PLAYER
        player1.set_speed_x(0);
    }

    // Redraw Fireline 1
    for (int i = 0; i < 3; i++) {
        par[i].tick();
    }
    sp1.tick();
    sp2.tick();
    player1.tick();
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    // Create the :
    // Player
    // Floor
    // Fireline 1, 2
    // Coins
    // Special 1, 2

    player1     = Player(0, 0, COLOR_BLACK);
    player1.set_speed(0, 0);

    for (int i = 0; i < 10; i++) {
        bfloor[i] = Brick(2*(i-2), -12, COLOR_GREEN);
        bfloor[i].set_speed(0, 0);
    }

    for (int i = 0; i < 15; i++) {
        actualfloor[i] = Brick(2*(i-7), -10, COLOR_GREEN);
        actualfloor[i].set_speed(0, 0);
    }

    for (int i = 0; i < 3; i++) {
        par[i] = Parallax(3+2*i, 5, COLOR_RED, 100, 5);
        par[i].set_speed(0, 0);
    }
    
    coins1[0] = Coin1(10, 10, COLOR_RED);
    coins1[0].set_speed(0, 0);    
    coins2[0] = Coin2(5, 10, COLOR_WHITE);
    coins2[0].set_speed(0, 0);    
    coins3[0] = Coin3(10, 5, COLOR_BLUE);
    coins3[0].set_speed(0, 0);


    sp1 = Special1(100, 10, COLOR_GREEN, 80);
    sp1.set_speed(0, 0);

    sp2 = Special2(25, 10, COLOR_GREEN, 90);
    sp2.set_speed(0, 0);

    

    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


int main(int argc, char **argv) {
    srand(time(0));
    int width  = 600;
    int height = 600;

    window = initGLFW(width, height);

    initGL (window, width, height);

    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers

        if (t60.processTick()) {
            // 60 fps
            // OpenGL Draw commands
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            tick_elements();
            tick_input(window);
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    return (abs(a.x - b.x) * 2 <= (a.width + b.width)) &&
           (abs(a.y - b.y) * 2 <= (a.height + b.height));
}

bool detect_slant_collision(bounding_box_t a, bounding_box_custom b) {
    return false;
}

void reset_screen() {
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
    Matrices.projection = glm::ortho(left, right, bottom, top, 1.0f, 500.0f);
}
