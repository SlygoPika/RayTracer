#ifndef GEOMETRY_CLASS_H
#define GEOMETRY_CLASS_H

#include <iostream>
#include <string>
#include <Eigen/Core>
#include <Eigen/Dense>

#include "../external/json.hpp"
#include "../external/simpleppm.h"
#include "Ray.h"

class Geometry
{
protected:
	Geometry();
	Geometry(Eigen::Vector3f& ambiantColor, Eigen::Vector3f& diffuseColor, 
		Eigen::Vector3f& specularColor, Eigen::Vector3f& reflectionCoefficients, float pc);


public:
	Eigen::Vector3f ambiantColor;
	Eigen::Vector3f diffuseColor;
	Eigen::Vector3f specularColor;

	Eigen::Vector3f reflectionCoefficients;

	float pc;

	virtual void prettyPrint();
	virtual bool intersects(Ray& ray);
};

#endif