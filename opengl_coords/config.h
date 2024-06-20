#pragma once


//screen configuration
const unsigned int WIDTH  = 800;
const unsigned int HEIGHT = 800;

//object configuration
const int nObject   = 50;
const float MIN_POS = -20.0f;
const float MAX_POS = 20.0f;

//light configuration
glm::vec3 lightPos(0.0f, 0.0f, 0.0f);
glm::vec3 lightColor(0.0f, 1.0f, 1.0f);
glm::vec3 lightAmbient(glm::vec3(0.1f, 0.1f, 0.1f));
glm::vec3 lightDiffuse(glm::vec3(0.4f, 0.4f, 0.4f));
glm::vec3 lightSpecular(glm::vec3(0.8f, 0.8f, 0.8f));

//texture files
const char* texturePath1 = "resources/textures/rayman.png";
const char* texturePath2 = "resources/textures/container2.png";
const char* texturePath3 = "resources/textures/skybox/top.jpg";
const char* texturePath4 = "resources/textures/window.png";
const char* texturePath5 = "resources/textures/matrix.jpg";

std::vector<std::string> cubemap
{
	"resources/textures/skybox/right.jpg",
	"resources/textures/skybox/left.jpg",
	"resources/textures/skybox/top.jpg",
	"resources/textures/skybox/bottom.jpg",
	"resources/textures/skybox/back.jpg",
	"resources/textures/skybox/front.jpg"
};

//skybox configuration
float skyboxDist = 300.0f;

glm::vec3 skyboxPos[] =
{
	glm::vec3(0.0f, skyboxDist, 0.0f),
	glm::vec3(0.0f, -skyboxDist, 0.0f),
	glm::vec3(skyboxDist, 0.0f, 0.0f),
	glm::vec3(-skyboxDist, 0.0f, 0.0f),
	glm::vec3(0.0f, 0.0f, -skyboxDist),
	glm::vec3(0.0f, 0.0f, skyboxDist)
};

glm::vec3 skyboxScale[] =
{
	glm::vec3(2*skyboxDist, 0.1f, 2*skyboxDist),
	glm::vec3(2*skyboxDist, 0.1f, 2*skyboxDist),
	glm::vec3(0.1f, 2*skyboxDist, 2*skyboxDist),
	glm::vec3(0.1f, 2*skyboxDist, 2*skyboxDist),
	glm::vec3(2*skyboxDist, 2*skyboxDist, 0.1f),
	glm::vec3(2*skyboxDist, 2*skyboxDist, 0.1f)
};

//skybox configuration
glm::vec3 blendPos[] =
{
	glm::vec3(0.0f, 0.0f, 5.0f),
	glm::vec3(0.0f, 0.0f, 10.0f),
};

glm::vec3 blendPos2[] =
{
	glm::vec3(1.0f, 1.0f, 13.0f),
	glm::vec3(1.0f,-1.0f, 7.0f),
};

//shader files
const char* vertexPath = "lighting.vs";
const char* fragmentPath = "lighting.fs";

const char* lightVertexPath = "lighting2.vs";
const char* lightFragmentPath = "lighting2.fs";

const char* kernelVertexPath = "kernel_test.vs";
const char* kernelFragmentPath = "kernel_test.fs";

const char* blendVertexPath = "blend_test.vs";
const char* blendFragmentPath = "blend_test.fs";
