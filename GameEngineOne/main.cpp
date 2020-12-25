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
// instead of soil we use stb_image.h
// from github nothings/stb
#define STB_IMAGE_IMPLEMENTATION
#include "Texture.h"


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

	auto simpleWhiteShader = make_unique<Shader>();
	simpleWhiteShader->create("shaders/simpleWhite.vert", "shaders/simpleWhite.frag");

	auto simpleTextureShader = make_unique<Shader>();
	simpleTextureShader->create("shaders/simpleTexture.vert", "shaders/simpleTexture.frag");


	// this uses almost 30 MB of main memory
	// see: 
	// http://community.foundry.com/discuss/topic/56755/how-much-memory-does-a-texture-really-take?mode=Post&postID=510096
	auto brickTexture = make_unique<Texture>("./textures/brick.png");
	brickTexture->load();

	// and this one only 3 MB ...
	auto dirtTexture = make_unique<Texture>("./textures/dirt.png");
	dirtTexture->load();

	auto pyramidObject = make_unique<GameObject>();
	auto pyramidObject2 = make_unique<GameObject>();
	auto pyramidObject3 = make_unique<GameObject>();
	auto cubeObject = make_unique<GameObject>();
	auto cubeObject2 = make_unique<GameObject>();
	
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
		pyramidObject3->setTranslation(-3.0f, 3.0f, -3.0f);
		pyramidObject3->setScale(0.3f, 0.3f, 0.3f);
		cubeObject->setTranslation(0.0f, 3.0f, -3.0f);
		cubeObject2->setTranslation(3.0f, 3.0f, -3.0f);
		cubeObject2->setScale(0.3f, 0.3f, 0.3f);

		// every following render will use this shader program
		simpleShader->setActive();

		pyramidObject->render(*pyramidMesh, *simpleShader, camera);
		cubeObject->render(*cubeMesh, *simpleShader, camera);

		simpleWhiteShader->setActive();
		cubeObject2->render(*cubeMesh, *simpleWhiteShader, camera);

		brickTexture->use();
		simpleTextureShader->setActive();
		pyramidObject2->render(*pyramidMesh, *simpleTextureShader, camera);

		dirtTexture->use();
		pyramidObject3->render(*pyramidMesh, *simpleTextureShader, camera);

		// back buffer is drawn
		// Swap front and back buffers
		mainWindow.swapBuffer();
	}

	return 0;
}