#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include <GL/glew.h>

class Mesh {
public:
	Mesh();
	~Mesh();
	void create(const GLfloat* vertices, unsigned int verticesSize, const unsigned int* indices, unsigned int indicesSize);
	void create(const std::vector<unsigned int>& indices, const std::vector<GLfloat>& vertices);
	// const for the object, not in sense of purity, at is has a lot of side effects
	void render() const;
	void clear();
private:
	GLuint mVAO;
	GLuint mVBO;
	GLuint mIBO;
	unsigned int mIndexCount;
};



