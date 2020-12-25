#pragma once
#include <iostream>

#include <GL/glew.h>

#include "stb_image.h"

class Texture {
public:
	Texture(const char* fileLoc);
	void load();
	void use();
	void clear();

private:
	GLuint textureID;
	int mWidth, mHeight, mBitDepth;
	// string litteral is const char*
	const char* mFileLocation;
};
