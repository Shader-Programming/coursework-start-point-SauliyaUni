# version 330 core

out vec4 FragColor;
in vec3 normal;
in vec3 posInWS;
uniform vec3 viewPos;

vec3 cubeColour = vec3(0.1, 0.2, 0.3);

vec3 lightColour = vec3(1.0f);
vec3 lightDirection = vec3(0.0f, -1.0f, 0.0f);

float ambientFactor = 0.5;
float shine = 64;
float specStrength = 0.9;
float specLevel;

vec3 getDirectionalLight() {
    //ambient
    vec3 ambient = cubeColour * lightColour * ambientFactor;
    //diffuse
    vec3 n = normalize(normal);
    float diffuseFactor = dot(n, -lightDirection);
    diffuseFactor = max(diffuseFactor, 0.0f);
    vec3 diffuse = cubeColour * lightColour * diffuseFactor;
    //Blinn Phong Specular
    vec3 viewDir = normalize(viewPos - posInWS);
    vec3 H = normalize(-lightDirection + viewDir);
    specLevel = dot(n, H);
    specLevel = max(specLevel, 0.0);
    specLevel = pow(specLevel, shine);
    vec3 specular = lightColour * specLevel * specStrength;


    return  ambient + diffuse + specular;
}

void main() {
   
    vec3 result = getDirectionalLight();
    FragColor = vec4(result, 1.0);

}