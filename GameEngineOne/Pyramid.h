#pragma once

#include "Model.h"

class Pyramid : public Model {
public:
    Pyramid() {
        // did not find another way to do this
        // as I know only now what would be the size of the array
        // TODO: find a better pattern
        unsigned int tempIndices[] = {
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

        mIndices = tempIndices;

        mIndicesSize = sizeof(tempIndices) / sizeof(tempIndices[0]);

        GLfloat tempVertices[] = {
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

        mVertices = tempVertices;

        mVerticesSize = sizeof(tempVertices) / sizeof(tempVertices[0]);
	}
};
