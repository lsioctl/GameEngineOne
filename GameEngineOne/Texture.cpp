#include "Texture.h"

Texture::Texture(const char* fileLoc) :
	textureID{ 0 },
	mWidth{ 0 },
	mHeight{ 0 },
	mBitDepth{ 0 },
	mFileLocation{ fileLoc } {}

void Texture::load() {
	// unsigned char same as a byte
	unsigned char* texData = stbi_load(mFileLocation, &mWidth, &mHeight, &mBitDepth, 0);

	if (!texData) {
		std::cout << "Failed to load " << mFileLocation << std::endl;
	}

	glGenTextures(1, &textureID);
	// for clouds, other GL_TEXTURE_ are available
	glBindTexture(GL_TEXTURE_2D, textureID);

	// S along x axis, if we get over the border, repeat
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	// T along y axis
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// when we zoom in
	// linear when we zoom in, try to blend
	// nearest looks more pixelated
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	// when we zoom out (magnify)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(
		GL_TEXTURE_2D,
		0, // mipmap, to change image if we are close or far. we will use a function
		GL_RGBA, // format of the image
		mWidth,
		mHeight,
		0, // legacy
		GL_RGBA,
		GL_UNSIGNED_BYTE, //same as unsigned char, 1 byte
		texData
	);

	// we generate mipmap automatically with this function
	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);

	// free memory used by image load
	stbi_image_free(texData);
}

void Texture::use() {
	// Texture unit
	// some graphic card have 32 texture units
	// here only one, if not we need one uniform for each in GLSL
	glActiveTexture(GL_TEXTURE0);
	// could use also mesh, blend textures, mix, ...
	glBindTexture(GL_TEXTURE_2D, textureID);

}

void Texture::clear() {
	glDeleteTextures(1, &textureID);
	textureID = 0;
	mWidth = 0;
	mHeight = 0;
	mBitDepth = 0;
	delete mFileLocation;
}

