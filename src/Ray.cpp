#include "Ray.h"

Ray::Ray(const Eigen::Vector3f& origin, const Eigen::Vector3f& direction) 
	:origin(origin), direction(direction) {}

void Ray::prettyPrint() const
{
	std::cout << "Ray:" << std::endl;
	std::cout << "Direction (x,y,z): " << direction[0] << ", " << direction[1] << ", " << direction[2] << "\n" << std::endl;
}

void Ray::prettyPrint(const int& x, const int& y) const
{
	std::cout << "Ray [" << x << ", " << y << "]:" << std::endl;
	std::cout << "Direction (x,y,z): " << direction[0] << ", " << direction[1] << ", " << direction[2] << "\n" << std::endl;
}