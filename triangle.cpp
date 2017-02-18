//
// Created by diana on 2/14/17.
//

#include <sstream>
#include <vector>
#include "triangle.h"

triangle::triangle(std::string verts, const std::vector<point<float>>& points) {
    std::istringstream v(verts);
    int size;
    v >> size;
    if(size != 3) throw std::runtime_error("OFF not triangles");
    int i1, i2, i3;
    v >> i1 >> i2 >> i3;
    v1 = &points[i1];
    v2 = &points[i2];
    v3 = &points[i3];
}
/*
point<float> triangle::normal() {
    get the vectors
    cross product;
    normalize;
}*/