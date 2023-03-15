#include "Geometry.h"

Geometry::Geometry() {}

Geometry::Geometry(const Eigen::Vector3f& ambiantColor, const Eigen::Vector3f& diffuseColor,
	const Eigen::Vector3f& specularColor, const float& ka, const float& kd, const float& ks, const float& pc)
	:ambiantColor(ambiantColor), diffuseColor(diffuseColor), specularColor(specularColor), 
	ambiantColorFinal(ambiantColor * ka), reflectionCoefficients{ka, kd, ks}, pc(pc) 
{}

void Geometry::prettyPrint() const {
	std::cout << "Virtual function has failed" << std::endl;
}

bool Geometry::intersects(const Ray& ray, float& z) const
{
	std::cout << "Virtual function has failed" << std::endl;
	return false;
}

Eigen::Vector3f Geometry::computeLighting(const Eigen::Vector3f& point) const
{
	std::cout << "Virtual function has failed" << std::endl;
	return Eigen::Vector3f(0,0,0);
}