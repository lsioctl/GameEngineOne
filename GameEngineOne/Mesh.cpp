#include "Mesh.h"

using namespace std;

Mesh::Mesh() : mVAO{ 0 }, mVBO{ 0 }, mIBO{ 0 }, mIndexCount{ 0 } {
}

// when array decay to pointer, sizeof(pointer) gives the size of the pointer, we lost sizeof(array)
void Mesh::create(const GLfloat* vertices, unsigned int verticesSize, const unsigned int* indices, unsigned int indicesSize) {

    // keep track of number of indexes, it will be needed for render()
    mIndexCount = indicesSize;

    // create a vertex array and store its id
    glGenVertexArrays(1, &mVAO);
    // note: this change the vertex array for everyone
    glBindVertexArray(mVAO);

    // create a vertex buffer
    glGenBuffers(1, &mVBO);
    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    // copy the vertices data to the vertex buffer
    glBufferData(GL_ARRAY_BUFFER, verticesSize * sizeof(vertices[0]), vertices, GL_STATIC_DRAW);

    // create an index buffer
    glGenBuffers(1, &mIBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIBO);
    // copy the indices data to the index buffer
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize * sizeof(indices[0]), indices, GL_STATIC_DRAW);

    // Vertex layout (also name vertex attributes)
    // Vertices
    glVertexAttribPointer(
        0,                          // Attribute index
        3,                          // Number of components
        GL_FLOAT,                   // type of the component
        GL_FALSE,                   // Only used for integral types
        sizeof(vertices[0]) * 8,    // Strides
        0                           // Offset from start of vertex to this attribute
    );
    // u, v coordinate (textures)
    glVertexAttribPointer(
        1,
        2,
        GL_FLOAT,
        GL_FALSE,
        sizeof(vertices[0]) * 8,
        (void*)(sizeof(vertices[0]) * 3)
    );
    // normals
    glVertexAttribPointer(
        2,
        3,
        GL_FLOAT,
        GL_FALSE,
        sizeof(vertices[0]) * 8,
        (void*)(sizeof(vertices[0]) * 5)
    );

    // enable vertices, texture and normals on VAO
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

void Mesh::render() const {
    // reactivate the vertex array (as it is called by each
    // other vertex array creation)
    glBindVertexArray(mVAO);
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
