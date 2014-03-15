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
    float size;
    Color color;
    int position;
    Point translation;
} Cube;

// Pointers to Point objects that represent the starting positions
// of the player and enemy ships
Point* player_start;
Point* enemy_start;

// Pointers to Color objects that represent the colors used in the 
// program.
//      - White for the background, 
//      - Black for player lines,
//      - Red for the enemy ships.
Color* white;
Color* black;
Color* red;

// Pointers to Cube objects representing the player and enemy ships.
Cube* player;
Cube* enemy;

// Floats that represent the size of the player and enemy cubes
float player_size;
float enemy_size;



// ------------------------------------
// -------> Utility Functions <--------
// ------------------------------------

// Used as a constructor to initialize a new Point object.
Point* newPoint(float x, float y, float z) {
    Point* point = (Point*)malloc(sizeof(Point));

    point->x = x;
    point->y = y;
    point->z = z;

    return point;
}

// Used as a constructor to initialize a new Color object.
Color* newColor(float red, float green, float blue) {
    Color* color = (Color*)malloc(sizeof(Color));

    color->red = red;
    color->green = green;
    color->blue = blue;

    return color;
}

// Used as a constructor to initialize a new Cube object.
Cube* newCube(float size, Color* color) {
    Cube* cube = malloc(sizeof(Cube));
    cube->size = size;
    cube->color = *color;
    cube->translation.x = 0.0;
    cube->translation.y = 0.0;
    cube->translation.z = 0.0;
    return cube;
}



// ------------------------------------
// -------> Drawing Functions <--------
// ------------------------------------

// 
void DrawCube(Cube* cube) {
    glPushMatrix();
    glTranslatef(cube->translation.x,
                 cube->translation.y,
                 cube->translation.z);

    glutWireCube(cube->size);

    glTranslatef((cube->translation.x * -1),
                 (cube->translation.y * -1),
                 (cube->translation.z * -1));
    glPopMatrix();
}

// 
void drawAll() {

}

// 
void animate() {

}



// ------------------------------------
// -----> User Input Functions <-------
// ------------------------------------

// 
void handleKeys(unsigned char c, GLint x, GLint y) {

}



// ------------------------------------
// --------> Main Functions <----------
// ------------------------------------

// Initializes that objects and variables that will be used.
void init() {
    enemy_start = newPoint( canvas_Width / 2,
                            canvas_Height + (enemy_size / 2),
                            z_plane );
    enemy_start = newPoint( canvas_Width / 2,
                            canvas_Height + (enemy_size / 2),
                            z_plane );

    player = newCube(player_start, 25.0, black);
    enemy = newCube(enemy_start, 25.0, red);
}

int main(int argc, char** argv) {
    init();
    glutInit(&argc, argv);
    my_setup(canvas_Width, canvas_Height, canvas_Name);
    glutDisplayFunc(drawAll);
    glutKeyboardFunc(handleKeys);
    glutMainLoop();
    return 0;
}