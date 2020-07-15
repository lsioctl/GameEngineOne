#include <iostream>
#include <memory>
#include "GameWindow.h"
#include "Pyramid.h"
#include "Mesh.h"
#include "Shader.h";
#include "GameObject.h";


using namespace std;

GLdouble deltaTime{ 0.0 };
GLdouble lastTime{ 0.0 };


int main() {
	// All objects are created in the heap to avoid memory limits of the stack
	// as a game could have many objects
	// TODO: is it appropriate ?
	// TODO: as I use unique_ptr, does passing by pointer is OK ?
	auto mainWindow = make_unique<GameWindow>(800, 600);
	mainWindow->create();

	auto pyramidModel = make_unique<Pyramid>();

	// TODO: find another constructor or pattern
	auto pyramidMesh = make_unique<Mesh>();
	pyramidMesh->createFromModel(pyramidModel.get());

	auto simpleShader = make_unique<Shader>();
	simpleShader->create("shaders/simple.vert", "shaders/simple.frag");

	auto pyramidObject = make_unique<GameObject>();
	
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

		pyramidObject->setScale(0.3f, 0.3f, 0.3f);

		// every following render will use this shader program
		simpleShader->setActive();

		// not sure of the pattern to apply here with smart pointers
		pyramidObject->render(pyramidMesh.get(), simpleShader.get());
				
		// back buffer is drawn
		// Swap front and back buffers
		mainWindow->swapBuffer();
	}

	return 0;
}