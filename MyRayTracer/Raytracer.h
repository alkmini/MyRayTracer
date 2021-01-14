#pragma once
#include "vec3geometry.h"
#include <GL/glew.h> //always glew before glfw
#include <GLFW/glfw3.h>
#include <vector>

#include "Hittable_List.h"
#include "Camera.h"

class ray;

struct Vertex
{
	GLfloat x, y, red, green, blue;
};

class Raytracer
{
	
public:
	Raytracer();
	~Raytracer();

	void Run();
	color ray_color(const ray& r, const Hittable& world, int depth);
	double hit_sphere(const point3& center, double radius, const ray& r);

	hittable_list random_scene();
	
	std::vector<Vertex> vertices;

};

