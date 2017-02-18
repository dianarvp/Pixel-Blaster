//
// Created by diana on 2/14/17.
//

#include <sstream>
#include <vector>
#include <iostream>
#include "triangle.h"

triangle::triangle(std::string verts, const std::vector<point<float>> &points) {
    std::istringstream v(verts);
    int size;
    v >> size;
    if (size != 3) throw std::runtime_error("OFF not triangles");
    int i1, i2, i3;
    v >> i1 >> i2 >> i3;
    v1 = &points[i1];
    v2 = &points[i2];
    v3 = &points[i3];
}

void triangle::normal() {
    point<float> vec1 = *v1 - *v2;
    point<float> vec2 = *v1 - *v3;

    point<float> cross = vec1.cross(vec2);
    float magnitude = cross.mag();
    norm = cross / magnitude;
}

void triangle::color(const point<float> &lighting) {
    shade = fabs(lighting.dot(norm));
}