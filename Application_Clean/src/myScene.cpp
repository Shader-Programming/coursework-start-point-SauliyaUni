#pragma once
#include "myScene.h"


Myscene::Myscene(GLFWwindow* window, InputHandler* H) : Scene(window, H) {
	m_camera = new FirstPersonCamera();
	m_camera->attachHandler(m_window, m_handler);
	m_myShader = new Shader("..\\Shaders\\Whatever.glsl", "..\\Shaders\\Fragment.glsl");
	m_directionalLight = new DirectionalLight(glm::vec3(1.0), glm::vec3(0.0, -1.0f, 0.0f));
	m_directionalLight->setLightUniforms(m_myShader);
	m_cube = new Cube(glm::vec3(0.1, 0.2, 0.3), 64, 16);
	m_cube->setCubeMaterialValues(m_myShader);
}

Myscene::~Myscene()
{
	delete m_myShader;
	delete m_cube;
	delete m_directionalLight;
}

void Myscene::render()
{
	m_model = glm::mat4(1.0f);
	/*m_projection = m_camera->getProjectionMatrix();
	m_view = m_camera->getViewMatrix();*/
	m_myShader->use();

	m_myShader->setMat4("View", m_camera->getViewMatrix());
	m_myShader->setMat4("Projection", m_camera->getProjectionMatrix());
	m_myShader->setVec3("viewPos", m_camera->getPosition());

	glBindVertexArray(m_cube->getVAO());
	m_cube->rotate((float)(glfwGetTime() * 0.2), glm::vec3(10.0, 0.0, 0.0));
	m_cube->setTransform(m_myShader);
	glDrawElements(GL_TRIANGLES, m_cube->getIndicesCount(), GL_UNSIGNED_INT, 0);

	m_cube->translate(glm::vec3(5.0, 0.0, 0.0));
	m_cube->rotate((float)(glfwGetTime() * 0.5), glm::vec3(1.0, 0.0, 0.0));
	m_cube->setTransform(m_myShader);
	glDrawElements(GL_TRIANGLES, m_cube->getIndicesCount(), GL_UNSIGNED_INT, 0);
	m_cube->resetTransform();

	//glBindVertexArray(m_cube->getVAO());
	////m_model = glm::rotate(m_model, (float)(glfwGetTime() * 0.5), glm::vec3(1.0, 0.0, 0.0));
	//m_myShader->setMat4("Model", m_model);
	//glDrawElements(GL_TRIANGLES, m_cube->getIndicesCount(), GL_UNSIGNED_INT, 0);

	//if (m_handler->keyHasBeenPressed()) {
	//	if (m_handler->isKeyPressed(GLFW_KEY_X)) {
	//		m_model = glm::rotate(m_model, (float)(glfwGetTime() * 0.5), glm::vec3(1.0, 0.0, 0.0));
	//	}
	//}
	//m_model = glm::translate(m_model, glm::vec3(5.0, 0.0, 0.0));
	//
	//m_myShader->setMat4("Model", m_model);

	//glDrawElements(GL_TRIANGLES, m_cube->getIndicesCount(), GL_UNSIGNED_INT, 0);

	//m_model = glm::translate(m_model, glm::vec3(7.0, 0.0, 0.0));
	//m_myShader->setMat4("Model", m_model);

	//glDrawElements(GL_TRIANGLES, m_cube->getIndicesCount(), GL_UNSIGNED_INT, 0);
}

void Myscene::update(float dt) {
	m_camera->update(dt);
	render();
}
