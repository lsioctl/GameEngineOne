#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <GL/glew.h>
#include "Model.h"

class Mesh {
public:
	Mesh();
	~Mesh();
	void create(GLfloat* vertices, unsigned int verticesSize, unsigned int* indices, unsigned int indicesSize);
	void createFromModel(Model* model);
	void render() const;
	void clear();
private:
	GLuint mVAO;
	GLuint mVBO;
	GLuint mIBO;
	unsigned int mIndexCount;
};



