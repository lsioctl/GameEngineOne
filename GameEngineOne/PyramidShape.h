#pragma once
#include "BasicShape.h"

class PyramidShape : public BasicShape {
};

// static so can't be initialized in constructor
// TODO: maybe a way with C++17 to add it in the class
// with inline static
const std::vector<unsigned int> PyramidShape::mIndices = {
    // bottom
    0, 1, 2,
        2, 3, 0,
        // back face
        4, 5, 6,
        // right face
        7, 8, 9,
        // left face
        10, 11, 12,
        // front face
        13, 14, 15,
};

const std::vector<GLfloat> PyramidShape::mVertices = {
    // x    y      z     u  v          nx    ny    nz
    // bottom of the pyramid
    -1.0f, -1.0f, -1.0f, 0.0f, 0.0f,  0.0f, +1.0f, 0.0f,
    1.0f, -1.0f, -1.0f,  1.0f, 0.0f,  0.0f, +1.0f, 0.0f,
    1.0f, -1.0f, 1.0f,   1.0f, 1.0f,  0.0f, +1.0f, 0.0f,
    -1.0f, -1.0f, 1.0f,  0.0f, 1.0f,  0.0f, +1.0f, 0.0f,
    // back face
    -1.0f, -1.0f, -1.0f, 0.0f, 0.0f,  0.0f, -0.5f, -1.0f,
    1.0f, -1.0f, -1.0f,  1.0f, 0.0f,  0.0f, -0.5f, -1.0f,
    0.0f, 1.0f, 0.0f,  0.5f, 1.0f,    0.0f, -0.5f, -1.0f,
    // right face
    1.0f, -1.0f, -1.0f,  0.0f, 0.0f,  1.0f, -0.5f, 0.0f,
    1.0f, -1.0f, 1.0f,   1.0f, 0.0f,  1.0f, -0.5f, 0.0f,
    0.0f, 1.0f, 0.0f,  0.5f, 1.0f,    1.0f, -0.5f, 0.0f,
    // left face
    -1.0f, -1.0f, 1.0f,  0.0f, 0.0f,  -1.0f, -0.5f, 0.0f,
    -1.0f, -1.0f, -1.0f, 1.0f, 0.0f,  -1.0f, -0.5f, 0.0f,
    0.0f, 1.0f, 0.0f,  0.5f, 1.0f,    -1.0f, -0.5f, 0.0f,
    // front face
    1.0f, -1.0f, 1.0f,   0.0f, 0.0f,  0.0f, -0.5f, 1.0f,
    -1.0f, -1.0f, 1.0f,  1.0f, 0.0f,  0.0f, -0.5f, 1.0f,
    0.0f, 1.0f, 0.0f,  0.5f, 1.0f,    0.0f, -0.5f, 1.0f,
};