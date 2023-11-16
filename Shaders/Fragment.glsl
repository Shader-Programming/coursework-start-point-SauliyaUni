# version 330 core
uniform vec3 viewPos;
uniform vec3 cubeColour;
uniform vec3 lightColour;
uniform vec3 lightDirection;;

uniform float ambientFactor;
uniform float shine;
uniform float specStrength;
float specLevel;

uniform sampler2D diffuseMap;
uniform sampler2D specularMap;

uniform vec3 slightPosition;
uniform vec3 slightColour;
uniform vec3 sAttentuation;
uniform vec3 sDirection;
uniform vec2 sRadii;

struct pointLight {
    vec3 colour;
    vec3 position;
    vec3 constants;
};

#define numPL 2
uniform pointLight pArray[numPL];

out vec4 FragColor;

in vec3 normal;
in vec3 posInWS;
in vec2 UV;



vec3 n = normalize(normal);
vec3 viewDir = normalize(viewPos - posInWS);

vec3 getDirectionalLight() {

    vec3 objCol = texture(diffuseMap, UV).rgb;
    float specStrength = texture(specularMap, UV).r;

    //ambient
    vec3 ambient = objCol * lightColour * ambientFactor;
    //diffuse
    
    float diffuseFactor = dot(n, -lightDirection);
    diffuseFactor = max(diffuseFactor, 0.0f);
    vec3 diffuse = objCol * lightColour * diffuseFactor;
    //Blinn Phong Specular
    
    vec3 H = normalize(-lightDirection + viewDir);
    specLevel = dot(n, H);
    specLevel = max(specLevel, 0.0);
    specLevel = pow(specLevel, shine);
    vec3 specular = lightColour * specLevel * specStrength;


    return  ambient + diffuse + specular;
}

vec3 getPointLight()
{
    vec3 objCol = texture(diffuseMap, UV).rgb;
    float specStrength = texture(specularMap, UV).r;

    vec3 ambient = objCol * pArray[0].colour * ambientFactor;

    float distance = length(pArray[0].position - posInWS);
    float attn = 1.0 / (pArray[0].constants.x + (pArray[0].constants.y * distance) + (pArray[0].constants.z * (distance * distance)));
    vec3 lightDir = normalize((pArray[0].position - posInWS));

    //diffuse
    float diffuseFactor = dot(n, -lightDir);
    diffuseFactor = max(diffuseFactor, 0.0f);
    vec3 diffuse = objCol * pArray[0].colour * diffuseFactor;

    vec3 H = normalize(-lightDir + viewDir);
    specLevel = dot(n, H);
    specLevel = max(specLevel, 0.0);
    specLevel = pow(specLevel, shine);
    vec3 specular = pArray[0].colour * specLevel * specStrength;

    diffuse = diffuse* attn;
    specular = specular* attn;
    return diffuse + specular;
}

vec3 getSpotLight(){

     vec3 objCol = texture(diffuseMap, UV).rgb;
    float specStrength = texture(specularMap, UV).r;

    float distance = length(slightPosition - posInWS);
    float attn = 1.0 / (sAttentuation.x + (sAttentuation.y * distance) + (sAttentuation.z * (distance * distance)));
    vec3 lightDir = normalize((slightPosition - posInWS));

    float diffuseFactor = dot(n, lightDir);
    diffuseFactor = max(diffuseFactor, 0.0f);
    vec3 diffuse = objCol * slightColour * diffuseFactor;

    vec3 ambient = objCol * slightColour * ambientFactor;

    vec3 H = normalize(lightDir + viewDir);
    specLevel = dot(n, H);
    specLevel = max(specLevel, 0.0);
    specLevel = pow(specLevel, shine);
    vec3 specular = slightColour * specLevel * specStrength;

    diffuse = diffuse * attn;
    specular = specular * attn;

    float theta = dot(-lightDir, normalize(sDirection));
    float denom = (sRadii.x - sRadii.y);
    float intensity = (theta - sRadii.y) / denom;
    intensity = clamp(intensity, 0.0, 1.0);
    diffuse = diffuse * intensity;
    specular = specular * intensity;

    return diffuse + specular + ambient;

}

void main() {
   
    vec3 result = getDirectionalLight();
  
    result += getPointLight();
    //result +=getSpotLight();
    FragColor = vec4(result, 1.0);

}