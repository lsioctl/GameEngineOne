#version 330                                     

layout(location = 0) in vec3 pos;
layout(location = 1) in vec2 tex;
layout(location = 2) in vec3 norm;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec4 vCol;
out vec2 texCoord0;
out vec3 normal;
out vec3 vertWorldPos;

void main() {
    //gl_Position = projection * view * model * vec4(pos, 1.0);
    //gl_Position = projection * model * vec4(pos, 1.0);
    // save the worlPosition
    vertWorldPos = vec3(model * vec4(pos, 1.0));

    // calculate position in the clipping space
    gl_Position = projection * view * model * vec4(pos, 1.0);
    vCol = vec4(clamp(pos, 0.0f, 1.0f), 1.0f);

    texCoord0 = tex;

    // normal in relation with where the model is
    // influenced by the rotation
    // but not influenced by the transform of the model
    // if we stretch the object (Scale in one direction)
    // interpolated normals will change and we don't want
    // this
    // transform is handle on the forth column (last and bottom)
    // we also need to invert the scale process
    normal = mat3(transpose(inverse(model))) * norm;
    //normal = norm;
}
   