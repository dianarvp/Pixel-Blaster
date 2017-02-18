//
// Created by diana on 2/17/17.
//

#ifndef GPU_SCREEN_COORDS_H
#define GPU_SCREEN_COORDS_H

#include <vector>
#include "point.h"

struct screen {
    int width, height, depth;
    std::vector<uint32_t> pixels;

    screen(int x, int y, int z) : pixels(x * y, 0xFFFFFFFF) {
        width = x;
        height = y;
        depth = z;
    }

    bool inbounds(int x, int y) const;
    bool inbounds(const point<int> &p) const;

    void set_pixel(int x, int y, uint32_t color);
    void set_pixel(const point<int> &p, uint32_t color);

    void draw_line(const point<int> &p1, const point<int> &p2, uint32_t color);

    point<int> projection(const point<float> &p) const;
};


#endif //GPU_SCREEN_COORDS_H
