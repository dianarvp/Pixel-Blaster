//
// Created by diana on 2/14/17.
//

#include <sstream>
#include "triangle.h"

triangle::triangle(std::string verts) {
    std::istringstream v(verts);
    int size;
    v >> size;
    if(size != 3) throw std::runtime_error("OFF not triangles");

    v >> v1 >> v2 >> v3;
}