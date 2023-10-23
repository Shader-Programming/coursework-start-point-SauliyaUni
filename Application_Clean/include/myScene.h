#pragma once

#include "Scene.h"
#include "Shader.h"

/*
Child Class of Scene
*/

class Myscene : public Scene {

public:
	Myscene(GLFWwindow* window, InputHandler* H);
	~Myscene();
	void update(float dt) override;

private:
	unsigned int VBO, VAO;
	float vertexData[9] = { 0.5,0.5,0.0,
							-0.5,0.5,0.0
							- 0.5, -0.5,0.0 };
	void makeVAO();
	void render();
};