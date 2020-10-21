#pragma once
#include <vector>
#include <GL/glew.h>

// still not at the top of my C++ foo
// this is, for me a 'non polymorphic base class'
// it is there to store vectors declared in headers
// like pyramid.h
class Model2 {
public:
	virtual const std::vector<GLfloat>& getVertices() const;
	virtual const std::vector<unsigned int>& getIndices() const;
protected:
	Model2();
	static const std::vector<GLfloat> mVertices;
	static const std::vector<unsigned int> mIndices;
};


