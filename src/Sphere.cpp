#include "Sphere.h"

Sphere::Sphere(const Eigen::Vector3f& centre, const float radius, const Eigen::Vector3f& ambiantColor, const Eigen::Vector3f& diffuseColor,
	const Eigen::Vector3f& specularColor, const float& ka, const float& kd, const float& ks, const float& pc)
	: centre(centre), radius(radius), Geometry(ambiantColor, diffuseColor, specularColor, ka, kd, ks, pc) {}

bool Sphere::intersects(const Ray& ray, float& z) const
{
	Eigen::Vector3f f = ray.origin - centre;
	int aa = 1;
	float bb = 2 * f.dot(ray.direction);
	float cc = f.dot(f) - (radius * radius);

	float discriminant = (bb * bb) - (4 * aa * cc);

	if (discriminant <= 0)
	{
		return false;
	}

	float t = (-bb - sqrtf(discriminant)) / (2 * aa);
	
	if (t < 0)
	{
		return false;
	}

	z = t;
	return true;
}

Eigen::Vector3f Sphere::computeLighting(const Eigen::Vector3f& point) const
{
	Eigen::Vector3f normal = getNormal(point);

	std::vector<Light*>& lights = Lights::getInstance()->lights;
	std::vector<Geometry*>& geometries = Geometries::getInstance()->geometries;

	Eigen::Vector3f diffuseIntensity(0,0,0);
	Eigen::Vector3f specularIntensity(0,0,0);

	for (auto lightsItr = lights.begin(); lightsItr != lights.end(); lightsItr++)
	{
		Eigen::Vector3f direction = (*lightsItr)->getOrigin() - point;
		float len = direction.norm();
		direction.normalize();

		Ray intersectLightRay(point, direction);		

		if (!intersectsInRangeExcludeSelf(intersectLightRay, len))
		{
			diffuseIntensity += (*lightsItr)->computeDiffuseIntensity(point, normal) * (*lightsItr)->getDiffuseIntensity();
			specularIntensity += powf((*lightsItr)->computeSpecularIntensity(point, normal), pc) * (*lightsItr)->getSpecularIntensity();
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

bool Sphere::intersectsInRangeExcludeSelf(const Ray& ray, const float& range) const
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

Eigen::Vector3f Sphere::getNormal(const Eigen::Vector3f& point) const
{
	Eigen::Vector3f norm = point - centre;
	norm.normalize();
	return norm;
}

void Sphere::prettyPrint() const
{
	std::cout << "Sphere: " << std::endl;
	std::cout << "Center (x,y,z): " << centre[0] << ", " << centre[1] << ", " << centre[2] << std::endl;
	std::cout << "Radius: " << radius << "\n" << std::endl;
}