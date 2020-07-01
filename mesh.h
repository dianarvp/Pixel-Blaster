//
// Created by diana on 2/14/17.
//

#ifndef GPU_MESH_H
#define GPU_MESH_H


#include "triangle.h"
#include "point.h"
#include "matrix.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

template<typename T>
struct mesh {
    std::vector<point<T>> points;
    std::vector<triangle> triangles;

    mesh(std::ifstream &in) {
        std::string line;
        std::getline(in, line);
        if (line != "OFF") throw std::runtime_error("Not OFF file.");

        std::getline(in, line);
        std::istringstream ss(line);

        unsigned int pt_size, t_size;
        ss >> pt_size;
        points.reserve(pt_size);
        ss >> t_size;
        triangles.reserve(t_size);

        for (int i = 0; i < pt_size; i++) {
            std::getline(in, line);
            points.emplace_back(line);
        }

        for (int i = 0; i < t_size; i++) {
            std::getline(in, line);
            triangles.emplace_back(line, points);
        }

    }

    void transform(const matrix &transformation) {
        for (point<T> &p: points) {
            p = transformation.vector_mult(p);
        }
    }
};

#endif //GPU_MESH_H
