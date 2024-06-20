#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/random.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <math.h>
#include <vector>
#include "camera.h" 

using namespace std;

Camera::Camera(GLFWwindow* window, const float &WIDTH, const float &HEIGHT)
{
	lastX = WIDTH / 2.0f;
	lastY = HEIGHT / 2.0f;

	width = WIDTH;
	height = HEIGHT;
};

void Camera::SetProjection()
{
	projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 1000.0f);
};

void Camera::SetView()
{
	view = glm::lookAt(cameraPos, cameraPos+cameraFront, cameraUp);
};

void Camera::MoveCamera(Directions direction)
{
	if (direction == FORWARD)
		cameraPos += cameraSpeed * cameraFront;
	else if (direction == BACKWARD)
		cameraPos -= cameraSpeed * cameraFront;
	else if (direction == LEFT)
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	else if (direction == RIGHT)
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
};

void Camera::MouseScroll(double xoffset, double yoffset)
{
	fov -= (float)yoffset;

	if (fov < 1.0f)
		fov = 1.0f;
	if (fov > 45.0f)
		fov = 45.0f;
};

void Camera::MoveMouse(double xposln, double yposln)
{
	float xpos = static_cast<float>(xposln);
	float ypos = static_cast<float>(yposln);

	if (this->firstMouse)
	{
		this->lastX = xpos;
		this->lastY = ypos;
		this->firstMouse = false;
	}

	float xoffset = xpos - this->lastX;
	float yoffset = this->lastY - ypos;

	this->lastX = xpos;
	this->lastY = ypos;

	float sensitivity = 0.1f;

	xoffset *= sensitivity;
	yoffset *= sensitivity;

	this->yaw += xoffset;
	this->pitch += yoffset;

	if (this->pitch > 89.0f)
		this->pitch = 89.0f;
	if (this->pitch < -89.0f)
		this->pitch = -89.0f;

	glm::vec3 front;
	front.x = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
	front.y = sin(glm::radians(this->pitch));
	front.z = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));

	this->cameraFront = glm::normalize(front);
};

Camera::~Camera()
{
};
