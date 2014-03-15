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
#define canvas_Width 400
#define canvas_Height 400
#define canvas_Name "Blaster Game"

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



// ------------------------------------
// -------> Utility Functions <--------
// ------------------------------------

// Used as a constructor to initialize a new Point object.
Point* make_Point(float x, float y, float z) {
    Point* point = (Point*)malloc(sizeof(Point));

    point->x = x;
    point->y = y;
    point->z = z;

    return point;
}

// Used as a constructor to initialize a new Color object.
Color* make_Color(float red, float green, float blue) {
    Color* color = (Color*)malloc(sizeof(Color));

    color->red   = red;
    color->green = green;
    color->blue  = blue;

    return color;
}

// Used as a constructor to initialize a new Color object.
Cube* make_Cube(Point* center, float size, Color* color) {
    Cube* cube   = malloc(sizeof(Cube));
    cube->center = *center;
    cube->size   = size;
    cube->color  = *color;
    return cube;
}



// ------------------------------------
// -------> Drawing Functions <--------
// ------------------------------------

// 
void draw_Cube(Cube* cube) {
    glPushMatrix();
    glTranslatef(cube->center.x,
                 cube->center.y,
                 cube->center.z);
    glColor3f( cube->color.red, cube->color.green, cube->color.blue);
    glutWireCube(cube->size);

    glTranslatef((cube->center.x * -1),
                 (cube->center.y * -1),
                 (cube->center.z * -1));
    glPopMatrix();
}

// 
void draw_all_objects() {
    glClearColor(bg_color->red, bg_color->green, bg_color->blue, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    draw_Cube(player);
    draw_Cube(enemy);
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

}



// ------------------------------------
// --------> Main Functions <----------
// ------------------------------------

// Initializes that objects and variables that will be used.
void init() {
    origin = make_Point(0.0, 0.0, 0.0);
    z_plane = -1.0;

    player_size = 25.0;
    enemy_size  = 25.0;

    bg_color     = make_Color(1.0, 1.0, 1.0);
    player_color = make_Color(0.0, 0.0, 0.0);
    enemy_color  = make_Color(0.9, 0.1, 0.1);

    player_start = make_Point(origin->x,
                              origin->y - (canvas_Height / 2) - (player_size / 2),
                              z_plane);
    enemy_start  = make_Point(origin->x,
                              origin->y + (canvas_Height / 2) + (enemy_size / 2),
                              z_plane);

    player = make_Cube(player_start, 25.0, player_color);
    enemy  = make_Cube(enemy_start, 25.0, enemy_color);
}

int main(int argc, char** argv) {
    init();
    glutInit(&argc, argv);
    my_setup(canvas_Width, canvas_Height, canvas_Name);
    glutDisplayFunc(draw_all_objects);
    glutKeyboardFunc(handle_keys);
    glutMainLoop();
    return 0;
}