//
// Created by diana on 2/14/17.
//

#ifndef GPU_POINT_H
#define GPU_POINT_H

#include <string>
#include <sstream>
template <typename T>
struct point {
    T x, y, z;
    point(std::string coords) {
        std::istringstream dims(coords);
        dims >> x >> y >> z;
    }

};
template<typename T>
std::ostream& operator<< (std::ostream & out, point<T> const& data) {
    return out << data.x << ", " << data.y <<", "<<data.z;
}


#endif //GPU_POINT_H
