#include "Model.h"
#include <iostream>

using namespace std;
Model::Model() : mIndices{ nullptr }, mVertices{ nullptr }, mIndicesSize{ 0 }, mVerticesSize{ 0 } {};

// TODO: return const pointer to avoid data corruption
// TODO: singleton or something alike
GLfloat* Model::getVertices() {
    return mVertices;
}

unsigned int* Model::getIndices() {
    return mIndices;
}

unsigned int Model::getVerticesSize() {
    return mVerticesSize;
}

unsigned int Model::getIndicesSize() {
    return mIndicesSize;
}