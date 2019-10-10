#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>


#include <vector>

#include "Line3d.h"


int left = -500, right = 500, bot = -500, top = 500;

void display(){
    //Set Axis


    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();
    glTranslatef(0, 0, -500);

    Line3d line(0, 0, 0, 100, 100, 0);
    
    glBegin(GL_POINTS);
        glColor3f(1.0f, 1.0f, 1.0f);
        line.draw();

        
    glEnd();   // Done drawing the pyramid

    glutSwapBuffers();
}

void reshape(int width, int height){
   // Compute aspect ratio of the new window
   if (height == 0) height = 1;                // To prevent divide by 0
   GLfloat aspect = (GLfloat)width / (GLfloat)height;
 
   // Set the viewport to cover the new window
   glViewport(0, 0, width, height);
 
   // Set the aspect ratio of the clipping volume to match the viewport
   glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
   glLoadIdentity();             // Reset
   // Enable perspective projection with fovy, aspect, zNear and zFar
   gluPerspective(45.0f, aspect, 0.1f, 500.0f);
}

int main(int argc, char** argv){
    glutInit(& argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE );

    glutInitWindowPosition(200,100);
    glutInitWindowSize(500,500);

    glutCreateWindow("Hello 3D");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    //Options
    glClearColor(0, 0, 0, 1);
    glClearDepth(1);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glShadeModel(GL_SMOOTH);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    glutMainLoop();
}
