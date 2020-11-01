#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include <vector>
#include <GL/glew.h>

class Mesh {
public:
	Mesh();
	~Mesh();
	void create(const GLfloat* vertices, unsigned int verticesSize, const unsigned int* indices, unsigned int indicesSize);
	void create(const std::vector<unsigned int>& indices, const std::vector<GLfloat>& vertices);
	void render() const;
	void clear();
private:
	GLuint mVAO;
	GLuint mVBO;
	GLuint mIBO;
	unsigned int mIndexCount;
};



