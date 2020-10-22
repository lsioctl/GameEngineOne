#include "GameWindow.h"

GameWindow::GameWindow(GLint width, GLint height) :
    mWidth{ width },
    mHeight{ height },
    mBufferWidth{ 0 },
    mBufferHeight{ 0 },
    mKeys{ false },
    mWindow{ nullptr },
    mLastX{ 0 },
    mLastY{ 0 },
    mChangeX{ 0.0f },
    mChangeY{ 0.0f },
    mMouseFirstMoved{ true }
{};

void GameWindow::createCallbacks() {
    glfwSetKeyCallback(mWindow, GameWindow::handleKeys);
    glfwSetCursorPosCallback(mWindow, GameWindow::handleMouse);
}

int GameWindow::create() {
    // Initialize GLFW
    if (!glfwInit()) {
        std::cout << "GLFW init failed" << std::endl;
        glfwTerminate();
        return 1;
    }

    // Setup GLFW Windows property
    // OpenGL Version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // Core profile, no backward compatibility
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // Allow forward compatbility
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);

    mWindow = glfwCreateWindow(mWidth, mHeight, "GLFW Window", NULL, NULL);
    /*this->width = width;
    this->height = height;*/

    if (!mWindow) {
        std::cout << "GLFW window creation failed" << std::endl;
        glfwTerminate();
        return 1;
    }

    // Get the framebuffer size information
    glfwGetFramebufferSize(mWindow, &mBufferWidth, &mBufferHeight);

    // Set context for GLEW to use
    // we could swich between mutliple windows with this function
    glfwMakeContextCurrent(mWindow);

    // Allow modern extensions
    // should not be used in the training
    glewExperimental = GL_TRUE;

    if (glewInit() != GLEW_OK) {
        std::cout << "Glew init failed" << std::endl;
        glfwDestroyWindow(this->mWindow);
        glfwTerminate();
        return 1;
    }

    // enable GL DEPTH BUFFER
    glEnable(GL_DEPTH_TEST);

    // set viewPort size
    glViewport(0, 0, mBufferWidth, mBufferHeight);

    // callback for keyboard input
    // this instance is user of this window
    glfwSetWindowUserPointer(mWindow, this);

    // Handle Key and Mouse input
    this->createCallbacks();

    // ensure the cursor is disabled when captured
    glfwSetInputMode(mWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    return 0;
}

void GameWindow::handleKeys(GLFWwindow* window, int key, int code, int action, int mode) {
    // get the GameWindow instance using the GLFW window
    GameWindow* theWindow = static_cast<GameWindow*>(glfwGetWindowUserPointer(window));

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }

    if (key > 0 && key < 1024) {
        if (action == GLFW_PRESS) {
            theWindow->mKeys[key] = true;
            //cout << "pressed " << key << endl;
        }
        else if (action == GLFW_RELEASE) {
            theWindow->mKeys[key] = false;
            //cout << "released " << key << endl;
        }
    }

}

bool* GameWindow::getKeys() {
    // we could request the key, and see if up and down, it would be more object oriented
    // with getter and setters
    // so not proper design patterm
    // so just pass back array of keys
    return mKeys;
}

void GameWindow::pollEvents() {
    glfwPollEvents();
}


void GameWindow::handleMouse(GLFWwindow* window, double xPos, double yPos) {
    // get the GameWindow instance using the GLFW window
    GameWindow* theWindow = static_cast<GameWindow*>(glfwGetWindowUserPointer(window));
    // GLFW callback function have incorrect type for what we need
    auto floatXPos = static_cast<GLfloat>(xPos);
    auto floatYPos = static_cast<GLfloat>(yPos);

    if (theWindow->mMouseFirstMoved) {
        theWindow->mLastX = floatXPos;
        theWindow->mLastY = floatYPos;
        theWindow->mMouseFirstMoved = false;
        return;
    }

    theWindow->mChangeX = floatXPos - theWindow->mLastX;
    // defend if want inverted control
    theWindow->mChangeY = theWindow->mLastY - floatYPos;

    theWindow->mLastX = floatXPos;
    theWindow->mLastY = floatYPos;

    //cout << "changeX " << theWindow->changeX << endl;
    //cout << "changeY " << theWindow->changeY << endl;


}

GLfloat GameWindow::getXChange() {
    // here it is an over simplfication
    // in game we would want to check if mouse has moved since lastframe
    // here we reset the change to 0 everytime we asked for it
    GLfloat theChange = mChangeX;
    mChangeX = 0;
    return theChange;
}

GLfloat GameWindow::getYChange() {
    // here it is an over simplfication
    // in game we would want to check if mouse has moved since lastframe
    // here we reset the change to 0 everytime we asked for it
    GLfloat theChange = mChangeY;
    mChangeY = 0;
    return theChange;
}


int GameWindow::getBufferWidth() {
    return mBufferWidth;
}

int GameWindow::getBufferHeight() {
    return mBufferHeight;
}

bool GameWindow::shouldClose() {
    return glfwWindowShouldClose(mWindow);
}

void GameWindow::swapBuffer() {
    glfwSwapBuffers(mWindow);
    // TODO: needed only on my new laptop
    // it's linked to vsync, not sure I have to call it for every frame
    // disable because GPU usage > 70% 
    //glfwSwapInterval(0);
}

void GameWindow::clear() {
    // alpha to 1 to be opaque
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    //glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    // bitwise operator to clear color and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

GameWindow::~GameWindow() {
    glfwDestroyWindow(mWindow);
    glfwTerminate();
}

