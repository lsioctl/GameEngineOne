#pragma once

#include "Model.h"

class Pyramid : public Model {
public:
    Pyramid() {
        // I know only now what would be the size of the array
        // I can't find a way to avoid specifying the size
        // TODO: find a better pattern
        mIndicesSize = 18;
        mIndices  = new unsigned int[mIndicesSize] {
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

        mVerticesSize = 128;
        mVertices = new GLfloat[mVerticesSize] {
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
	}

    ~Pyramid() {
        // this is also not clean
        // as the new[] as been called here, only child class nows the 
        // delete[] and not the delete must be called
        delete[] mIndices;
        delete[] mVertices;

    }

};
