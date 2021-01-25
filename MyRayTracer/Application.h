#pragma once

#define GLEW_STATIC
#include <GL/glew.h> //always glew before glfw
#include <GLFW/glfw3.h>
#include <iostream>
#include "Shader.h"

class camera;
class Raytracer;

class Application
{
public:

	Application();
	~Application();
	
	
	void Init();
	void ProcessInput(GLFWwindow* window);
	void Update();
	void Render();

	bool Running(){return isRunning;}

	void Run();
	void Terminate();


	GLFWwindow* Gwindow;

private:
	bool isRunning;
	GLuint initGl();
	GLFWwindow* window;
	camera* cam;
	Raytracer* raytracer;
};