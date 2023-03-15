#include "PointLight.h"

PointLight::PointLight(Eigen::Vector3f& centre, Eigen::Vector3f& diffuseIntensity, Eigen::Vector3f& specularIntensity)
	:centre(centre), Light(diffuseIntensity, specularIntensity) {}

float PointLight::computeDiffuseIntensity(const Eigen::Vector3f& point, const Eigen::Vector3f& normal) const
{
	Eigen::Vector3f lightVector = centre - point;
	lightVector.normalize();

	float dotProduct = lightVector.dot(normal);

	return dotProduct > 0 ? dotProduct : 0;
}

const Eigen::Vector3f& PointLight::getOrigin() const
{
	return centre;
}

float PointLight::computeSpecularIntensity(const Eigen::Vector3f& point, const Eigen::Vector3f& normal) const
{
	Eigen::Vector3f lightVector = centre - point;
	lightVector.normalize();

	Eigen::Vector3f viewVector = Camera::getInstance()->getPosition() - point;
	viewVector.normalize();

	Eigen::Vector3f H = lightVector + viewVector;
	H.normalize();

	float phong = normal.dot(H);

	return phong > 0 ? phong : 0;
}

Eigen::Vector3f PointLight::computeRelectedVector(const Eigen::Vector3f& lightVector, const Eigen::Vector3f& normal) const
{
	return 2 * lightVector.dot(normal) * normal - lightVector;
}

void PointLight::prettyPrint() const
{
	std::cout << "Point Light: " << std::endl;
	std::cout << "Center (x,y,z): " << centre[0] << ", " << centre[1] << ", " << centre[2] << std::endl;
	std::cout << "Diffuse Intensity (x,y,z): " << diffuseIntensity[0] << ", " << diffuseIntensity[1] << ", " << diffuseIntensity[2] << std::endl;
	std::cout << "Specular Intensity (x,y,z): " << specularIntensity[0] << ", " << specularIntensity[1] << ", " << specularIntensity[2] << "\n" << std::endl;
}