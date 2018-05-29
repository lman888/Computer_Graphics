#pragma once
#include <iostream>
#include <crtdbg.h>
#include <glm.hpp>
#include <ext.hpp>
#include "../dependencies/glCore/gl_core_4_5.h"
#include <glfw3.h>

#include "Gizmos.h"
#include "Camera.h"
#include "Mesh.h"

class Application3D
{
public:
	Application3D();
	~Application3D();

	bool update();
	
	void draw();
	
	void shutdown();

private:

	GLFWwindow* window;

	Mesh* mesh;

	glm::mat4 view;

	glm::mat4 projection;
};

