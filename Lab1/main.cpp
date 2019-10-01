#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <stdio.h>
#include <vector>

#include "Poligon2d.h"
#include "Circle2d.h"

#include "Axis2d.h"

int left = -500, right = 500, bot = -500, top = 500;

void display(){
    //Set Axis

    Axis2d axis(left, right, bot, top);
    

    //Set Points

    Point2d p1(600, 250);
    Point2d p2(300, 300);
    std::cout << " - p1: "<< p1 << std::endl;
    p1 = p2;
    std::cout << " - p1: "<< p1 << std::endl;
    Line2d line1(0, 250, 250, 0);
    Line2d line2(250, 0, 500, 250);
    Line2d line3(500, 250, 250, 500);
    Line2d line4(250, 500, 0, 250);

    Poligon2d rombus({
            {0  , 250},
            {250, 0},
            {500, 250},
            {250, 500},
        });

    Circle2d circle(Point2d(0,0), 100);

    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();


    rombus.draw();
    circle.basic_octant_draw();

    axis.draw();

    //Draw things
    //inc_line(p1,p2);

    glFlush();
}

void reshape(int width, int heigth){
    glViewport(0, 0, (GLsizei)width, (GLsizei)heigth);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    gluOrtho2D(left, right, bot, top);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv){
    glutInit(& argc, argv);
    glutInitDisplayMode(GLUT_RGB);

    glutInitWindowPosition(200,100);
    glutInitWindowSize(500,500);

    glutCreateWindow("Hello");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    glClearColor(0, 0, 0, 1);

    glutMainLoop();
}

