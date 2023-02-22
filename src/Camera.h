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

struct Viewport
{
	int x;
	int y;
	
	std::vector<std::vector<Ray>> pixelRays;
};

class Camera
{
private:
	float tanVal;
	float deltaXPixel;
	float deltaYPixel;
	float halfDeltaXPixel;
	float halfDeltaYPixel;

	float nearPlaneEdge;
	float nearPlane = 0.1f;
	float farPlane = 100.0f;

	void parseCamera(nlohmann::json& file);
	void setupRays();
	void appendRay(int x, int y, std::vector<Ray>& row);

public:
	Viewport viewport;

	// Coordinate vectors
	Eigen::Vector3f lookat;
	Eigen::Vector3f up;
	Eigen::Vector3f side;

	Eigen::Vector3f backgroundColor;
	Eigen::Vector3f position;
	float fov;

	Camera(nlohmann::json& file);
	Eigen::Vector3f emitRay(int& pixelX, int& pixelY, std::vector<Geometry*>& geometries);
	void prettyPrint();
};

#endif