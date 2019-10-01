#ifndef CIRCLE2D_H
#define CIRCLE2D_H

#include "Point2d.h"

struct Circle2d
{
    Point2d center;
    int r;

    Circle2d(Point2d center, int r){
        this->center    = center;
        this->r         = r;
    }

    void basic_octant_draw(){
        int x, y;
        float d;

        x = 0;
        y = r;

        d = 1 - r;

        draw_point(x, y);

        while ( y > x ){
            if ( d < 0 ){
                d = d + 2 * x + 3;
                x++;
            }
            else{
                d = d + 2 * ( x - y ) + 5;
                x++;
                y--;
            }
            printf("%i \n", d);
            draw_point(x,y);
        }
    }

    void draw(){
        
    }
};


#endif