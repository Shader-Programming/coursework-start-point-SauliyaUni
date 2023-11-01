# version 330 core
uniform vec3 viewPos;
uniform vec3 cubeColour;
uniform vec3 lightColour;
uniform vec3 lightDirection;

uniform float ambientFactor;
uniform float shine;
uniform float specStrength;
float specLevel;

out vec4 FragColor;

in vec3 normal;
in vec3 posInWS;

vec3 n = normalize(normal);
vec3 viewDir = normalize(viewPos - posInWS);

vec3 getDirectionalLight() {
    //ambient
    vec3 ambient = cubeColour * lightColour * ambientFactor;
    //diffuse
    
    float diffuseFactor = dot(n, -lightDirection);
    diffuseFactor = max(diffuseFactor, 0.0f);
    vec3 diffuse = cubeColour * lightColour * diffuseFactor;
    //Blinn Phong Specular
    
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