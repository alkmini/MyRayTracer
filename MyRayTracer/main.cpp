//#include <limits>
//#include <cmath>
//#include <iostream>
//#include <fstream>
//#include <algorithm>
//#include <vector>
//#include <math.h>
//#include "vec3geometry.h"
//#include "Ray.h"
//#include "color.h"
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include <iostream>
#include "Application.h"
#include "Camera.h"
#undef main


 camera cam;
 
//  void init()
//  {
//  	glClearColor(0, 0, 0, 1);
//  	glMatrixMode(GL_PROJECTION);
//  	glLoadIdentity();
//  	//gluPerspective(50, 640.0 / 480.0, 1, 1000);
//  	glMatrixMode(GL_MODELVIEW);
//  	glEnable(GL_DEPTH_TEST);
//  }
//  
//  void display()
//  {
//  	glLoadIdentity();
//  	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
//  	cam.Control();
//  	cam.UpdateCamera();
//  
//  	glBegin(GL_TRIANGLES);
//  	glVertex3f(0, 1, -4);
//  	glVertex3f(-1, -1, -4);
//  	glVertex3f(1, -1, -4);
//  	glEnd();
//  }


int main(int argc, const char* argv[])
{
	//GLFWwindow* window;

	///* Initialize the library */
	//if (!glfwInit())
	//	return -1;

	///* Create a windowed mode window and its OpenGL context */
	//window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	//if (!window)
	//{
	//	glfwTerminate();
	//	return -1;
	//}

	///* Make the window's context current */
	//glfwMakeContextCurrent(window);

	///* Loop until the user closes the window */
	//while (!glfwWindowShouldClose(window))
	//{
	//	/* Render here */
	//	glClear(GL_COLOR_BUFFER_BIT);

	//	// testing OpenGL
	//	glBegin(GL_TRIANGLES);
	//	glVertex2f(-0.5f, -0.5f);
	//	glVertex2f(0.5f, 0.5f);
	//	glVertex2f(0.5f, -0.5f);
	//	glEnd();

	//	/* Swap front and back buffers */
	//	glfwSwapBuffers(window);

	//	/* Poll for and process events */
	//	glfwPollEvents();
	//}

 //	glfwTerminate();

 	Application* app = new Application();
 	app->Init();
 	app->Run();
 	app->clean();
  	
     //app->Terminate();
 	std::cout << "done" << std::endl;
 	delete app;
	while(true) {}
	return 0;
}