#pragma once
#include "myScene.h"


Myscene::Myscene(GLFWwindow* window, InputHandler* H) : Scene(window, H) {
	m_camera = new FirstPersonCamera();
	m_camera->attachHandler(m_window, m_handler);
	m_myShader = new Shader("..\\Shaders\\Shader.glsl", "..\\Shaders\\Fragment.glsl");
	m_directionalLight = new DirectionalLight(glm::vec3(1.0), glm::vec3(0.0, -1.0f, 0.0f));
	m_directionalLight->setLightUniforms(m_myShader);

	

	m_textureManager = new TextureManager();
	unsigned int cubeDiff = TextureManager::loadTexture("..\\Resources\\diffuseCube.jpg");
	unsigned int cubeSpec = TextureManager::loadTexture("..\\Resources\\specularCube.jpg");
	
	m_pointLight = new PointLight(glm::vec3(1.0, 0.0, 0.0), glm::vec3(-2.0, 0.0, 0.0), glm::vec3(1.0, 0.22, 0.02));
	m_pointLight->setLightUniforms(m_myShader);

	m_spotLight = new SpotLight(glm::vec3(0.5, 1.0, 0.0), glm::vec3(0.0, 7.0, 0.0), glm::vec3(1.0, 0.027, 0.0028), glm::vec3(0.0, -1.0, 0.0), glm::vec2(glm::cos(glm::radians(12.5f)), glm::cos(glm::radians(17.5f))));
	m_spotLight->setLightUniform(m_myShader);

	m_cube = new Cube(cubeDiff,cubeSpec, 5.0f);
	m_cube->setCubeMaterialValues(m_myShader);

	m_plane = new Plane(cubeDiff, cubeSpec, 2.0f);
	m_plane->setPlaneMaterialValues(m_myShader);



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

	m_myShader->use();

	m_myShader->setMat4("View", m_camera->getViewMatrix());
	m_myShader->setMat4("Projection", m_camera->getProjectionMatrix());
	m_myShader->setVec3("viewPos", m_camera->getPosition());

	glBindVertexArray(m_cube->getVAO());
	if (m_handler->keyHasBeenPressed()) {
		if (m_handler->isKeyPressed(GLFW_KEY_X)) {
			m_cube->rotate((float)(glfwGetTime() * 0.5), glm::vec3(0.0, 0.0, 5.0));
		}
	}
	m_cube->setTransform(m_myShader);
	glDrawElements(GL_TRIANGLES, m_cube->getIndicesCount(), GL_UNSIGNED_INT, 0);

	m_cube->translate(glm::vec3(5.0, 0.0, 0.0));
	m_cube->rotate((float)(glfwGetTime() * 0.5), glm::vec3(1.0, 0.0, 0.0));
	m_cube->setTransform(m_myShader);
	glDrawElements(GL_TRIANGLES, m_cube->getIndicesCount(), GL_UNSIGNED_INT, 0);
	m_cube->resetTransform();

}
void Myscene::update(float dt) {
	m_camera->update(dt);
	render();
}
