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

	Ray(const Eigen::Vector3f& origin, const Eigen::Vector3f& direction);
	void prettyPrint() const;
	void prettyPrint(const int& x, const int& y) const;
};

#endif