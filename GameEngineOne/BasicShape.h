#pragma once
#include <vector>
#include <GL/glew.h>

// still not at the top of my C++ foo
// this is, for me a 'non polymorphic base class'
// it is there to store vectors declared in headers
// like pyramid.h
// the absence of virtual method is wanted
class BasicShape {
public:
	const std::vector<GLfloat>& getVertices() const;
	const std::vector<unsigned int>& getIndices() const;
protected:
	BasicShape();
	const std::vector<GLfloat> mVertices;
	const std::vector<unsigned int> mIndices;
};


