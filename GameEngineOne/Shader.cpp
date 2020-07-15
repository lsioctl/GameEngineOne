#include "Shader.h"
#include <glm/gtc/type_ptr.hpp>

using namespace std;

Shader::Shader() :
    mShaderId{ 0 },
    mVertexShader{ 0 },
    mFragmentShader{ 0 }
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
    glGetProgramiv(mShaderId, GL_LINK_STATUS, &status);

    if (status != GL_TRUE) {
        char errorLog[1024];
        memset(errorLog, 0, 1024);
        glGetProgramInfoLog(mShaderId, 1023, nullptr, errorLog);
        cout << "Error Linking program: " << errorLog << endl;
        return false;
    }

    return true;
}


bool Shader::isValidProgram() {
    GLint status;
    // Query the validate status
    glGetProgramiv(mShaderId, GL_VALIDATE_STATUS, &status);

    if (status != GL_TRUE) {
        char errorLog[1024];
        memset(errorLog, 0, 1024);
        glGetProgramInfoLog(mShaderId, 1023, nullptr, errorLog);
        cout << "Error Validating program: " << errorLog << endl;
        return false;
    }

    return true;
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
    glValidateProgram(mShaderId);

    // Check if the programm is linked and validated successfully
    if (!isLinkedProgram() || !isValidProgram()) {
        return false;
    }

    return true;
}


void Shader::setMatrixUniform(const char* name, const glm::mat4& matrix) {
    // Find the uniform by its name
    GLuint location = glGetUniformLocation(mShaderId, name);

    // Send the matrix data to the uniform
    glUniformMatrix4fv(
        location,                   // Uniform ID
        1,                          // Number of matrices
        GL_FALSE,                   // true for row vectors, false for column vectors
        glm::value_ptr(matrix)      // pointer to matrix data
    );
}


// TODO: some public functions needs other functions being called before
// for instances properties to have meaningfull values
// there should be a better design pattern (Builder, Factory, ...) somewhere
// and I don't want to put to much code in the constructor
void Shader::setActive() {
    glUseProgram(mShaderId);
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
