#pragma once
#include <vector>

#include <GL/glew.h>

namespace shape {
    struct Cube {
        static const std::vector<unsigned int> indices;
        static const std::vector<GLfloat> vertices;
    };

    const std::vector<unsigned int> Cube::indices{
        // bottom
        0, 1, 2,
        2, 3, 0,
        // back face
        0, 1, 5,
        5, 4, 0,
        // right face
        2, 1, 5,
        5, 6, 2,
        // left face
        0, 4, 7,
        7, 3, 0,
        // front face
        3, 2, 6,
        6, 7, 3,
        // top
        4, 5, 6,
        6, 7, 4
    };

    const std::vector<GLfloat> Cube::vertices{
        // x    y      z     u  v          nx    ny    nz
        // left bottom back
        -1.0f, -1.0f, -1.0f, 0.0f, 0.0f,  0.0f, 0.0f, 0.0f,
        // right bottom back
        1.0f, -1.0f, -1.0f,  0.0f, 0.0f,  0.0f, 0.0f, 0.0f,
        // right bottom front
        1.0f, -1.0f, 1.0f,   0.0f, 0.0f,  0.0f, 0.0f, 0.0f,
        // left bottom front
        -1.0f, -1.0f, 1.0f,  0.0f, 0.0f,  0.0f, 0.0f, 0.0f,
        // left top back
        -1.0f, 1.0f, -1.0f, 0.0f, 0.0f,  0.0f, 0.0f, 0.0f,
        // right top back
        1.0f, 1.0f, -1.0f, 0.0f, 0.0f,  0.0f, 0.0f, 0.0f,
        // right top front
        1.0f, 1.0f, 1.0f, 0.0f, 0.0f,  0.0f, 0.0f, 0.0f,
        // left top front
        -1.0f, 1.0f, 1.0f, 0.0f, 0.0f,  0.0f, 0.0f, 0.0f,
    };
};


