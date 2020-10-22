#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include <GL/glew.h>
#include "BasicShape.h"

class Mesh {
public:
	Mesh();
	~Mesh();
	void create(const GLfloat* vertices, unsigned int verticesSize, const unsigned int* indices, unsigned int indicesSize);
	void create(const std::vector<unsigned int>& indices, const std::vector<GLfloat>& vertices);
	void create(const BasicShape& shape);
	void render() const;
	void clear();
private:
	GLuint mVAO;
	GLuint mVBO;
	GLuint mIBO;
	unsigned int mIndexCount;
};



