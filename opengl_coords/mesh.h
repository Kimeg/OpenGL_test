#pragma once

class Mesh 
{
public:
	unsigned int VAO, VBO, EBO;
	
	Mesh(const char* meshType);
	~Mesh();

	void GenerateCubeMesh();
	void GenerateBlendCubeMesh();
	void GenerateCubeMapMesh();
	void BindVertexArray();
	void Render();
	void DeleteVertexArrays();
	void DeleteBuffers();
};
