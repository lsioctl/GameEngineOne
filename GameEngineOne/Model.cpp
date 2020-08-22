#include "Model.h"
#include <iostream>

using namespace std;
Model::Model() : mIndices{ nullptr }, mVertices{ nullptr }, mIndicesSize{ 0 }, mVerticesSize{ 0 } {
    cout << "Model constructor called" << endl;
};

// TODO: return const pointer to avoid data corruption
// TODO: singleton or something alike
GLfloat* Model::getVertices() const {
    return mVertices;
}

unsigned int* Model::getIndices() const {
    return mIndices;
}

unsigned int Model::getVerticesSize() const {
    return mVerticesSize;
}

unsigned int Model::getIndicesSize() const {
    return mIndicesSize;
}