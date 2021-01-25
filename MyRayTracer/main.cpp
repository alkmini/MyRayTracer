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


int main(int argc, const char* argv[])
{
 	Application* app = new Application();
 	app->Init();
 	app->Run();
  	
 	std::cout << "done" << std::endl;
 	delete app;
	while(true) {}
	return 0;
}