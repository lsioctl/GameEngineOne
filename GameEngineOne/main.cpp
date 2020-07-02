#include "GameWindow.h"
#include <memory>

GLdouble deltaTime{ 0.0 };
GLdouble lastTime{ 0.0 };

int main() {
	auto mainWindow = make_unique<GameWindow>(800, 600);

	mainWindow->create();

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