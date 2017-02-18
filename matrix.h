//
// Created by diana on 2/15/17.
//

#ifndef GPU_MATRIX_H
#define GPU_MATRIX_H


#include <vector>
#include "point.h"

struct matrix {
    float m[3][4];

    matrix(std::vector<float> &elements);

    matrix(std::istream &elements);

    template<typename T>
    point<T> vector_mult(const point<T> &p) const {
        point<T> pt;
        for (int i = 0; i < 3; i++) {
            pt[i] = 0;
            for (int j = 0; j < 3; j++) {
                pt[i] += m[i][j] * p[j];
            }
            pt[i] += m[i][3];
        }
        return pt;
    }

    void scale(float scale) {
        for(int i=0; i<3; i++) {
            for(int j=0; j<4; j++) {
                m[i][j] *= scale;
            }
        }
    }
};


std::ostream &operator<<(std::ostream &out, matrix const &data);

#endif //GPU_MATRIX_H
