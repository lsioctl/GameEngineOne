#include "GameObject.h"

GameObject::GameObject() :
	mTranslation{glm::vec3(0.0f)},
	mRotationRadians{ 0 },
	// we need an axis with angle 0 for 'identity' rotation
	mRotationAxis{ glm::vec3(0.0f, 0.0f, 1.0f) },
	// we need a scale of 1 for 'identity' scale
	mScale{ glm::vec3(1.0f) },
	mWorldTransform{ glm::mat4(1.0f) }
{};

void GameObject::setTranslation(float x, float y, float z) {
	mTranslation = glm::vec3(x, y, z);
}

void GameObject::setRotation(float radians, float x, float y, float z) {
	mRotationRadians = radians;
	mRotationAxis = glm::vec3(x, y, z);
}

void GameObject::setScale(float x, float y, float z) {
	mScale = glm::vec3(x, y, z);
}

void GameObject::setWorldTransform() {
	// Calculate the world transform
	// first we want identity matrix
	mWorldTransform = glm::mat4(1.0f);

	// firs translate
	mWorldTransform = glm::translate(mWorldTransform, mTranslation);
	// then rotate
	mWorldTransform = glm::rotate(mWorldTransform, mRotationRadians, mRotationAxis);
	// then scale
	mWorldTransform = glm::scale(mWorldTransform, mScale);

}

void GameObject::render(Mesh* mesh, Shader* activeShader) {
	setWorldTransform();
	// set world transform in the shader
	activeShader->setMatrixUniform("uWorldTransform", mWorldTransform);
	mesh->render();
}
