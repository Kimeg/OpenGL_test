#pragma once

class Light 
{
public:

	glm::vec3 m_lightPos;
	glm::vec3 m_lightColor;

	glm::vec3 m_ambientStrength;
	glm::vec3 m_diffuseStrength;
	glm::vec3 m_specularStrength;

	Light(glm::vec3 lightPos, glm::vec3 lightColor, glm::vec3 ambientStrength, glm::vec3 diffuseStrength, glm::vec3 specularStrength);
	~Light();
};
