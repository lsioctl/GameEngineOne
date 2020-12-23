#pragma once
// instead of soil we use stb_image.h
// from github nothings/stb
#define STB_IMAGE_IMPLEMENTATION

#include <iostream>

#include <GL/glew.h>

#include "stb_image.h"


class Texture
{
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
