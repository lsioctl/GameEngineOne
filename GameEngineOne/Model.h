#pragma once
#include <memory>
#include <GL/glew.h>

class Model {
public:
	GLfloat* getVertices() const;
	unsigned int* getIndices() const;
	unsigned int getVerticesSize() const;
	unsigned int getIndicesSize() const;
protected:
	Model();
	GLfloat* mVertices;
	unsigned int* mIndices;
	unsigned int mVerticesSize;
	unsigned int mIndicesSize;
};
