#include "Camera.h"



Camera::Camera()
{
}


Camera::~Camera()
{
}

void Camera::setPerspective(float fieldOfView, float aspectRatio, float near, float)
{

}

void Camera::updateProjectionViewTransform()
{

}

void Camera::setLookAt(glm::vec3 from, glm::vec3 to, glm::vec3 up)
{

}

void Camera::setPosition(glm::vec3 postion)
{
	
}

void Camera::getWorld(glm::mat4 world)
{
	worldTransform = world;
}

void Camera::getView(glm::mat4 view)
{
	viewTransform = view;
}

void Camera::getProjection(glm::mat4 projection)
{
	projectionTransform = projection;
}

void Camera::getProjectionView(glm::mat4 projectionView)
{
	projectionViewTransform = projectionView;
}

