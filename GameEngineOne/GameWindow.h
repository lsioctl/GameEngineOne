#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h> 
#include <iostream>

using namespace std;

class GameWindow
{
public:
	GameWindow(GLint width, GLint height);
	int create();
	void pollEvents();
	int getBufferWidth();
	int getBufferHeight();
	bool shouldClose();
	void swapBuffer();

	// we could request the key, and see if up and down, it would be more object oriented
	// with getter and setters
	// so not proper design patterm
	// so just pass back array of keys
	bool* getKeys();

	GLfloat getXChange();
	GLfloat getYChange();

	void clear();

	~GameWindow();
private:
	GLint mWidth;
	GLint mHeight;
	int mBufferWidth;
	int mBufferHeight;
	GLFWwindow* mWindow;
	// cover all ascii code
	bool mKeys[1024];
	GLfloat mLastX;
	GLfloat mLastY;
	GLfloat mChangeX;
	GLfloat mChangeY;
	bool mMouseFirstMoved;

	// GLFW needs callback, and we cannot call
	// an instance member, so we make it static
	static void handleKeys(GLFWwindow* window, int key, int code, int action, int mode);
	static void handleMouse(GLFWwindow* window, double xPos, double yPos);

	void createCallbacks();


};


