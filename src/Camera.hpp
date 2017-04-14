#pragma once

#include <glm/glm.hpp>

class Camera
{
public:
	Camera();
	~Camera();

	void Forward();
	void Backward();
	void Left();
	void Right();
	void Rotate(float pitch, float yaw);

	glm::vec3 GetPosition();
	glm::vec3 GetFront();
	glm::vec3 GetUp();
	glm::vec3 GetRight();


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

