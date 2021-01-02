//
// Created by dianarvp on 1/1/21.
//

#include <cstdlib>
#include "line_drawer.h"

line_drawer::line_drawer(int num_steps, int side_steps) : num_steps(abs(num_steps)), side_steps(side_steps), cross(0), y(0){}

int line_drawer::step_through() {
    // cross = num_steps * y - side_steps * abs(x)
    int side_dir = (side_steps > 0) ? 1 : -1;
    cross -= side_steps;
    while ((side_steps >= 0) == (cross < 0)) {
        cross += num_steps * side_dir;
        y += side_dir;
    }
    return y;
}