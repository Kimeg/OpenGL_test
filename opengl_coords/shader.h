#pragma once

class Shader 
{
public:
	unsigned int vertexID, fragmentID, programID;

	Shader(const char* vertexPath, const char* fragmentPath);
	~Shader();

	void UseProgram();
	void CreateProgram();
	void DeleteProgram();
	void DeleteShaders();

	void SetInt(const char* name, int val);
	void SetVec3(const char* name, float x, float y, float z);
	void SetVec3(const char* name, glm::vec3 vec);
	void SetMat4(const char* name, glm::mat4 &matrix);
	void SetTexture(const char* name, const int index);
};
