#include "Shader.h"

using namespace std;

Shader::Shader() :
    mShaderId{ 0 },
    mVertexShader{ 0 },
    mFragmentShader{ 0 },
    mUniformProjection{ 0 },
    mUniformModel{ 0 },
    mUniformView{ 0 },
    mUniformAmbientIntensity{ 0 },
    mUniformAmbientColor{ 0 },
    mUniformDiffuseIntensity{ 0 },
    mUniformLightPosition{ 0 },
    mUniformCameraPosition{ 0 }
{};

string Shader::readFile(const char* fileName) {
    string content;
    // TODO: learn this syntax
    ifstream fileStream(fileName, ios::in);

    if (!fileStream.is_open()) {
        cout << "Failed to read " << fileName << endl;
        return "";
    }

    string line = "";
    while (!fileStream.eof()) {
        getline(fileStream, line);
        // GLSL not sensitive to whitespace, but it could help us to read/debug
        content.append(line + "\n");
    }

    fileStream.close();

    return content;
}

bool Shader::isCompiled(GLuint shaderId, GLenum shaderType) {
    GLint status;
    // Query the compile status
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &status);

    if (status != GL_TRUE) {
        char errorLog[1024];
        memset(errorLog, 0, 1024);
        glGetShaderInfoLog(shaderId, 1023, nullptr, errorLog);
        cout << "Error Compiling the " << shaderType << " shader: " << errorLog << endl;
        return false;
    }

    return true;
}

bool Shader::isLinkedProgram() {
    GLint status;
    // Query the Link status
    glGetShaderiv(mShaderId, GL_LINK_STATUS, &status);

    if (status != GL_TRUE) {
        char errorLog[1024];
        memset(errorLog, 0, 1024);
        glGetProgramInfoLog(mShaderId, 1023, nullptr, errorLog);
        cout << "Error Linking programm: " << errorLog << endl;
        return false;
    }

    return true;
}

bool Shader::isValidProgram() {
    GLint status;
    // Query the validate status
    glGetShaderiv(mShaderId, GL_VALIDATE_STATUS, &status);

    if (status != GL_TRUE) {
        char errorLog[1024];
        memset(errorLog, 0, 1024);
        glGetProgramInfoLog(mShaderId, 1023, nullptr, errorLog);
        cout << "Error Validating programm: " << errorLog << endl;
        return false;
    }

    return true;
}

void Shader::setUniforms() {
    // get the id of the references we want to change
    // TODO: not applicable to all shaders, so refactor it
    mUniformModel = glGetUniformLocation(mShaderId, "model");
    mUniformView = glGetUniformLocation(mShaderId, "view");
    mUniformProjection = glGetUniformLocation(mShaderId, "projection");
    mUniformAmbientIntensity = glGetUniformLocation(mShaderId, "directionalLight.ambientIntensity");
    mUniformAmbientColor = glGetUniformLocation(mShaderId, "directionalLight.color");
    mUniformDiffuseIntensity = glGetUniformLocation(mShaderId, "directionalLight.diffuseIntensity");
    mUniformLightPosition = glGetUniformLocation(mShaderId, "directionalLight.position");
    mUniformCameraPosition = glGetUniformLocation(mShaderId, "cameraPosition");
}

bool Shader::compile(const char* shaderFile, GLenum shaderType, GLuint& outShader) {

    string shaderString = readFile(shaderFile);
    const char* shaderCode = shaderString.c_str();

    // create a shader of the specified type
    outShader = glCreateShader(shaderType);

    // this:
    const GLchar* theCode[] = { shaderCode };
    GLint codeLength[] = { strlen(shaderCode) };
    // may be replaced by something like this:
    //glShaderSource(outShader, 1, &(shaderCode), nullptr);
    glShaderSource(outShader, 1, theCode, codeLength);
    glCompileShader(outShader);

    if (!isCompiled(outShader, shaderType)) {
        cout << "Failed to compile " << shaderType << " shader: " << shaderFile << endl;
        return false;
    }

    return true;
}

bool Shader::create(const char* vertexFile, const char* fragmentFile) {
    // Compile vertex and fragment shaders
    if (
        !compile(vertexFile, GL_VERTEX_SHADER, mVertexShader) ||
        !compile(fragmentFile, GL_FRAGMENT_SHADER, mFragmentShader)
    ) {
        return false;
    }

    // Create a shader program that links together 
    // vertex and fragment shaders

    mShaderId = glCreateProgram();
    glAttachShader(mShaderId, mVertexShader);
    glAttachShader(mShaderId, mFragmentShader);
    glLinkProgram(mShaderId);

    // Check if the programm is linked and validated successfully
    if (!isLinkedProgram() || !isValidProgram()) {
        return false;
    }

    return true;
}


// TODO: some public functions needs other functions being called before
// for instances properties to have meaningfull values
// there should be a better design pattern (Builder, Factory, ...) somewhere
// and I don't want to put to much code in the constructor
void Shader::setActive() {
    glUseProgram(mShaderId);
}

// TODO: not applicable for all shaders, refactor
GLuint Shader::getModelLocation() {
    return mUniformModel;
}

GLuint Shader::getViewLocation() {
    return mUniformView;
}

GLuint Shader::getProjectionLocation() {
    return mUniformProjection;
}

GLuint Shader::getUniformAmbientColorLocation() {
    return mUniformAmbientColor;
}

GLuint Shader::getUniformAmbientIntensityLocation() {
    return mUniformAmbientIntensity;
}

GLuint Shader::getUniformDiffuseIntensityLocation() {
    return mUniformDiffuseIntensity;
}

GLuint Shader::getUniformLightPositionLocation() {
    return mUniformLightPosition;
}

GLuint Shader::getUniformCameraPositionLocation() {
    return mUniformCameraPosition;
}

void Shader::clear() {
    // tell the Graphic Card to release the shaders
    if (mShaderId != 0) {
        glDeleteProgram(mShaderId);
    }
    if (mVertexShader != 0) {
        glDeleteShader(mVertexShader);
    }
    if (mFragmentShader != 0) {
        glDeleteShader(mFragmentShader);
    }
}

Shader::~Shader() {
    clear();
}
