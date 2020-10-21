#include "Model2.h"
#include <iostream>

using namespace std;
Model2::Model2() {
    cout << "Model constructor called" << endl;
};

// TODO: return const pointer to avoid data corruption
// TODO: singleton or something alike
const std::vector<GLfloat>& Model2::getVertices() const {
    return mVertices;
}

const std::vector<unsigned int>& Model2::getIndices() const {
    return mIndices;
}
