#pragma once

#define GLEW_STATIC
#include <GL/glew.h> //always glew before glfw
#include <GLFW/glfw3.h>
#include <SDL.h>
#include <iostream>
#include "Shader.h"

class camera;
class Raytracer;

class Application
{
public:

	Application();
	~Application();
	
	GLuint initGl();
	void Init();
	void initSDL(const char* title, int xpos, int ypos, int width, int height, bool fullscreen, bool useOpenGL);

	void handleEvents();
	void update();
	void render();
	void clean();

	bool Running(){return isRunning;}

	void Run();
	void Terminate();


	GLFWwindow* Gwindow;

private:
	bool isRunning;
	SDL_Window* window;
	SDL_Renderer* renderer;
	camera* cam;
	Raytracer* raytracer;
};