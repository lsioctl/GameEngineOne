#pragma once
#include <memory>
#include <GL/glew.h>

class Model {
public:
	GLfloat* getVertices();
	unsigned int* getIndices();
	unsigned int getVerticesSize();
	unsigned int getIndicesSize();
protected:
	Model();
	GLfloat* mVertices;
	unsigned int* mIndices;
	unsigned int mVerticesSize;
	unsigned int mIndicesSize;
};
