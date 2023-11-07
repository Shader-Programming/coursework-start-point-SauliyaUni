#include "PointLight/PointLight.h"

PointLight::PointLight(glm::vec3 colour, glm::vec3 position, glm::vec3 constants) :
	Light(colour),
	m_constants(constants),
	m_position(position) {}


void PointLight::setLightUniforms(Shader* shader)
{
	shader->use();
	shader->setVec3("pArray[0].position", m_position);
	shader->setVec3("pArray[0].colour", m_colour);
	shader->setVec3("pArray[0].constants", m_constants);
}
