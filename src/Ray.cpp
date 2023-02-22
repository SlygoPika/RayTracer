#include "Ray.h"

Ray::Ray(Eigen::Vector3f& origin, Eigen::Vector3f& direction) :origin(origin), direction(direction) {}

void Ray::prettyPrint()
{
	std::cout << "Ray:" << std::endl;
	std::cout << "Direction (x,y,z): " << direction[0] << ", " << direction[1] << ", " << direction[2] << "\n" << std::endl;
}

void Ray::prettyPrint(int x, int y)
{
	std::cout << "Ray [" << x << ", " << y << "]:" << std::endl;
	std::cout << "Direction (x,y,z): " << direction[0] << ", " << direction[1] << ", " << direction[2] << "\n" << std::endl;
}