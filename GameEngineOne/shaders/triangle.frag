#version 330

in vec4 vCol;
in vec2 texCoord0;
in vec3 normal;
in vec3 vertWorldPos;

out vec4 color;

struct DirectionalLight {
    vec3 color;
    float ambientIntensity;
    // we don't need position, source is like an infinity away
    vec3 position;
    float diffuseIntensity;
};

// we won't have to setup anything for
// this uniform because the default is 0
// if not change glActiveTexture
uniform sampler2D theTexture;

uniform DirectionalLight directionalLight;

uniform vec3 cameraPosition;

void main() {

    vec3 ambientLight = directionalLight.color * directionalLight.ambientIntensity;

    // variable between 0 and 1
    // dot produc of unit vectors (normalize function)
    // cosinus of the angle the 2 vectors
    // folowwing the formula A . B = |a| * |b| * cosinus(angle)
    // note: here the angle is calculated with l which is a vector from the surface
    // to the light
    // if the angle is above 0, the surface does not face the light, so 0
    // Surface normal
    vec3 N = normalize(normal);
    // Vector from surface to Light
    vec3 L = normalize(directionalLight.position - vertWorldPos);
    // Vector from the surface to Camera
    vec3 V = normalize(cameraPosition - vertWorldPos);
    // Reflection of -L, with normal N
    vec3 R = normalize(reflect(-L, N));

    // compute Phong reflection
    vec3 Phong = ambientLight;
    float NdotL = dot(N, L);

    if (NdotL > 0) {
        vec3 Diffuse = directionalLight.color * directionalLight.diffuseIntensity * NdotL;

        float RdotV = dot(R, V);
    
        int specPower = 128;

        vec3 Specular = directionalLight.color * pow(max(0.0, RdotV), specPower);
        //vec3 Specular = directionalLight.color * pow(RdotV, specPower);
    
        //Phong += Diffuse + Specular;
        //Phong += Specular;
        Phong += Diffuse;
    }
    
    // Final color is texture color times phone light (alpha = 1);
    //color = texture(theTexture, texCoord0) * vec4(Phong, 1.0f);
    //color = texture(theTexture, texCoord0)
    color = texture(theTexture, texCoord0) * vec4(Phong, 1.0f);
    //color = vCol;
    
};