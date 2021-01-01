//
// Created by dianarvp on 12/31/20.
//

#ifndef GPU_COLOR_H
#define GPU_COLOR_H


#include <cstdint>

class color {
    uint8_t r, g, b;

public:
    color(uint8_t r, uint8_t g, uint8_t b);

    void operator *=(float f);

    color operator *(float f);

    friend std::ostream& operator<<(std::ostream& os, const color& colour);

    uint32_t pack();
};


#endif //GPU_COLOR_H
