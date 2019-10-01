#ifndef POLIGON2D_H
#define POLIGON2D_H

#include "Line2d.h"
#include <vector>

typedef std::vector<std::vector<int>> PointList;

struct Poligon2d{
    std::vector<Line2d*> sides;
    Poligon2d(PointList points){
        int i = 0;
        for (i = 0; i < points.size() - 1; i++){   
            this->sides.push_back(new Line2d(   points[i][0]    , points[i][1], 
                                                points[i+1][0]  , points[i+1][1]));
        }
        this->sides.push_back(new Line2d(   points[i][0]    , points[i][1], 
                                            points[0][0]  , points[0][1]));
    }

    void draw(){
        for(auto i: this->sides){
            i->draw();
        }
    }
};

#endif