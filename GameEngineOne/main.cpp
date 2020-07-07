#include "GameWindow.h"
#include <memory>
#include "Pyramid.h"
#include <iostream>

using namespace std;

GLdouble deltaTime{ 0.0 };
GLdouble lastTime{ 0.0 };

int main() {
	auto mainWindow = make_unique<GameWindow>(800, 600);
	mainWindow->create();

	Pyramid pyramidModel = Pyramid();

	cout << pyramidModel.getVerticesSize() << endl;
	cout << pyramidModel.getIndicesSize() << endl;

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
		
		// back buffer is drawn
		// Swap front and back buffers
		mainWindow->swapBuffer();
	}

	return 0;
}