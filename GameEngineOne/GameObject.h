#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Model.h"
#include "Shader.h"
#include "Mesh.h"
#include "Camera.h"
#include <memory>


class GameObject {
public:
	GameObject();
	void setTranslation(float x, float y, float z);
	void setRotation(float radians, float x, float y, float z);
	void setScale(float x, float y, float z);
	void render(const std::unique_ptr<Mesh>& mesh, const std::unique_ptr<Shader>& activeShader, const Camera& camera);
private:
	glm::vec3 mTranslation;
	float mRotationRadians;
	glm::vec3 mRotationAxis;
	glm::vec3 mScale;
	glm::mat4 mWorldTransform;
	void setWorldTransform();
};

