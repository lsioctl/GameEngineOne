#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <GL/glew.h>
#include "Model.h"
#pragma once
#include <memory>
#include "BasicShape.h"

class Mesh {
public:
	Mesh();
	~Mesh();
	void create(const GLfloat* vertices, unsigned int verticesSize, const unsigned int* indices, unsigned int indicesSize);
	void create(const std::vector<unsigned int>& indices, const std::vector<GLfloat>& vertices);
	void create(const std::unique_ptr<BasicShape>& shapePtr);
	void render() const;
	void clear();
private:
	GLuint mVAO;
	GLuint mVBO;
	GLuint mIBO;
	unsigned int mIndexCount;
};



