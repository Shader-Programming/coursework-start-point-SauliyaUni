#include "Floor/Floor.h"

Plane::Plane(unsigned int diffuseTexture, unsigned int specTexture, float shine):
	m_diffuseTexture(diffuseTexture),
	m_specularTexture(specTexture),
	m_shine(shine)
{
	makeVAO();
	resetTransform();
}

void Plane::makeVAO()
{
	glCreateBuffers(1, &m_VAO);
	glNamedBufferStorage(m_VAO, sizeof(float) * vertexData.size(), vertexData.data(), GL_DYNAMIC_STORAGE_BIT);

	glCreateBuffers(1, &EBO);
	glNamedBufferStorage(EBO, sizeof(unsigned int) * floorIndices.size(), floorIndices.data(), GL_DYNAMIC_STORAGE_BIT);

	glCreateVertexArrays(1, &m_VAO);
	glVertexArrayVertexBuffer(m_VAO, 0, m_VAO, 0, sizeof(float) * 6);
	glVertexArrayElementBuffer(m_VAO, EBO);

	glEnableVertexArrayAttrib(m_VAO, 0);

	glVertexArrayAttribFormat(m_VAO, 0, 3, GL_FLOAT, GL_FALSE, 0);

	glVertexArrayAttribBinding(m_VAO, 0, 0);
}

void Plane::setPlaneMaterialValues(Shader* shader)
{
	shader->use();
	shader->setFloat("shine", m_shine);
	shader->setInt("diffuseMap", 0);
	shader->setInt("specularMap", 1);

	glBindTextureUnit(0, m_diffuseTexture);
	glBindTextureUnit(1, m_specularTexture);
}
