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
	void create(GLfloat* vertices, unsigned int verticesSize, unsigned int* indices, unsigned int indicesSize);
	void create(const std::vector<unsigned int>& indices, const std::vector<GLfloat>& vertices);
	void createFromShape(const std::unique_ptr<BasicShape>& shapePtr);
	void create2(std::vector<GLfloat> vertices, unsigned int verticesSize, std::vector<unsigned int> indices, unsigned int indicesSize);
	void render() const;
	void clear();
private:
	GLuint mVAO;
	GLuint mVBO;
	GLuint mIBO;
	unsigned int mIndexCount;
};



