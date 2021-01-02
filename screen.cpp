//
// Created by diana on 2/17/17.
//

#include <cstdint>
#include <algorithm>
#include "screen.h"
#include "line_drawer.h"

bool screen::inbounds(int x, int y, int z) const {
    return 0 <= x && x < width && 0 <= y && y < height && 0 <= z && z < depth;
}

bool screen::inbounds(const point<int> &p) const {
    return inbounds(p[0], p[1], p[2]);
}

void screen::set_pixel(int x, int y, int z, uint32_t color) {
    if (inbounds(x, y, z) && z < z_buffer[x + width * y]) {
        z_buffer[x + width * y] = z;
        pixels[x + width * y] = color;
    }
}

void screen::set_pixel(const point<int> &p, uint32_t color) {
    set_pixel(p[0], p[1], p[2], color);
}

void screen::draw_line(const point<int> &p1, const point<int> &p2, uint32_t color) {
    int w = p2[0] - p1[0];
    int h = p2[1] - p1[1];
    int d = p2[2] - p1[2];

    int x_dir = w > 0 ? 1 : -1;
    int y_dir = h > 0 ? 1 : -1;
    int z_dir = d > 0 ? 1 : -1;

    w = abs(w);
    h = abs(h);
    d = abs(d);
    int z_error = 0;
    if (w > h) {
        int y_error = 0;
        int y = p1[1];
        int z = p1[2];
        for (int x = p1[0]; x != p2[0] + x_dir; x += x_dir) {
            if ((abs(y_error) * 2 > w)) {
                y += y_dir;
                y_error += w;
            }
            while ((abs(z_error) * 2 > w)) {
                z += z_dir;
                z_error += w;
            }
            set_pixel(x, y, z, color);
            y_error -= h;
            z_error -= d;
        }
    } else {
        int x_error = 0;
        int x = p1[0];
        int z = p1[2];
        for (int y = p1[1]; y != p2[1] + y_dir; y += y_dir) {
            if ((abs(x_error) * 2 > h)) {
                x += x_dir;
                x_error += h;
            }
            while ((abs(z_error) * 2 > h)) {
                z += z_dir;
                z_error += h;
            }
            set_pixel(x, y, z, color);
            x_error -= w;
            z_error -= d;
        }
    }
}

void screen::draw_triangle(const point<int> &p1, const point<int> &p2, const point<int> &p3, uint32_t color) {
    const point<int> *point1 = &p1, *point2 = &p2, *point3 = &p3;

    //sort ascending by y value
    if ((*point1)[1] > (*point2)[1])
        std::swap(point1, point2);
    if ((*point1)[1] > (*point3)[1])
        std::swap(point1, point3);
    if ((*point2)[1] > (*point3)[1])
        std::swap(point2, point3);
    const point<int> &pt1 = *point1, &pt2 = *point2, &pt3 = *point3;

    //check if midpoint is left or right of side
    point<int> vec1 = pt3 - pt2;
    point<int> vec2 = pt3 - pt1;
    bool mid_to_left = vec1.cross(vec2)[2] > 0;
    // We're computing the boundaries of two lines in 3D space (the two sides of a triangle),
    // then filling in the pixels between them.
    // We step through the y-dimension and track the other two separately with line_drawer.
    {
        point<int> left_diff = pt2 - pt3;
        point<int> right_diff = pt1 - pt3;

        if (!mid_to_left) {
            std::swap(left_diff, right_diff);
        }

        line_drawer lx(left_diff[1], left_diff[0]);
        line_drawer lz(left_diff[1], left_diff[2]);
        line_drawer rx(right_diff[1], right_diff[0]);
        line_drawer rz(right_diff[1], right_diff[2]);
        //upper triangle from p3 down to p2
        for (int y = pt3[1] - 1; y >= pt2[1]; y--) {
            int leftmost_x = lx.step_through();
            int rightmost_x = rx.step_through();
            int leftmost_z = lz.step_through() + pt3[2];
            int rightmost_z = rz.step_through() + pt3[2];

            line_drawer dz(rightmost_x - leftmost_x, rightmost_z - leftmost_z);
            int z = leftmost_z;
            for (int x = pt3[0] + leftmost_x; x < pt3[0] + rightmost_x; x++) {
                set_pixel(x, y, z, color);
                z = leftmost_z + dz.step_through();
            }
        }
    }
    {
        point<int> left_diff = pt2 - pt1;
        point<int> right_diff = pt3 - pt1;

        if (!mid_to_left) {
            std::swap(left_diff, right_diff);
        }

        line_drawer lx(left_diff[1], left_diff[0]);
        line_drawer lz(left_diff[1], left_diff[2]);
        line_drawer rx(right_diff[1], right_diff[0]);
        line_drawer rz(right_diff[1], right_diff[2]);
        //lower triangle is p1 up to p2
        for (int y = pt1[1] + 1; y < pt2[1]; y++) {
            int leftmost_x = lx.step_through();
            int rightmost_x = rx.step_through();
            int leftmost_z = lz.step_through() + pt1[2];
            int rightmost_z = rz.step_through() + pt1[2];

            line_drawer dz(rightmost_x - leftmost_x, rightmost_z - leftmost_z);
            int z = leftmost_z;
            for (int x = pt1[0] + leftmost_x; x < pt1[0] + rightmost_x; x++) {
                set_pixel(x, y, z, color);
                z = leftmost_z + dz.step_through();
               // std::cout << "x, y, z: " << x << ", " << y << ", " << z << "\n";
            }
        }
    }
}

point<int> screen::projection(const point<float> &p) const {
    point<int> result;
    result[0] = ((p[0] / 4 + 1) / 2) * width;
    result[1] = ((p[1] / 4 + 1) / 2) * height;
    result[2] = ((p[2] / 4 + 1) / 2) * depth;
    return result;
}

void screen::clear() {
    std::fill(pixels.begin(), pixels.end(), WHITE);
    std::fill(z_buffer.begin(), z_buffer.end(), depth);
}
