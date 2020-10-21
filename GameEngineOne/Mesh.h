#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <GL/glew.h>
#include "Model.h"
#include "Model2.h"
#include <memory>

class Mesh {
public:
	Mesh();
	~Mesh();
	void create(GLfloat* vertices, unsigned int verticesSize, unsigned int* indices, unsigned int indicesSize);
	void create(const std::vector<unsigned int>& indices, const std::vector<GLfloat>& vertices);
	void createFromHeaders(const std::unique_ptr<Model2>& model);
	void create2(std::vector<GLfloat> vertices, unsigned int verticesSize, std::vector<unsigned int> indices, unsigned int indicesSize);
	void render() const;
	void clear();
private:
	GLuint mVAO;
	GLuint mVBO;
	GLuint mIBO;
	unsigned int mIndexCount;
};



