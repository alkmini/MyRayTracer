#include "Raytracer.h"
#include <iostream>
#include "utilities.h"
#include "Sphere.h"
#include "Ray.h"
#include <fstream>
#include <memory>
#include "Material.h"


Raytracer::Raytracer()
{

}

Raytracer::~Raytracer()
{

}

void Raytracer::Run()
{
	vertices.clear();
	//Image
	const auto aspect_ratio = 3.0 / 2.0;
	const int image_width = 1280;
	const int image_height = static_cast<int>(image_width / aspect_ratio);
	int samples_per_pixel = 1;
	const int max_depth = 50;

	// World
	auto world = random_scene();

	//Camera
	point3 lookfrom(13, 2, 3);
	point3 lookat(0, 0, 0);
	vec3 vup(0, 1, 0);
	auto dist_to_focus = 10.0;
	auto aperture = 0.1;

	camera cam(lookfrom, lookat, vup, 20, aspect_ratio, aperture, dist_to_focus);
	//Render
	glBegin(GL_POINTS);
	for (int j = image_height - 1; j >= 0; --j)
	{
		std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
		for (int i = 0; i < image_width; ++i)
		{
			color pixel_color(0, 0, 0);
			for (int s = 0; s < samples_per_pixel; ++s)
			{
				const auto u = (i + random_double()) / (image_width - 1.0);
				const auto v = (j + random_double()) / (image_height - 1.0);
				const ray r = cam.get_ray(u, v);
				pixel_color += ray_color(r, world, max_depth);

			}

			auto red = pixel_color.x();
			auto green = pixel_color.y();
			auto blue = pixel_color.z();

			//divide the color by the number of samples.
			const auto scale = 1.0 / samples_per_pixel;
			red = sqrt(scale * red);
			green = sqrt(scale * green);
			blue = sqrt(scale * blue);

			//Clamp the RGB values for convenience. 
			// 			red = clamp(red, 0.0, 0.999);
			// 			green = clamp(green, 0.0, 0.999);
			// 			blue = clamp(blue, 0.0, 0.999);

			Vertex vert;
			vert.x = i;
			vert.y = j;
			vert.red = red;
			vert.green = green;
			vert.blue = blue;


			glColor3f(vert.red, vert.green, vert.blue);
			glVertex2i(vert.x, vert.y);
			

		}
	}
	glEnd();
	std::cerr << "\nDone,\n";
}

color Raytracer::ray_color(const ray& r, const Hittable& world, int depth)
{
	hit_record rec;

	if (depth <= 0)
	{
		return color(0, 0, 0);
	}

	if (world.hit(r, 0.001, infinity, rec))
	{
		ray scattered;
		color attenuation;
		if (rec.mat_ptr->scatter(r, rec, attenuation, scattered))
			return attenuation * ray_color(scattered, world, depth - 1);
		return color(0, 0, 0);
	}
	vec3 unit_direction = unit_vector(r.direction());
	auto t = 0.5 * (unit_direction.y() + 1.0);
	return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}

double Raytracer::hit_sphere(const point3& center, double radius, const ray& r)
{
	vec3 oc = r.origin() - center;
	auto a = r.direction().length_squared();
	auto half_b = dot(oc, r.direction());
	auto c = oc.length_squared() - radius * radius;
	auto discriminant = half_b * half_b - a * c;
	if (discriminant < 0)
	{
		return -1.0;
	}
	else
	{
		return(-half_b - sqrt(discriminant)) / a;
	}
}

hittable_list Raytracer::random_scene()
{
	hittable_list world;

	auto ground_material = make_shared<lambertian>(color(0.5, 0.5, 0.5));
	world.add(make_shared<Sphere>(point3(0, -100, 0), 100, ground_material));

	for (int a = -1; a < 1; a++)
	{
		for (int b = -1; b < 1; b++)
		{
			auto choose_mat = random_double();
			point3 center(a + 0.9 * random_double(), 0.2, b + 0.9 * random_double());

			if ((center - point3(4, 0.2, 0)).length() > 0.9)
			{
				shared_ptr<material> sphere_material;

				if (choose_mat < 0.8)
				{
					// diffuse
					auto albedo = color::random() * color::random();
					sphere_material = make_shared<lambertian>(albedo);
					world.add(make_shared<Sphere>(center, 0.2, sphere_material));
				}
				else if (choose_mat < 0.95)
				{
					// metal
					auto albedo = color::random(0.5, 1);
					auto fuzz = random_double(0, 0.5);
					sphere_material = make_shared<metal>(albedo, fuzz);
					world.add(make_shared<Sphere>(center, 0.2, sphere_material));
				}
				else
				{
					// glass
					sphere_material = make_shared<dielectric>(1.5);
					world.add(make_shared<Sphere>(center, 0.2, sphere_material));
				}
			}
		}
	}

	auto material1 = make_shared<dielectric>(1.5);
	world.add(make_shared<Sphere>(point3(0, 1, 0), 1.0, material1));

	auto material2 = make_shared<lambertian>(color(0.4, 0.2, 0.1));
	world.add(make_shared<Sphere>(point3(-4, 1, 0), 1.0, material2));

	auto material3 = make_shared<metal>(color(0.7, 0.6, 0.5), 0.0);
	world.add(make_shared<Sphere>(point3(4, 1, 0), 1.0, material3));

	return world;
}
