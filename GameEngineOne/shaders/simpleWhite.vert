#version 330                                     

layout(location = 0) in vec3 inPosition;

uniform mat4 uWorldTransform;
uniform mat4 uViewTransform;
uniform mat4 uProjectionTransform;

void main() {

    // convert the position to homogeneous coordinates
    vec4 pos = vec4(inPosition, 1.0f);

    // calculate position in the clipping space
    gl_Position = uProjectionTransform * uViewTransform * uWorldTransform * pos;
    //gl_Position = pos;
}