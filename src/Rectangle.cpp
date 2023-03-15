#include "Rectangle.h"

Rectangle::Rectangle(const Eigen::Vector3f& p1, const Eigen::Vector3f& p2, const Eigen::Vector3f& p3, const Eigen::Vector3f& p4,
	const Eigen::Vector3f& ambiantColor, const Eigen::Vector3f& diffuseColor,
	const Eigen::Vector3f& specularColor, const float& ka, const float& kd, const float& ks, const float& pc)
	:p1(p1), p2(p2), p3(p3), p4(p4), normal((p2 - p1).cross(p4 - p1)),
	edge1(p2 - p1), edge2(p3 - p2), edge3(p4 - p3), edge4(p1 - p4),
	Geometry(ambiantColor, diffuseColor, specularColor, ka, kd, ks, pc)
{
	normal.normalize();
}

bool Rectangle::intersects(const Ray& ray, float& z) const
{
	float dotProduct = normal.dot(ray.direction);

	if (dotProduct < 0.001f && dotProduct > -0.001f)
	{
		return false;
	}

	float t = normal.dot(p2 - ray.origin) / dotProduct;

	if (t < 0)
	{
		return false;
	}

	Eigen::Vector3f intersectPoint = ray.origin + ray.direction * t;

	if (edge1.dot(intersectPoint - p1) < 0 ||
		edge2.dot(intersectPoint - p2) < 0 ||
		edge3.dot(intersectPoint - p3) < 0 ||
		edge4.dot(intersectPoint - p4) < 0)
	{
		return false;
	}

	z = t;
	return true;
}

Eigen::Vector3f Rectangle::computeLighting(const Eigen::Vector3f& point) const
{
		std::vector<Light*>& lights = Lights::getInstance()->lights;

		Eigen::Vector3f diffuseIntensity(0, 0, 0);
		Eigen::Vector3f specularIntensity(0, 0, 0);

		for (auto lightsItr = lights.begin(); lightsItr != lights.end(); lightsItr++)
		{
			Eigen::Vector3f direction = (*lightsItr)->getOrigin() - point;
			float len = direction.norm();
			direction.normalize();

			Ray intersectLightRay(point, direction);

			if (!intersectsInRangeExcludeSelf(intersectLightRay, len))
			{
				diffuseIntensity += (*lightsItr)->computeDiffuseIntensity(point, normal) * (*lightsItr)->getDiffuseIntensity();
				specularIntensity += pow((*lightsItr)->computeSpecularIntensity(point, normal), pc) * (*lightsItr)->getSpecularIntensity();
			}
		}

		for (int i = 0; i < 3; i++)
		{
			diffuseIntensity[i] *= diffuseColor[i];
			specularIntensity[i] *= specularColor[i];
		}

		return ambiantColorFinal +
			diffuseIntensity * reflectionCoefficients.diffuse +
			specularIntensity * reflectionCoefficients.specular;
}

bool Rectangle::intersectsInRangeExcludeSelf(const Ray& ray, const float& range) const
{
	std::vector<Geometry*>& geometries = Geometries::getInstance()->geometries;

	for (auto geoItr = geometries.begin(); geoItr != geometries.end(); geoItr++)
	{
		if ((*geoItr) != this)
		{
			float z;
			if ((*geoItr)->intersects(ray, z))
			{
				if (z < range)
				{
					return true;
				}
			}
		}
	}

	return false;
}

void Rectangle::prettyPrint() const
{
	std::cout << "Rectangle: " << std::endl;
	std::cout << "Normal (x,y,z): " << normal[0] << ", " << normal[1] << ", " << normal[2] << std::endl;
	std::cout << "P1 (x,y,z): " << p1[0] << ", " << p1[1] << ", " << p1[2] << std::endl;
	std::cout << "P2 (x,y,z): " << p2[0] << ", " << p2[1] << ", " << p2[2] << std::endl;
	std::cout << "P3 (x,y,z): " << p3[0] << ", " << p3[1] << ", " << p3[2] << std::endl;
	std::cout << "P4 (x,y,z): " << p4[0] << ", " << p4[1] << ", " << p4[2] << "\n" << std::endl;
}