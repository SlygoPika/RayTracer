#include "Rectangle.h"

Rectangle::Rectangle(Eigen::Vector3f & p1, Eigen::Vector3f & p2, Eigen::Vector3f & p3, Eigen::Vector3f & p4)
:p1(p1), p2(p2), p3(p3), p4(p4) {}

Rectangle::Rectangle(Eigen::Vector3f& p1, Eigen::Vector3f& p2, Eigen::Vector3f& p3, Eigen::Vector3f& p4, 
	Eigen::Vector3f& ambiantColor, Eigen::Vector3f& diffuseColor,
	Eigen::Vector3f& specularColor, Eigen::Vector3f& reflectionCoefficients, float pc)
	:p1(p1), p2(p2), p3(p3), p4(p4), Geometry(ambiantColor, diffuseColor, specularColor, reflectionCoefficients, pc) {}

bool Rectangle::intersects(Ray& ray)
{
	return false;
}

void Rectangle::prettyPrint()
{
	std::cout << "Rectangle: " << std::endl;
	std::cout << "P1 (x,y,z): " << p1[0] << ", " << p1[1] << ", " << p1[2] << std::endl;
	std::cout << "P2 (x,y,z): " << p2[0] << ", " << p2[1] << ", " << p2[2] << std::endl;
	std::cout << "P3 (x,y,z): " << p3[0] << ", " << p3[1] << ", " << p3[2] << std::endl;
	std::cout << "P4 (x,y,z): " << p4[0] << ", " << p4[1] << ", " << p4[2] << "\n" << std::endl;
}