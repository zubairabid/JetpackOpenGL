#include "main.h"
#include "timer.h"
#include "ball.h"
#include "player.h"
#include "brick.h"
#include "coin.h"
#include "parallax.h"
#include "special.h"
#include "boomerang.h"
#include "firelines.h"

using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/

// GLOBALS IN USE


// VARIABLES TO USE
// Player
// Floor
// Ceil
// Coin 1 array
// Coin 2 array
// Coin 3 array
// Parralax array
// Array of Fireline arrays
// Special 1 array
// Special 2 array
// Boomerang array


Player player1;
Brick actualfloor[15];
Brick actualceil[15];

Coin1 coins1[15];
Coin2 coins2[15];
Coin3 coins3[15];

int c1t = 0, c2t = 0, c3t = 0, flt = 0, s1t = 0, s2t = 0;

Parallax beam[2][30];
Firelines line[15][30];
Special1 sp1[15];
Special2 sp2[15];
Boomerang boomerang;

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
    // cout << "In tick_elements" << endl;





    // Scene render
    // 1. Drawing floor+ceil
    // 3. Drawing coins
    // 4. Drawing specials
    // 5. Drawing fireline1
    // 6. Drawing fireline2
    // 7. Drawing player


    // Floor+Ceiling
    for (int i = 0; i < 15; i++) {
        actualfloor[i].draw(VP);
        actualceil[i].draw(VP);
    }

    // Coins
    for (int i = 0; i < c1t; i++) {
        coins1[i].draw(VP);
    }
    for (int i = 0; i < c2t; i++) {
        coins2[i].draw(VP);
    }
    for (int i = 0; i < c3t; i++) {
        coins3[i].draw(VP);
    }

    // Special
    for (int i = 0; i < s1t; i++) {
        sp1[i].draw(VP);
    }
    for (int i = 0; i < s2t; i++) {
        sp2[i].draw(VP);
    }

    // Fireline
    for (int i = 0; i < flt; i++) {
        for (int j = 0; j < 30; j++) {
            line[i][j].draw(VP);
        }
    }
    // boomerang.draw(VP);

    // 5
    player1.draw(VP);
}

void tick_input(GLFWwindow *window) {
    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int up = glfwGetKey(window, GLFW_KEY_SPACE);
    glfwSetScrollCallback(window, scroll_callback);
    
    if (left) {
        player1.set_speed_x(0.10);
    }
    else if (right) {
        player1.set_speed_x(-0.10);
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
    // cout << "In tick_elements" << endl;


    // COLLISIONS
    // Real floor
    for (int i = 0; i < 15; i++) {
        if ( detect_collision(player1.bounds, actualfloor[i].bounds) ) {
            if (player1.speed_y < 0) {
                player1.set_position(player1.bounds.x, actualfloor[i].bounds.y + actualfloor[i].bounds.height);
                player1.set_speed_y(0); 
            }
        }
    }
    // Real Ceiling
    for (int i = 0; i < 15; i++) {
        if ( detect_collision(player1.bounds, actualceil[i].bounds) ) {
            if (player1.speed_y > 0) {
                player1.set_position(player1.bounds.x, actualceil[i].bounds.y - actualceil[i].bounds.height);
                player1.set_speed_y(0); 
            }
        }
    }

    // Fireline
    for (int i = 0; i < flt; i++) {
        for (int j = 0; j < 30; j++) {
            if (detect_collision(player1.bounds, line[i][j].bounds)) {
                cout << "DIE DIE DIE" << endl;
                player1.set_position(-100000, 0);
            }
        }
    }

    // Coin type 1
    for (int i = 0; i < c1t; i++) {
        if ( detect_collision(player1.bounds, coins1[i].bounds) ) {
            coins1[i].set_speed_y(1000);
            coins1[i].tick();
            player1.score += 1;
            cout << player1.score << endl;
        }
    }
    
    // Coin type 2
    for (int i = 0; i < c2t; i++) {
        if ( detect_collision(player1.bounds, coins2[i].bounds) ) {
            coins2[i].set_speed_y(1000);
            coins2[i].tick();
            player1.score += 2;
            cout << player1.score << endl;
        }
    }
    // Coin type 3
    for (int i = 0; i < c3t; i++) {
        if ( detect_collision(player1.bounds, coins3[i].bounds) ) {
            coins3[i].set_speed_y(1000);
            coins3[i].tick();
            player1.score += 3;
            cout << player1.score << endl;
        }
    }
    
    
    // Special 1
    for (int i = 0; i < s1t; i++) {
        if ( detect_collision(player1.bounds, sp1[i].bounds) ) {
            sp1[i].set_speed_y(1000);
            sp1[i].tick();
            player1.score += 100;
            cout << player1.score << endl;
        }
    }
    // Special 2
    for (int i = 0; i < s2t; i++) {
        if ( detect_collision(player1.bounds, sp2[i].bounds) ) {
            sp2[i].set_speed_y(1000);
            sp2[i].tick();
            player1.score += 100;
            cout << player1.score << endl;
        }
    }

    // MOVE IN GENERAL
    createMap();
    for (int i = 0; i < flt; i++) {
        for (int j = 0; j < 30; j++) {
            line[i][j].tick();
        }
    }
    for (int i = 0; i < c1t; i++) {
        coins1[i].tick();
    }
    for (int i = 0; i < c2t; i++) {
        coins2[i].tick();
    }
    for (int i = 0; i < c3t; i++) {
        coins3[i].tick();
    }
    // Special
    for (int i = 0; i < s1t; i++) {
        sp1[i].tick();
    }
    for (int i = 0; i < s2t; i++) {
        sp2[i].tick();
    }
    // boomerang.tick();

    // PANNING
    // If in pan range
    if ((player1.bounds.x >= 5 && player1.speed_x < 0) || (player1.bounds.x <= -10 && player1.speed_x > 0)) {
        // cout << "Player position: " << player1.bounds.x << endl;
        
        
        // PAN ENVIRONMENT
        
        // Fireline
        for (int i = 0; i < flt; i++) {
            for (int j = 0; j < 30; j++) {
                line[i][j].set_speed_x(line[i][j].speed_x + player1.speed_x);
                line[i][j].tick();
            }
        }

        // Coins
        for (int i = 0; i < c1t; i++) {
            coins1[i].set_speed_x(coins1[i].speed_x + player1.speed_x);
            coins1[i].tick();
        }
        for (int i = 0; i < c2t; i++) {
            coins2[i].set_speed_x(coins2[i].speed_x + player1.speed_x);
            coins2[i].tick();
        }
        for (int i = 0; i < c3t; i++) {
            coins3[i].set_speed_x(coins3[i].speed_x + player1.speed_x);
            coins3[i].tick();
        }

        // Special
        for (int i = 0; i < s1t; i++) {
            // sp1[i].set_speed_x(sp1[i].speed_x + player1.speed_x);
            sp1[i].tick();
            sp1[i].position.x += player1.speed_x;
        }
        for (int i = 0; i < s2t; i++) {
            // sp2[i].set_speed_x(sp2[i].speed_x +  player1.speed_x);
            sp2[i].tick();
            sp2[i].position.x += player1.speed_x;
        }
        
        // DO NOT MOVE PLAYER
        player1.set_speed_x(0);
    }

    player1.tick();
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models


    // Generate the level scene here
    //      Create Player, Floor, Ceiling
    //      Place coins and firelines across the place
    //      Initialise parallax and boomerang
    cout << "In initGL" << endl;

    // Player creation
    player1     = Player(0, 0, COLOR_BLACK);
    player1.set_speed(0, 0);
    cout << "Made player" << endl;

    // Floor and Ceiling creation
    for (int i = 0; i < 15; i++) {
        actualfloor[i] = Brick(2*(i-7), -13, COLOR_GREEN);
        actualfloor[i].set_speed(0, 0);

        actualceil[i] = Brick(2*(i-7), 13, COLOR_GREEN);
        actualceil[i].set_speed(0, 0);
    }
    cout << "Made floor, ceiling" << endl;


    // for (int i = 0; i < 30; i++) {
    //     par[i] = Parallax(3+0.2*i, 5, COLOR_RED, 100, 5);
    //     par[i].set_speed(0, 0);
    // }

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

void createMap() {
    double player_location = player1.position.x;
    int value = rand() % 20000;
    int i = (int)player_location + 25;
    if (value > 500 && value <= 600) {
        coins1[c1t] = Coin1(i, rand()%12, COLOR_ORED);
        coins1[c1t].set_speed(0, 0);
        c1t = (c1t + 1)%15;
        cout << "Coin1 added" << c1t << endl;
    }
    if (value > 600 && value <= 700) {
        coins2[c2t] = Coin2(i, rand()%12, COLOR_BRED);
        coins2[c2t].set_speed(0, 0);
        c2t = (c2t + 1)%15;
        cout << "Coin2 added" << c2t << endl;
    }
    if (value > 700 && value <= 800 && c3t < 50) {
        coins3[c3t] = Coin3(i, rand()%12, COLOR_BURED);
        coins3[c3t].set_speed(0, 0);
        c3t = (c3t + 1)%15;;
        cout << "Coin3 added" << c3t << endl;
    }


    // Generating firelines on map:
    if(value > 38 && value <= 138) {
        int begin = rand() % 12;
        for (int j = 0; j < 30; j++) {
            // if (rand() - RAND_MAX/2 > 0) {
                line[flt][j] = Firelines(i+0.2*j, begin-12+0.2*j, COLOR_RED);
                line[flt][j].set_speed(0, 0);
            // }
            // else {
            //     line[flt][j] = Firelines(i+0.2*j, 10-0.2*j, COLOR_RED, -1, -1);
            // }               
        }
        flt = (flt + 1)%15; 

        cout << "Fireline added" << flt << endl;
    }
    if (value > 469 && value < 1469) {
        // boomerang = Boomerang(i, 10, COLOR_BLUE, 100);
        // boomerang.set_speed(0, 0);
    }

    // Generating special powerups
    if (value > 298 && value <= 308 && s1t < 10) {
        sp1[s1t] = Special1(i, 12, COLOR_PRED, 70);
        sp1[s1t].set_speed(0, 0);
        s1t = (s1t + 1)%15;
        cout << "Powerup 1 added" << s1t << endl;
    }

    if (value > 757 && value <= 767 && s2t < 10) {
        sp2[s2t] = Special2(i, 12, COLOR_LPRED, 70);
        sp2[s2t].set_speed(0, 0);
        s2t = (s2t + 1)%15;
        cout << "Powerup 2 added" << s2t << endl;
    }
}


int main(int argc, char **argv) {
    srand(time(0));
    int width  = 750;
    int height = 750;

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
