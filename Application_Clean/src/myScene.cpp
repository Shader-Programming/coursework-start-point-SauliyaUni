#pragma once
#include "myScene.h"

Myscene::Myscene(GLFWwindow* window, InputHandler* H) : Scene(window, H) {
	m_camera = new FirstPersonCamera();
	m_camera->attachHandler(m_window, m_handler);
	m_myShader = new Shader("..\\Shaders\\Whatever.glsl", "..\\Shaders\\Fragment.glsl");
	makeVAO();
}

Myscene::~Myscene()
{
	delete m_myShader;
}

void Myscene::makeVAO()
{
	glCreateBuffers(1, &VBO);
	glNamedBufferStorage(VBO, sizeof(float) * 36, vertexData,  GL_DYNAMIC_STORAGE_BIT); // 9 is number of floats in vertexData array

	glCreateVertexArrays(1, &VAO);
	glVertexArrayVertexBuffer(VAO, 0, VBO, 0, sizeof(float) * 6);

	glEnableVertexArrayAttrib(VAO, 0);
	glEnableVertexArrayAttrib(VAO, 1);

	glVertexArrayAttribFormat(VAO, 0, 3, GL_FLOAT, GL_FALSE, 0);
	glVertexArrayAttribFormat(VAO, 1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float));

	glVertexArrayAttribBinding(VAO, 0, 0);
	glVertexArrayAttribBinding(VAO, 1, 0);

}

void Myscene::render()
{
	m_myShader->use();
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Myscene::update(float dt) {
	m_camera->update(dt);
	render();
}
