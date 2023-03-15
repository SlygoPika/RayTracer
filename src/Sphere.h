#ifndef SPHERE_CLASS_H
#define SPHERE_CLASS_H

#include <Eigen/Core>
#include <Eigen/Dense>

#include "Geometries.h"
#include "Geometry.h"
#include "Lights.h"
#include "Ray.h"

class Sphere : public Geometry
{
private:
	Eigen::Vector3f centre;
	float radius;

	Eigen::Vector3f getNormal(const Eigen::Vector3f& point) const;

	bool intersectsInRangeExcludeSelf(const Ray& ray, const float& range) const;

public:
	Sphere(const Eigen::Vector3f& centre, const float radius, const Eigen::Vector3f& ambiantColor, const Eigen::Vector3f& diffuseColor,
		const Eigen::Vector3f& specularColor, const float& ka, const float& kd, const float& ks, const float& pc);

	void prettyPrint() const override;
	bool intersects(const Ray& ray, float& z) const override;

	Eigen::Vector3f computeLighting(const Eigen::Vector3f& point) const override;
};

#endif