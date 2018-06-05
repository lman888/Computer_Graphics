#pragma once
#include <gl_core_4_5.h>
#include <GLFW\glfw3.h>
#include <iostream>
#include <string>
#include <chrono>


#include <glm\glm.hpp>
#include <glm\ext.hpp>

class Application
{
public:
	~Application();

	//Functions for children to call
	virtual void StartUp() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void Shutdown() = 0;

	//Runs the application
	int Run(const char* name, int screenWidth, int screenHeight);

	//Initialises the window and sets it up
	bool Initialise();

	//Creates the main game loop
	void StartUp();

	//ShutsDown the spplication
	void ShutDown();

	//Getters
	GLFWwindow* getWindow() { return m_window; }
	int getWindowWitdth() { return m_windowWidth; }
	int getWindowHeight() { return m_windowHeight; }
	bool getFullScreen() { return m_isFullscreen; }
	bool getIsRunning() { return m_isRunning; }
	float getDeltaTime() { return m_deltaTime; }
	float getElapsedTime() { return m_elapsedTime; }

	//Setters
	void SetIsRunning(bool value) { m_isRunning = value; }

protected:
	

private:
	//Variables
	GLFWwindow * m_window;	//The applications window
	int m_windowHeight;
	int m_windowWidth;
	bool m_isFullscreen = false;
	bool m_isRunning = true;
	float m_deltaTime = 0.0f;
	float m_elapsedTime = 0.0f;
	std::chrono::high_resolution_clock::time_point m_previousFrameTime;
	std::chrono::high_resolution_clock::time_point m_applicationStartTime;
};

