#pragma once

enum Directions {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
};

class Camera 
{
public:
	//camera configuration
	glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f, 0.0f);

	glm::mat4 projection, view;

	bool firstMouse = true;
	float yaw   = -90.0f;
	float pitch = 0.0f;

	float deltaTime = 0.1f;
	float lastFrame = 0.0f;

	float cameraSpeed = static_cast<float>(10.0 * deltaTime);
	float lastX;
	float lastY;
	float fov = 45.0f;

	float width, height;

	Camera(GLFWwindow* window, const float &WIDTH, const float &HEIGHT);
	~Camera();

	void SetProjection();
	void SetView();

	void MouseScroll(double xoffset, double yoffset);
	void MoveMouse(double xposln, double yposln);
	void MoveCamera(Directions direction);
};


