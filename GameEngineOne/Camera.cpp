#include "Camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 worldUp, GLfloat yaw, GLfloat pitch, GLfloat moveSpeed, GLfloat turnSpeed) :
	mPosition{ position },
	mWorldUp{ worldUp },
	mYaw{ yaw },
	mPitch{ pitch },
	mFront{ glm::vec3(0.0f, 0.0f, -1.0f) },
	mUp{ worldUp },
	mRight{ glm::vec3(1.0f, 0.0f, 0.0f) },
	mMoveSpeed{ moveSpeed },
	mTurnSpeed{ turnSpeed },
	mProjectionTransform{ glm::mat4(1.0f) } 
{
	update();
}

void Camera::update() {
	// something was weird in theory lesson
	// for me, at 0 pitch and 0 yaw, I should face along the z axis
	// so I inverted z and x on the formula
	// but in the course, he starts with a yaw of 90 degrees
	mFront.x = cos(glm::radians(mYaw)) * cos(glm::radians(mPitch));
	mFront.y = sin(glm::radians(mPitch));
	mFront.z = sin(glm::radians(mYaw)) * cos(glm::radians(mPitch));

	// need to normalize (1 unit magnitude)
	mFront = glm::normalize(mFront);

	// find the right with cross product
	//mRight = glm::normalize(glm::cross(mWorldUp, mFront));
	mRight = glm::normalize(glm::cross(mFront, mWorldUp));
	/*cout << "right is:" << endl;
	cout << right.x << endl;
	cout << right.y << endl;
	cout << right.z << endl;*/

	// find the actual up
	//mUp = glm::normalize(glm::cross(mFront, mRight));
	mUp = glm::normalize(glm::cross(mRight, mFront));
}

void Camera::keyControl(bool* keys, GLfloat deltaTime) {
	// need to handle deltat time because we could press
	// keys through a lot of a cycle

	GLfloat velocity = mMoveSpeed * deltaTime;

	if (keys[GLFW_KEY_W]) {
		mPosition += mFront * velocity;
	}

	if (keys[GLFW_KEY_S]) {
		mPosition -= mFront * velocity;
	}


	if (keys[GLFW_KEY_A]) {
		mPosition -= mRight * velocity;
	}

	if (keys[GLFW_KEY_D]) {
		mPosition += mRight * velocity;
	}
}


// xChange, yChange for the screen, not the world
void Camera::mouseControl(GLfloat xChange, GLfloat yChange) {
	xChange *= mTurnSpeed;
	yChange *= mTurnSpeed;

	mYaw += xChange;
	mPitch += yChange;

	// we avoid complexity like fligh simulation
	// so limit the pitch as in a FPS

	if (mPitch > 89.0f) {
		mPitch = 89.0f;
	}
	if (mPitch < -89.0f) {
		mPitch = -89.0f;
	}

	// we need to call update here, to update front, right, ...
	update();
}

glm::mat4 Camera::getViewTransform() const {
	// calculate a matrix which look at
	return glm::lookAt(
		mPosition, // position
		mPosition + mFront, // target
		mUp // up
	);
}

glm::vec3 Camera::getPosition() const {
	return mPosition;
}

void Camera::setProjectionTransform(glm::mat4 perspective) {
	mProjectionTransform = perspective;
}

glm::mat4 Camera::getProjectionTransform() const {
	return mProjectionTransform;
}

