#pragma once

#include <iostream>
#include <fstream>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>

class Shader
{
public:
	Shader();
	~Shader();
	bool create(const char* vertexFile, const char* fragmentFile);
	void setActive();
	void setMatrixUniform(const char* name, const glm::mat4& matrix);
	void clear();

private:
	GLuint mShaderId;
	GLuint mVertexShader;
	GLuint mFragmentShader;

	std::string readFile(const char* fileName);
	bool compile(const char* shaderFile, GLenum shaderType, GLuint& outShader);
	bool isCompiled(GLuint shaderId, GLenum shaderType);
	bool isLinkedProgram();
	bool isValidProgram();
	// TODO: not applicable to all shader, refactor
	void setUniforms();

};