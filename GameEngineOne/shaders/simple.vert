#version 330                                     

layout(location = 0) in vec3 inPosition;

uniform mat4 uWorldTransform;

out vec4 vertexColor;

void main() {

    // convert the position to homogeneous coordinates
    vec4 pos = vec4(inPosition, 1.0f);

    // calculate position in the clipping space
    //gl_Position = uWorldTransform * pos;
    gl_Position = pos;

    // make the vertex color depending on the model's vertex position
    // last parameter is alpha (transparency)
    vertexColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
    //vertexColor = vec4(clamp(inPosition, 0.0f, 1.0f), 1.0f);
}