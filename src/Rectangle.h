#ifndef RECTANGLE_CLASS_H
#define RECTANGLE_CLASS_H

#include <Eigen/Core>
#include <Eigen/Dense>

#include "Geometry.h"

class Rectangle : public Geometry
{
public:
	Eigen::Vector3f p1;
	Eigen::Vector3f p2;
	Eigen::Vector3f p3;
	Eigen::Vector3f p4;

	Rectangle(Eigen::Vector3f& p1, Eigen::Vector3f& p2, Eigen::Vector3f& p3, Eigen::Vector3f& p4);

	Rectangle(Eigen::Vector3f& p1, Eigen::Vector3f& p2, Eigen::Vector3f& p3, Eigen::Vector3f& p4, 
		Eigen::Vector3f& ambiantColor, Eigen::Vector3f& diffuseColor,
		Eigen::Vector3f& specularColor, Eigen::Vector3f& reflectionCoefficients, float pc);

	void prettyPrint() override;
	bool intersects(Ray& ray) override;
};

#endif