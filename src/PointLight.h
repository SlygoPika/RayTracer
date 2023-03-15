#ifndef POINTLIGHT_CLASS_H
#define POINTLIGHT_CLASS_H

#include <Eigen/Core>
#include <Eigen/Dense>

#include "Light.h"
#include "Camera.h"

class PointLight : public Light
{
private:
	Eigen::Vector3f centre;

	Eigen::Vector3f computeRelectedVector(const Eigen::Vector3f& lightVector, const Eigen::Vector3f& normal) const;

public:
	
	PointLight(Eigen::Vector3f& centre, Eigen::Vector3f& diffuseIntensity, Eigen::Vector3f& specularIntensity);

	void prettyPrint() const override;

	const Eigen::Vector3f& getOrigin() const override;

	float computeDiffuseIntensity(const Eigen::Vector3f& point, const Eigen::Vector3f& normal) const override;

	float computeSpecularIntensity(const Eigen::Vector3f& point, const Eigen::Vector3f& normal) const override;
};

#endif