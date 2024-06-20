#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include <glm/glm.hpp>
#include "light.h"

Light::Light(glm::vec3 lightPos, glm::vec3 lightColor, glm::vec3 ambientStrength, glm::vec3 diffuseStrength, glm::vec3 specularStrength)
{
	m_lightPos = lightPos;
	m_lightColor = lightColor;

	m_ambientStrength = ambientStrength;
	m_diffuseStrength = diffuseStrength;
	m_specularStrength = specularStrength;
};

Light::~Light() 
{
};
