
/***********************************************************


   This header file contains initialization function calls and set-ups
for basic 3D CS 445/545 Open GL (Mesa) programs that use the GLUT.
The initializations involve defining a callback handler (my_reshape_function)
that sets viewing parameters for orthographic 3D display.

   TSN 02/2010, updated 01/2012

 ************************************************************/

#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif
/* reshape callback handler - defines viewing parameters */

void my_3d_projection(int width, int height)
{
    GLfloat width_bound, height_bound;
    width_bound = width; height_bound = height;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, width_bound, 0.0, height_bound, 100.0, -300.0);
    // gluPerspective(58.0, width_bound/height_bound, 100.0, 300.0); 
    glTranslatef(-200.0, -200.0, -200.0);
    glMatrixMode(GL_MODELVIEW);
}

#define STRT_X_POS 25
#define STRT_Y_POS 25

void my_setup(int width, int height, char *window_name_str)
{
    // To get double buffering, uncomment the following line
    // glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); 
    // below code line does single buffering - if above line is uncommented,
    // the single buffering line will have to be commented out
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);  
    glutInitWindowSize(width, height);
    glutInitWindowPosition(STRT_X_POS,STRT_Y_POS);

    glutCreateWindow(window_name_str);

    glutReshapeFunc(my_3d_projection);
}

