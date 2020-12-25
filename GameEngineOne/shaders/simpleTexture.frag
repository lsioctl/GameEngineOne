#version 330

in vec2 fragTexCoord;

out vec4 outColor;

// For texture sampling (see glActiveTexture)
// we won't have to setup anything for
// this uniform because the default is 0
uniform sampler2D uTexture;

void main() {

    // sample color from texture
    outColor = texture(uTexture, fragTexCoord);
}