#ifndef POINT3D_H
#define POINT3D_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void draw_3d_point(int x, int y, int z){
        glBegin(GL_POINTS);           // Begin drawing the pyramid with 4 triangles
        glVertex3f(x, y, z);
    glEnd();   // Done drawing the pyramid
}

struct Point3d
{
    int x, y, z;

    Point3d(){

    }

    Point3d(int x, int y, int z){
        this->x = x;
        this->y = y;
        this->z = z;
    }

    void operator = (Point3d const & other){
        this->x = other.x;
        this->y = other.y;
        this->z = other.z;
    }
    
};


#endif