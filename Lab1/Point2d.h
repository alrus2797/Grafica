#ifndef POINT2D_H
#define POINT2D_H
#include <iostream>

void draw_point(int x, int y){
    glBegin(GL_POINTS);
        glVertex2i(x,y);
    glEnd();
}


struct Point2d
{
    int x;
    int y;

    Point2d(){
        
    }

    Point2d(int x, int y){
        this->x = x;
        this->y = y;
    }

    void operator = (Point2d const & other){
        this->x = other.x;
        this->y = other.y;
    }

    friend std::ostream& operator << (std::ostream& os, const Point2d& point);
};

std::ostream& operator << (std::ostream& os, const Point2d& point){
    os << "(" << point.x << "," << point.y << ")";
    return os;
}

#endif