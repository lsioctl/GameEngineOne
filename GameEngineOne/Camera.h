#pragma once
#include <iostream>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>


using namespace std;

class Camera
{
public:
	Camera(glm::vec3 position, glm::vec3 worldUp, GLfloat yaw, GLfloat pitch, GLfloat movespeed, GLfloat turnspeed);
	void keyControl(bool* keys, GLdouble deltaTime);
	void mouseControl(GLfloat xChange, GLfloat yChange);
	glm::vec3 getPosition() const;
	glm::mat4 getViewTransform() const;
	// TODO: init, update, and enun for ortho, perspective
	void setProjectionTransform(glm::mat4 perspective);
	glm::mat4 getProjectionTransform() const;
private:
	glm::vec3 mPosition;
	glm::vec3 mFront;
	glm::vec3 mUp;
	glm::vec3 mRight;
	glm::vec3 mWorldUp;
	glm::mat4 mProjectionTransform;

	GLfloat mYaw;
	GLfloat mPitch;

	GLfloat mMoveSpeed;
	GLfloat mTurnSpeed;

	void update();
};


