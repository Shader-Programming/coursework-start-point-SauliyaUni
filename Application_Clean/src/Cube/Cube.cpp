#include "Cube/Cube.h"

Cube::Cube(glm::vec3 col, float shine, float specStrength) : m_colour(col), m_shine(shine), m_specularStrength(specStrength)
{
	makeVAO();
	resetTransform();
}

Cube::~Cube()
{

}


void Cube::rotate(float angle, glm::vec3 axis)
{

}

void Cube::makeVAO()
{
	glCreateBuffers(1, &m_VAO);
	glNamedBufferStorage(m_VAO, sizeof(float) * vertexData.size(), vertexData.data(), GL_DYNAMIC_STORAGE_BIT); // 9 is number of floats in vertexData array

	glCreateBuffers(1, &EBO);
	glNamedBufferStorage(EBO, sizeof(unsigned int) * cubeIndices.size(), cubeIndices.data(), GL_DYNAMIC_STORAGE_BIT);

	glCreateVertexArrays(1, &m_VAO);
	glVertexArrayVertexBuffer(m_VAO, 0, m_VAO, 0, sizeof(float) * 6);
	glVertexArrayElementBuffer(m_VAO, EBO);

	glEnableVertexArrayAttrib(m_VAO, 0);
	glEnableVertexArrayAttrib(m_VAO, 1);

	glVertexArrayAttribFormat(m_VAO, 0, 3, GL_FLOAT, GL_FALSE, 0);
	glVertexArrayAttribFormat(m_VAO, 1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float));

	glVertexArrayAttribBinding(m_VAO, 0, 0);
	glVertexArrayAttribBinding(m_VAO, 1, 0);

}

void Cube::setCubeMaterialValues(Shader* shader)
{
	shader->use();
	shader->setVec3("cubeColour", m_colour);
	shader->setFloat("shine", m_shine);
	shader->setFloat("specStrength", m_specularStrength);
}

