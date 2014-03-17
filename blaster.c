#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif
#include "my_setup_3D.h"

//  Constants for use with the my_setup() function.
#define canvas_width 400
#define canvas_height 400
#define canvas_name "Blaster Game"

// Represents a point in 3-Dimensional space.
typedef struct {
    float x;
    float y;
    float z;
} Point;

// Represents a rgb-style color.
typedef struct {
    float red;
    float green;
    float blue;
} Color;

// Represents a 3-Dimensional cube object and its attributes.
typedef struct {
    Point center;
    float size;
    Color color;
    int is_alive;
} Cube;

// Pointer to Point object that represents the origin of the scene.
Point* origin;

// Float that represents the current location of the z-plane on which 
// the drawn objects' origins lie.
float z_plane;

// Floats that represent the size of the player and enemy cubes
float player_size;
float enemy_size;

// Pointers to Point objects that represent the starting positions
// of the player and enemy ships
Point* player_start;
Point* enemy_start;

// Pointers to Color objects that represent the colors used in the 
// program.
//      - White for the background, 
//      - player_color for player lines,
//      - Red for the enemy ships.
Color* bg_color;
Color* player_color;
Color* enemy_color;

// Pointers to Cube objects representing the player and enemy ships.
Cube* player;
Cube* enemy;

//
int enemy_min_x, enemy_max_x;
int enemy_spawn_x;
int enemy_min_time, enemy_max_time;
int enemy_spawn_time;

// 
float enemy_total_dist;
float enemy_total_time;
float enemy_step_time; 
float enemy_step_dist; 



// ------------------------------------
// -------> Utility Functions <--------
// ------------------------------------

// Used as a constructor to initialize a new Point object.
Point* make_point(float x, float y, float z) {
    Point* point = (Point*)malloc(sizeof(Point));

    point->x = x;
    point->y = y;
    point->z = z;

    return point;
}

// Used as a constructor to initialize a new Color object.
Color* make_color(float red, float green, float blue) {
    Color* color = (Color*)malloc(sizeof(Color));

    color->red   = red;
    color->green = green;
    color->blue  = blue;

    return color;
}

// Used as a constructor to initialize a new Color object.
Cube* make_cube(Point* center, float size, Color* color) {
    Cube* cube   = malloc(sizeof(Cube));
    cube->center = *center;
    cube->size   = size;
    cube->color  = *color;
    cube->is_alive = 0;
    return cube;
}

// Sets the enemy's center point to a random point along the top of 
// the canvas, and then calls itself again after a time interval 
// between 2.75 and 3.50 minutes. 
void spawn_enemy() {
    srand(time(NULL));
    enemy_spawn_x = (rand() % (enemy_max_x+1 - enemy_min_x)) + enemy_min_x;
    enemy->center.y = enemy_start->y;
    enemy->center.x = enemy_spawn_x;

    srand(time(NULL));
    enemy_spawn_time = (rand() % (enemy_max_time+1 - enemy_min_time)) + enemy_min_time;
    enemy->is_alive = 1;
    glutTimerFunc(enemy_spawn_time, spawn_enemy, 1);
}

//
void update_enemy() {
    if(enemy->is_alive) {
        enemy->center.y -= enemy_step_dist;
        glutTimerFunc(enemy_step_time, update_enemy, 1);
    }
}

//
void kill_enemy() {
    enemy->is_alive = 0;
}

//
void move_player(char* direction) {

}



// ------------------------------------
// -------> Drawing Functions <--------
// ------------------------------------

// Draws a Cube object at the translated point stored in its 
// center field.
void draw_cube(Cube* cube) {
    glPushMatrix();
    glTranslatef(cube->center.x,
                 cube->center.y,
                 cube->center.z);
    glColor3f(cube->color.red, cube->color.green, cube->color.blue);
    glutWireCube(cube->size);
    glTranslatef((cube->center.x * -1),
                 (cube->center.y * -1),
                 (cube->center.z * -1));
    glPopMatrix();
}

// Draws a laser line at the translated point stored in the Cube 
// parameter's center field.
void draw_laser(Cube* cube) {
    glPushMatrix();
    glTranslatef(cube->center.x,
                 cube->center.y,
                 cube->center.z);
    glColor3f(cube->color.red, cube->color.green, cube->color.blue);
    glBegin(GL_LINES);
        glVertex3f(cube->center.x, 
                   cube->center.y + (cube->size / 2),
                   z_plane);
        glVertex3f(cube->center.x, 
                   (canvas_height / 2),
                   z_plane);
    glEnd();
    glTranslatef((cube->center.x * -1),
                 (cube->center.y * -1),
                 (cube->center.z * -1));
    glPopMatrix();
}

// Draws all of the objects onto the canvas.
void draw_all_objects() {
    glClearColor(bg_color->red, bg_color->green, bg_color->blue, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    draw_cube(player); 
    spawn_enemy();
    draw_cube(enemy);
    glFlush();
}

// 
void animate() {

}



// ------------------------------------
// -----> User Input Functions <-------
// ------------------------------------

// 
void handle_keys(unsigned char c, GLint x, GLint y) {
    if(c == 'h' || c == 'h') {
        move_player("left");
    }
    else if(c == 'l' || c == 'L') {
        move_player("right");
    }
    else if(c == ' ') {

    }
    else if(c == '\0') {
        exit(0);
    }
}



// ------------------------------------
// --------> Main Functions <----------
// ------------------------------------

// Initializes that objects and variables that will be used.
void init() {
    origin = make_point(0.0, 0.0, 0.0);
    z_plane = -1.0;

    player_size = 25.0;
    enemy_size  = 25.0;

    bg_color     = make_color(1.0, 1.0, 1.0);
    player_color = make_color(0.0, 0.0, 0.0);
    enemy_color  = make_color(0.9, 0.1, 0.1);

    player_start = make_point(origin->x,
                              origin->y - (canvas_height / 2) + (player_size / 2),
                              z_plane);
    enemy_start  = make_point(origin->x,
                              origin->y + (canvas_height / 2) - (enemy_size / 2),
                              z_plane);

    player = make_cube(player_start, 25.0, player_color);
    enemy  = make_cube(enemy_start, 25.0, enemy_color);

    enemy_min_x = origin->x - (canvas_width / 2) + enemy->size / 2;
    enemy_max_x = origin->x + (canvas_width / 2) - enemy->size / 2;

    // Minimum and Maximum times in Milliseconds.
    enemy_min_time = 2750;
    enemy_max_time = 3500;

    enemy_total_dist = (canvas_height - enemy->size);
    enemy_total_time = 2.5;
    enemy_step_time  = 10/1000;
    enemy_step_dist  = (enemy_total_dist / enemy_total_time) * enemy_step_time;
}

int main(int argc, char** argv) {
    init();
    glutInit(&argc, argv);
    my_setup(canvas_width, canvas_height, canvas_name);
    glutDisplayFunc(draw_all_objects);
    glutKeyboardFunc(handle_keys);
    glutMainLoop();
    return 0;
}