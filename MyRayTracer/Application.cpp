#include "Application.h"
#include "Camera.h"
#include "Raytracer.h"

Application::Application()
{
	raytracer = new Raytracer();
}

Application::~Application()
{
	delete raytracer;
}

 GLuint Application::initGl()
 {
 
  	if (!glfwInit())
  	{
  		std::cout << "init failed" << std::endl;
  		return -1;
  	}

  	Gwindow = glfwCreateWindow(1280, 720, "LearnOpenGL", NULL, NULL); //monitor on NULL
  
  	if (!Gwindow)
  	{
  		glfwTerminate();
  		std::cout << "terminated" << std::endl;
  		return -1;
  	}
  
  	glfwMakeContextCurrent(Gwindow);
 
	if (glewInit())
	{
		return -1;
	}

	//Graphics
	//glEnable(GL_DEPTH_TEST);
	glViewport(0, 0, 1280, 720);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, 1280, 0, 720, -1, 1);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	GLfloat verts[] =
	{
		0.f, 1.f,
		1.f, 0.f, 0.f,
		-1.f, -1.f,
		1.f, 1.f, 0.f,
		1.f, -1.f,
		1.f, 0.f, 1.f,
	};

	GLuint vertexBufferID; //create buffer point
	glGenBuffers(1, &vertexBufferID); //bind buffer point
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts),
		verts, GL_STATIC_DRAW);

 	return 1;
 }

void Application::Init()
{
	initGl();
	
}

void Application::ProcessInput(GLFWwindow* Gwindow)
{
	if (glfwGetKey(Gwindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(Gwindow, true);
	}
}
void Application::Update()
{
	
}

void Application::Render()
{
	raytracer->Run();

}

void Application::Run()
{
	//raytracer->Run();
 	while (!glfwWindowShouldClose(Gwindow))
 	{
		ProcessInput(Gwindow);
 		/* Render here */
 		glClear(GL_COLOR_BUFFER_BIT);
		glClear(GL_DEPTH_BUFFER_BIT);
 		Render();
 		/* Swap front and back buffers */
 		glfwSwapBuffers(Gwindow);
 		/* Poll for and process events */
 		glfwPollEvents();
 	}

	//raytracer->Run();
	
}

void Application::Terminate()
{
	glfwDestroyWindow(Gwindow);
	glfwTerminate();
}

