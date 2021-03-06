#pragma once
#include <iostream>
#include <crtdbg.h>
#include <chrono>
#include <sstream>


#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/ext.hpp>
#include <gl_core_4_5.h>
#include <GLFW\glfw3.h>


#include <Gizmos.h>
#include "Camera.h"
#include "Mesh.h"
#include <Shader.h>
#include <OBJMesh.h>
#include "RenderTarget.h"

struct  Light
{
	glm::vec4 position;
	glm::vec3 intensities;
	float attenuation;
	float ambientCoefficient;
	float coneAngle;
	glm::vec3 coneDirection;

	glm::vec3 direction;
	glm::vec3 diffuse;
	glm::vec3 specular;
};

class Application3D
{
public:
	Application3D();
	~Application3D();

	//template <typename T>
	//void BindLightUniform(aie::ShaderProgram * shaders, const char * propertyName, size_t lightIndex, const T& value);

	///STarting up the program
	bool startup();

	///Initialises the window
	bool initialise(int windowH, int windowW, std::string windowTitle, bool isFullScreen);

	///Updates the screen per frame
	bool update();
	

	///Draws the objects to the screen
	void draw();
	
	void clearScreen();

	///Shutdowns the application
	void shutdown();

	///Getters
	int getWindowH() { return m_windowHeight; }
	int getWindowW() { return m_windowWidth; }
	


private:

	///Window height and width
	int m_windowHeight = 1280;
	int m_windowWidth = 720;

	//float setBackgroundColour;

	///Variables
	GLFWwindow*			m_window;
	Mesh				m_quadMesh;
	Light				m_light;
	Light				m_secondaryLight;
	Light				m_thirdLight;
	//Light				m_spotLight;
	//Light				m_directionLight;

	///aie variables
	aie::ShaderProgram  m_phongShader;
	aie::ShaderProgram  m_shader;
	aie::ShaderProgram  m_texturedShader;
	aie::ShaderProgram  m_normalShader;
	aie::OBJMesh		m_bunnyMesh;
	aie::OBJMesh		m_dragonMesh;
	aie::OBJMesh		m_spearMesh;
	aie::Texture		m_gridTexture;
	aie::RenderTarget   m_renderTarget;

	std::chrono::high_resolution_clock::time_point m_previousFrameTime;
	std::chrono::high_resolution_clock::time_point m_applicationStartTime;

	///VariablesS
	//std::vector<Light>	gLights;
	glm::vec3			m_ambientLight;
	glm::mat4			m_spearTransform;
	glm::mat4			m_dragonTransform;
	glm::mat4			m_bunnyTransform;
	glm::mat4			m_quadTransform;
	glm::mat4			m_view;
	glm::mat4			m_projection;
};

//This uses the BindLightUniform, which constructs the uniform names based on the struct element and the index
//template<typename T>
//inline void Application3D::BindLightUniform(aie::ShaderProgram * shaders, const char* propertyName, size_t lightIndex, const T& value)
//{
//	std::ostringstream ss;
//	ss << "allLights[" << lightIndex << "]." << propertyName;
//	std::string uniformName = ss.str();
//
//	shaders->bindUniform(uniformName.c_str(), value);
//}
