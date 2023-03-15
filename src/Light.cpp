#include "Light.h"

Light::Light(Eigen::Vector3f& diffuseIntensity, Eigen::Vector3f& specularIntensity)
	:diffuseIntensity(diffuseIntensity), specularIntensity(specularIntensity) {}

void Light::prettyPrint() const {
	std::cout << "Virtual function has failed" << std::endl;
}

const Eigen::Vector3f& Light::getDiffuseIntensity() const
{
	return diffuseIntensity;
}

const Eigen::Vector3f& Light::getSpecularIntensity() const
{
	return specularIntensity;
}

const Eigen::Vector3f& Light::getOrigin() const
{
	std::cout << "Virtual function has failed" << std::endl;
	return Eigen::Vector3f(0,0,0);
}

float Light::computeDiffuseIntensity(const Eigen::Vector3f& point, const Eigen::Vector3f& normal) const {
	std::cout << "Virtual function has failed" << std::endl;
	return -1.0f;
}

float Light::computeSpecularIntensity(const Eigen::Vector3f& point, const Eigen::Vector3f& normal) const {
	std::cout << "Virtual function has failed" << std::endl;
	return -1.0f;
}