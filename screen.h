//
// Created by diana on 2/17/17.
//

#ifndef GPU_SCREEN_COORDS_H
#define GPU_SCREEN_COORDS_H

#include <vector>
#include <cstdint>
#include "point.h"

/**
 * Screen is a buffer of pixels
 */
struct screen {
    int width, height, depth;
    std::vector<uint32_t> pixels;

    screen(int x, int y, int z) : pixels(x * y, 0xFFFFFFFF) {
        width = x;
        height = y;
        depth = z;
    }

    /**
     * Checks to see whether an x, y pair are within the bounds of the screen.
     */
    bool inbounds(int x, int y) const;

    /**
     * Checks to see whether a point is within the bounds of the screen.
     */
    bool inbounds(const point<int> &p) const;

    /**
     * Sets a pixel on the screen to be a certain throw_shade.
     *
     * @param x-coordinate
     * @param y-coordinate
     * @param color
     */
    void set_pixel(int x, int y, uint32_t color);

    /**
     * Sets a pixel on the screen to be a certain throw_shade.
     *
     * @param point
     * @param color
     */
    void set_pixel(const point<int> &p, uint32_t color);

    /**
     * Sets pixels on the screen .
     *
     * @param p1
     * @param p2
     * @param color
     */
    void draw_line(const point<int> &p1, const point<int> &p2, uint32_t color);

    /**
     * Draws a triangle
     * @param p1
     * @param p2
     * @param p3
     * @param color
     */
    void draw_triangle(const point<int> &p1, const point<int> &p2, const point<int> &p3, uint32_t color);

    /**
     * Converts
     *
     * @param p: A point with floating point coordinates from the intermediary coordinate frame.
     * @return: A point with integer coordinates
     */
    point<int> projection(const point<float> &p) const;
};


#endif //GPU_SCREEN_COORDS_H
