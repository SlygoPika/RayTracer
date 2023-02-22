#include "Sphere.h"

Sphere::Sphere(Eigen::Vector3f& centre, float radius, Eigen::Vector3f& ambiantColor, Eigen::Vector3f& diffuseColor,
	Eigen::Vector3f& specularColor, Eigen::Vector3f& reflectionCoefficients, float pc)
	: centre(centre), radius(radius), Geometry(ambiantColor, diffuseColor, specularColor, reflectionCoefficients, pc) {}

Sphere::Sphere(Eigen::Vector3f& centre, float radius) : centre(centre), radius(radius) {}


bool Sphere::intersects(Ray& ray)
{
	Eigen::Vector3f f = ray.origin - centre;
	float aa = 1;
	float bb = 2 * f.dot(ray.direction);
	float cc = f.dot(f) - (radius * radius);

	float discriminant = (bb * bb) - (4 * aa * cc);

	if (discriminant < 0)
	{
		return false;
	}

	return true;
}


void Sphere::prettyPrint()
{
	std::cout << "Sphere: " << std::endl;
	std::cout << "Center (x,y,z): " << centre[0] << ", " << centre[1] << ", " << centre[2] << std::endl;
	std::cout << "Radius: " << radius << "\n" << std::endl;
}