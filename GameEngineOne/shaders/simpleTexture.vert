#version 330                                     

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec2 inTexCoord;

uniform mat4 uWorldTransform;
uniform mat4 uViewTransform;
uniform mat4 uProjectionTransform;

out vec2 fragTexCoord;

void main() {

    // convert the position to homogeneous coordinates
    vec4 pos = vec4(inPosition, 1.0f);

    // calculate position in the clipping space
    gl_Position = uProjectionTransform * uViewTransform * uWorldTransform * pos;
    
    // make the vertex color depending on the model's vertex position
    // last parameter is alpha (transparency)
    fragTexCoord = inTexCoord;
}