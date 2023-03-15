#ifndef GEOMETRY_CLASS_H
#define GEOMETRY_CLASS_H

#include <iostream>
#include <string>
#include <Eigen/Core>
#include <Eigen/Dense>

#include "../external/json.hpp"
#include "../external/simpleppm.h"
#include "Ray.h"

struct LightCoefficients
{
	float ambiant;
	float diffuse;
	float specular;
};

class Geometry
{
protected:
	Eigen::Vector3f ambiantColor;
	Eigen::Vector3f diffuseColor;
	Eigen::Vector3f specularColor;

	Eigen::Vector3f ambiantColorFinal;

	LightCoefficients reflectionCoefficients;

	float pc;

	Geometry();
	Geometry(const Eigen::Vector3f& ambiantColor, const Eigen::Vector3f& diffuseColor,
		const Eigen::Vector3f& specularColor, const float& ka, const float& kd, const float& ks, const float& pc);

public:

	virtual void prettyPrint() const;

	virtual bool intersects(const Ray& ray, float& z) const;

	virtual Eigen::Vector3f computeLighting(const Eigen::Vector3f& point) const;
};

#endif