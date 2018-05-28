#pragma once
#include <glm.hpp>

#include <glfw3.h>
#include "../glm/glm.hpp"
#include "../glm/ext.hpp"


class Camera
{
public:
	Camera();
	~Camera();
	virtual void update(float deltaTime) = 0;
	void setPerspective(float fieldOfView, float aspectRatio, float near, float far);
	void setLookAt(glm::vec3 from, glm::vec3 to, glm::vec3 up);
	void setPosition(glm::vec3 postion);
	void getWorld(glm::mat4 world);
	void getView(glm::mat4 view);
	void getProjection(glm::mat4 projection);
	void getProjectionView(glm::mat4 projectionView);

private:
	void updateProjectionViewTransform();

	glm::mat4 worldTransform;
	glm::mat4 viewTransform;
	glm::mat4 projectionTransform;
	glm::mat4 projectionViewTransform;
};

