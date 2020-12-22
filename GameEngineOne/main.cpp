#include <iostream>
#include <memory>
#include <vector>

#include <glm/gtc/matrix_transform.hpp>

#include "GameWindow.h"
#include "PyramidShape.h"
#include "CubeShape.h"
#include "Mesh.h"
#include "Shader.h"
#include "GameObject.h"
#include "Camera.h"

using namespace std;

GLdouble deltaTime{ 0.0 };
GLdouble lastTime{ 0.0 };


int main() {

	// all main objects uses intensively and everywhere
	// are created in the stack

	GameWindow mainWindow{ 800, 600 };
	mainWindow.create();

	// standard fov 45.0, y direction. Top to bottom
	// aspect ratio: widht/height of the window
	const auto aspectRatio{ static_cast<GLfloat>(mainWindow.getBufferWidth() / mainWindow.getBufferHeight()) };
	glm::mat4 projection{
		glm::perspective(
			45.0f, //fov y
			aspectRatio,
			0.1f, //near
			100.0f //far
		)
	};

	Camera camera{
		glm::vec3(0.0f, 0.0f, 3.0f), // position
		glm::vec3(0.0f, 1.0f, 0.0f), // worldUp
		-90.0f, // yaw
		0.0f, // pitch
		3.0f, // moveSpeed
		0.1f // turnSpeed
	};

	// standard fov 45.0, y direction. Top to bottom
	// aspect ratio: widht/height of the window
	camera.setProjectionTransform(glm::perspective(
		45.0f, //fov y
		((GLfloat)mainWindow.getBufferWidth() / (GLfloat)mainWindow.getBufferHeight()), //aspect ratio
		0.1f, //near
		100.0f //far
	));

	// All game objects are created in the heap to avoid memory limits of the stack
	// as:  objects could be heavy and a game could have many objects
	auto pyramidMesh = make_unique<Mesh>();
	pyramidMesh->create(shape::Pyramid::indices, shape::Pyramid::vertices);

	auto cubeMesh = make_unique<Mesh>();
	cubeMesh->create(shape::Cube::indices, shape::Cube::vertices);

	auto simpleShader = make_unique<Shader>();
	simpleShader->create("shaders/simple.vert", "shaders/simple.frag");

	// auto cubeShader = make_unique<Shader>();
	// cubeShader->create("shaders/simple.vert", "shaders/simple.frag");

	auto pyramidObject = make_unique<GameObject>();
	auto pyramidObject2 = make_unique<GameObject>();
	auto cubeObject = make_unique<GameObject>();
	
	// main loop
	while (!mainWindow.shouldClose()) {
		// deltaTime handling
		GLdouble now{ glfwGetTime() };
		deltaTime = now - lastTime;
		lastTime = now;

		// Get and handle user input events
		mainWindow.pollEvents();

		camera.keyControl(mainWindow.getKeys(), deltaTime);
		camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());

		// Clear Window
		mainWindow.clear();

		pyramidObject->setTranslation(0.0f, 0.0f, -3.0f);
		pyramidObject->setScale(0.3f, 0.3f, 0.3f);
		pyramidObject2->setTranslation(-3.0f, 0.0f, -3.0f);
		pyramidObject2->setScale(0.3f, 0.3f, 0.3f);
		cubeObject->setTranslation(0.0f, 3.0f, -3.0f);

		// every following render will use this shader program
		simpleShader->setActive();

		pyramidObject->render(*pyramidMesh, *simpleShader, camera);
		pyramidObject2->render(*pyramidMesh, *simpleShader, camera);
		cubeObject->render(*cubeMesh, *simpleShader, camera);

		// back buffer is drawn
		// Swap front and back buffers
		mainWindow.swapBuffer();
	}

	return 0;
}