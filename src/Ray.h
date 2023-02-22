#ifndef RAY_CLASS_H
#define RAY_CLASS_H

#include <Eigen/Core>
#include <Eigen/Dense>

#include <iostream>

class Ray
{
public:
	Eigen::Vector3f origin;
	Eigen::Vector3f direction;

	Ray(Eigen::Vector3f& origin, Eigen::Vector3f& direction);
	void prettyPrint();
	void prettyPrint(int x, int y);
};

#endif