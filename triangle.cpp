//
// Created by diana on 2/14/17.
//

#include <sstream>
#include <vector>
#include <iostream>
#include "triangle.h"

triangle::triangle(std::string verts, const std::vector<point<float>> &points) : colour(128, 128, 128) {
    std::istringstream v(verts);
    int size;
    v >> size;
    if (size != 3) throw std::runtime_error("OFF not triangles");
    int i1, i2, i3;
    v >> i1 >> i2 >> i3;
    v1 = &points[i1];
    v2 = &points[i2];
    v3 = &points[i3];

    if(!v.eof()) {
        int r, g, b;
        v >> r >> g >> b;
        colour = color(uint8_t(r), uint8_t(g), uint8_t(b));
    }
}

void triangle::normal() {
    point<float> vec1 = *v1 - *v2;
    point<float> vec2 = *v1 - *v3;

    point<float> cross = vec1.cross(vec2);
    float magnitude = cross.mag();
    norm = cross / magnitude;
}

void triangle::throw_shade(const point<float> &lighting) {
    float dot = lighting.dot(norm);
    if (dot * lighting[2] < 0) {
        dot = 0;
    }
    shade = fabs(dot);
    //shade = 1;
}

color triangle::fade_color() {
    return colour * shade;
}
