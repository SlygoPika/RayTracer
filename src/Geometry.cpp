#include "Geometry.h"

Geometry::Geometry() {}

Geometry::Geometry(Eigen::Vector3f& ambiantColor, Eigen::Vector3f& diffuseColor, 
	Eigen::Vector3f& specularColor, Eigen::Vector3f& reflectionCoefficients, float pc)
	:ambiantColor(ambiantColor), diffuseColor(diffuseColor), specularColor(specularColor), reflectionCoefficients(reflectionCoefficients), pc(pc) {}

void Geometry::prettyPrint() {
	std::cout << "Virtual function has failed" << std::endl;
}

bool Geometry::intersects(Ray& ray)
{
	std::cout << "Virtual function has failed" << std::endl;
	return false;
}