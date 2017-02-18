//
// Created by diana on 2/14/17.
//

#ifndef GPU_POINT_H
#define GPU_POINT_H

#include <string>
#include <sstream>
#include <math.h>
#include <iomanip>
#include <iostream>

template<typename T>
struct point {
    T p[3];

    point() {};

    point(std::string coords) {
        std::istringstream dims(coords);
        dims >> p[0] >> p[1] >> p[2];
    }

    point(T x, T y, T z) {
        p[0] = x;
        p[1] = y;
        p[2] = z;
    }

    point<T> cross(const point<T> &p2) const {
        point<T> result;
        result[0] = (*this)[1] * p2[2] - (*this)[2] * p2[1];
        result[1] = -((*this)[0] * p2[2] - (*this)[2] * p2[0]);
        result[2] = (*this)[0] * p2[1] - (*this)[1] * p2[0];
        return result;
    }

    T dot(const point<T> &p2) const {
        T result = 0;
        for (int i = 0; i < 3; i++) {
            result += p[i] * p2[i];
        }
        return result;
    }

    T mag() const {
        return sqrt(this->dot(*this));
    }

    point<T> operator-(const point<T> &p) const {
        point<T> vector;
        for (int i = 0; i < 3; i++) {
            vector[i] = (*this)[i] - p[i];
        }
        return vector;
    }

    T &operator[](int i) {
        return p[i];
    }

    const T &operator[](int i) const {
        return p[i];
    }

    point<T> operator/(T t) {
        point<T> result;
        for (int i = 0; i < 3; i++) {
            result[i] = (*this)[i] / t;
        }
        return result;
    }


};

template<typename T>
std::ostream &operator<<(std::ostream &out, point<T> const &data) {
    return out << "(" << std::setprecision(3) << data[0] << ", " << data[1] << ", " << data[2] << ")";
}


#endif //GPU_POINT_H
