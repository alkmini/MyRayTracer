#pragma once
#include <GL/glew.h> //always glew before glfw
#include <GLFW/glfw3.h>

#include <iostream>

class Shader
{
public:

	static unsigned int CompileShader(unsigned int type, const std::string& source);
	static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);

	//static const char* src;
};