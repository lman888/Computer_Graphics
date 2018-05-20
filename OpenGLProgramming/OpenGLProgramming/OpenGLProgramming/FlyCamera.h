#pragma once
#include "Camera.h"
#include <glfw3.h>

class FlyCamera
{
public:
	FlyCamera();
	~FlyCamera();

	void update(float deltaTime);
	void setSpeed(float setSpeed);

	//Camera myCamera;


private:

	float speed;
	glm::vec3 up;
};

