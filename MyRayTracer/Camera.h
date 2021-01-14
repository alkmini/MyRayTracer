#pragma once

#ifndef CAMERA_H
#define CAMERA_H
#include <cmath>
#include <iostream>
#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#endif
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL.h>
#undef main
#include <string>
#include <fstream>
#include "utilities.h"
#include "glm.hpp"
#include "Ray.h"
#include "vec3geometry.h"


class camera
{
public:
	camera() {};
	camera(
		point3 lookfrom,
		point3 lookat,
		vec3   vup,
		double vfov, // vertical field-of-view in degrees
		double aspect_ratio,
		double aperture,
		double focus_dist
	)
	{
		auto theta = degrees_to_radians(vfov);
		auto h = tan(theta / 2);
		auto viewport_height = 2.0 * h;
		auto viewport_width = aspect_ratio * viewport_height;

		w = unit_vector(lookfrom - lookat);
		u = unit_vector(cross(vup, w));
		v = cross(w, u);

		origin = lookfrom;
		horizontal = focus_dist * viewport_width * u;
		vertical = focus_dist * viewport_height * v;
		lower_left_corner = origin - horizontal / 2 - vertical / 2 - focus_dist * w;

		lens_radius = aperture / 2;
	}

	ray get_ray(double s, double t) const
	{
		vec3 rd = lens_radius * random_in_unit_disk();
		vec3 offset = u * rd.x() + v * rd.y();

		return ray(
			origin + offset,
			lower_left_corner + s * horizontal + t * vertical - origin - offset);
	}

private:
	point3 origin;
	point3 lower_left_corner;
	vec3 horizontal;
	vec3 vertical;
	vec3 u, v, w;
	double lens_radius;
};

//data->geometry->vertex->rasterization->fragment
// 
// class camera
// {
// 	glm::vec3 loc;
// 	float camPitch, camYaw;
// 	float movevel;
// 	float mousevel;
// 	bool mi, ismoved;
// 	void lockCamera();
// 	void moveCamera(float dir);
// 	void moveCameraUp(float dir);
// public:
// 	camera();
// 	camera(glm::vec3 loc);
// 	camera(glm::vec3 loc, float yaw, float pitch);
// 	camera(glm::vec3 loc, float yaw, float pitch, float mv, float mov);
// 	void Control();
// 	void UpdateCamera();
// 	glm::vec3 getVector();
// 	glm::vec3 getLocation();
// 	float getPitch();
// 	float getYaw();
// 	float getMovevel();
// 	float getMousevel();
// 	bool isMouseIn();
// 
// 	void setLocation(glm::vec3 vec);
// 	void lookAt(float pitch, float yaw);
// 	void mouseIn(bool b);
// 	void setSpeed(float mv, float mov);
// 
// 	bool isMoved();
// };
// 
#endif