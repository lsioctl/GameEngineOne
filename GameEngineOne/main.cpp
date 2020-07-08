#include <iostream>
#include <memory>
#include <glm/gtc/matrix_transform.hpp>
#include "GameWindow.h"
#include "Pyramid.h"
#include "Mesh.h"
#include "Shader.h";


using namespace std;

GLdouble deltaTime{ 0.0 };
GLdouble lastTime{ 0.0 };

int main() {
	auto mainWindow = make_unique<GameWindow>(800, 600);
	mainWindow->create();

	Pyramid pyramidModel = Pyramid();

	// TODO: find another constructor or pattern
	Mesh pyramidMesh = Mesh();
	pyramidMesh.create(
		pyramidModel.getVertices(),
		pyramidModel.getVerticesSize(),
		pyramidModel.getIndices(),
		pyramidModel.getIndicesSize()
	);

	Shader simpleShader = Shader();
	simpleShader.create("shaders/simple.vert", "shaders/simple.frag");

	// every following render will use this shader program
	simpleShader.setActive();
	
	// main loop
	while (!mainWindow->shouldClose()) {
		// deltaTime handling
		GLdouble now{ glfwGetTime() };
		deltaTime = now - lastTime;
		lastTime = now;

		// Get and handle user input events
		mainWindow->pollEvents();
		
		// Clear Window
		mainWindow->clear();

		// Calculate the world transform
		// first we want identity matrix
		glm::mat4 worldTransform = glm::mat4(1.0f);

		// firs translate
		//worldTransform = glm::translate(worldTransform, glm::vec3(1.0f, 0.0f, -3.0f));
		// then rotate
		//model = glm::rotate(model, curAngle * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		// then scale
		worldTransform = glm::scale(worldTransform, glm::vec3(0.4f, 0.4f, 0.4f));

		// set world transform in the shader
		simpleShader.setMatrixUniform("uWorldTransform", worldTransform);
		
		pyramidMesh.render();
		
		// back buffer is drawn
		// Swap front and back buffers
		mainWindow->swapBuffer();
	}

	return 0;
}