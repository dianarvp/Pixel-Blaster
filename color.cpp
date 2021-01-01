//
// Created by the krew on 12/31/20.
//

#include <iostream>
#include "color.h"


void color::operator*=(float f) {
    if (f > 1 || f < 0) {
        std::cout << "Fix me (colour out of range)";
    }
    r *= f;
    g *= f;
    b *= f;
}


color color::operator*(float f) {
    color colour = *this;
    colour *= f;

    return colour;
}

color::color(uint8_t r, uint8_t g, uint8_t b) : r(r), g(g), b(b){}

uint32_t color::pack() {
    return (uint32_t(r) << 16) + (uint32_t(g) << 8) + uint32_t(b);
}

std::ostream &operator<<(std::ostream &os, const color &colour) {
    return os << "r: " << int(colour.r) << ", g: " << int(colour.g) << ", b: " << int(colour.b);
}
