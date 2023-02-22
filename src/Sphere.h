#ifndef SPHERE_CLASS_H
#define SPHERE_CLASS_H

#include <Eigen/Core>
#include <Eigen/Dense>

#include "Geometry.h"

class Sphere : public Geometry
{
public:
	Eigen::Vector3f centre;
	float radius;

	Sphere(Eigen::Vector3f& centre, float radius);

	Sphere(Eigen::Vector3f& centre, float radius, Eigen::Vector3f& ambiantColor, Eigen::Vector3f& diffuseColor, 
		Eigen::Vector3f& specularColor, Eigen::Vector3f& reflectionCoefficients, float pc);

	void prettyPrint() override;
	bool intersects(Ray& ray) override;
};

#endif