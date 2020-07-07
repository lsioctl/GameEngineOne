#pragma once

#include <iostream>
#include <fstream>
#include <GL/glew.h>
#include <string>

class Shader
{
public:
	Shader();
	~Shader();
	bool create(const char* vertexFile, const char* fragmentFile);
	void setActive();
	void clear();

	// TODO: not applicable to all shader, refactor
	GLuint getModelLocation();
	GLuint getViewLocation();
	GLuint getProjectionLocation();
	GLuint getUniformAmbientIntensityLocation();
	GLuint getUniformAmbientColorLocation();
	GLuint getUniformDiffuseIntensityLocation();
	GLuint getUniformLightPositionLocation();
	GLuint getUniformCameraPositionLocation();

private:
	GLuint mShaderId;
	GLuint mVertexShader;
	GLuint mFragmentShader;

	// TODO: not applicable to all shader, refactor
	GLuint mUniformModel;
	GLuint mUniformView;
	GLuint mUniformProjection;
	GLuint mUniformAmbientIntensity;
	GLuint mUniformAmbientColor;
	GLuint mUniformDiffuseIntensity;
	GLuint mUniformLightPosition;
	GLuint mUniformCameraPosition;

	std::string readFile(const char* fileName);
	bool compile(const char* shaderFile, GLenum shaderType, GLuint& outShader);
	bool isCompiled(GLuint shaderId, GLenum shaderType);
	bool isLinkedProgram();
	bool isValidProgram();
	// TODO: not applicable to all shader, refactor
	void setUniforms();

};