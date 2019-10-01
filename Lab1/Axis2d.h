#ifndef AXIS2D_H
#define AXIS2D_H

#include "Line2d.h"

struct Axis2d
{
    Line2d x_axis, y_axis;
    Axis2d(int left, int right, int bot, int top){
        x_axis = Line2d(left, 0,right, 0);
        y_axis = Line2d(0, bot, 0, top);
    }

    void draw(){
        this->x_axis.draw();
        this->y_axis.draw();
    }
};



#endif