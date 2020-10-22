#include "BasicShape.h"
#include <iostream>

BasicShape::BasicShape() {
    std::cout << "Model constructor called" << std::endl;
};

// TODO: return const pointer to avoid data corruption
// TODO: singleton or something alike
const std::vector<GLfloat>& BasicShape::getVertices() const {
    return mVertices;
}

const std::vector<unsigned int>& BasicShape::getIndices() const {
    return mIndices;
}
