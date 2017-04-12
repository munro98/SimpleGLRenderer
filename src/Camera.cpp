#include "Camera.hpp"



Camera::Camera()
{
	mPosition = glm::vec3(0.0f, 0.0f, 2.0f);

	mTarget = glm::vec3(0.0f, 0.0f, 0.0f);
	mDirection = glm::normalize(mPosition - mTarget);
	mFront = glm::vec3(0.0f, 0.0f, -1.0f);
	mUp = glm::vec3(0.0f, 1.0f, 0.0f);
	mRight = glm::normalize(glm::cross(mUp, mDirection));

	mSpeed = 0.001f;

	mYaw = -90.0f;
	mPitch = 0.0f;

	Rotate(0.0f, 0.0f);
}


Camera::~Camera()
{
}

void Camera::Forward() {
	mPosition += mSpeed * mFront;
}

void Camera::Backward() {
	mPosition -= mSpeed * mFront;
}

void Camera::Left() {
	mPosition -= mSpeed * glm::normalize(glm::cross(mFront, mUp));
}

void Camera::Right() {
	mPosition += mSpeed * glm::normalize(glm::cross(mFront, mUp));
}

void Camera::Rotate(float x, float y) {

	mYaw += x;
	mPitch += y;

	///*
	if (mPitch > 89.0f)
		mPitch = 89.0f;
	if (mPitch < -89.0f)
		mPitch = -89.0f;
	//*/

	glm::vec3 front;
	front.x = cos(glm::radians(mYaw)) * cos(glm::radians(mPitch));
	front.y = sin(glm::radians(mPitch));
	front.z = sin(glm::radians(mYaw)) * cos(glm::radians(mPitch));
	mFront = glm::normalize(front);

	mUp = glm::vec3(0.0f, 1.0f, 0.0f);
	mRight = glm::normalize(glm::cross(mUp, mDirection));
}

glm::vec3 Camera::GetPosition() {
	return mPosition;

}

glm::vec3 Camera::GetFront() {
	return mFront;

}

glm::vec3 Camera::GetUp() {
	return mUp;

}

glm::vec3 Camera::GetRight() {
	return mRight;

}
