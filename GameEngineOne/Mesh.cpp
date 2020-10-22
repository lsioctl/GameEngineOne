#include "Mesh.h"

using namespace std;

Mesh::Mesh() : mVAO{ 0 }, mVBO{ 0 }, mIBO{ 0 }, mIndexCount{ 0 } {
}

// when array decay to pointer, sizeof(pointer) gives the size of the pointer, we lost sizeof(array)
void Mesh::create(const GLfloat* vertices, unsigned int verticesSize, const unsigned int* indices, unsigned int indicesSize) {

    // keep track of number of indexes, it will be needed for render()
    mIndexCount = indicesSize;

    // Note: &mVAO equivalent to &this->mVAO or &(this->mVAO)
    glGenVertexArrays(1, &mVAO);
    glBindVertexArray(mVAO);

    glGenBuffers(1, &mIBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize * sizeof(indices[0]), indices, GL_STATIC_DRAW);

    glGenBuffers(1, &mVBO);
    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    glBufferData(GL_ARRAY_BUFFER, verticesSize * sizeof(vertices[0]), vertices, GL_STATIC_DRAW);

    // here 0 refers to the same 'stuff' (a bit lost for now)
    // with u v coordinates, we will have 3 values out of 8 for the vertices
    // stride is here for that purpose
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 8, 0);
    // slot 1 for u, v so for texture coordinates
    // offset for the first value is 3
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 8, (void*)(sizeof(vertices[0]) * 3));
    // for normals
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 8, (void*)(sizeof(vertices[0]) * 5));
    // enable vertices, texture and normal on VAO
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

}

void Mesh::create(const std::vector<unsigned int>& indices, const std::vector<GLfloat>& vertices) {
    // TODO: get rid of those cast issues
    auto verticesSize{ static_cast<unsigned int>(vertices.size()) };
    auto indicesSize{ static_cast<unsigned int>(indices.size()) };
    create(
        vertices.data(),
        verticesSize,
        indices.data(),
        indicesSize
    );
}

void Mesh::create(const BasicShape& shape) {
    create(
        shape.getIndices(),
        shape.getVertices()
    );
}

void Mesh::render() const {
    // TODO: render is done with active shaders and textures
   
    // for some bug in Graphic Cards, we need it
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIBO);

    // with mIBO, not DrawArrays, but DrawElements 
    glDrawElements(GL_TRIANGLES, mIndexCount, GL_UNSIGNED_INT, 0);
}

void Mesh::clear() {
    // make sure the buffers are deleted from the graphic card
    // when mesh is deleted
    if (mIBO != 0) {
        glDeleteBuffers(1, &mIBO);
    }
    if (mVBO != 0) {
        glDeleteBuffers(1, &mVBO);
    }
    if (mVAO != 0) {
        glDeleteVertexArrays(1, &mVAO);
    }
}

Mesh::~Mesh() {
    this->clear();
}
