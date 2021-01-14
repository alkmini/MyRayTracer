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
// 	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
// 	const GLFWvidmode* mode = glfwGetVideoMode(monitor);
//    	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//    	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//   	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
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

	
	//glEnableVertexAttribArray(0);
	//glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, 0);
	//glEnableVertexAttribArray(1);
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (char*)(sizeof(float) * 2));

	//GLushort indices[] = { 0,1,2};
	//GLuint indexBufferID;
	//glGenBuffers(1, &indexBufferID); //bind buffer point
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices),
	//	indices, GL_STATIC_DRAW);

	//std::string vertexShader =
	//	"#version 330 core\n"
	//	"\n"
	//	"layout(location = 0) in vec2 position;\n"
	//	"layout(location = 1) in vec3 vertexcolor;\n"
	//	"\n"
	//	"out vec3 mycolor;\n"
	//	"\n"
	//	"void main()\n"
	//	"{\n"
	//	"gl_Position = vec4(position, 0.0, 1.0);\n"
	//	"mycolor = vertexcolor;"
	//	"}\n";

	//std::string fragmentShader =
	//	"#version 330 core\n"
	//	"\n"
	//	"out vec4 color;\n"
	//	"in vec3 mycolor;\n"
	//	"\n"
	//	"void main()\n"
	//	"{\n"
	//	"color = vec4(mycolor, 1.0);\n"
	//	"}\n";

	//unsigned int shader = Shader::CreateShader(vertexShader, fragmentShader);
	//glUseProgram(shader);

 	return 1;
 }

void Application::Init()
{
	initSDL("My BP", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, false, true);
	initGl();
	
}

void Application::initSDL(const char* title, int xpos, int ypos, int width, int height, bool fullscreen, bool useOpenGL)
{
 	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
 	{
 		int flags = 0;
 		if (fullscreen)
 			flags |= SDL_WINDOW_FULLSCREEN;
 		/*if (useOpenGL)
 			flags |= SDL_WINDOW_OPENGL;*/
 
 		std::cout << "Subsystems Initialized!..." << std::endl;
 
 		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
 		if (window)
 		{
 			std::cout << "Window created!" << std::endl;
 		}
 
 		renderer = SDL_CreateRenderer(window, -1, 0);
 		if (renderer)
 		{
 			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
 			std::cout << "Renderer created" << std::endl;
 		}
 		isRunning = true;
 	}
 	else
 	{
 		isRunning = false;
 	}
}

void Application::handleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;
	//case SDL_KEYDOWN:

	}
}

void Application::update()
{
	
}

void Application::render()
{
	//SDL_RenderClear(renderer);
	////this is where stuff renders
	//SDL_RenderPresent(renderer);

//	glClearColor(1, 0, 0, 1);
// 	glClear(GL_COLOR_BUFFER_BIT);
// 	glBegin(GL_TRIANGLES);
// 	  	glVertex2f(0.5f, -0.5f);
// 	  	glVertex2f (0.0f, 0.5f);
// 	  	glVertex2f(0.5f, -0.5f);
// 	  	glEnd();
 	//glDrawArrays(GL_TRIANGLES, 0, 3);
	//glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, NULL);
	raytracer->Run();

	//std::cout << raytracer->vertices.size() << std::endl;
	//glDrawArrays(GL_POINTS, 0, 800 * 600);
	//glBegin(GL_TRIANGLES);
}

void Application::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << " GameCleaned" << std::endl;
}

void Application::Run()
{
	//raytracer->Run();
 	while (!glfwWindowShouldClose(Gwindow))
 	{
 		/* Render here */
 		glClear(GL_COLOR_BUFFER_BIT);
		glClear(GL_DEPTH_BUFFER_BIT);
 
 		render();
 		/* Swap front and back buffers */
 		glfwSwapBuffers(Gwindow);
 		/* Poll for and process events */
 		glfwPollEvents();
 	}

	while (Running())
	{
		handleEvents();
		update();
		render();
	}
	//raytracer->Run();
	
}

void Application::Terminate()
{
	clean();
	glfwDestroyWindow(Gwindow);
	glfwTerminate();
}

