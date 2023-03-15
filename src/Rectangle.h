#ifndef RECTANGLE_CLASS_H
#define RECTANGLE_CLASS_H

#include <Eigen/Core>
#include <Eigen/Dense>

#include "Geometry.h"
#include "Lights.h"

class Rectangle : public Geometry
{
private:
	Eigen::Vector3f p1;
	Eigen::Vector3f p2;
	Eigen::Vector3f p3;
	Eigen::Vector3f p4;

	Eigen::Vector3f edge1;
	Eigen::Vector3f edge2;
	Eigen::Vector3f edge3;
	Eigen::Vector3f edge4;

	Eigen::Vector3f normal;

	bool intersectsInRangeExcludeSelf(const Ray& ray, const float& range) const;

public:
	Rectangle(const Eigen::Vector3f& p1, const Eigen::Vector3f& p2, const Eigen::Vector3f& p3, const Eigen::Vector3f& p4,
		const Eigen::Vector3f& ambiantColor, const Eigen::Vector3f& diffuseColor,
		const Eigen::Vector3f& specularColor, const float& ka, const float& kd, const float& ks, const float& pc);

	void prettyPrint() const override;

	bool intersects(const Ray& ray, float& z) const override;

	Eigen::Vector3f computeLighting(const Eigen::Vector3f& point) const override;
};

#endif