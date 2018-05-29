#pragma once
#include "Camera.h"
#include <GLFW\glfw3.h>

class FlyCamera : Camera
{
public:
	FlyCamera();
	~FlyCamera();

	virtual void update(float deltaTime) override;
	void setSpeed(float setSpeed);

	//Camera myCamera;


private:

	float speed;
	glm::vec3 up;
};

