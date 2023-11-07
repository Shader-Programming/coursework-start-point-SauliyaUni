#pragma once

#include "Scene.h"
#include "Shader.h"
#include "Light/DirectionalLight.h"
#include "Cube/Cube.h"
#include <PointLight/PointLight.h>

/*
Child Class of Scene
*/

class Myscene : public Scene {

public:
	Myscene(GLFWwindow* window, InputHandler* H);
	~Myscene();
	void update(float dt) override;

private:
	
	glm::mat4 m_model, m_view, m_projection;
	/*float vertexData[36] = { 0.5,0.5,0.0, 1.0, 0.0, 0.0,
							-0.5,0.5,0.0, 0.0,1.0, 0.0,
							- 0.5,-0.5,0.0, 0.0, 0.0, 1.0,
							0.5,0.5,0.0, 1.0, 0.0, 0.0,
							0.5, -0.5, 0.0, 0.0, 1.0, 0.0,
							-0.5,-0.5,0.0, 0.0, 0.0, 1.0};*/
	DirectionalLight* m_directionalLight;
	Cube* m_cube;
	PointLight* m_pointLight;
	void render();
	Shader* m_myShader;
};