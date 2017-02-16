//
// Created by diana on 2/15/17.
//

#include <iostream>
#include "matrix.h"

matrix::matrix(std::vector<float> &elements) {
    float* start = &m[0][0];
    for(int i=0; i<12; i++){
        start[i] = elements[i];
    }
}

matrix::matrix(std::istream& elements) {
    float* start = &m[0][0];
    for(int i=0; i<12; i++) {
        elements >> start[i];
    }
}


std::ostream& operator<<(std::ostream &out, matrix const &data) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            out << data.m[i][j]<<" ";
        }
        out << std::endl;
    }

    return out;
}
