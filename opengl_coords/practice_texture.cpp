#define STB_IMAGE_IMPLEMENTATION

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/random.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <math.h>
#include <vector>
#include <map>

#include "texture.h" 
#include "shader.h" 
#include "mesh.h" 
#include "camera.h" 
#include "light.h" 
#include "config.h" 

using namespace std;

//GLFW configuration
GLFWwindow* window;
Camera camera(window, WIDTH, HEIGHT);

// helper functions ##########################################################

void processInput(GLFWwindow* window);
void moveMouse(GLFWwindow* window, double xposln, double yposln);
void mouseScroll(GLFWwindow* window, double xoffset, double yoffset);
void moveCamera(GLFWwindow* window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

void processInput(GLFWwindow* window) 
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	moveCamera(window);
}

void moveMouse(GLFWwindow* window, double xposln, double yposln)
{
	camera.MoveMouse(xposln, yposln);
};

void mouseScroll(GLFWwindow* window, double xoffset, double yoffset) 
{
	camera.MouseScroll(xoffset, yoffset);
}

void moveCamera(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.MoveCamera(FORWARD);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.MoveCamera(BACKWARD);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.MoveCamera(LEFT);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.MoveCamera(RIGHT);
};

void framebuffer_size_callback(GLFWwindow* window, int width, int height) 
{
	glViewport(0, 0, width, height);
}

bool InitializeGLFW() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(WIDTH, HEIGHT, "kimeg's graphics practice", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, moveMouse);
	glfwSetScrollCallback(window, mouseScroll);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return false;
	}

	glEnable(GL_DEPTH_TEST);

	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//glDepthFunc(GL_LEQUAL);

	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);
	//glFrontFace(GL_CCW);
	return true;
}

map<float, glm::vec3> calcZ(glm::vec3* vec)
{
	map<float, glm::vec3> m;

	for (int i = 0; i < 4; i++) 
	{
		float dist = glm::length(camera.cameraPos - vec[i]);
		m[dist] = vec[i];
	}

	return m;
}

// ##########################################################
int main()
{
	if (!InitializeGLFW())
		return -1;

	// angle vectors just for fun
	vector<glm::vec3> angles;

	for (int i = 0; i < nObject; i++) 
	{
		angles.push_back(glm::vec3(glm::linearRand(0.0f, 360.0f), glm::linearRand(0.0f, 360.0f), glm::linearRand(0.0f, 360.0f)));
	}

	// Object coordinates
	vector<glm::vec3> objectCoords;
	vector<glm::vec3> lightCoords;
	vector<glm::vec3> lightColors;

	for (int i = 0; i < nObject; i++) 
	{
		objectCoords.push_back(glm::vec3(glm::linearRand(MIN_POS, MAX_POS), glm::linearRand(MIN_POS, MAX_POS), glm::linearRand(MIN_POS, MAX_POS)));
		lightCoords.push_back(glm::vec3(glm::linearRand(MIN_POS, MAX_POS), glm::linearRand(MIN_POS, MAX_POS), glm::linearRand(MIN_POS, MAX_POS)));
		lightColors.push_back(glm::vec3(glm::linearRand(0.0f, 1.0f), glm::linearRand(0.0f, 1.0f), glm::linearRand(0.0f, 1.0f)));
	}

	// VAO, VBO 
	Mesh mesh("cube");
	Mesh blendMesh("blend");
	//Mesh meshCubeMap("cubemap");

	// Textures 
	Texture texture1(texturePath1);
	Texture texture2(texturePath2);
	Texture skyTexture(texturePath3);
	Texture blendTexture(texturePath4);
	Texture matrixTexture(texturePath5);

	// Shaders 
	Shader shader(vertexPath, fragmentPath);
	Shader lightShader(lightVertexPath, lightFragmentPath);
	Shader kernelShader(kernelVertexPath, kernelFragmentPath);
	Shader blendShader(blendVertexPath, blendFragmentPath);
	Shader blendShader2(blendVertexPath, blendFragmentPath);

	shader.UseProgram();
	shader.SetTexture("material.diffuse", 0);
	shader.SetTexture("material.specular", 1);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture1.ID);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture2.ID);

	lightShader.UseProgram();
	lightShader.SetTexture("cubemap", 2);

	glActiveTexture(GL_TEXTURE2);
	//glBindTexture(GL_TEXTURE_CUBE_MAP, skyTexture.ID);
	glBindTexture(GL_TEXTURE_2D, skyTexture.ID);

	kernelShader.UseProgram();
	kernelShader.SetTexture("material.diffuse", 3);
	kernelShader.SetTexture("material.specular", 4);

	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, texture1.ID);
	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D, texture2.ID);

	
	blendShader.UseProgram();
	blendShader.SetTexture("text", 3);

	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, blendTexture.ID);

	blendShader2.UseProgram();
	blendShader2.SetTexture("text", 4);

	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D, matrixTexture.ID);
	

	// Lights
	Light light(
		lightPos,
		lightColor,
		lightAmbient,
		lightDiffuse,
		lightSpecular
	);

	// Create projection and view matrices
	camera.SetProjection();

	// Render 
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		camera.SetView();

		// Render skybox 
		/*glDepthMask(GL_FALSE);

		lightShader.UseProgram();

		meshCubeMap.BindVertexArray();

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, skyTexture.ID);

		lightShader.SetMat4("projection", camera.projection);
		glm::mat4 view = glm::mat4(glm::mat3(camera.view));
		lightShader.SetMat4("view", view);

		meshCubeMap.Render(); 

		glDepthMask(GL_TRUE);
		*/

		// ###################################################################
		blendMesh.BindVertexArray();

		// Render objects for blending test 
		blendShader.UseProgram();

		blendShader.SetMat4("projection", camera.projection);
		blendShader.SetMat4("view", camera.view);

		map<float, glm::vec3> m = calcZ(blendPos);

		for (map<float, glm::vec3>::reverse_iterator it=m.rbegin(); it!=m.rend(); ++it)
		{
			glm::mat4 model(1.0f);
			model = glm::translate(model, it->second);
			model = glm::scale(model, glm::vec3(3.0f, 3.0f, 0.1f));

			blendShader.SetMat4("model", model);
			blendMesh.Render();
		}

		blendShader2.UseProgram();

		blendShader2.SetMat4("projection", camera.projection);
		blendShader2.SetMat4("view", camera.view);

		m = calcZ(blendPos2);

		for (map<float, glm::vec3>::reverse_iterator it=m.rbegin(); it!=m.rend(); ++it)
		{
			glm::mat4 model(1.0f);
			model = glm::translate(model, it->second);
			model = glm::scale(model, glm::vec3(5.0f, 5.0f, 0.1f));

			blendShader2.SetMat4("model", model);
			blendMesh.Render();
		}
		
		// ###################################################################
		// Render skybox 
		mesh.BindVertexArray();

		kernelShader.UseProgram();
		kernelShader.SetMat4("projection", camera.projection);
		kernelShader.SetMat4("view", camera.view);

		glm::mat4 model(1.0f);
		model = glm::translate(model, glm::vec3(0.0f));
		model = glm::scale(model, glm::vec3(10.0f, 10.0f, 0.1f));

		kernelShader.SetMat4("model", model);

		mesh.Render(); 

		lightShader.UseProgram();

		lightShader.SetMat4("projection", camera.projection);
		lightShader.SetMat4("view", camera.view);

		for (int i = 0; i < 6; i++) 
		{
			glm::mat4 model(1.0f);
			model = glm::translate(model, skyboxPos[i]);
			model = glm::scale(model, skyboxScale[i]);

			lightShader.SetMat4("model", model);
			mesh.Render(); 
		}

		// ###################################################################
		// Render objects
		shader.UseProgram();

		shader.SetMat4("projection", camera.projection);
		shader.SetMat4("view", camera.view);

		shader.SetVec3("camPos", camera.cameraPos);
		shader.SetVec3("light.pos", light.m_lightPos);
		shader.SetVec3("light.ambient", light.m_ambientStrength);
		shader.SetVec3("light.diffuse", light.m_diffuseStrength);
		shader.SetVec3("light.specular", light.m_specularStrength);

		shader.SetInt("material.shininess", 32);

		for (int i = 0; i < nObject; i++) 
		{
			glm::mat4 model(1.0f);
			model = glm::translate(model, objectCoords[i]);
			model = glm::rotate(model, glm::radians((float)(i*glfwGetTime())+angles[i].x), glm::vec3(1.0f, 0.0f, 0.0f));
			model = glm::rotate(model, glm::radians((float)(i*glfwGetTime())+angles[i].y), glm::vec3(0.0f, 1.0f, 0.0f));
			model = glm::rotate(model, glm::radians((float)(i*glfwGetTime())+angles[i].z), glm::vec3(0.0f, 0.0f, 1.0f));
			//model = glm::scale(model, glm::vec3(4.0f));

			shader.SetMat4("model", model);

			mesh.Render(); 
		}
		// ###################################################################

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}




