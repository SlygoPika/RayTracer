#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H

#include <iostream>
#include <math.h>
#include <Eigen/Core>
#include <Eigen/Dense>

#include <vector>

#include "../external/json.hpp"
#include "../external/simpleppm.h"

#include "Ray.h"
#include "Geometries.h"
#include "Lights.h"

struct Viewport
{
	int x;
	int y;
	
	std::vector<std::vector<Ray>> pixelRays;
};

class Camera
{
private:
	const float NEAR_PLANE = 0.1f;
	const float FAR_PLANE = 2000.0f;

	static Camera* instancePtr;

	Viewport viewport;

	// Coordinate vectors
	Eigen::Vector3f lookat;
	Eigen::Vector3f up;
	Eigen::Vector3f side;

	Eigen::Vector3f backgroundColor;
	Eigen::Vector3f position;
	float fov;

	// Math constants
	float tanVal;
	float deltaPixel;
	float halfDeltaPixel;

	float nearPlaneXEdge;
	float nearPlaneYEdge;

	void parseCamera(const nlohmann::json& file);
	void setupRays();
	void appendRay(const int& x, const int& y, std::vector<Ray>& row) const;
	void clampColor(Eigen::Vector3f& color) const;

public:

	Camera(const nlohmann::json& file);

	Camera(const Camera& obj) = delete;

	Eigen::Vector3f emitRay(const int& pixelX, const int& pixelY) const;

	const Viewport& getViewport() const;
	const Eigen::Vector3f& getPosition() const;

	static Camera* getInstance();

	void prettyPrint() const;
};

#endif