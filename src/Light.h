#ifndef LIGHT_CLASS_H
#define LIGHT_CLASS_H

#include <iostream>
#include <string>
#include <vector>
#include <Eigen/Core>
#include <Eigen/Dense>

#include "../external/json.hpp"
#include "../external/simpleppm.h"


class Light
{
protected:
	Eigen::Vector3f diffuseIntensity;
	Eigen::Vector3f specularIntensity;

	Light(Eigen::Vector3f& diffuseIntensity, Eigen::Vector3f& specularIntensity);

public:
	virtual void prettyPrint() const;

	const Eigen::Vector3f& getDiffuseIntensity() const;
	const Eigen::Vector3f& getSpecularIntensity() const;

	virtual const Eigen::Vector3f& getOrigin() const;

	virtual float computeDiffuseIntensity(const Eigen::Vector3f& point, const Eigen::Vector3f& normal) const;

	virtual float computeSpecularIntensity(const Eigen::Vector3f& point, const Eigen::Vector3f& normal) const;
};

#endif