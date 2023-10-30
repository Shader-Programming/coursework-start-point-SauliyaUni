# version 330 core

out vec4 FragColor;
in vec3 normal;

vec3 cubeColour = vec3(0.1, 0.2, 0.3);

vec3 lightColour = vec3(1.0f);
vec3 lightDirection = vec3(0.0f, -1.0f, 0.0f);

float ambientFactor = 0.5;

void main() {
    //diffuse
    vec3 ambient = cubeColour * lightColour * ambientFactor;
    //diffuse
    vec3 n = normalize(normal);
    float diffuseFactor = dot(n, -lightDirection);
    diffuseFactor = max(diffuseFactor, 0.0f);
    vec3 diffuse = cubeColour * lightColour * diffuseFactor;


    vec3 result = ambient + diffuse;

    FragColor = vec4(result, 1.0);

}