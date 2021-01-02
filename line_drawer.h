//
// Created by dianarvp on 1/1/21.
//

#ifndef GPU_LINE_DRAWER_H
#define GPU_LINE_DRAWER_H


class line_drawer {
    int num_steps, side_steps, cross, y;

public:
    line_drawer(int num_steps, int side_steps);

    int step_through();
};


#endif //GPU_LINE_DRAWER_H
