#pragma once

#include <glm/glm.hpp>

class Camera
{
public:
	Camera::Camera();
	Camera::~Camera();

	void Camera::Forward();
	void Camera::Backward();
	void Camera::Left();
	void Camera::Right();
	void Camera::Rotate(float pitch, float yaw);

	glm::vec3 Camera::GetPosition();
	glm::vec3 Camera::GetFront();
	glm::vec3 Camera::GetUp();
	glm::vec3 Camera::GetRight();


private:

	float mSpeed;
	float mPitch, mYaw;

	glm::vec3 mTarget;
	glm::vec3 mPosition;

	glm::vec3 mDirection;
	glm::vec3 mFront;
	glm::vec3 mUp;
	glm::vec3 mRight;
};

