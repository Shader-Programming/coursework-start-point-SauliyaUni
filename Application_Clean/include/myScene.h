#pragma once

#include "Scene.h"
#include "Shader.h"
#include "Light/DirectionalLight.h"
#include "Cube/Cube.h"
#include <PointLight/PointLight.h>
#include "Texture/TextureManager.h"
#include "SpotLight/SpotLight.h"
#include "Floor/Floor.h"

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

	DirectionalLight* m_directionalLight;

	Cube* m_cube;

	PointLight* m_pointLight;

	TextureManager* m_textureManager;

	SpotLight* m_spotLight;

	Plane* m_plane;

	void render();

	Shader* m_myShader;
};