#version 330

in vec4 vertexColor;

out vec4 outColor;

void main() {

    // let the fragment shader interpolate vertex colors
    //outColor = vertexColor;
    outColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
    
}