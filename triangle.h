//
// Created by diana on 2/14/17.
//

#ifndef GPU_TRIANGLE_H
#define GPU_TRIANGLE_H

#include <string>
#include <vector>
#include "point.h"

struct triangle {
    const point<float> *v1, *v2, *v3;
    triangle(std::string verts,const std::vector<point<float>>& points);
    //point<float> normal();
};


#endif //GPU_TRIANGLE_H
