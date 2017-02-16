//
// Created by diana on 2/14/17.
//

#ifndef GPU_POINT_H
#define GPU_POINT_H

#include <string>
#include <sstream>
template <typename T>
struct point {
    T p[3];

    point(){};
    point(std::string coords) {
        std::istringstream dims(coords);
        dims >> p[0] >> p[1] >> p[2];
    }

    T& operator[] (int i) {
        return p[i];
    }

    const T& operator[] (int i) const{
        return p[i];
    }

    point<int> screen_coords(int SCREEN_WIDTH, int SCREEN_HEIGHT, int SCREEN_DEPTH) const {
        point<int> result;
        result[0] = ((p[0]/4+1)/2)*SCREEN_WIDTH;
        result[1] = ((-p[1]/4+1)/2)*SCREEN_HEIGHT;
        result[2] = ((p[2]/4+1)/2)*SCREEN_DEPTH;
        return result;
    }
    bool inbounds(int width, int height) {
        return 0<=p[0] && p[0]<width && 0<=p[1] && p[1]< height;
    }

};

template<typename T>
std::ostream& operator<< (std::ostream & out, point<T> const& data) {
    return out << data[0] << ", " << data[1] <<", "<<data[2];
}


#endif //GPU_POINT_H
