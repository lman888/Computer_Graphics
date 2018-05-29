#pragma once
#include <iostream>
#include <crtdbg.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <gl_core_4_5.h>
#include <GLFW\glfw3.h>

#include <Gizmos.h>
#include "Camera.h"
#include "Mesh.h"
#include <Shader.h>
#include <OBJMesh.h>

#include <chrono>



class Application3D
{
public:
	Application3D();
	~Application3D();

	bool startup();

	bool initialise(int windowH, int windowW, std::string windowTitle, bool isFullScreen);

	bool update();
	
	void draw();
	
	void shutdown();

	int getWindowH() { return m_windowHeight; }
	int getWindowW() { return m_windowWidth; }
	


private:

	int m_windowHeight = 1280;
	int m_windowWidth = 720;

	//float setBackgroundColour;

	GLFWwindow*			m_window;

	Mesh				m_quadMesh;

	aie::ShaderProgram  m_shader;
	aie::OBJMesh  m_bunnyMesh;

	std::chrono::high_resolution_clock::time_point m_previousFrameTime;
	std::chrono::high_resolution_clock::time_point m_applicationStartTime;

	glm::mat4			m_bunnyTransform;
	glm::mat4			m_quadTransform;
	glm::mat4			m_view;
	glm::mat4			m_projection;
};