//
// Created by diana on 2/17/17.
//

#include <cstdint>
#include "screen.h"

bool screen::inbounds(int x, int y) const {
    return 0 <= x && x < width && 0 <= y && y < height;
}

bool screen::inbounds(const point<int> &p) const {
    return inbounds(p[0], p[1]);
}

void screen::set_pixel(int x, int y, uint32_t color) {
    if (inbounds(x, y)) {
        pixels[x + width * y] = color;
    }
}

void screen::set_pixel(const point<int> &p, uint32_t color) {
    set_pixel(p[0], p[1], color);
}

void screen::draw_line(const point<int> &p1, const point<int> &p2, uint32_t color) {
    int y = p1[1];
    int w = p2[0] - p1[0];
    int h = p2[1] - p1[1];

    int x_dir = w > 0 ? 1 : -1;
    int y_dir = h > 0 ? 1 : -1;

    w = abs(w);
    h = abs(h);
    int error = 0;
    for (int x = p1[0]; x != p2[0] + x_dir; x += x_dir) {
        while(true) {
            set_pixel(x, y, color);
            if((abs(error) * 2 <= w)) break;
            y += y_dir;
            error += w;
        }
        error -= h;
    }
}

point<int> screen::projection(const point<float> &p) const {
    point<int> result;
    result[0] = ((p[0] / 4 + 1) / 2) * width;
    result[1] = ((-p[1] / 4 + 1) / 2) * height;
    result[2] = ((p[2] / 4 + 1) / 2) * depth;
    return result;
}