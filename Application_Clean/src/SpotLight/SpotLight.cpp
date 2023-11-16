#include "SpotLight/SpotLight.h"

SpotLight::SpotLight(glm::vec3 colour, glm::vec3 position, glm::vec3 constants, glm::vec3 dir, glm::vec2 radii) :
	PointLight(colour, position,constants),
	m_direction(dir),
	m_radii(radii){}

void SpotLight::setLightUniform(Shader* shader)
{
	shader->use();
	shader->setVec3("slightColour", m_colour);
	shader->setVec3("sDirection", m_direction);
	shader->setVec2("sRadii", m_radii);
}
