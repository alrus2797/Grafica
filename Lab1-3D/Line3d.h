#ifndef LINE3D_H
#define LINE3D_H

#include "Point3d.h"

struct Line3d
{
    Point3d source;
    Point3d destination;

    Line3d(){

    }

    Line3d(Point3d source, Point3d destination){
        this->source        = source;
        this->destination   = destination;
    }

    Line3d(int x1, int y1, int z1, int x2, int y2, int z2){
        this->source        = Point3d(x1, y1, z1);
        this->destination   = Point3d(x2, y2, z2);
    }

    void draw(){
        float slope = (destination.y - source.y) / (float)(destination.x - source.x);

        int number_points = destination.x - source.x;

        float step = (destination.z - source.z) / (float)number_points;

        float z = source.z;

        float y;

        for (int x = source.x; x < destination.x; x++)
        {
            y = round(source.y + slope * (x - source.x));
            draw_3d_point(x, y, z += step);
        }
        
    }
};


#endif